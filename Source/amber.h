#ifndef VOID16_H
#define VOID16_H

typedef enum {
    TOKEN_show,   // show text in the fucking double quote
    TOKEN_str,    // "string" Fucking Double Quote Not a SIngle
    TOKEN_clear,    // Clear Screen
    TOKEN_EOF,    // End Of File
    TOKEN_Unknow  // Unknown Type
} TokenType;

// Struct
typedef struct {
    TokenType type;  
    char value[256]; 
} Token;

#endif
