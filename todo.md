# To do, to think about

## So

- you have a problem. Solve for that problem, not an abstracted generalised solution
- micro/milliseconds only. Fps is fake
- learn about memory allocation & management, arenas maybe
- are to trying to make pretty code, or trying to create something that works well

## Naming Conventions

- own_functions_like_this :snake_case
- MyStructName, myStructInstance :camelCase
- variableName
- #define MACRO_NAME_IN_CAPS
- enums nameLikeDis whilst members are LIKE_MUH_MACROS

## Gameloop

- input -> update loop -> render

## Input

- basic key input: store all keyboard input in keyPressed[], keypress down = 1, keypress up = 0
- use a second array wasPressed[]
- change input from using is_pressed() was_pressed() directly to using get_keytate() which uses them to check if a key has just been pressed, has been held since last frame or has been released.

### Movement

- All directions can be done with unit vectors, then multiply by speed and of course deltatime
- vec2 to represent velocity vector
- player diagonal movement
- Vec2 operators
- enable moving player by mouse click. Cancel move when any movekey pressed
- implement a queue system to store movement commands
- ctrl + left-click to add waypoints to player movement queue

## Updating

- update position: calculus, vectors. Semi-implicit Euler integration
- clipping: screen, reflecting vectors
- collision: if, when , where. Simple circle collider checking by dist^2 generated by dot product of distance between points(no sqrt)
- unit facing based on velocity x-component being > 0 or < 0

## Rendering

- using alpha value to render part-frame
- open window with SDL then open renderer with SDL_gpu
- need window resizing !! ONE DAY

### render layers

- Sorting Layers: Background, Middleground, Foreground
- Background holds the world: sky, land, etc
- Middleground holds the action, Npcs & Players
- Foreground holds anything drawn in front of the action (so that you have "depth"), including "facades" which fade as the player passes them
- Order in Layer: sublayers numbered as -1, 0, 1 for example. why into -ve tho ????????

## Coordinates. ONE DAY

- screen + camera = world
- screen = world - camera

## GUI. LOW PRIORITY

- Atomic-ish modular ui system
- change button labels back to GPU_Image to be loaded at init
- Implement a better version of doButton & doMenu
- move drawing into draw.cpp & ui logic stays in ui.cpp - maybe ?
- Tooltips: Instant to start with
