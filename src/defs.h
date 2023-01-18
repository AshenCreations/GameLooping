#pragma once

#define internal static
#define global_variable static

// window
#define WINDOW_TITLE "Game Looping"
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define MAX_KEYBOARD_KEYS 350

// fonts
#define FONT_PATH "fonts/continuum.ttf"
#define FONT_SIZE 24

// images
#define IMAGEPATH_smiley "img/smiley.png"
#define IMAGEPATH_player "img/monakS_64x64.png"

// sounds
#define SOUNDPATH_NOPE "sound/nope.wav"
#define SOUNDPATH_BRUH "sound/bruh.wav"

// Colors
#define COLOR_BLACK {0, 0, 0, 255}
#define COLOR_WHITE {255, 255, 255, 255}
#define COLOR_RED {255, 0, 0, 255}
#define COLOR_GREEN {0, 255, 0, 255}
#define COLOR_BLUE {0, 0, 255, 255}

// math
#define INVERSE_ROOT_2 0.707106781186f
#define PI_32 3.14159265359f

// stats
#define PLAYER_SPEED 12.0f
#define PLAYER_MAX_NUM_MOVES 8
#define ENEMY_SPEED 12.0f
#define MAX_ENEMIES 30
#define PLAYER_WAYPOINT_MIN_DISTANCE 0.33f
#define ENEMY_WAYPOINT_MIN_DISTANCE 0.33f

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Templated Array BEGIN ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// template <typename T, u32 N>
// struct Array
// {
//     static constexpr u32 maxElements = N;

//     s32 count = 0;
//     T elements[N];

//     T& operator[](u32 idx)
//     {
//         assert(idx >= 0);
//         assert(idx < count);
//         return elements[idx];
//     }

//     s32 add(T item);
    
// };

// template <typename T, u32 N>
// s32 Array<T, N>::add(T item)
// {
//     assert(count < maxElements);
//     elements[count] = item;
//     return count++;
// }

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Templated Array END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Circular Queue Template BEGIN ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

template <typename T, u32 N>
struct Queue
{
    static constexpr u32 capacity = N;

    T array[capacity];
    s32 front, rear, size;

    // Queue is full when size becomes equal to the capacity
    bool queue_is_full()
    {
        return(size == capacity);
    }

    bool queue_is_empty();
    bool enqueue(T const &item);
    bool dequeue();
    T queue_front();
    T queue_rear();
    void reset_queue();
    void array_to_linear();
};

// Queue is empty when size is 0
template <typename T, u32 N>
bool Queue<T, N>::queue_is_empty()
{
    return(size == 0);
}

// add an item to the queue. It changes rear and size
template <typename T, u32 N>
bool Queue<T, N>::enqueue(T const& item)
{
    if(queue_is_full())
        return false;
    rear = (rear + 1) % capacity;
    array[rear] = item;
    size = size + 1;
    return true;
}

// remove an item from queue. It changes front and size
template <typename T, u32 N>
bool Queue<T, N>::dequeue()
{
    if(queue_is_empty())
        return false;
    front = (front + 1) % capacity;
    size = size - 1;
    return true;
}

// get front of queue
template <typename T, u32 N>
T Queue<T, N>::queue_front()
{
    if(!queue_is_empty())
        return array[front];
    // if(queue_is_empty())
    //     return something;
    // return array[front];
}

// get rear of queue
template <typename T, u32 N>
T Queue<T, N>::queue_rear()
{
    if(!queue_is_empty())
        return array[rear];
}

// empty a circular queue
template <typename T, u32 N>
void Queue<T, N>::reset_queue()
{
    memset(array, 0, sizeof(array));
    front = size = 0;
    rear = capacity - 1;
}

// linearise a Queue.array into app.player.lArray
template <typename T, u32 N>
void Queue<T, N>::array_to_linear()
{
    for (int i = 0; i < size; i++)
    {
        app.player.lArray[i] = array[(front + i) % capacity];
    }
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Circular Queue Template END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
