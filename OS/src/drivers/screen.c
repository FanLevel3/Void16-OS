#define VIDEO_ADDRESS 0xB8000
#define MAX_ROWS 25;
#define MAX_COLS 80;
#define WHITE_ON_BLACK 0x0f

void print_char(char character, int col, int row, char attribute_byte) {
	unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;

	if (!attribute_byte) {
		attribute_byte = WHITE_ON_BLACK;
	}

	int offset = (row * 80 + col) * 2;
	vidmem[offset] = character;
	vidmem[offset + 1] = attribute_byte;
}

void print(char *message, int col, int row) {
	int i = 0;

	while(message[i] != 0) {
		print_char(message[i++], col++, row, WHITE_ON_BLACK);

		if (col >= 80) {col = 0; row++;}
	}
}

void clear() {
	for (int i = 0; i < 80 * 25; i++) {
		print_char(' ', i % 80, i / 80, WHITE_ON_BLACK);
	}
}
