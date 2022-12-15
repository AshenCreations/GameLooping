# What is this project?

- It is very much a work in progress to build a small game engine to help me slowly learn how to code

- Building a game loop using fixed interval updates & variable rendering so that the project
 can remain consistent over different refresh rates

- I'm using C & SDL2 & compiling with a build.bat in CL. Only really using some simple operator overloading from C++

- VSCode is being used for editing the project & debugging

## To Run

- .exe

- the 3 SDL dll's

- img folder & fonts folders

## When running

- opens a fixed size 1600 x 900 window

- Tries to use desktop displaymode to find refresh rate & auto adjusts for 60Hz, 75Hz, 120Hz, 144Hz and 165Hz

- No resolution size changes

- Player sprite is, (seems to be), adjusted to be frame rate independant. The enemy sprite (smiley) is not for testing
