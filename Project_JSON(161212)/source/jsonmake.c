
#include<stdio.h>
#include<stdlib.h>

int tabs=0;
void create_object(FILE *fp);
void create_array(FILE *fp);
void main()
{
    char strng[100];
    char o_a,sapo;

    printf("\nWhat do you want to create?\n\n1:JSON OBJECT(o)\n2:JSON ARRAY(a)\n\t\t\t\t\t\tOption(o/a): ");
    scanf("%c",&o_a);
    getchar();
    printf("\n\nWhat do you want to name the file where this data shall be stored?  :  ");
    scanf("%s",&strng);

    FILE *fp=fopen(strng,"w+");
    if(fp==NULL)
    {
        printf("\n\nSorry! Unable to open the file. Try again later.\n");
        exit(1);
    }

    switch(o_a)
    {
        case 'o': 
                    create_object(fp);
                    break;
        case  'a':
                    create_array(fp);
                    break;
    }

    fclose(fp);
    
}



void create_object(FILE *fp)
{
    char sapo,strng[50],exit='a';
    int i=0;
        fprintf(fp,"\{");
        getchar();
    while(exit!='n')
    {
            if(i!=0)
                fprintf(fp," ,");
        fprintf(fp," \"");
        printf("\nPlease enter the key : ");
        gets(strng);
        fputs(strng,fp);
        fprintf(fp,"\" : ");
        printf("\nWhat do you want the value to be?\n1:String(s)\n2:Array(a)\n3:Primitive(p)\n4:Object(o)\n\t\t\t\tOption(s/a/p/o): ");
        scanf("%c",&sapo);
            while(sapo!='s'&&sapo!='a'&&sapo!='p'&&sapo!='o')
            {     
                printf("\nGive a valid input (s/a/p/o) : ");
                scanf("%c",&sapo);
            }
        getchar();
        
        if(sapo=='s')
        {
            fprintf(fp,"\"");
		    printf("\nplease enter the string : ");
	    	gets(strng);
	    	fputs(strng,fp);
	    	fprintf(fp,"\" ");
        }
        else if(sapo=='p')
        {
            printf("\nplease enter a primitive(either a number or the following strings: 1.\"true\" 2.\"false\" 3.\"null\" ");
	    	gets(strng);
	    	fprintf(fp,"%s ",strng);
        }
        else if(sapo=='o')
        {
            create_object(fp);
        }
        else  if(sapo=='a')
        {
            create_array(fp);
        }
        else
        {
            printf("\nGive a valid input");
            scanf("%c",&sapo);
            while(sapo!='s'&&sapo!='a'&&sapo!='p'&&sapo!='o')
            {     
                printf("\nGive a valid input");
                scanf("%c",&sapo);
            }
        }
    
        printf("do you wish to insert another key value pair(y/n): ");
        scanf("%c",&exit);
        if(exit=='y')
            fprintf(fp," , ");
        getchar();
    }
    fprintf(fp," }");
}


void create_array(FILE *fp)
{
    int i=0;
    char sapo,strng[50],exit='a';
    fprintf(fp,"[ ");
    
    while(exit!='n')    
    {
        //fprintf(fp,"[ ");
        getchar();
        printf("\nWhat do you want the value to be?\n1:String(s)\n2:Array(a)\n3:Primitive(p)\n4:Object(o)\n\t\t\t\tOption(s/a/p/o): ");
        scanf("%c",&sapo);
            while(sapo!='s'&&sapo!='a'&&sapo!='p'&&sapo!='o')
            {     
                printf("\nGive a valid input : ");
                scanf("%c",&sapo);
            }
        getchar();
        if(sapo=='s')
        {
            if(i!=0)
            {
                fprintf(fp," ,");
            }
            ++i;
            fprintf(fp,"\"");
		    printf("\nplease enter the string : ");
	    	gets(strng);
	    	fputs(strng,fp);
	    	fprintf(fp,"\" ");
            ++i;
        }
        else if(sapo=='p')
        {
            if(i!=0)
                fprintf(fp," ,");
            ++i;
            getchar();
            printf("\nPlease enter a primitive(either a number or the following strings: \n1.\"true\"\n 2.\"false\" \n3.\"null\" : ");
	    	gets(strng);
	    	fprintf(fp,"%s ",strng);
        }
        else if(sapo=='o')
        {
            if(i!=0)
                fprintf(fp," ,");
            ++i;
            create_object(fp);
        }
        else if(sapo=='a')
        {
            if(i!=0)
                fprintf(fp," ,");
            ++i;
            create_array(fp);
        }
        printf("do you wish to insert another value (y/n): ");
        scanf("%c",&exit);
        getchar();
            while(exit!='y'&&exit!='n')
            {     
                printf("\nGive a valid input");
                scanf("%c",&exit);
            }

    }

    fprintf(fp," ]");
}


