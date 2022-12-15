# To do, to think about

## So

- you have a problem. Solve for that problem, not an abstracted generalised solution
- micro/milliseconds only. Fps is fake
- learn about memory allocation & management, arenas maybe
- are to trying to make pretty code, or trying to create something that works well

## Naming Conventions

- own_functions_like_this
- MyStructName, myStructInstance
- variableName
- #define MACRO_NAME_IN_CAPS
- enums nameLikeDis whilst members are LIKE_MUH_MACROS

## Time

- input -> update loop -> render

## Input

- basic key input: store all keyboard input in bool[MAX_KEYS], keypress down = 1, keypress up = 0
- player diagonal movement

## Updating

- update position: calculus, vectors
- clipping: screen, reflecting vectors
- collision:

### Vectors

## Rendering

- need window resizing !!

### render sorting layers

- Sorting Layers: Background, Middleground, Foreground
- Background holds the world: sky, land, etc
- Middleground holds the action, Npcs & Players
- Foreground holds anything drawn in front of the action (so that you have "depth"), including "facades" which fade as the player passes them
- Order in Layer: sublayers numbered as -1, 0, 1 for example. why into -ve tho ????????
- first render Background Layer (-1, then 0 then 1 sublayers), then middleground & foreground similarly.

## Coordinates

- screen + camera = world
- screen = world - camera

## GUI

- Atomic-ish modular ui system
- change button labels back to GPU_Image to be loaded at init
- Implement a better version of doButton & doMenu
- move drawing into draw.cpp & ui logic stays in ui.cpp - maybe ?
- Tooltips: Instant to start with
