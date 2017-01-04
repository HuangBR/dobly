#include "drivers/screen.h"

void main()
{
//    unsigned char *video_memory = (unsigned char *)0xb8000;
    set_cursor(get_screen_offset(2, 3));
    print("a");
}
