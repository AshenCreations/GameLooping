# Main ideas

## ???

- you have a number of things. Solve for those things, not an abstracted generalised solution
- learn to profile, milliseconds only. Fps is fake

## Code

- learn about memory allocation & management, arenas maybe
- are to trying to make pretty code, or trying to create something that works well

### Naming Conventions

- own_functions_like_this
- MyStructName, myStructInstance
- variableName
- #define MACRO_NAME_IN_CAPS

## Ui

- Atomic modular ui system
- change button labels back to GPU_Image to be loaded at init
- Implement a better version of doButton & doMenu
- move drawing into draw.cpp & ui logic stays in ui.cpp - maybe ?

### Tooltips

- Instant to begin then maybe use a short delay before drawing

## Input

- Key > Action > Events
- bool check actions(keypress), then call event on success

## Later stuff

### Coordinates

- screen + camera = world
- screen = world - camera

### Time

- unhook physics from framerate by using time based movements
- Timestep
- movespeed(per second) / framerate = distance moved per timestep
- fixed delta time
- variable delta time
- semi-fixed delta time
- unlocked
