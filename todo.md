# TO DO

## So

- you have a number of things. Solve for those things, not an abstracted generalised solution
- learn to profile, milliseconds only. Fps is fake

## Rendering

### render sorting layers

- Sorting Layers: Background, Middleground, Foreground
- Background holds the world: sky, land, etc
- Middleground holds the action, Npcs & Players
- Foreground holds anything drawn in front of the action (so that you have "depth"), including "facades" which may fade as the player passes behind them
- Order in Layer: sublayers numbered as -1, 0, 1 for example. why into -ve tho?
- first render Background Layer (-1, then 0 then 1 sublayers), then middleground & foreground similarly.

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
