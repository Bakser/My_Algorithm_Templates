//bzoj1823
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define N 2000
#define MIN(a,b) (((a)<(b))?(a):(b))
struct hh
{
	int next,v;
}edges[30000];
int T,n,m,dfn[N],low[N],stack[N],id[N],top,tot,cnt,point[N];
char c1,c2;
bool in[N];
inline void addedge(int u,int v)
{
	static int en(0);
	edges[++en].next=point[u];
	point[u]=en;
	edges[en].v=v;
}
inline void tarjan(int x)
{
	low[x]=dfn[x]=++tot;in[x]=1;stack[top++]=x;
	for(int i=point[x];i;i=edges[i].next)
	if(!dfn[edges[i].v]){
		tarjan(edges[i].v);
		low[x]=MIN(low[x],low[edges[i].v]);
	}
	else if(in[edges[i].v])low[x]=MIN(low[x],dfn[edges[i].v]);
	if(dfn[x]==low[x])
	{
		int v;
		cnt++;
		do
		{
			v=stack[--top];
			in[v]=0;
			id[v]=cnt;
		}
		while(x!=v);
	}
}
inline bool solve()
{
	tot=cnt=top=0;
	memset(dfn,0,sizeof(dfn));
	for(int i=2;i<=(n<<1^1);i++)
		if(!dfn[i])tarjan(i);
	for(int i=1;i<=n;i++)
		if(id[i<<1]==id[i<<1^1])return 0;
	return 1;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		memset(point,0,sizeof(point));
		scanf("%d%d",&n,&m);
		for(int i=1,x,y;i<=m;i++)
		{
			scanf(" ");
			scanf("%c%d %c%d",&c1,&x,&c2,&y);
			addedge(x<<1^(c1=='m'),y<<1^(c2!='m'));
			addedge(y<<1^(c2=='m'),x<<1^(c1!='m'));
		}
		puts(solve()?"GOOD":"BAD");	
	}
	return 0;
}
