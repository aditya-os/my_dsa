#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
	int key;
	void *value;
	int szval;
	int size;
	int height;
	struct node *lchild;
	struct node *rchild;
};
struct tree {
	struct node *root;
};
int max(int a,int b)
{
	return a>=b?a:b;
}
int bst_node_init(struct node *t)
{
	if(!t)
		return 0;
	t->key=0;
	t->lchild=NULL;
	t->rchild=NULL;
	t->value=NULL;
	t->size=1;
	t->szval=0;
	t->height=1;	
	return 1;
}
struct node * bst_search(struct node *root,int key)
{
	while(root!=NULL)
	{
		if(key < root->key)
		{
			root=root->lchild;
		}
		else if (key>root->key)
		{
			root=root->rchild;
		}
		else
		{
			return root;
		}
	}
	return NULL;
}
void bst_fill_node(struct node *t,int key,void *value, int szval)
{
	if(!t)
		return;
	t->key=key;
	t->value=value;
	t->szval=szval;
}
int sizeoftree(struct node *r)
{
	if (!r)
		return 0;
	return r->size;
}
int bst_size_of_tree(struct tree *t)
{
	return sizeoftree(t->root);
}
int bst_height(struct node *r)
{
	if(!r)
		return 0;
	return r->height;
}
struct node * bst_insert_node(struct node *r,int key, void * value,int szval)
{
	struct node *item;
	if(r==NULL)
	{
		item=malloc(sizeof(struct node));
		if(!item)
			return NULL;
		bst_node_init(item);
		printf("Inserting element %d at address %p\n",key,item);
		bst_fill_node(item,key,value,szval);
		return item;
	}
	if(key < r->key)
	{
		printf ("%d ",r->key);
		r->lchild=bst_insert_node(r->lchild,key,value,szval);	
	}
	else if(r->key < key)
	{
		printf ("%d ",r->key);
		r->rchild=bst_insert_node(r->rchild,key,value,szval);
	}
	else
	{
		r->value=value;
		r->szval=szval;
	}
	r->size=1+sizeoftree(r->lchild)+sizeoftree(r->rchild);
	r->height=max(bst_height(r->lchild),bst_height(r->rchild))+1;
		
	return r;
}
void bst_insert(struct tree *t,int key,void *val,int szval)
{
	t->root=bst_insert_node(t->root,key,val,szval);
}
void bst_init(struct tree *t)
{
	t->root=NULL;
}

void bst_inorder(struct node *r)
{
	if(r==NULL)
		return;
	bst_inorder(r->lchild);
	printf("%d ", r->key);
	bst_inorder(r->rchild);
}
void bst_inorder_traversal(struct tree *t)
{
	if(!t)
		return;
	bst_inorder(t->root);	
}
struct node * bst_min_node(struct node *r)
{
	struct node *root,*lchild;
	root=r;
	if(!root)
		return NULL;
	lchild=root->lchild;
	while(lchild)
	{
		root=lchild;
		lchild=root->lchild;
	}
	return root;
}
struct node * bst_max_node(struct node *r)
{
	struct node *root,*rchild;
	root=r;
	if(!root)
		return NULL;
	rchild=root->rchild;
	while(rchild)
	{
		root=rchild;
		rchild=root->rchild;
	}
	return root;
}
struct node * bst_min(struct tree *t)
{
	if(!t->root)
		return bst_min_node(t->root);	
	return NULL;
}
struct node * bst_max(struct tree *t)
{
	if(!t->root)
		return bst_max_node(t->root);
	return NULL;
}

int bst_count_lt_key(struct node *r,int key)
{
  	if(!r)
		return 0;
	if(key < r->key)
	{
		return bst_count_lt_key(r->lchild,key);
	}
	else if (r->key< key)
	{
		return 1 + sizeoftree(r->lchild) + bst_count_lt_key(r->rchild,key);
	}
	else
	{
		return sizeoftree(r->lchild);
	}
			
}
int bst_elements_lt_key(struct tree *t,int key)
{
	return bst_count_lt_key(t->root,key);
}
struct node * bst_del_min_node(struct node *r)
{
	struct node *rchild;
	if(r->lchild==NULL)
	{
		rchild=r->rchild;
		free(r);
		return rchild;
	}
	r->lchild=bst_del_min_node(r->lchild);
	r->size=1+sizeoftree(r->lchild)+sizeoftree(r->rchild);
	return r;
}



void bst_del_min(struct tree *t)
{
	if(!t->root)
		bst_del_min_node(t->root);		
}

struct node * bst_floor_node(struct node *r,int key)
{
	struct node *t;
	if(r==NULL)
		return NULL;
	if( key < r->key )
	{
		printf("%d ",r->key);
		return bst_floor_node(r->lchild,key);
	}
	else if ( key > r->key)
	{	
		printf("%d ",r->key);
		t=bst_floor_node(r->rchild,key);

		if(t!=NULL)
			return t;
		return r;
	}
	else
	{
		return r;
	}

}
void bst_floor(struct tree *t,int key)
{
	struct node *n;
	if(t->root)
	{
		printf("\nFinding floor\n");
		n=bst_floor_node(t->root,key);
		if(n)
			printf(" floor of Key %d is %d\n",key,n->key);
	}	
}

struct node * bst_del_node_key(struct node * r, int key)
{
	struct node *succ,*succmin,*rchild,*lchild;
	if(r==NULL)
		return NULL;
	if(key < r->key)
	{
		bst_del_node_key(r->lchild,key);
	}
	else if(r->key < key )
	{
		bst_del_node_key(r->rchild,key);
	}
	else
	{
		if(r->rchild==NULL)
			return r->lchild;
		//succ=malloc(sizeof(struct node));
		//if(!succ)
		//	return r;
		lchild=r->lchild;
		succmin=bst_min_node(r->rchild);	
		memcpy(r,succmin,sizeof(struct node));
		r->rchild=bst_del_min_node(r->rchild);
		r->lchild=lchild;
		
	}
	r->size=1+sizeoftree(r->lchild)+sizeoftree(r->rchild);
	return r;
}
void bst_del_key(struct tree *t,int key)
{
	if(!t->root)
		t->root=bst_del_node_key(t->root,key);
}



struct node * bst_ceiling_node(struct node *r,int key)
{
	struct node *t;
	if(r==NULL)
		return NULL;
	if( key < r->key )
	{
		printf("%d ",r->key);
		t=bst_ceiling_node(r->lchild,key);
		if(t!=NULL)
			return t;
		return r;
	}
	else if ( key > r->key)
	{	
		printf("%d ",r->key);
		return bst_ceiling_node(r->rchild,key);
	}
	else
	{
		return r;
	}

}
void bst_ceiling(struct tree *t,int key)
{
	struct node *n;
	if(t->root)
	{
		printf("\nFinding ceiling \n");
		n=bst_ceiling_node(t->root,key);
		if(n)
			printf(" floor of Key %d is %d\n",key,n->key);
	}	
}


int main()
{
	struct tree t1;
	long arr[]={100,232,2434,2,900,45,8,300,1,54,23,88,13,21, 12, 33, 87},i,j;
	bst_init(&t1);
	for(i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		bst_insert(&t1,arr[i],NULL,0);
	}
	printf("\n");
	bst_inorder_traversal(&t1);
	printf("\n");
//	printf("Size %d\n",sizeoftree((&t1)->root));
	bst_ceiling(&t1,25234);		
	printf("Size %d left half %d right half %d\n",bst_size_of_tree(&t1),sizeoftree((&t1)->root->lchild),sizeoftree((&t1)->root->rchild));
	return 0;
}
