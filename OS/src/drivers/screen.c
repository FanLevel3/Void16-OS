#include "kernel.h"

/* 1. print_char: Standard White on Black (0x0F) */
void print_char(char character, int col, int row) {
	uint8_t *vidmem = (uint8_t *) 0xB8000;
	int offset = (row * 80 + col) * 2;
	vidmem[offset] = character;
	vidmem[offset + 1] = 0x0F;
}

/* 2. print_charc: Custom Color */
void print_charc(char c, int col, int row, uint8_t color) {
	uint8_t *vidmem = (uint8_t *) 0xB8000;
	int offset = (row * 80 + col) * 2;
	vidmem[offset] = c;
	vidmem[offset + 1] = color;
}

/* 3. print: Simple string (White on Black) */
void print(char *message, int col, int row) {
	int i = 0;
	while (message[i] != '\0') {
		print_char(message[i], col + i, row);
		i++;
	}
}

/* 4. printc: String with Custom Color */
void printc(char *message, int col, int row, uint8_t color) {
	int i = 0;
	while (message[i] != '\0') {
		print_charc(message[i], col + i, row, color);
		i++;
	}
}

/* 5. clear: Fill screen with spaces and default color */
void clear() {
	for (int i = 0; i < 80 * 25; i++) {
		print_char(' ', i % 80, i / 80);
	}
}

/* 6. draw: Draw a solid block (Fills character and color) */
void draw(int x, int y, int width, int height, char color_byte) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			print_charc(' ', x + j, y + i, color_byte);
		}
	}
}

/* 7. draw_bg: THE MAGIC ONE - Changes color WITHOUT erasing characters */
void draw_bg(int x, int y, int width, int height, char bg_color) {
	uint8_t *vidmem = (uint8_t *) 0xB8000;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int offset = ((y + i) * 80 + (x + j)) * 2 + 1; /* Point to Attribute Byte */
			vidmem[offset] = bg_color; /* Change only the color/attribute */
		}
	}
}

/* 8. update_cursor: Update hardware cursor position */

void update_cursor(int x, int y) {
	uint16_t pos = y * 80 + x;
	port_byte_out(0x3D4, 0x0E);
	port_byte_out(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
	port_byte_out(0x3D4, 0x0F);
	port_byte_out(0x3D5, (uint8_t)(pos & 0xFF));
}

/* 10. draw_cursor: Empty helper if needed */
void draw_cursor() {
	/* Placeholder for complex cursor logic if you want later */
}


void invert_cursor(int x, int y, int active) {
    uint8_t *vidmem = (uint8_t *) 0xB8000;
    int offset = (y * 80 + x) * 2 + 1; 
    
    if (active) {
        vidmem[offset] = 0x70;  
    } else {
        vidmem[offset] = 0x0F; 
    }
}
