this worked:

~/Downloads/g0ridev.github.io/storage/platform-game $ ls
game.cpp     libraylib.a  notes.md     raylib.h
~/Downloads/g0ridev.github.io/storage/platform-game $ gcc -o game.exe game.cpp libraylib.a -lopengl32 -lgdi32 -lwinmm
~/Downloads/g0ridev.github.io/storage/platform-game $ ./game.exes




Get a basic window running with Raylib first - just a colored background
Draw a simple rectangle that represents your player character
Make that rectangle move left/right with keyboard input
Add gravity - make it fall down constantly
Add a ground collision - stop falling when it hits the bottom