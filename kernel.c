#include "drivers/screen.h"

void main()
{
//    unsigned char *video_memory = (unsigned char *)0xb8000;
    clear_screen();
    set_cursor(get_screen_offset(30, 15));
    print("welcome to dobly's world\n");
//    print_char('c', 1, 1, WHITE_ON_BLACK);
    print("h");
}
