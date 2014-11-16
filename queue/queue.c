#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
	long long data;
	int size;
	struct node *next;
};
struct queue{
	struct node *first;
	struct node *last;
};
void queue_initialize(struct queue *q)
{	
	q->first=NULL;
	q->last=NULL;
}
int enqueue(struct queue *q,struct node *d)
{
//	struct node *oldlast;
	struct node *new_item;
//	oldlast=q->last;
	new_item=malloc(sizeof(struct node ));
	if(new_item)
	{
		memcpy(&(new_item->data),&(d->data),d->size);
		new_item->size=d->size;
		new_item->next=NULL;
		if(q->last!=NULL)
			q->last->next=new_item;
		else
			q->first=new_item;
		q->last=new_item;
//		printf("first %p last  %p \n",q->first,q->last);
		return 1;
	}
	return 0;	
}
int dequeue(struct queue *q,struct node *d )
{
	struct node *item=NULL;
	struct node *next;
	if(q->first)
	{
		memcpy(&(d->data),&(q->first->data),q->first->size);
		d->size = q->first->size;
		d->next=NULL;
		next=q->first->next;
		free(q->first);
		q->first=next;
		if(q->first==NULL)
			q->last=NULL;

//		printf("first %p last  %p \n",q->first,q->last);

		return 1;				
	}
	return 0;
}
int main()
{
	int i;
	struct queue q;
	struct node item;
	item.size=sizeof(item.data);
	item.next=NULL;
	queue_initialize(&q);
	for(i=1;i<5;i++)
	{
		item.data=i*10;
		enqueue(&q,&item);
	}		
	for(i=1;i<5;i++)
	{
//		item.data=i*10;
		dequeue(&q,&item);
		printf("%lld\n",item.data);
	}
	return 0;
}
