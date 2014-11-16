#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct segtree_node
{
	int data;
};
int findstsize(int n)
{
	int size=1;
	while(size<n)
	{
		size=size<<1;
	}
	return size;
}
struct segtree_node * init_create_st(int sz)
{
	struct segtree_node *st;
	st=malloc(sizeof(struct segtree_node)*(sz+1));
	if(!st)
		return NULL;
	memset(st,0,sizeof(struct segtree_node)*(sz+1));
	return st;
}
int min(int a,int b)
{
	return a<b?a:b;
}
void build_st(int *arr, int n,struct segtree_node * st, int stindex, int lo, int hi)
{
	int mid,left,right;
	if(lo==hi)
	{
		st[stindex].data=arr[lo];
		return;
	}
	mid=(lo+hi)/2;
	left=2*stindex;
	right=2*stindex+1;
	//building left subtree 
	build_st(arr,n,st,left,lo,mid);
	// building right subtree
	build_st(arr,n,st,right,mid+1,hi);
//	Based on what st does modify the operation accodingly
//	st.[stindex].data=operation(st[left].data,st[right]);
	st[stindex].data=min(st[left].data,st[right].data);
	
}

int query_st(struct segtree_node *st,int stindex,int left, int right,int lo, int hi)
{
	int mid,leftindex,rightindex;
	int leftresult,rightresult,result=0;
	if(lo==left && hi==right)
		return st[stindex].data;

	mid=(left+right)/2;
	leftindex=2*stindex;
	rightindex=2*stindex+1;
	// results completely in either left subtree or right subtree
	if(lo>mid)
		return query_st(st,rightindex,mid+1,right,lo,hi);
	if(hi>=mid)
		return query_st(st,leftindex,left,mid,lo,hi);
	//results are split in left subtree and right subtree 
	leftresult=query_st(st,leftindex,left,mid,lo,hi);
	rightresult=query_st(st,rightindex,mid+1,right,lo,hi);
//	result=operation(leftresult,rightresult)
	result=min(leftresult,rightresult);
	return result;	
}
int main()
{
	int *inpt;
	struct segtree_node *st;
	int n,i,st_size,lo,hi,res;
	scanf("%d",&n);
	inpt=malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	{	
		scanf("%d",&inpt[i]);
	}
	st_size=findstsize(n);
	st=init_create_st(st_size);
	build_st(inpt,n,st,1,0,n-1);
	while(1)	
	{
		printf("Input query range\n");
		scanf("%d %d",&lo,&hi);
		res=query_st(st,1,0,n-1,lo,hi);
		printf("Ans = %d \n",res);	
	}
	return 0;	
	
}
