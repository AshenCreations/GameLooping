#include "events.h"

// Carries out actions based on input event.
void do_event(s32 event)
{
    if(event == EVENT_QUIT)
    {
        exit(0);
    }

    if(event == EVENT_KEYPRESSED_SCREENSHOT)
    {
        do_screenshot();
    }
}
