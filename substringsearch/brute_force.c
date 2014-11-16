#include<stdio.h>
#include<string.h>
int brute_force_substring_search(char *text,char *pattern)
{
	int i,j;
	int n,m;
	n=strlen(text);
	m=strlen(pattern);
	for(i=0;i<n-m;i++)
	{
		for(j=0;j<m;j++)
		{
			if(text[i+j]!=pattern[j])
				break;
		}
		if(j==m)
			return i;
	}
	return -1;
}

int main()
{
	char text[1000000],pattern[2000];
	scanf("%s",text);
	scanf("%s",pattern);
	printf("Pattern Matches at index %d\n",brute_force_substring_search(text,pattern));	
	return 0;
}
