#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct pqitem{
	int key;
	void *data;
	int dsz;
};
struct pqueue{
	struct pqitem *q;
	int  size;
	int noitem;
};
int maxq_isempty(struct pqueue *pq)
{
	if(pq->noitem==0)
		return 1;
	return 0;
}
int maxq_init(struct pqueue *pq,int size)
{
	pq->size=0;
	pq->noitem=0;
	pq->q=malloc(size*sizeof(struct pqitem));
	if(!pq->q)
	{
		return 0;
	}
	pq->size=size;
	return 1;
}

void maxq_heapifydown(struct pqueue *pq, int pos)
{
	int lchild,rchild,j;
	struct pqitem temp;
	if((2*pos+2)<pq->noitem )
	{
		// both left and right child are in tree
		lchild=2*pos+1;
		rchild=2*pos+2;
		if(pq->q[lchild].key > pq->q[rchild].key)
			j=lchild;
		else
			j=rchild;
	}
	else if ((2*pos+1) < pq->noitem)
	{
		// only left child is in the tree
		j=2*pos+1;
	}
	else
	{
		return ;
	}
	if(pq->q[j].key > pq->q[pos].key)
	{
		temp=pq->q[j];
		pq->q[j]=pq->q[pos];
		pq->q[pos] = temp;
		maxq_heapifydown(pq,j); 
	}
	
}
void maxq_heapifyup(struct pqueue *pq,long pos)
{
	int parent;
	struct pqitem temp;
	if(pos>0)
	{
		parent=(pos-1)/2;
		if(pq->q[parent].key < pq->q[pos].key)
		{
			temp=pq->q[pos];
			pq->q[pos]=pq->q[parent];
			pq->q[parent]=temp;
			maxq_heapifyup(pq,parent);
		}
	}
}
int maxq_insert(struct pqueue *pq,int key)
{
	int parent;
	if(pq->size==pq->noitem)
	{
		return 0;
	}
	pq->q[pq->noitem].key=key;
	pq->noitem++;
	maxq_heapifyup(pq,pq->noitem-1);
	return 1;	
}
void maxq_delete(struct pqueue *pq,int pos)
{
	int lchild,rchild,parent;
	if(pq->noitem >1)
	{
		pq->q[pos]=pq->q[pq->noitem-1];
		pq->noitem--;
		parent=(pos-1)/2;
		lchild=2*pos+1;
		rchild=2*pos+2;
		if(pq->q[pos].key < pq->q[parent].key)
		{
			maxq_heapifyup(pq,pos);	
		}
		else
		{
			maxq_heapifydown(pq,pos);
		}
	}
	else if (pq->noitem==1)
	{
		pq->noitem--;
	}	
}
struct pqitem * maxq_extractmin(struct pqueue *pq)
{
	struct pqitem *min;
	min=malloc(sizeof(struct pqitem) );
	memcpy(min,pq->q,sizeof(struct pqitem));
	maxq_delete(pq,0);
	return min;
}
int main()
{
	
	long arr[]={100,232,2434,2,900,45,8,300,1,54,23,88,13,21, 12, 33, 87},i,j;
	struct pqueue pq;
	if(!maxq_init(&pq,sizeof(arr)/sizeof(arr[0])) )
	{
		exit(1);	
	}
	
	for(i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		maxq_insert(&pq,arr[i]);
		for(j=0;j<(&pq)->noitem;j++)
		{
			printf("%d ",(&pq)->q[j].key);
		}
		printf("\n");	
	}
	
	for(i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		printf("%d ",maxq_extractmin(&pq)->key);	
	}
	printf("\n");
}
