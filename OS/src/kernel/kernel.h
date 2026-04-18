#ifndef KERNEL_H
#define KERNEL_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;

void clear();
////
void print(char *message, int col, int row);
////
void printc(char *message, int col, int row, uint8_t color);
////
void print_char(char character, int col, int row);
////
void print_charc(char c, int col, int row, uint8_t color);
////
void draw(int x, int y, int width, int height, char color_byte);
////
void draw_bg(int x, int y, int width, int height, char bg_color);
////
void draw_cursor();
////
void update_cursor(int x, int y);
////
extern unsigned char port_byte_in(unsigned short port);
////
extern void port_byte_out(unsigned short port, unsigned char data);
////
char get_ascii_char(uint8_t scancode, int shift_pressed);
////
int strcmp(const char *s1, const char *s2);

#endif
