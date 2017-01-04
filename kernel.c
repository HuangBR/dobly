#include "drivers/screen.h"

void main()
{
//    unsigned char *video_memory = (unsigned char *)0xb8000;
    set_cursor(80 , 25);
    print("a");
}
