#include"stack_headers.h"

int isempty(stack s)
{
    return s->next==NULL;                          //checks if the stack is empty
}

stack create_stack(void)
{
    stack s;
    s=(node*)calloc(1,sizeof(node));               //creates the head node of the stack
    make_empty(s);
    return s;
}

void make_empty(stack s)
{
    if(s==NULL)
        printf("sorry out of space");              //empties the stack that is passed
    else
        while(!isempty(s))
            pop(s);
}

void push(char x,int p,stack s)
{
    ptr_to_node temp;

    temp=(node*)calloc(1,sizeof(node));            //inserts a node onto the top of the stack
    temp->data=x;                                 
    temp->position=p;                          
    temp->next=s->next;
    s->next=temp;
}

char top_l(stack s)
{
    if(!isempty(s))
        return s->next->data;
    else                                           //returns the value of the element that is on top of the stack
        printf("empty stack");
    return '\0';
}

int top_pos(stack s)
{
    if (!isempty(s))
        return s->next->position;                 //returns the position of the top element
    else
        printf("empty stack");
    return '\0';
}

void pop(stack s)
{
    ptr_to_node temp;
    temp=s->next;                                 //deletes the node that is on top of the stack
    s->next=s->next->next;
    free(temp);
}

void display(stack s)
{
    
    printf("data  position\n");
    while(s->next)
    {
        s=s->next;                                    // displays the elements that are stacked up
        printf("%c       %d \n",s->data,s->position);
    }
}


int checkline(int top,FILE *fp)
{
    fseek(fp,0,0);
    int i=1;
    while((ftell(fp))<top)
    {
                                      //given a particular position in the file, while line does that character belong to
        if((fgetc(fp))=='\n')
            ++i;
    }
    fgetc(fp);
    return i;
}

void print_tokens(FILE *fp,int start,int size)
{
    int i=1;
    fseek(fp,start,0);
    while(i<=size)
    {
                                                    //prints the tokens in their whole sense
        printf("%c",fgetc(fp));
        ++i;
    }
}
