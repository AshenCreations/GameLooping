# What is this project?

- It is very much a work in progress to build a small game engine to help me slowly learn how to code

- Building a game loop using fixed interval updates & variable rendering so that the project
 can remain consistent over different refresh rates

- I'm using C & SDL2 & compiling with a build.bat in CL. Only really using some simple operator overloading from C++

- VSCode is being used for editing the project & debugging

## SDL addons used

- SDL_gpu
- SDL_ttf
- SDL_mixer

## To Run

- .exe

- the 4 SDL dll's & libmpg123-0.dll

- The 3 folders: img, font, sound.

## The app

- Enemies are spawned then moved by vectors to follow waypoints round & round
- Player moves by vectors with WASD, screen clipped by relection vector
- Both player & enemies change facing based on x component of velocity vector
- There may be some short sound played
- Quit by pressing Esc or window close button

## When running

- opens a fixed size 1600 x 900 window

- Tries to use desktop displaymode to find refresh rate & auto adjusts for 60Hz, 75Hz, 120Hz, 144Hz and 165Hz. Uses refresh rate found then scales the deltatime & player speed, using 60Hz as the base.

- No resolution size changes
