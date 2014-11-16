#include<stdio.h>
#include<stdlib.h>
long long max(long long a, long long b)
{
	if(a>b)
	{
		return a; 
	}
	else
	{
		return b;
	}
}
int main()
{
	long long w,size,i,j;
	long long **a,*v,*wt;
	scanf("%lld %lld",&w,&size);
	v=malloc(sizeof(long long)*(size+1));	
	wt=malloc(sizeof(long long)*(size+1));	
	for(i=1;i<=size;i++)
	{
		scanf("%lld %lld",&v[i],&wt[i]);
//		printf("%lld %lld\n",v[i],wt[i]);
	}
	a=malloc( sizeof(long long *)*(2));
	for(i=0;i<2;i++)
	{
		a[i]=malloc(sizeof(long long)*(w+1));
	}
	for(i=0;i<=w;i++)
	{
		a[0][i]=0;
	}
	for(i=1;i<=size;i++)
	{
		for(j=0;j<=w;j++)
		{
			if(j-wt[i]>=0)
				a[i%2][j]=max(a[(i-1)%2][j],a[(i-1)%2][j-wt[i]]+v[i]);
			else
				a[i%2][j]=a[(i-1)%2][j];
		}
	}
	
	printf("Value of knapsack %lld \n",a[i-1][w]);	
	return 0;
}
