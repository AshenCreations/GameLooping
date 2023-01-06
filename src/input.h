#include "common.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

extern Vec2 move_up(void);
extern Vec2 move_down(void);
extern Vec2 move_left(void);
extern Vec2 move_right(void);

extern bool queue_is_full(Queue* queue);
extern bool queue_is_empty(Queue* queue);
extern bool enqueue(Queue* queue, Vec2 item);
extern bool dequeue(Queue* queue);
extern Vec2 queue_front(Queue* queue);
extern Vec2 queue_rear(Queue* queue);
extern void reset_queue(Queue* queue);

extern App app;
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
