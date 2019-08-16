#include<stdio.h>
#include<stdlib.h>


int isArray(FILE *fp,int start,int size);                   //checks if the passed token adheres to the array format 
int isObject(FILE *fp,int start,int size);                  //checks if the token is a JSON object  
