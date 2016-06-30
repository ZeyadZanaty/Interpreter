#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "linkedlist.h"
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <conio.h>
#define TYPE float

int priority (char c);
int isOperator (char c);
void readFile(char* filename);
void error();
TYPE evaluatePostfix (char postfix[]);
void infixTopostfix(char infix[],char postfix[]);
int getInput(char input[]);
int isSpecialCharacter(char c);
int checkVariable(char *c,Linkedlist* list);
void addVariable(char string[]);
Variable* getVariable(char *c,Linkedlist* list);

Linkedlist list;

int main()
{
    char string [100];
    char postfix[50];

    initList(&list);
    Variable *var;
    printf("\t\t\t\t\t ::QomboTM Interpreter::\n\n");
    printf("Commands::kill- exit the program\n\t  list- list all variables\n\t  search- search with variable name\n\t  wipe- clear the screen\n\t  fread- read variables from a file\n\t  fsave- save variables in a file\n\t  help me pls- list the commands\n");
    printf(">");
    gets(string);
    while (strcmp(string,"kill") != 0)
    {
        if (strcmp(string,"list")==0)
        {
            listVariables(&list);
        }
        else if (strcmp(string,"search")==0)
        {
            char sstring [50];
            printf("Search for\n>");
            gets(sstring);
            if(checkVariable(sstring,&list))
            {
                printf("%s = %.3f\n",getVariable(sstring,&list)->name,getVariable(sstring,&list)->value);
            }
            else printf("'%s' doesn't exist\n",sstring);
        }
        else  if (strcmp(string,"wipe")==0)
        {
            system("cls");
        }
        else  if (strcmp(string,"help me pls")==0)
        {
           printf("Commands::kill- exit the program\n\t  list- list all variables\n\t  search- search with variable name\n\t  wipe- clear the screen\n\t  fread- read variables from a file\n\t  fsave- save variables in a file\n\t  help me pls- list the commands\n");
        }
        else if(strcmp(string,"fread")==0)
        {
            char filename[50];
            printf("Enter file name\n>");
            gets(filename);
            readFile(filename);
            fflush(stdin);
        }
        else if(strcmp(string,"fsave") == 0)
        {
            char filename [50];
            printf("Enter file name\n>");
            gets(filename);
            fileSave(filename);
        }
        else if (getInput(string) == -1)
        {
            error();
        }
        else if(getInput(string) == 1 )
        {
            addVariable(string);
        }

        else  if (getInput(string)==0)
        {
            infixTopostfix(string,postfix);
            printf("%.3f\n",evaluatePostfix(postfix));
        }
        else
        {
            error();
            printf("'%s' is not a command - enter 'help me pls' to list the available commands\n",string);
        }
        printf(">");
        gets(string);
    }
    return 0;
}
/*
returns a number from 0 to 3 according
to the priority of the operator
*/
int priority(char x)
{
    if(x=='(')
        return 0 ;
    if(x=='+'||x=='-')
        return 1;
    if(x=='*'||x=='/'||x=='%')
        return 2;

    return 3 ;
}

int isSpecialCharacter(char c)
{
    if(c== '!' || c== '@' || c== '#' || c== '$' ||c == '~'|| c== '`' || c=='_')
        return 1;
    return 0;
}

// gets input from user
int getInput(char input[])
{
    int i=0,j=0;
    int oflag=0, cflag=0;
    int count=0;
    while(input[i]!='\0')
    {

        while(input[i] == ' ')
        {
            ++i;
        }
        if (input[i]=='=')
        {
            return 1;
            break;
        }
         if(input[i] == '(')
        {
            oflag++;
        }
        if (input[i] == ')')
        {
            cflag++;
        }
        if(isOperator(input[i])&& isOperator(input[i+1]))
        {
            return -1;
        }
        if(!isOperator(input[i]))
        {
            count++;
        }
        ++i;    //equality
    }
    if(cflag!=oflag)
    {
        return -1;
    }
    if(count==strlen(input))
    {
        return 2;
    }
    return 0; //expression

}

int isOperator (char c)
{
    if (c == '+' || c == '-' || c == '*' ||
            c == '/' || c == '%')
        return 1;
    return 0;
}

Variable* getVariable(char *c,Linkedlist* list)
{

    Variable *traverse = list->head;
    while(traverse)
    {
        if(strcmp(c,traverse->name)==0)
        {
            return traverse;
        }
        else
            traverse=traverse->next;
    }
    printf("No such variable as '%s'\n",c);
}

void error()
{
    printf("Error!\n\a");
}

void listVariables(Linkedlist *l)
{
    Variable *traverse = l->head;
    if(!traverse)
    {
        printf("No variables registered!\n");
    }
    while(traverse)
    {
        printf("%s = %.2f\n",traverse->name,traverse->value);
        traverse=traverse->next;
    }

}
void printVariable(Variable *var)
{

    printf("%s = %.2f\n",var->name,var->value);

}

