#include<stdio.h>
#include<string.h>
void backuparray(char *pat,int m,int *backup)
{
	int len=0,i;
	backup[0]=0;
	i=1;
	for(i=1;i<m;)
	{
		if(pat[i]==pat[len])
		{
			len++;
			backup[i]=len;
			i++;
		}
		else
		{
			if(len!=0)
			{
				len=backup[len-1];		
			}
			else
			{
				backup[i]=0;
				i++;
			}
		}
	}
}

int kmp(char *text,int n, char *pat,int m)
{
	int i,j;
	int backup[10000];
	backuparray(pat,m,backup);
	j=0;
	for(i=0;i<n;)
	{
		if(text[i]==pat[j])
		{
			i++;
			j++;
			if(j==m)
				return (i-m);
		}
		else
		{
			if(j!=0)
				j=backup[j-1];
			else
				i++;
		}

	}	
}

/*int brute_force_substring_search(char *text,char *pattern)
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
*/
int main()
{
	char text[1000000],pattern[2000];
	scanf("%s",text);
	scanf("%s",pattern);
//	printf("Pattern Matches at index %d\n",brute_force_substring_search(text,pattern));	
	return 0;
}
