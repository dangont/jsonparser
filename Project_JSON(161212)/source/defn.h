#include<stdio.h>

typedef enum
{
    JSON_UNDEFINED = 0,
    JSON_OBJECT = 1,
    JSON_ARRAY = 2,
    JSON_STRING = 3,
    JSON_PRIMITIVE = 4
}json_token_type;                                          // enumerating various data types in JavaScript Object Notation

typedef struct
{
    json_token_type type;
    int start;
    int size;
    int end;                                               // a structure containing the token type, start position,end position , and token size
}json_token;


