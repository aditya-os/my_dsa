#include<stdio.h>
int binary_Search(long long  *arr,long long size ,long long key)
{
	long long hi,lo,mid;
	hi=size-1;
	lo=0;
	while(lo<=hi)
	{
		mid=lo+(hi-mid)/2;
		if(arr[mid]==key)
		{
			return mid;
		}
		else if(arr[mid]< key)
		{
			lo=mid+1;
		}
		else
		{
			hi=mid-1;
		}
				
	}
		return -1;
}

int main()
{
	
}
