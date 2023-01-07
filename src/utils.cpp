#include "utils.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

bool mouse_in_rect(GPU_Rect rect);
s32 round_float2Int(f32 fNum);
f32 square(f32 num);
f32 check_distance(Vec2 a, Vec2 b);
f32 get_vector_length(Vec2 vec);

// f32 lerp(f32 v0, f32 v1, f64 t);
// Vec2 lerp_Vec2(Vec2 start, Vec2 end, f64 t);

Vec2 make_Vec2(f32 x, f32 y);
f32 dot_product(Vec2 a, Vec2 b);
Vec2 unit_Vec2(Vec2 a);
bool circle_in_circle(Circle a, Circle b);

//^^^^^^^^^^^^^^^^^ cirular queueing ^^^^^^^^^^^^^^^^

bool queue_is_full(Queue* queue);
bool queue_is_empty(Queue* queue);
bool enqueue(Queue* queue, Vec2 item);
bool dequeue(Queue* queue);
Vec2 queue_front(Queue* queue);
Vec2 queue_rear(Queue* queue);
void reset_queue(Queue* queue);

void ring_to_linear_array(Queue* queue);

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// checks if the mouse is inside rect
bool mouse_in_rect(GPU_Rect rect)
{
	f32 x1 = rect.x;
    f32 x2 = x1 + rect.w;
    f32 y1 = rect.y;
    f32 y2 = y1 + rect.h;
    f32 mx = (f32)app.mouse.pos.x;
    f32 my = (f32)app.mouse.pos.y;

    return ((mx >= x1 && mx < x2) && (my >= y1 && my < y2)) ? true:false;
}

// round a f32 to nearest s32
s32 round_float2Int(f32 fNum)
{
    f32 offset = 0.5f;
    if(fNum < 0)
        offset = -0.5f;
    return (s32)(fNum + offset);
}

// return the square of float
f32 square(f32 num)
{
    return num * num;
}

// returns the distance between Vec2 positions
f32 check_distance(Vec2 a, Vec2 b)
{
    return sqrtf(square(b.x - a.x) + square(b.y - a.y));
}

// returns vector magnitude from Vec2 input
f32 get_vector_length(Vec2 vec)
{
    return sqrtf(square(vec.x) + square(vec.y));
}

// // float lerp
// f32 lerp(f32 v0, f32 v1, f64 t)
// {
//     return ((1 - (f32)t) * v0) + ((f32)t * v1);
// }

// // vector lerp
// Vec2 lerp_Vec2(Vec2 start, Vec2 end, f64 t)
// {
//     return (start * (1 - (f32)t)) + (end * (f32)t);    
// }

// make 2 floats into a Vec2
Vec2 make_Vec2(f32 x, f32 y)
{
    return {x, y};
}

// return inner product of 2 Vec2's
f32 dot_product(Vec2 a, Vec2 b)
{
    return (a.x * b.x) + (a.y * b.y);
}

// returns a Vec2 input as a unit vector
Vec2 unit_Vec2(Vec2 a)
{
    return (a / get_vector_length(a));
}

// return if 2 circles collide
bool circle_in_circle(Circle a, Circle b)
{
    Vec2 dist = a.pos - b.pos;
    f32 dist2 = dot_product(dist, dist);
    f32 radiusSum = a.radius + b.radius;
    return dist2 <= square(radiusSum);
}


//^^^^^^^^^^^^^^^^^^^^^^^ circular queue ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// Queue is full when size becomes
// equal to the capacity
bool queue_is_full(Queue* queue)
{
    return(queue->size == queue->capacity);
}

// Queue is empty when size is 0
bool queue_is_empty(Queue* queue)
{
    return(queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
bool enqueue(Queue* queue, Vec2 item)
{
    if(queue_is_full(queue))
        return false;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    return true;
}

// Function to return & remove an item from queue.
// It changes front and size
bool dequeue(Queue* queue)
{
    if(queue_is_empty(queue))
        return false;
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return true;
}

// Function to get front of queue
Vec2 queue_front(Queue* queue)
{
    if(queue_is_empty(queue))
        return {0, 0};
    return queue->array[queue->front];
}

// Function to get rear of queue
Vec2 queue_rear(Queue* queue)
{
    if(queue_is_empty(queue))
        return {0, 0};
    return queue->array[queue->rear];
}

// empty a circular queue
void reset_queue(Queue* queue)
{
    memset(queue->array, 0, sizeof(queue->array));
    queue->front = queue->size = 0;
    queue->rear = queue->capacity - 1;
}

// linearise moveQueue for the renderer
void ring_to_linear_array(Queue* queue)
{
    for (int i = 0; i < queue->size; i++)
    {
        app.player.lArray[i] = queue->array[(queue->front + i) % queue->capacity];
    }
}
