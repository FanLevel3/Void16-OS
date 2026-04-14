#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

void clear();
void print(char *message, int col, int row);
void print_char(char character, int col, int row, char attribute_byte);

unsigned char port_byte_in(unsigned short port);
char get_ascii_char(uint8_t scancode);

#endif
