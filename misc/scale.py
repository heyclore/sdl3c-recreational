import matplotlib.pyplot as plt
import numpy as np
import requests
from io import BytesIO
from PIL import Image

def upscale_nearest_neighbor_3x(image):
    upscaled = []

    for row in image:
        new_row = []
        for pixel in row:
            # Duplicate each pixel horizontally
            #new_row.append(pixel)
            #new_row.append(pixel)
            new_row.append(int(pixel))
            new_row.append(int(pixel))
        # Duplicate each row vertically
        upscaled.append(new_row)
        upscaled.append(new_row[:])

    return upscaled

def upscale_nearest_neighbor_2x(image):
    upscaled = []

    for row in image:
        new_row = []
        for pixel in row:
            # Assuming pixel is a list of [R, G, B], for example
            new_pixel = [int(channel) for channel in pixel]  # Convert each channel to an integer

            # Duplicate each pixel horizontally
            new_row.append(new_pixel)
            new_row.append(new_pixel)
        # Duplicate each row vertically
        upscaled.append(new_row)
        upscaled.append(new_row[:])

    return upscaled

def downscale_nearest_neighbor_2x(image):
    new_image = image.copy()

    # Ensure image dimensions are even
    if len(new_image) % 2 != 0:  # If height is odd
        new_image.append(new_image[-1])  # Duplicate the last row
        new_image = image.copy()

    if len(new_image[0]) % 2 != 0:  # If width is odd
        [ row.append(row[-1]) for row in new_image ]
        new_image = image.copy()
        #for row in image:
        #    row.append(row[-1])  # Duplicate the last column in each row


    # Now that dimensions are even, proceed with downscaling
    new_height = len(new_image) // 2
    new_width = len(new_image[0]) // 2

    downscaled = []
    artefact = []

    for i in range(new_height):
        new_row = []
        for j in range(new_width):
            # Take the top-left pixel of the 2x2 block
            pixel = new_image[i * 2][j * 2]
            new_row.append(pixel)

            x, y = i * 2, j * 2

            top_left     = new_image[x][y]
            top_right    = new_image[x][y + 1]
            bottom_left  = new_image[x + 1][y]
            bottom_right = new_image[x + 1][y + 1]

            vals = [top_left, top_right, bottom_left, bottom_right]
            #print(vals)
            r_sum = 0
            g_sum = 0
            b_sum = 0

# Iterate through each pixel in vals
            for pixel in vals:
                r_sum += pixel[0]  # Add red value
                g_sum += pixel[1]  # Add green value
                b_sum += pixel[2]  # Add blue value

            # Calculate averages
            num_pixels = len(vals)
            avg_r = r_sum / num_pixels
            avg_g = g_sum / num_pixels
            avg_b = b_sum / num_pixels

            # Create the average color as a list
            avg_color = [int(avg_r), int(avg_g), int(avg_b)]
            new_image[x][y] = avg_color
            new_image[x][y + 1] = avg_color
            new_image[x + 1][y] = avg_color
            new_image[x + 1][y + 1] = avg_color

            if not all(v == vals[0] for v in vals):  # check if all values are the same
                #artefact.append(vals)
                artefact.append([i,j])
        downscaled.append(new_row)

    return [downscaled, new_image, artefact]

image_url = "" 

response = requests.get(image_url, stream=True)
response.raise_for_status()  # Raise an exception for bad responses (4xx or 5xx)

image = Image.open(BytesIO(response.content))

image_np = np.array(image)
image_list = image_np.tolist()
new,copy, arte = downscale_nearest_neighbor_2x(image_list)
new,copy, arte = downscale_nearest_neighbor_2x(copy)
up = upscale_nearest_neighbor_2x(new)

image_np = np.array(new, dtype=np.uint8)
image = Image.fromarray(image_np)
image.save("new.jpg")

image_np = np.array(up, dtype=np.uint8)
image = Image.fromarray(image_np)
image.save("up.jpg")
