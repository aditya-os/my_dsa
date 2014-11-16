#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
	long data;
	long size;
	struct node *next;
};
struct stack
{
	struct node *first;
};
void stack_initialize(struct stack *s)
{
	s->first = NULL;
}
int stack_is_empty(struct stack *s)
{
	return s->first == NULL;
}
int stack_push(struct stack *s,struct node *d)
{
	struct node *new_data;
	new_data=malloc(sizeof(struct node));
	if(!new_data)
		return 0;
	memcpy(&(new_data->data),&(d->data),d->size);
	new_data->size=d->size;
	//new_data->data=data;
	new_data->next=s->first;
	s->first=new_data;
	printf("Top of stack is %p\n",s->first);
//	assert(s->first==NULL);
	return 1;
}

int stack_pop(struct stack *s,struct node *d)
{
	struct node *next=NULL;
	if(s->first)
	{
		memcpy(&(d->data),&(s->first->data),s->first->size);
		d->size=s->first->size;
		d->next=NULL;
		next=s->first->next;
		free(s->first);
		s->first=next;
		return 1;
	}
	return 0; 
}
int main()
{
	struct stack s1;
	struct node s[10]={{10,sizeof(int),NULL},{22,sizeof(long),NULL},{23,sizeof(long),NULL},{43,sizeof(long),NULL},{55,sizeof(long),NULL}};
	struct node item;
	stack_initialize(&s1);
//	stack_push(&s1,{ 10, sizeof(long), NULL}  );
	stack_push(&s1,&s[0]);
	stack_push(&s1,&s[1]);
	stack_push(&s1,&s[2]);
	stack_push(&s1,&s[3]);
	stack_push(&s1,&s[4]);

//	stack_push(&s1,20);
//	stack_push(&s1,30);
//	stack_push(&s1,40);
//	stack_push(&s1,11);
//	stack_push(&s1,12);
//	stack_push(&s1,13);
//	stack_push(&s1,14);
	printf("items in stack are \n");
	while(!stack_is_empty(&s1))
	{
		stack_pop(&s1,&item);
		printf("%ld\n",item.data);
	}
	return 0;
}
