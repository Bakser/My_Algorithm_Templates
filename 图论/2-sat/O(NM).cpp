//hdu1814 ×ÖµäĞò×îĞ¡ 
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 20000
#define M 100000
struct hh
{
	int next,v;
}edges[M];
int n,m,point[N],s[N],top,en;
bool mark[N];
inline void addedge(int u,int v)
{
	edges[++en].next=point[u];
	edges[en].v=v;
	point[u]=en;
}
inline bool dfs(int x)
{
	if(mark[x])return 1;
	if(mark[x^1])return 0;
	mark[x]=1;
	s[top++]=x;
	for(int i=point[x];i;i=edges[i].next)
	if(!dfs(edges[i].v))
	return 0;
	return 1;
}
inline bool solve()
{
	for(int i=0;i<(n<<1);i+=2)
	if(!mark[i]&&!mark[i^1])
	{
		top=0;
		if(!dfs(i))
		{
			while(top)mark[s[--top]]=0;
			if(!dfs(i^1))return 0;
		}
	}
	return 1;
}
inline void init()
{
	memset(point,0,sizeof(point));
	memset(mark,0,sizeof(mark));
	top=en=0;
}
int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		init();
		for(int i=0,u,v;i<m;i++)
		{
			scanf("%d%d",&u,&v);
			u--;v--;
			addedge(u,v^1);
			addedge(v,u^1);
		}
		if(!solve())puts("NIE");
		else
		{
			for(int i=0;i<(n<<1);i++)
			if(mark[i])printf("%d\n",i+1);
		}
	}
	return 0;
}
