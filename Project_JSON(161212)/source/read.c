#include<stdio.h>
#include<stdlib.h>
#include"defn.h"
#include"stack_headers.h"
void main(int argc,char *argv[])
{
    FILE *fp;
    char c,prim[10];
    stack s;
    int pos,top,i=0,x=0;
    json_token token[100];
    
    if(argc!=2)
    {
        printf("\nPlease enter the file name as a command line arg.\n");
        exit(-1);
    }
    
    fp=fopen(argv[1],"r");                                                                                 //opening the file
    s=create_stack();

    if(fp==NULL)
    {
        printf("error in opening the file\n");
        exit(1);
    }
   while(1)
    {
                                                   
        c=fgetc(fp);
         if(c==EOF)                                                                                        //stop if EOF is encountered
             break;
       // display(s);                                                                                      //displays what is happening in the stack
        if(isdigit(c))                                                                                     //if the char is a digit
        {
            token[i].type=JSON_PRIMITIVE;
            token[i].start=(ftell(fp)-1);
            while(isdigit(fgetc(fp)));
            fseek(fp,-1,SEEK_CUR);
            token[i].end=(ftell(fp)-1);
            token[i].size=(token[i].end-token[i].start)+1;
            ++i;
        }
        else
            switch (c)
            {
                case '{':
                          push('{',(ftell(fp)-1),s);                                                       //push the character onto the stack
                          break;

                case '}': 
                          if((top_l(s))=='{')                                                              //when the closing character is encountered
                          {
    
                              token[i].type=JSON_OBJECT;
                              token[i].start=top_pos(s);
                              token[i].end=(ftell(fp)-1);
                              token[i].size=((token[i].end-token[i].start)+1);
                              pos=ftell(fp);                                                               //taking the pos of the fp before it enters the function
                              if(isObject(fp,token[i].start,token[i].size))                                //check if the token conforms with its format
                              {
                                  ++i;
                                  pop(s);
                                  fseek(fp,pos,0);                                                         //repositioning the fp
                              }
                              else
                              {
                                display(s);
                                exit(9);
                              }
                          }
                          else
                          {
                            printf("\n\t\t\t\tsorry...incorrect data\n");
                            printf("Either of the two may be incorrect:\n");
                            printf("1. '}' is a stray character for which there is no corresponding opening brace('}' is in line number %d)\n",checkline((ftell(fp)-1),fp));
                            top=top_pos(s);
                            printf("2. '%c' character's corresponding closing character is missing('%c' is in line number %d)\n",top_l(s),top_l(s),checkline(top,fp));
                            exit(-1);
                          }
                          break;

            
                case '"': 
                          token[i].type=JSON_STRING;
                          pos=(ftell(fp)-1);
                          token[i].start=(ftell(fp)-1);
                          cont :
                          {
                              while((c=fgetc(fp))!='"')
                              {
                                if(c==EOF)
                                {
                                    printf(" \t\t\t\nincorrect data\n\n'\"' character's corresponding opening or closing character is missing('\"' is in line number %d)",checkline(pos,fp));
                                    break;
                                }
                              }
                              
                              fseek(fp,-2,SEEK_CUR);
                              if((c=fgetc(fp))=='\\')
                              {
                                fgetc(fp);
                                goto cont;                                                                  //if a '"' is encountered in the middle of the string continue searching for '"'
                              }
                              else
                                  fgetc(fp);
                          }
                              token[i].end=(ftell(fp)-1);
                              token[i].start=pos;
                              token[i].type=JSON_STRING;
                              token[i].size=((token[i].end-token[i].start)+1);
                              i++;  
                              break;
                          

                case '[':
                         push('[',(ftell(fp)-1),s);
                         break;
            
                case ']':
                          if((top_l(s))=='[')
                          {
                              token[i].type=JSON_ARRAY;
                              token[i].start=top_pos(s);
                              token[i].end=(ftell(fp)-1);
                              token[i].size=((token[i].end-token[i].start)+1);
                              pos=ftell(fp);
                            
                              if(isArray(fp,token[i].start,token[i].size))
                              {
                                  i++;
                                  pop(s);
                                  fseek(fp,pos,0);
                              }
                              else
                              {
                                  exit(-1);
                                  display(s);
                              }
                          }
                          else
                          {
                            printf("\n\t\t\t\tsorry...incorrect data\n");
                            printf("either of the two may be incorrect:\n");
                            printf("1. ']' is a stray character for which there is no corresponding opening brace(']' is in line number %d)\n",checkline((ftell(fp)-1),fp));
                            top=top_pos(s);
                            printf("2. '%c' character's corresponding closing character is missing('%c' is in line number %d)\n",top_l(s),top_l(s),checkline(top,fp));
                            exit(-1);
                          }
                          break;
                default:
                          if(isalpha(c))                                                                   //if an alphabet is encountered which doesnt lie in any of the tokens, check if it is any of the primitive tokens, ie 'true' or 'false' or 'null'
                          {
                              if(c=='t')
                              {
                                  pos=ftell(fp)-1;
                                  prim[x]=c;
                                  ++x;
                                  while((c=fgetc(fp))!=' ' && c!=',')
                                  {
                                      prim[x]=c;
                                      ++x;
                                  }
                                  prim[x]='\0';
                                  if(!strcmp(prim,"true"))
                                  {
                                    token[i].type=JSON_PRIMITIVE;
                                    token[i].start=pos;
                                    fseek(fp,-1,SEEK_CUR);
                                    token[i].end=(ftell(fp)-1);
                                    token[i].size=(token[i].end-token[i].start)+1;
                                    ++i;
                                  }
                                  x=0;
                              }    
                              
                              else if(c=='f')
                              {
                                  pos=ftell(fp)-1;
                                  prim[x]=c;
                                  ++x;
                                  while((c=fgetc(fp))!=' ' && c!=',')
                                  {
                                      prim[x]=c;
                                      ++x;
                                  }
                                  prim[x]='\0';
                                  if(!strcmp(prim,"false"))
                                  {
                                    token[i].type=JSON_PRIMITIVE;
                                    token[i].start=pos;
                                    fseek(fp,-1,SEEK_CUR);
                                    token[i].end=(ftell(fp)-1);
                                    token[i].size=(token[i].end-token[i].start)+1;
                                    ++i;
                                  }    
                                  x=0;
                              }
                              else if(c=='n')
                              {
                                  pos=ftell(fp)-1;
                                  prim[x]=c;
                                  ++x;
                                  while((c=fgetc(fp))!=' ' && c!=',')
                                  {
                                      prim[x]=c;
                                      ++x;
                                  }
                                  prim[x]='\0';
                                  if(!strcmp(prim,"null"))
                                  {
                                    token[i].type=JSON_PRIMITIVE;
                                    token[i].start=pos;
                                    fseek(fp,-1,SEEK_CUR);
                                    token[i].end=(ftell(fp)-1);
                                    token[i].size=(token[i].end-token[i].start)+1;
                                    ++i;
                                  }
                                  x=0;
                              }
                              else
                              {
                                  printf("\nThe character '%c' does not lie in either a string or an array or a object. It is in line number %d\n",c,checkline((ftell(fp)-1),fp));
                                  exit(4);
                              }

                          }
            
        }

    }
       
    if(isempty(s))                                                                                         //if the stack is empty
        printf("\t\t\tsuccessfully tokenised\n");
    else
    {
        c=top_l(s);
        top=top_pos(s);
        printf("\nplease insert the corresponding character for '%c' in line number %d ",c,checkline(top,fp));
        
    }
        
    

    //print token details
    
    int j;
    printf("\t\tthe total number of tokens are: %d\n\n",i);
        printf("no\ttoken type\tstart\tend \tsize\n");
    for(j=0;j<i;++j)
    {
        printf("%d\t   %d\t   \t  %d\t%d\t %d\n",j+1,token[j].type,token[j].start,token[j].end,token[j].size);
    }
  


    //print token specific frequencies
    
    int object=0,array=0,string=0,primitive=0;

    for(j=0;j<i;++j)
    {
        if(token[j].type==1)
            ++object;
        else if(token[j].type==2)
            ++array;
        else if(token[j].type==3)
            ++string;
        else if (token[j].type==4)
            ++primitive;
    }

    printf("\n\nobjects: %d\narrays: %d\nstrings: %d\nprimitives: %d\n",object,array,string,primitive);
    

    for(j=0;j<i;++j)
    {
        printf("%d. ",j+1);
        print_tokens(fp,token[j].start,token[j].size);
        printf("\n");
    }
    
    fclose(fp);
}
