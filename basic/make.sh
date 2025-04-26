main='demo.c'
exe='exe.exe'

gcc $main dry/sdl_app.c -o $exe -I ~/apps/pac/sdl3/include/ -L ~/apps/pac/sdl3/lib/ -lSDL3
./$exe
