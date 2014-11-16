#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
struct rbnode{
	int key;
	void *value;
	int dsz;
	int size;
	char color;
	struct rbnode *lchild;
	struct rbnode *rchild;
};
struct rbtree {
	struct node *root;
};
int rbt_isred(struct rbnode *r)
{
	if(r==NULL)
		return 0;
	if(r->color=='R')
		return 1;
	else
		return 0;
}
struct rbnode* rbt_rotate_left(struct rbnode *r)
{
	struct rbnode *rtree;
	assert(rbt_isred(r->rchild));
	rtree=r->rchild;
	r->rchild=rtree->lchild;
	rtree->lchild=r;
	rtree->color=r->color;
	r->color='R';
	return rtree;
	
}
struct rbnode* rbt_rotate_right(struct rbnode *r)
{
	struct rbnode *ltree;
	assert(rbt_isred(r->lchild));
	ltree=r->lchild;
	r->lchild=ltree->rchild;
	ltree->rchild=r;
	ltree->color=r->color;
	r->color='R';
	return ltree;
	
}
void rbt_flipcolor(struct rbnode * root)
{
	assert(!rbt_isred(root));
	assert(rbt_isred(root->lchild));
	assert(rbt_isred(root->rchild));
	root->color='R';
	root->lchild->color='B';
	root->rchild->color='B';
}
void rbt_node_init(struct rbnode *r)
{
	if(!r)
		return ;
	r->lchild=NULL;
	r->rchild=NULL;
	r->size=1;
	r->color='R';
	r->value=NULL;
	r->dsz=0;
	return;
}
void rbt_node_fill(struct rbnode *r,int key, void *val,int szval)
{
	if(!r)
		return;
	r->key=key;
	r->value=val;
	r->dsz=szval;
}
struct rbnode * rbt_insert_node(struct rbnode *r,int key,void *val,int szval)
{
	if(r==NULL)
	{
		struct rbnode *item;
		item=malloc(sizeof(struct rbnode));
		if(!item)
			return NULL;
		rbt_node_init(item);
		rbt_node_fill(item,key,val,szval);
		return item;		
	}
	if(key < r->key)
	{
		r->lchild=rbt_insert_node(r->lchild,key,val,szval);
	}
	else if (key > r->key)
	{
		r->rchild=rbt_insert_node(r->rchild,key,val,szval);
	}
	else
	{
		r->dsz=szval;
	}
	
	if(rbt_isred(r->rchild) && !rbt_isred(r->lchild))
	{
		r=rbt_rotate_left(r);
	}
	if(rbt_isred(r->lchild) && rbt_isred(r->lchild->lchild))
	{	
		r=rbt_rotate_right(r);
	}
	if(rbt_isred(r->lchild) && rbt_isred(r->rchild))
	{
		rbt_flipcolor(r);
	}

	return r;
}
struct rbnode * rbt_search_node(struct rbnode *root,int key)
{
	while(root!=NULL)
	{
		if(key < root->key)
		{
			root=root->lchild;
		}
		else if (key > root->key)
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


int main()
{	
	return 0;
}
