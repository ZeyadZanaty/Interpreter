#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED
#define TYPE float
#include <string.h>
typedef struct Variable{
TYPE value;
char name[50];
struct Variable * next;
}Variable;

typedef struct {
Variable* head;
Variable* tail;
}Linkedlist;

void initList(Linkedlist *list){
list->head = NULL;
list->tail = NULL;
}
Variable* newVariable(TYPE value , char *name)
{
    Variable *n = (Variable*)malloc(sizeof(Variable));
     n->value = value;
     strcpy(n->name,name);
     n->next = NULL;
     return n;
}
void addHead (TYPE value, char *var, Linkedlist *list){

    Variable *n = newVariable(value,var);

    n->next = list->head;
    list->head = n;
    if(!list->tail)
    list->tail = n;

}

void addTail(TYPE value, char *var, Linkedlist *list){

    Variable *n = newVariable(value,var);
    Variable *old = list->tail;
    list->tail = n;
    if(old)
    {
        old->next=n;
    }
    else
    {
        list->head=n;
    }
}

int isEmpty_list(Linkedlist *list){
if (list->head == NULL && list->tail == NULL)
    return 1;
return 0;
}


#endif // LINKEDLIST_H_INCLUDED
