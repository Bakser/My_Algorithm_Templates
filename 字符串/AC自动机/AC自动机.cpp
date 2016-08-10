#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
#define N 10000
#define M 22
#define LEN 100
#define idx(x)(x-'a')
#define maxsize 26
int ch[N][27],val[N],f[N],last[N],tot,n;
char mode[M][LEN],s[LEN];
inline void insert(char* t,int tag)
{
	int len=strlen(t),pos=0;
	for(int i=0;i<len;i++)
	{
		if(!ch[pos][idx(t[i])])ch[pos][idx(t[i])]=tot++;
		pos=ch[pos][idx(t[i])];
	}
	val[pos]=tag;
}
inline void build_trie()
{
	tot=1;
	for(int i=1;i<=n;i++)
		insert(mode[i],i);
}
inline void build_AC_automachine()
{
	queue<int> q;
	f[0]=0;
	for(int i=0;i<maxsize;i++)
	if(ch[0][i])
	{
		f[ch[0][i]]=last[ch[0][i]]=0;
		q.push(ch[0][i]);
	}
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=0,u;i<maxsize;i++)
		{
			u=ch[x][i];
			if(!u){ch[x][i]=ch[f[x]][i];continue;}
			q.push(u);
			int v=f[x];
			while(v&&!ch[v][i])v=f[v];
			f[u]=ch[v][i];
			last[u]=val[f[u]]?f[u]:last[f[u]];
		}
	}
}
inline void print(int pos,int x)
{
	if(x)
	{
		printf("%d %d\n",pos,val[x]);
		print(pos,last[x]);
	}
}
inline void find(char* t)
{
	int len=strlen(t);
	int j=0;
	for(int i=0;i<len;i++)
	{
		int c=idx(t[i]);
		j=ch[j][c];
		if(val[j])print(i+1,j);
		else if(last[j])print(i+1,last[j]);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%s",mode[i]);
	build_trie();
	build_AC_automachine();
	scanf("%s",s);
	find(s);
	return 0;
}
