#include "kernel.h"

#define STATE_SHELL	0
#define STATE_DUMBTEXT	1
#define MAX_BUFFER	256

int current_state = STATE_SHELL;
char shell_buffer[MAX_BUFFER];
int shell_idx = 0;
int shell_row = 2;
char dt_buffer[2048]; 
int dt_idx = 0;
int dt_col = 0;
int dt_row = 3;
int is_shift_pressed = 0;
int is_ctrl_pressed = 0;

void enable_block_cursor() {
	port_byte_out(0x3D4, 0x0A);
	port_byte_out(0x3D5, 0x00);
	port_byte_out(0x3D4, 0x0B);
	port_byte_out(0x3D5, 0x0F);
}

void disable_cursor() {
    port_byte_out(0x3D4, 0x0A);
    port_byte_out(0x3D5, 0x20);
}

void start_shell();
void start_dumbtext();
int strcmp(const char *s1, const char *s2);

uint8_t keyboard_ready() {
    return port_byte_in(0x64) & 0x01;
}

void kmain() {
    enable_block_cursor();
    start_shell();
    uint8_t last_scancode = 0;

    while (1) {
        if (keyboard_ready()) {
            unsigned char scancode = port_byte_in(0x60);
            if (scancode & 0x80) {
                scancode &= 0x7F;
                if (scancode == 0x2A || scancode == 0x36) is_shift_pressed = 0;
                if (scancode == 0x1D) is_ctrl_pressed = 0;
            } else {
                if (scancode == 0x2A || scancode == 0x36) {
                    is_shift_pressed = 1;
                    continue;
                }
                if (scancode == 0x1D) {
                    is_ctrl_pressed = 1;
                    continue;
                }

                if (current_state == STATE_SHELL) {
                    char c = get_ascii_char(scancode, is_shift_pressed);
                    if (scancode == 0x1C) {
                        shell_buffer[shell_idx] = '\0';
                        if (strcmp(shell_buffer, "dumb") == 0) {
                            current_state = STATE_DUMBTEXT;
                            start_dumbtext();
                        } else if (strcmp(shell_buffer, "clear") == 0) {
                            start_shell();
                        } else {
                            shell_row++;
                            if (shell_idx > 0) printc("Unknown Command", 0, shell_row++, 0x0C);
                            print("> ", 0, shell_row);
                        }
                        shell_idx = 0;
                        update_cursor(2, shell_row);
                    } else if (scancode == 0x0E) {
                        if (shell_idx > 0) {
                            shell_idx--;
                            print_char(' ', shell_idx + 2, shell_row);
                            update_cursor(shell_idx + 2, shell_row);
                        }
                    } else if (c > 0) {
                        if (shell_idx < MAX_BUFFER - 1) {
                            shell_buffer[shell_idx++] = c;
                            print_char(c, shell_idx + 1, shell_row);
                            update_cursor(shell_idx + 2, shell_row);
                        }
                    }
                } 
                else if (current_state == STATE_DUMBTEXT) {
                    invert_cursor(dt_col, dt_row, 0);

                    if (is_ctrl_pressed && scancode == 0x10) {
                        current_state = STATE_SHELL;
                        start_shell();
                        continue;
                    }

                    if (scancode == 0x0E) {
                        if(dt_col > 0) {
                            dt_col --;
                            print_char(' ', dt_col, dt_row);
                        } else if(dt_row > 1) {
                            dt_row--;
                            dt_col = 79;
                            print_char(' ', dt_col, dt_row);
                        }
                        update_cursor(dt_col, dt_row);
                    }
                    else if (scancode == 0x48) { /* Up */
					    if (dt_row > 1) dt_row--;
                        update_cursor(dt_col, dt_row);
				    }
				    else if (scancode == 0x50) { /* Down */
					    dt_row++;
                        update_cursor(dt_col, dt_row);
				    }
				    else if (scancode == 0x4B) { /* Left */
					    if (dt_col > 0) dt_col--;
                        update_cursor(dt_col, dt_row);
                        invert_cursor(dt_col, dt_row);
				    }
				    else if (scancode == 0x4D) { /* Right */
					    if (dt_col < 79) dt_col++;
                        update_cursor(dt_col, dt_row);
                        invert_cursor(dt_col, dt_row);
				    }

                    else {
                        char c = get_ascii_char(scancode, is_shift_pressed);
                        if (c > 0 && c != '\b') {
                            if (c == '\n') {
                                dt_row++;
                                dt_col = 0;
                            } else {
                                print_char(c, dt_col, dt_row);
                                dt_col++;
                                if (dt_col >= 80) {
                                    dt_col = 0;
                                    dt_row++;
                                }
                            }
                            invert_cursor(dt_col, dt_row, 1);

                            update_cursor(dt_col, dt_row);
                        }
                    }
                }//end keyboard_ready
            }
            for (volatile int i = 0; i < 1000; i++);
        }
    }
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++; s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void start_shell() {
    clear();
    printc("Void16 OS v0.7.2", 0, 0, 0x9f);
    printc("Type 'dumb' to start editor.", 0, 1, 0x0A);
    print("> ", 0, 2);
    shell_idx = 0;
    shell_row = 2;
    update_cursor(2, shell_row);
}

void start_dumbtext() {
    clear();
    printc("--- DumbText Editor v0.2 ---", 0, 0, 0x1f);
    print("CTRL+Q: Exit", 0, 1);
    dt_idx = 0;
    dt_col = 0;
    dt_row = 3;
    update_cursor(dt_col, dt_row);
}


void run_ultrac(char* source) {
    char* start_ptr = strstr(source, "main {");
    if (start_ptr == NULL) {
        printc("Error: No main function found!", 0, shell_row);
    }

    
}
