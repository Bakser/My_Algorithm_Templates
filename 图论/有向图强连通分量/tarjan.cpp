#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 100
#define M 10000
#define MIN(a,b) (((a)<(b))?(a):(b))
struct hh
{
	int v,next;
}edges[M];
int n,m,dfn[N],low[N],stack[N],top,point[N],times,tot,belong[N];
bool instack[N];
inline void addedge(int u,int v)
{
	static int en=-1;
	edges[++en].next=point[u];
	edges[en].v=v;
	point[u]=en;
}
inline void dfs(int u)
{
	dfn[u]=low[u]=++times;
	instack[u]=true;
	stack[++top]=u;
	for(int i=point[u];i!=-1;i=edges[i].next)
	if(!dfn[i])
	{
		dfs(edges[i].v);
		low[u]=MIN(low[u],low[edges[i].v]);
	}
	else if(instack[u])low[u]=MIN(low[u],dfn[edges[i].v]);
	if(low[u]==dfn[u])
	{
		tot++;
		int v;
		do
		{
			v=stack[top--];
			belong[v]=tot;
			instack[v]=false;
		}
		while(v!=u);
	}
}
int main()
{
	memset(point,0xff,sizeof(point));
	scanf("%d%d",&n,&m);
	for(int i=0,u,v;i<m;i++)
	{
		scanf("%d%d",&u,&v);
		addedge(u,v);
	}
	memset(dfn,0,sizeof(dfn));
	top=-1;times=tot=0;
	for(int i=1;i<=n;i++)
	if(!dfn[i])dfs(i);
	for(int i=1;i<=n;i++)
	printf("%d:%d\n",i,belong[i]);
	return 0;
}
