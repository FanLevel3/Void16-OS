#include <stdint.h>
#include "kernel.h"

void clear();
void print(char *message, int col, int row);

void kmain() {
	clear();
	
	print("Void16 OS v0.6", 0, 0);
	print("DumbText Editor v0.1", 0, 4);
	print("Input: ", 0, 6);

	char buffer[256];
	int i = 0;
	int col = 7;

	while(1) {
		if (port_byte_in(0x64) & 0x01) {
			uint8_t scancode = port_byte_in(0x60);
			char c = get_ascii_char(scancode);

			if (c > 0) {
				if (c == '\n') {
					print("Output: ", 0, 8);
					print(buffer, 8, 8);
					break;
				} else {
					buffer[i++] = c;
					buffer[i] = '\0';
					print_char(c, col++, 6, 0x0f);
				}
			}
		}
	}
	
	while(1);
}
