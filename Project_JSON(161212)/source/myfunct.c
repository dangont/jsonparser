#include"myheaders.h"


//checks if the sytax of the array is preserved

int isArray(FILE *fp,int start,int size)
{
    int i,j=1,count=1;
    fseek(fp,start+1,0);
    char c;

    for(i=1;i<size;)
    {
        for(;(c=fgetc(fp))==' '||c=='\n';++i);                                                             //fp goes past the spaces
        ++i;
        
        if(c=='"')
        {
            for(;(c=fgetc(fp))!='"';++i);
            ++i;
            for(;((c=fgetc(fp))==' ' || c=='\n');++i);
            ++i;
            if(c!=',' && c!=']')                                                                           //if '"' is encountered goes to  the end of the string and checks if there is a ',' before the next value else the array must end
            {
                printf("expected ',' or ']' in line number %d",checkline((ftell(fp)-1),fp));
                return 0;
            }
        }

        else if(c=='[')
        {
            while(j<=count)
            {
                for(;(c=fgetc(fp))!=']';++i)
                    if(c=='[')                                                                             //while searching for the closing character, if another opening character is encountered of the same token type as int the case of nested tokens, appropriately search for the end char of the current token
                        ++count;
                ++i;
                if(c==']')
                    ++j;
            }
            count=1;
            j=1;
            
            for(;((c=fgetc(fp))==' '|| c=='\n' || c=='\r');++i);
            ++i;
            
                if(c!=',' && c!=']')
            {
                printf("expected ',' or ']' in line number %d",checkline((ftell(fp)-1),fp));
                return 0;
            }
        }

        else if(c=='{')
        {
            while(j<=count)
            {
                for(;(c=fgetc(fp))!='}';++i)
                    if(c=='{')
                        ++count;
                
                ++i;
                if(c=='}')
                    ++j;
            }
            count=1;
            j=1;
            
            for(;((c=fgetc(fp))==' '|| c=='\n'||c=='\r');++i);
            ++i;
            
            if(c!=',' && c!=']')
            {
                printf("expected ',' or ']' in line number %d befor the character '%c'",checkline((ftell(fp)-1),fp),c);
                return 0;
            }
        }
        else if(isalpha(c))
        {
            for(;(c=fgetc(fp))!=' ' &&  c!=',' && c!='}' ;++i);
            ++i;
            
            if(c==' ')
            {
                for(;((c=fgetc(fp))==' '|| c=='\n'||c=='\r');++i);
                ++i;
            }

            if(c!=',' && c!=']')
            {
                printf("expected ',' or ']' in line number %d befor the character '%c'",checkline((ftell(fp)-1),fp),c);
                return 0;
            }
            
        }
    }

    return 1;
}



int isObject(FILE *fp,int start, int size)
{
    fseek(fp,start+1,0);
    int i=1,j=1,k=0;
    int count=1;                          //counts the number of spl char('[','{') to be encountered in a nested structured 
    char c;

new_kv:    //while(i<=size)
    {
        for(;(c=fgetc(fp))==' '||c=='\n'||c=='\r';++i);
        ++i;
        
        if(c!='"')                        //if the first token that is encountered is not a string
        {
            printf("1.expected a string as a key in the object in line %d before '%c'(else delete the character ',' before '%c')",checkline((ftell(fp)-1),fp),c,c);
            fclose(fp);
            exit(1);
        }

        else                               //if it is a string then proceed and check for ':'
        {
            for(;(c=fgetc(fp))!='"';++i);
            ++i;

            for(;(c=fgetc(fp))==' '||c=='\n'||c=='\r';++i);
            i++;

            if(c!=':')
            {
                printf("2.expected ':' after the key(string) in the object in line %d before the characters '",checkline((ftell(fp)-1),fp));
                    for(;k<=4;++k)
                        printf("%c",fgetc(fp));
                    printf("'...");
                    fclose(fp);
                exit(2);
            }
            else
            {
                for(;(c=fgetc(fp))==' '||c=='\n'||c=='\r';++i);
                i++;

                switch(c)
                {
                    case'{':while(j<=count)                        //case where the value after the key is an object
                            {
                                for(;(c=fgetc(fp))!='}';++i)
                                    if(c=='{')
                                        ++count;
                                
                                i++;
                                if(c=='}')
                                    ++j;
                            }
                            count=1;
                            j=1;
                                break;
                    
                    case'[':while(j<=count)                        //if it is an array
                            {
                                for(;(c=fgetc(fp))!=']';++i)
                                    if(c=='[')
                                        ++count;

                                i++;
                                if(c==']')
                                    ++j;
                            }
                            count=1;
                            j=1;
                                break;
                            
                    case'"':for(;(c=fgetc(fp))!='"';++i)          //if it is a string
                            {
                                if(c=='\\')
                                    fgetc(fp);
                            }
                                break;
                
                    default:if(isdigit(c))
                            {
                                for(;isdigit(c=fgetc(fp));++i);
                                ++i;
                                fseek(fp,-1,SEEK_CUR);
                            }
                            else if(c=='}')
                            {
                                printf("expected a value for the key after the colon in line %d",checkline((ftell(fp)-1),fp));
                                exit(10);
                            }
                            else if(isalpha(c))
                            {
                                for(;isalpha((c=fgetc(fp)));++i);
                                fseek(fp,-1,SEEK_CUR);
                            }
                }

                for(;(c=fgetc(fp))==' '||c=='\n'||c=='\r';i++);
                ++i;

                if(c==',')
                   // continue;
                    goto new_kv;                          //goes to checking the next key value pair
                else if(c=='}')
                    return 1;
                else
                {
                    printf("expected ',' or '}' in line %d before the characters '",checkline((ftell(fp)-1),fp));               
                    for(;k<=4;++k)
                        printf("%c",fgetc(fp));
                    printf("'...");
                    fclose(fp);
                    exit(11);
                }
        }
    }
}

