#include<stdio.h>
#include<stdlib.h>

struct heap{
	long  *h;
	long *name,*position;
	long  size;
	long no_element;
};
int heap_initialize(struct heap *heap,long size);
void minheap_heapify_up(struct heap *heap,long i);
int minheap_insert(struct heap *heap,long key,long *name);
long minheap_extractMin(struct heap *h);
int minheap_changeKey(struct heap *h,long e_name,long new_value);
int minheap_heapify_down(struct heap *heap,long i);
int minheap_delete(struct heap *heap,long i);

int heap_initialize(struct heap *heap,long size)
{
	heap->size=0;
	heap->no_element=0;
	heap->h=malloc(sizeof(long)*size);
	heap->name=malloc(sizeof(long)*size);
	heap->position=malloc(sizeof(long)*size);
	
	if(heap->h && heap->name && heap->position )
	{
		heap->size=size;
		return 1;
	}
	return 0;
}
void minheap_heapify_up(struct heap *heap,long i)
{
	long temp,parent;
	if(i>0)
	{
		parent=(i%2)?(i/2):(i/2-1);
		if( heap->h[i] < heap->h[parent]  )
		{
			temp=heap->h[i];
			heap->h[i]=heap->h[parent];
			heap->h[parent]=temp;
			
			temp=heap->name[i];
			heap->name[i]=heap->name[parent];
			heap->name[parent]=temp;
			
			heap->position[heap->name[parent]]=parent;
			heap->position[heap->name[i]]=i;	
			minheap_heapify_up(heap,parent);
		}
	}
}
int minheap_insert(struct heap *heap,long key,long *name)
{
	if(heap->no_element >= heap->size)
	{
		return 0;
	}
	heap->h[heap->no_element]=key;
	if(name)
	{
		heap->name[heap->no_element]=(*name);
		heap->position[*name]=heap->no_element;
	}
	else
	{
		heap->name[heap->no_element]=heap->no_element;
		heap->position[heap->name[heap->no_element]]=heap->no_element;
	}
	minheap_heapify_up(heap,heap->no_element);
	(heap->no_element)++;
}
int minheap_heapify_down(struct heap *heap,long i)
{
	long length=heap->no_element,j,left_child,right_child,temp;
	if(length <= 1)
	{
		return 0;
	}
	if((2*i+1)>length)
	{
		return 0;	
	}
	else if ((2*i+1)< length)
	{
		left_child=2*i+1;
		right_child=2*i+2;
		j= (heap->h[left_child] < heap->h[right_child] ) ? left_child : right_child ;
	}else if( 2*i+1 == length )
	{
		j=2*i+1;
	}
	
	if( heap->h[j] < heap->h[i])
	{
		temp=heap->h[j];
		heap->h[j]=heap->h[i];
		heap->h[i]=temp;
		
		temp=heap->name[j];
		heap->name[j]=heap->name[i];
		heap->name[i]=temp;

		heap->position[heap->name[i]]=i;
		heap->position[heap->name[j]]=j;

		minheap_heapify_down(heap,j);
	}
	return 1;		
}
int minheap_delete(struct heap *heap,long i)
{
	long parent,lchild,rchild;
	if(heap->no_element > 1)
	{
		heap->position[heap->name[i]]=-1;
		heap->h[i]=heap->h[heap->no_element-1];
		heap->name[i]=heap->name[heap->no_element-1];
		heap->position[heap->name[i]]=i;
		(heap->no_element)--;
		if(i)
			parent=(i%2)?(i/2):(i/2-1);
		else
			parent=0;
		lchild=2*i+1;
		rchild=2*i+2;
		if( heap->h[i] < heap->h[parent] )
		{	
			minheap_heapify_up(heap,i);
		}
		else
		{
			minheap_heapify_down(heap,i);
		}
	
		//(heap->no_element)--;
		return 1;
	}
	else if (heap->no_element == 1)
	{
//		heap->h[i]=0;
		heap->position[heap->name[i]]=-1;
		(heap->no_element)--;
		return 1;
	}
	return 0;
}
int minheap_changeKey(struct heap *h,long e_name,long new_value)
{
	long pos=h->position[e_name],parent;
	if(pos!=-1)
	{
		h->h[pos]=new_value;
//		printf("pos=%ld %ld\n",pos,h->h[pos]);
		if(pos)
			parent=(pos%2)?(pos/2):(pos/2-1);
		else
			parent=0;
		if(h->h[parent] > h->h[pos])
		{
			minheap_heapify_up(h,pos);
		}
		else
		{
			//Adjusting the number of element in heap 
			// This is necessary because no_element is the next position at which new element is to be inserted.
			//Since index is 0 based we no_element also indicate number of element in the heap. 
			//In 0 based index the last element of heap is at index no_element-1 .
			(h->no_element)--;
			minheap_heapify_down(h,pos);
			(h->no_element)++;
		}
	}
}
long minheap_extractMin(struct heap *h)
{
	long t=h->h[0];
	minheap_delete(h,0);
	return t;	
} 
int main()
{
	long arr[]={100,232,2434,2,900,45,8,300,1,54,23,88,13,21, 12, 33, 87},i,j;
	struct heap h1;
	heap_initialize(&h1,sizeof(arr)/sizeof(arr[0]));
	for(i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		printf("inserting elememt %ld \n",arr[i]);
		minheap_insert(&h1,arr[i],NULL);
//		for(j=0;j<h1.no_element;j++)
		{
//			printf(" %ld",h1.h[j]);
		}
		printf("\n");
		minheap_changeKey(&h1,i,arr[i]+22);
//		printf("size of heap %ld \n",h1.no_element);
		for(j=0;j<h1.no_element;j++)
		{
			printf(" %ld",h1.h[j]);
		}
		printf("\n");
	}
	printf("\n");

	for(i=0;i<h1.no_element;i++)
	{
		printf("%ld\t",h1.h[i]);
	}
	printf("\n");

	for(i=0;i<h1.no_element;i++)
	{
		printf("%ld\t",h1.name[i]);
	}
	printf("\n");
	for(i=0;i<h1.no_element;i++)
	{
		printf("%ld\t",h1.position[i]);
	}
	printf("\n");
	for(i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		printf("Extracting eleemnt %ld\n",minheap_extractMin(&h1));
/*		printf("element in heap ");
		for(j=0;j<h1.no_element;j++)
		{
			printf(" %ld\t",h1.h[j]);
		}
		printf("\n");
		printf("Name of element ");
		for(j=0;j<h1.no_element;j++)
		{
			printf(" %ld\t",h1.name[j]);
		}
		printf("\nPostion element ");
		for(j=0;j<sizeof(arr)/sizeof(arr[0]);j++)
		{
			printf(" %ld\t",h1.position[j]);
		}
*/
//		printf("\n");

	}
	for(i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		printf(" %ld",arr[i]+22);
	}
	printf("\n");
	return 0;
}
