#include<stdio.h>
#include<stdlib.h>
struct unionfind
{
	long long *id;
	long long *szcomp;
	long long  size;
};
int unionfind_initialize(struct unionfind *uf,long n)
{
	long i;
	uf->id=malloc(sizeof( long long)*n);
	uf->szcomp=malloc(sizeof(long long)*n);
	if(uf->id==NULL || uf->szcomp==NULL)
	{
		if(uf->id)
		{
			free(uf->id);
		}
		if(uf->szcomp)
		{
			free(uf->szcomp);
		}
		return 0;
	}
	for(i=0;i<n;i++)
	{
		uf->id[i]=i;
		uf->szcomp[i]=1;
	}
	uf->size=n;
	return 1;
}
long long unionfind_root(struct unionfind *uf,long long i)
{
	while(i!=uf->id[i])
	{
		uf->id[i]=uf->id[uf->id[i]];
		i=uf->id[i];
	}
	return i;
}
int unionfind_connected(struct unionfind *uf,long long p,long long q)
{
	return unionfind_root(uf,p) == unionfind_root(uf,q);
}
int unionfind_union(struct unionfind *uf,long long p, long long q)
{
	long long rootp,rootq;
	rootp=unionfind_root(uf,p);
	rootq=unionfind_root(uf,q);
	if(uf->szcomp[rootp] < uf->szcomp[rootq])
	{
		uf->id[rootp]=rootq;
		uf->szcomp[rootq] += uf->szcomp[rootp];
	}
	else
	{

		uf->id[rootq]=rootp;
		uf->szcomp[rootp] += uf->szcomp[rootq];
	}
}
int main()
{
	struct unionfind u;
	long n=100;
	if(!unionfind_initialize(&u,n))
	{
		printf("UnionFind:Initialization failed\n");
	}
	return 0;
}
