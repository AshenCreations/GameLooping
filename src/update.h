#include "common.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

extern Vec2 unit_Vec2(Vec2 a);
extern f32 dot_product(Vec2 a, Vec2 b);
extern void play_sound(Mix_Chunk *sound);
extern f32 square(f32 num);
extern bool circle_in_circle(Circle a, Circle b);

extern bool queue_is_full(Queue* queue);
extern bool queue_is_empty(Queue* queue);
extern bool enqueue(Queue* queue, Vec2 item);
extern bool dequeue(Queue* queue);
extern Vec2 queue_front(Queue* queue);
extern Vec2 queue_rear(Queue* queue);
extern void reset_queue(Queue* queue);
extern void ring_to_linear_array(Queue* queue);


extern App app;
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#define ONE_SECOND app.appHz / (4 * app.dt)
