#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_compiler_bridge(const char* code, char* outputBuffer) {
    //Take text in textBuffer to file .c
    FILE* f = fopen("temp.c", "w");
    if (f) {
        fprintf(f, "%s", code);
        fclose(f);
    }
    // compile GCC ; SPot Output Error to file output.txt
    system("gcc temp.c -o temp_run 2> output.txt && ./temp_run >> output.txt 2>&1");
    // read output.txt put in buffer send to terminal for draw text
    FILE* res = fopen("output.txt", "r");
    if (res) {
        memset(outputBuffer, 0, 1024);
        fread(outputBuffer, 1, 1024, res);
        fclose(res);
    } else {
        strcpy(outputBuffer, "Error: can't read output file");
      }
}
