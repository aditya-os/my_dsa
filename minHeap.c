#include<stdio.h>
#include<stdlib.h>
struct heap{
	long  *h;
	long  size;
	long no_element;
};
int heap_initialize(struct heap *heap,long size)
{
	heap->size=0;
	heap->no_element=0;
	heap->h=malloc(sizeof(long)*size);
	if(heap->h)
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
			minheap_heapify_up(heap,parent);
		}
	}
}
int minheap_insert(struct heap *heap,long key)
{
	if(heap->no_element >= heap->size)
	{
		return 0;
	}
	heap->h[heap->no_element]=key;
	minheap_heapify_up(heap,heap->no_element);
	(heap->no_element)++;
}
int minheap_heapify_down(struct heap *heap,long i)
{
	long length=heap->no_element,j,left_child,right_child,temp;
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
		minheap_heapify_down(heap,j);
	}
	return 1;		
}
int minheap_delete(struct heap *heap,long i)
{
	long parent,lchild,rchild;
	if(heap->no_element > 1)
	{
		heap->h[i]=heap->h[heap->no_element-1];
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
		return 1;
	}
	else if (heap->no_element == 1)
	{
		heap->h[i]=0;
		(heap->no_element)--;
		return 1;
	}
	return 0;
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
		minheap_insert(&h1,arr[i]);
		printf("size of heap %ld \n",h1.no_element);
		for(j=0;j<h1.no_element;j++)
		{
			printf(" %ld",h1.h[j]);
		}
		printf("\n");
	}
	printf("\n");
	for(i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		printf("Extracting eleemnt %ld\n",minheap_extractMin(&h1));
//		printf("element in heap ");
//		for(j=0;j<h1.no_element;j++)
		{
//			printf(" %ld",h1.h[j]);
		}
		printf("\n");
	}
	return 0;
}
