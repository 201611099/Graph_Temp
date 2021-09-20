#ifndef LINKED_LIST
# define LINKED_LIST

#include "list.h"

//#define MAX 10001

typedef struct StackListNodeType
{
	int vertex;
} StackListNode;

typedef struct _stack
{
	StackListNode *top;
	int count;
} Stack;

//typedef LinkedList Stack;

Stack *init(void);
int size(Stack a);
int IsEmpty(Stack a);
int IsFull(Stack a);
void push(Stack *a, ListNode *new);
ListNode *pop(Stack *a);
ListNode *peek(Stack * a);

#endif
