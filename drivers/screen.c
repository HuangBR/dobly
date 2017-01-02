#include "common.h"
#include "screen.h"

int get_screen_offset(int col, int row)
{
    return (row * 80 + col) * 2;
}

int get_cursor()
{
    outb(REG_SCREEN_CTRL, 14);
    int offset = inb(REG_SCREEN_DATA) << 8;
    outb(REG_SCREEN_CTRL, 15);
    offset += inb(REG_SCREEN_DATA);
    return(offset * 2);
} 

void set_cursor(int offset)
{
    offset /= 2;
    outb(REG_SCREEN_CTRL, 14);
    outb(REG_SCREEN_DATA, (u8)(offset >> 8));
    outb(REG_SCREEN_CTRL, 15);
}

void print_at(char *message, int col, int row)
{
    if(col >=0 && row >=0){
        set_cursor(get_screen_offset(col, row));
    }

    int i = 0;
    while(message[i] != 0){
        print_char(message[i++], col, row, WHITE_ON_BLACK);
    }
}

void print_char(char c, int col, int row, char attr)
{
    unsigned char *vidmem = (unsigned char *)VIDEO_MEMORY;

    if(!attr)
        attr = BLACK_ON_WHITE;

    int offset;

    if(col >= 0 || row >= 0)
        offset = get_screen_offset(col, row);
    else
        offset = get_cursor();

    if(c == '\n'){
        int rows = offset / (2 * MAX_ROWS);
        offset = get_screen_offset(col, rows);
    } else {
        vidmem[offset] = c;
        vidmoe[offset+1] = attr;
    }

    offset = handle_scrolling(offset);

    set_cursor(offset);
}

void print(char *message)
{
    print_at(message, -1, -1);
}