void addVariable(char string[])
{
    int i = 0;
    int count = 0;
    int counter = 0;
    char exp[50];
    char postfix [50];
    char var_name[50];
    TYPE var_value;

    while(string[i]!='\0')
    {
        if (string[i] == ' ')
        {
            ++i;
            continue;
        }
        if(isalpha(string[i]))
        {
            while(isalpha(string[i]))
            {
                if(string[i] == ' ')
                {
                    ++i;
                    continue;
                }
                var_name[count++]=string[i];
                ++i;
            }
            var_name[count]='\0';
        }
        if(string[i] == '=')
        {
            ++i;
            while(string[i] == ' ')
            {
                ++i;
            }
            if(isalnum(string[i])||isOperator(string[i])||string[i]=='(')
            {
                while((isalnum(string[i]) || string[i] == '.' || isOperator(string[i]) || string[i]=='(' ||string[i]==')')&& string[i]!='\0')
                {
                    exp[counter++] = string[i];
                    ++i;
                    while(string[i]  == ' ')
                    {
                        ++i;
                    }
                }
                exp[counter]='\0';
            }
            infixTopostfix(exp,postfix);
            var_value = evaluatePostfix(postfix);
            if(var_value!=-9999)
            {
            if(!checkVariable(var_name,&list))
            {
                addTail(var_value,var_name,&list);
                printf("%s = %.3f \n",var_name,var_value);
            }
            else
            {
                Variable *var = getVariable(var_name,&list);
                var->value = var_value;
                printf("@overwrite\n");
                printf("%s = %.3f \n",var->name,var->value);
            }
            }
        }
    }
}

void infixTopostfix(char infix[],char postfix[])
{
    Stack s;
    initialize(&s);
    int i,j=0;
    int num;
    char x;

    for(i=0; infix[i]!='\0'; i++)
    {
        if(isalnum(infix[i]))
        {
            postfix[j++]=infix[i];
            ++i;
            while(isalnum(infix[i])|| infix[i]=='.')
            {
                postfix[j++]=infix[i];
                ++i;
            }
            --i;
            postfix[j++]=' ';
        }
        else if(infix[i]=='(')
        {
            push('(',&s);
        }
        else if(infix[i]==')')
        {
            while((x=pop(&s))!='(')
                postfix[j++]=x;
        }
        else
        {
            while(priority(infix[i])<=priority(peak(&s))&&!isEmpty(&s))
            {
                x=pop(&s);
                postfix[j++]=x;
            }
            push(infix[i],&s);
        }
    }

    while(!isEmpty(&s))
    {
        x=pop(&s);
        postfix[j++]=x;
    }

    postfix[j]='\0';
}

TYPE evaluatePostfix(char postfix[])
{
    int i = 0;
    float a = 0, b = 0;
    float currentNum = 0;
    char var_name[50];
    int counter=0;
    int count = 0;
    char value[60];
    Stack s;
    initialize(&s);

    while(postfix[i]!='\0')
    {
        if (postfix[i] == ' ')
        {
            i++;
            continue;
        }
        if(isdigit(postfix[i]))
        {
            while(isdigit(postfix[i])|| postfix[i] == '.')
            {
                value[counter++]=postfix[i];
                ++i;
            }
            value[counter] = '\0';
            currentNum = atof(value);
            push(currentNum, &s);
            counter=0;
        }
        if(isalpha(postfix[i]))
        {
            while(isalpha(postfix[i]))
            {
                var_name[count++]=postfix[i];
                i++;
            }
            var_name[count] = '\0';
            if(checkVariable(var_name,&list))
            {
                currentNum=getVariable(var_name,&list)->value;
                push(currentNum,&s);
            }
            else
            {
                error();
                return -9999;
            }
            count =0;
        }
        if (isOperator(postfix[i]))
        {
            b = pop(&s);
            a = pop(&s);
        }

        switch (postfix[i])
        {

        case '+':
            push(a + b, &s);
            break;
        case '-':
            push(a - b, &s);
            break;
        case '*':
            push(a * b, &s);
            break;
        case '/':
            push(a / b, &s);
            break;
        case '%':
            push((int)a % (int)b, &s);
            break;
        default:
            break;

        }
        i++;

    }

    return pop(&s);
}

int checkVariable(char *c,Linkedlist* list)
{
    Variable *traverse = list->head;
    while(traverse)
    {
        if(strcmp(traverse->name,c)==0)
            return 1;
        traverse=traverse->next;
    }
    return 0;
}
void readFile(char* filename)
{
  //  Variable var[50];
    int count = 0;
    char line[600];
    char post [500];
    FILE *f;
    f=fopen(filename,"r");
    if(f == NULL)
    {
        printf("File Not Found !\a\n");
        return;
    }
    else
    {
        while (!feof(f))
        {
            fscanf(f,"%[^\n]",line);
            fscanf(f,"\n");
            if(getInput(line)==1)
            addVariable(line);
            else if(getInput(line)==0){
            infixTopostfix(line,post);
            printf("'%s' = %.3f\n",line,evaluatePostfix(post));
            }
            else
            {
                printf("Error while reading file !\n\a");
                return;
            }
        }
        fclose(f);
        puts("File Loaded !");
    }
}
void fileSave (char* filename)
{
    FILE* file;
    file  = fopen(filename, "w");
    Variable* currentHead = list.head;
    while (currentHead != NULL){
        fprintf(file,"%s = %f\n",currentHead->name,currentHead->value);
        currentHead = currentHead->next;
    }
    printf("File saved successfully\n");

    fclose(file);

}
