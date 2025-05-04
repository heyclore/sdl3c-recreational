main='08_rect_rotate.c'
exe='exe.exe'

gcc $main dry/sdl_app.c -o $exe \
    -I ~/apps/git/SDL/sdl3/include/ \
    -L ~/apps/git/SDL/sdl3/lib/ \
    -Wl,-rpath=$HOME/apps/git/SDL/sdl3/lib \
    -I ~/apps/git/SDL_image/SDL_image/include/ \
    -L ~/apps/git/SDL_image/SDL_image/lib/ \
    -Wl,-rpath=$HOME/apps/git/SDL_image/SDL_image/lib \
    -lSDL3 -lSDL3_image \
    -lm

if [ $? -eq 0 ]; then
    ./$exe
fi
