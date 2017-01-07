#ifndef _SCREEN_H
#define _SCREEN_H

#define VIDEO_MEMORY 0xb8000
#define MAX_COLS 80
#define MAX_ROWS 25

#define WHITE_ON_BLACK 0x0f

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

#define CURSOR_LOC_HIGH 0x0E
#define CURSOR_LOC_LOW  0x0F

void print(char *);
void print_char(char, int, int, char);

#define get_screen_offset(col, row) (((row) *80 + (col)) * 2)

int get_cursor();
void set_cursor(int);

void clear_screen();

#endif /* _SCREEN_H */
