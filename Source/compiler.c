#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "amber.h"

Token get_token(const char** input) {
    Token token;
    while (isspace(**input)) (*input)++; // Skip Space
    if (**input == '\0') {
        token.type = TOKEN_EOF;
	return token;
    }

    // Check Input Show
    if (strncmp(*input, "show", 4) == 0 && isspace((*input) [4])) {
        token.type = TOKEN_show;
	    strcpy(token.value, "show");
	    *input += 4;
	     return token;
    }

    if (strncmp(*input, "clear", 5) == 0 && (isspace((*input)[5]) || (*input)[5] == '\0')) {
        token.type = TOKEN_clear;
        strcpy(token.value, "clear");
        input += 5;
        return token;
    }


    if (**input == '"') {
	    (*input)++; // Skip First Double Qoute
	    int i = 0;
	    while (**input != '"' && **input != '\0') {
	        token.value[i++] = *(*input)++;
	    }
	
        token.value[i] = '\0';
	    if (**input == '"') (*input)++; //Skip Last Double Qoute
	    token.type = TOKEN_str;
	    return token;
    }
    token.type = TOKEN_Unknow;
        return token;

}

//Compiler Run
void abc_run(const char* code, char* outputBuffer) {
    const char* p = code;
    Token t1 = get_token(&p);

    if (t1.type == TOKEN_show) {
        Token t2 = get_token(&p);
        if (t2.type == TOKEN_str) {
            sprintf(outputBuffer, "Amber Output: %s", t2.value);
        }
    } else if (t1.type == TOKEN_clear) {
        outputBuffer[0] = '\0'; // Clear Buffer
    } else {
        sprintf(outputBuffer, "Amber Error: Unknown Command");
    }
}
