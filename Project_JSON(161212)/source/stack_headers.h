#include<stdio.h>
#include<stdlib.h>


struct node                                            //defining the structure of nodes for the stack
{
    char data;
    int position;
    struct node * next;
};

typedef struct node node;
typedef node * ptr_to_node;
typedef ptr_to_node stack;
                                                       //declaring various function prototypes that will be used 
int isempty(stack s);
stack create_stack(void);
void make_empty(stack s);
void push(char x,int p,stack s);
char top_l(stack s);
int top_pos(stack s);
void pop(stack s);
void display(stack s);
int checkline(int pos,FILE *fp);
void print_tokens(FILE *fp,int start, int size);
