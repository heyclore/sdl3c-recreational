main='03_draw_rect_dirty.c'
exe='exe.exe'

gcc $main dry/sdl_app.c -o $exe -I ~/apps/pac/sdl3/include/ -L ~/apps/pac/sdl3/lib/ -lSDL3
#./$exe
if [ $? -eq 0 ]; then
    ./$exe
fi
