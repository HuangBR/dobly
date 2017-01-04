#include "common.h"
#include "screen.h"


void memcpy(char *dest, char *src, int len)
{
    while(len-- > 0){
        *dest++ = *src++;
    }
}

int get_cursor()
{
    outb(REG_SCREEN_CTRL, CURSOR_LOC_HIGH);
    int offset = inb(REG_SCREEN_DATA) << 8;
    outb(REG_SCREEN_CTRL, CURSOR_LOC_LOW);
    offset += inb(REG_SCREEN_DATA);
    return(offset * 2);
} 

void set_cursor(int offset)
{
    offset /= 2;
    outb(REG_SCREEN_CTRL, CURSOR_LOC_HIGH);
    outb(REG_SCREEN_DATA, offset >> 8);
    outb(REG_SCREEN_CTRL, CURSOR_LOC_LOW);
    outb(REG_SCREEN_DATA, offset);
}


int handle_scrolling(int cursor_offset)
{
    if(cursor_offset < MAX_ROWS * MAX_COLS * 2){
        return cursor_offset;
    }

    int i;
    char * vidmem = (char *)VIDEO_MEMORY;
    for(i = 1; i < MAX_ROWS; i++){
        memcpy(get_screen_offset(0, i-1) + vidmem, get_screen_offset(0, i) + vidmem, MAX_COLS * 2);
    }

    char *last_line = get_screen_offset(0, MAX_ROWS -1) + vidmem;

    for(i = 0; i < MAX_COLS * 2; i++)
        last_line[i] = 0;

    cursor_offset -= 2 * MAX_COLS;

    return(cursor_offset);
}

void print_char(char c, int col, int row, char attr)
{
    unsigned char *vidmem = (unsigned char *)VIDEO_MEMORY;

    if(!attr)
        attr = WHITE_ON_BLACK;

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
        vidmem[offset+1] = attr;
    }

    offset = handle_scrolling(offset);

    set_cursor(offset);
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

void print(char *message)
{
    print_at(message, -1, -1);
}

void clear_screen()
{
    int row;
    int col;
    
    for(row = 0; row < MAX_ROWS; row++){
        for(col = 0; col < MAX_COLS; col++)
            print_char(' ', col, row, WHITE_ON_BLACK);
    }

    set_cursor(get_screen_offset(0, 0));
}
