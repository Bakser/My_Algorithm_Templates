#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue> 
using namespace std;
#define N 10000
#define MIN(a,b) (((a)<(b))?(a):(b))
#define INF 0x3f3f3f3f
struct hh
{
	int u,v,next,cost,cap;
}edges[N];
int point[N],n,m,a,b,c,co,cost,d[N],s,t,en;
bool vis[N];
void addedge(int u,int v,int cap,int cost)
{
	edges[++en].next=point[u];
	point[u]=en;
	edges[en].u=u;
	edges[en].v=v;
	edges[en].cap=cap;
	edges[en].cost=cost;
	edges[++en].next=point[v];
	point[v]=en;
	edges[en].u=v;
	edges[en].v=u;
	edges[en].cap=0;
	edges[en].cost=-cost;
}
bool spfa()
{
	queue<int> q;
	memset(d,0x3f,sizeof(d));
	d[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=point[x];i!=-1;i=edges[i].next)
		if(edges[i].cap&&d[edges[i].v]>d[x]+edges[i].cost)
		{
			d[edges[i].v]=d[x]+edges[i].cost;
			q.push(edges[i].v);
		}
	}
	return d[t]<INF;
}
int augment(int x,int m)
{
	if(x==t)return cost+=d[t]*m,m;
	vis[x]=true;
	int l=m;
	for(int i=point[x];i!=-1;i=edges[i].next)
	if(edges[i].cap&&d[edges[i].v]==d[x]+edges[i].cost&&!vis[edges[i].v])
	{
		int d=augment(edges[i].v,MIN(edges[i].cap,l));
		edges[i].cap-=d;
		edges[i^1].cap+=d;
		l-=d;
		if(!l)return m;
	}
	return m-l;
}
void mcmf()
{
	cost=0;
	while(spfa())
		do memset(vis,0,sizeof(vis));
		while(augment(s,INF));	
}
int main()
{
	scanf("%d%d",&n,&m);
	en=-1;
	memset(point,0xff,sizeof(point));
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&a,&b,&c,&co);
		addedge(a,b,c,co);
	}
	scanf("%d%d",&s,&t);
	mcmf();
	printf("%d\n",cost);
	return 0;
}
