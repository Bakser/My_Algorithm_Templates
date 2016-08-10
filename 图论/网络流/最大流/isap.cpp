//poj3469
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
#define M  500000
#define MIN(a,b) (((a)<(b))?(a):(b))
#define INF 0x3f3f3f3f
#define N 20100
struct edge
{
	int next,u,v,cap;
}edges[M];
int gap[N],cur[N],p[N],d[N],point[N],n,m,s,t,ednum;
inline void addedge(int u,int v,int cap)
{
	edges[++ednum].next=point[u];
	point[u]=ednum;
	edges[ednum].u=u;
	edges[ednum].v=v;
	edges[ednum].cap=cap;
}
inline void bfs()
{
	queue<int> q;
	memset(d,0xff,sizeof(d));
	q.push(t);
	d[t]=0;
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=point[x];i!=-1;i=edges[i].next)
		if(edges[i^1].cap&&d[edges[i^1].u]==-1)
		{
			d[edges[i^1].u]=d[x]+1;
			q.push(edges[i^1].u);
		}
	}
}
inline int augment()
{
	int x=t,flow=INF;
	while(x!=s)
	{
		flow=MIN(flow,edges[p[x]].cap);
		x=edges[p[x]].u;
	}
	x=t;
	while(x!=s)
	{
		edges[p[x]].cap-=flow;
		edges[p[x]^1].cap+=flow;
		x=edges[p[x]].u;
	}
	return flow;
}
inline int isap()
{
	int res=0,x=s;
	memset(p,-1,sizeof(-1));
	memcpy(cur,point,(n+5)*sizeof(int));
	memset(gap,0,sizeof(gap));
	bfs();
	for(int i=0;i<=n;i++)gap[d[i]]++;
	while(d[s]<n+1)
	{
		if(x==t)
		{
			res+=augment();
			x=s;
		}
		bool flag=false;
		for(int i=cur[x];i!=-1;i=edges[i].next)
		if(edges[i].cap&&d[x]-1==d[edges[i].v])
		{
			cur[x]=i;
			x=edges[i].v;
			p[x]=i;
			flag=true;
			break;
		}
		if(!flag)
		{
			int delta=n,tmp=point[x];
			for(int i=point[x];i!=-1;i=edges[i].next)
			if(edges[i].cap)
				if(d[edges[i].v]<delta)
				{
					tmp=i;
					delta=d[edges[i].v];
				}
			if(!(--gap[d[x]]))break;
			gap[d[x]=delta+1]++;
			cur[x]=tmp;
			if(x!=s)x=edges[p[x]].u;
		}
	}
	return res;
}
int main()
{
	while(~scanf("%d%d",&n,&m))
	{
		memset(point,0xff,sizeof(point));
		ednum=-1;
		for(int i=1;i<=n;i++)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			addedge(0,i,a);
			addedge(i,0,0);
			addedge(i,n+1,b);
			addedge(n+1,i,0);
		}
		for(int i=1;i<=m;i++)
		{
			int u,v,cap;
			scanf("%d%d%d",&u,&v,&cap);
			addedge(u,v,cap);
			addedge(v,u,cap);
		}
		s=0;t=n+1;
		printf("%d\n",isap());
	}
	return 0;
}
/*
inline void bfs(){
	static queue<int> q;
	memset(d,0xff,sizeof(d));gap[d[t]=0]++;
	for(q.push(t);!q.empty();q.pop()){
		int x(q.front());
		for(int i(point[x]),v;i!=-1;i=edges[i].next)
			if(edges[i^1].cap&&d[v=edges[i^1].u]==-1)
				gap[d[v]=d[x]+1]++,q.push(v);
	}
}
inline LL augment(){
	LL flow=INF;
	for(int x(t);x!=s;x=edges[p[x]].u)flow=MIN(flow,edges[p[x]].cap);
	for(int x(t);x!=s;x=edges[p[x]].u)edges[p[x]].cap-=flow,edges[p[x]^1].cap+=flow;
	return flow;
}
inline LL isap(){
	LL res=0;bfs();
	memcpy(cur,point,sizeof(int)*num);
	for(int x(s);d[s]<num;){
		if(x==t)res+=augment(),x=s;
		bool flag=0;
		for(int i(point[x]),v;i!=-1;i=edges[i].next)
			if(edges[i].cap&&d[x]-1==d[v=edges[i].v]){
				flag=1;cur[x]=i;
				p[x=v]=i;break;
			}
		if(!flag){
			int dlt(num);
			for(int i(point[x]),v;i!=-1;i=edges[i].next)
				if(edges[i].cap&&d[v=edges[i].v]<dlt)
					dlt=d[v],cur[x]=i;
			if(!(--gap[d[x]]))break;
			gap[d[x]=dlt+1]++;
			if(x!=s)x=edges[p[x]].u;
		}
	}
	return res;
}
*/
