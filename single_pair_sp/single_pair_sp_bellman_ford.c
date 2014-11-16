#include<stdio.h>
#include<stdlib.h>
#define INFINITY (1ll<<62)

struct edge{
	long cost;
	long to;
	int in;
	struct edge *e;
};
struct vertex{
	long name;
	struct edge *e;
};

struct graph{
	long size;
	struct vertex *v;	
};



struct heap{
	long  *h;
	long *name,*position;
	long  size;
	long no_element;
};

int graph_initialize(struct graph *g,long size)
{
	long node_index;
	g->v=malloc(sizeof(struct vertex)*size);
	if(!g->v)
	{
		printf("No memory allocatedfor nodes\n");
		return 0;
	}
	g->size=size;
	for(node_index=0;node_index<size;node_index++)
	{
	//	printf("currently no edge\n");
		g->v[node_index].e=NULL;
	}
	return 1;
}

int graph_insert_node(struct graph * g, long node_index, long name)	// the node index should be zero based
{
	if(g->v==NULL || node_index >= g->size )
	{
		return 0;
	}
	g->v[node_index].name=name;
}
int vertex_insert_edge(struct vertex *v,long cost,long to,int in)
{
	struct edge *e;
	if(v==NULL)
	{
		return 0;
	}
	e=malloc(sizeof(struct edge));
	if(e==NULL)
	{
		return 0;
	}
	e->cost=cost;
	e->to=to;
	e->in=in;
	e->e=v->e;
	v->e=e;
	return 1;	

}
int graph_insert_edge(struct graph *g, long from_node, long cost,long to_node,int in)
{
	if( g->v==NULL || from_node >=g->size)
	{
		return 0;
	}	
	if(  ! vertex_insert_edge( &(g->v[from_node]) , cost, to_node,in)  )
	{
		printf("Failed to insert edge %ld to %ld \n",from_node, to_node);
		return 0;	
	}
	return 1;
}
struct edge * graph_get_edges(struct graph *g,long vertex)
{
	return ((g->v[vertex]).e) ;
}

long graph_get_size(struct graph *g)
{
	return g->size;
}
long long min(long long a,long long b)
{
	if(a < b )
	 	return a;
	else
		return b;
}

long long  bellman_ford(struct graph *g,long s,long t)
{
	
	struct edge *e;
	long long **a;
	long long i,j,k,pseduok,min_wj;
	a=malloc(sizeof(long long *)*(graph_get_size(g)));

 	for(i=0;i<graph_get_size(g);i++)
	{
		a[i]=malloc(sizeof(long long)*(graph_get_size(g)));
	}


	for(i=0;i<graph_get_size(g);i++)
	{
		a[0][i]=INFINITY;
	}
	a[0][s]=0;

	for(i=1;i<graph_get_size(g);i++)
	{
		for(j=0;j<graph_get_size(g);j++)
		{		
			e=graph_get_edges(g,j);
			min_wj=a[i-1][j];
			while(e)
			{
				if(e->in)
				{
					min_wj=min(min_wj,a[i-1][e->to]+e->cost);
				}
				e=e->e;
			}
			a[i][j]=min(a[i-1][j],min_wj);
		}			
	}
/*	printf("Path from %ld : ",s);
	for(i=0;i<graph_get_size(g);i++)
	{
		printf("%lld\t",a[graph_get_size(g)-1][i]);
	}
	printf("\n");
*/
	return a[graph_get_size(g)-1][t];

}

int main()
{
	struct graph g;
	struct edge *e;
	long long a,shortest;
	long no_vertex,no_edges,from,to,i,cost,j,k,pseduok;
	scanf("%ld %ld",&no_vertex,&no_edges);
	graph_initialize(&g,no_vertex);	
	for(i=0;i<=no_vertex;i++)
	{
		graph_insert_node(&g,i,i);	
	}
	for(i=0;i<no_edges;i++)
	{
		scanf("%ld %ld %ld",&from,&to,&cost);
		graph_insert_edge(&g,from-1,cost,to-1,0);
		graph_insert_edge(&g,to-1,cost,from-1,1);
	}
		
	a=bellman_ford(&g,398,903);
/*	for(i=1;i<no_vertex+1;i++)
	{
		if(a[i][i][0]<0)
		{
			printf("graph has negative cycle at %ld\n",i);
			return 0;
			//break;
		}
		
	}
		
	shortest=0;
	for(i=1;i<no_vertex+1;i++)
	{
		for(j=1;j<no_vertex+1;j++)
		{
			shortest=min(shortest,a[i][j][0]);			
		}	
	}
*/
	printf("shortest path %lld\n",a);
	
//	printf("%d %lld \n",sizeof(long long), 1ll<<62 );	
	

	return 0;
}


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
	return 1;
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
