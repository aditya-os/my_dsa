#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define R 26
struct node 
{
	int val;
	struct node *next[R];
};
struct tries{
	struct node *trie;
};
void trie_init(struct tries *t)
{
	t->trie=NULL;
}
struct node * trie_alloc_node()
{
	struct node *n;
	int i;
	n=malloc(sizeof(struct node));
	if(!n)
		return NULL;
	n->val=-1;
	for(i=0;i<R;i++)
		n->next[i]=NULL;
	return n;	
	
}

struct node * trie_insert_string_node(struct node *trie,char *s,int val,int pos)
{
	char c;
	if(trie == NULL)
	{
		trie=trie_alloc_node();
	}
	if(pos==strlen(s))
	{
		trie->val=val;
		return trie;
	}
	c=s[pos];
	trie->next[c-'a']=trie_insert_string_node(trie->next[c-'a'],s,val,pos+1);
	return trie;	
}
void trie_insert(struct tries *t,char *s,int val )
{
	t->trie=trie_insert_string_node(t->trie,s,val,0);
}
struct node * trie_get_node(struct node *trie,char *s, int pos)
{
	char c;
	if(trie==NULL)
		return NULL;
	if(pos==strlen(s))
		return trie;
	c=s[pos];
	return trie_get_node(trie->next[c-'a'],s,pos+1);
}
int trie_get(struct tries *t,char *s)
{
	struct node *k;
	k=trie_get_node(t->trie,s,0);
	if(!k)
	{		
		return -1;
	}
	return k->val;
}
void collect_keys(struct node *trie,char *prefix,int c)
{
	int i;
	if(trie==NULL)
		return;
	if(trie->val != -1)
	{	
		prefix[c]='\0';
		printf("%s\n",prefix);
	}
	for(i=0;i<R;i++)
	{
		if(trie->next[i])
		{	
			prefix[c]=i+'a';
			collect_keys(trie->next[i],prefix,c+1);
		}
	}
}
void keys(struct tries *t)
{
	char prefix[1000];
	collect_keys(t->trie,prefix,0);
}
void keyswithprefix(struct tries *t,char *prefix)
{
	struct node *prefixnode=NULL;
	char prefixkey[1000];
	strcpy(prefixkey,prefix);
	prefixnode=trie_get_node(t->trie,prefix,0);
	if(prefixnode)
	{
		printf("found prefix with acc\n");
		//collect_keys(prefixnode,prefixkey,strlen(prefix)+1);
		collect_keys(prefixnode,prefixkey,strlen(prefixkey));
	}
}
int main()
{
	int i;
	char word[200];
	struct tries words;
	trie_init(&words);
	for(i=0;i<10000;i++)
	{
		scanf("%s",word);
		trie_insert(&words,word,1);
	}
		
/*	for(i=0;i<1;i++)
	{
		printf("abacus is present in trie %d",trie_get(&words,"ab"));
	}			
*/
//	keys(&words);
	keyswithprefix(&words,"acc");
	return 0;
}
