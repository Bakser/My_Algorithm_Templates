//poj3680
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
#define N 100010
#define M 300010
#define MIN(a,b) (((a)<(b))?(a):(b))
#define INF 0x3f3f3f3f
struct edge
{
	int u,v,next,cost,cap;
}edges[M];
struct hh
{
	int u,v,w;
}qj[210];
int a,b,w,point[N],ls[N],map[N],n,k,T,en=-1,s,t,lsnum,res,d[N],f[N],p[N];
queue<int> q;
bool in[N];
inline void init()
{
	memset(point,0xff,sizeof(point));
	en=-1;lsnum=0;
}
inline void addedge(int u,int v,int cap,int cost)
{
	edges[++en].next=point[u];
	point[u]=en;
	edges[en].u=u;
	edges[en].v=v;
	edges[en].cost=cost;
	edges[en].cap=cap;
	if(cap)addedge(v,u,0,-cost);
}
inline bool spfa()
{
	memset(d,0x7f,sizeof(d));
	memset(in,0,sizeof(in));
	d[s]=0;f[s]=INF;in[s]=true;
	q.push(s);
	while(!q.empty())
	{
		int x=q.front();q.pop();in[x]=false;
		for(int i=point[x];i!=-1;i=edges[i].next)
		if(edges[i].cap&&d[x]+edges[i].cost<d[edges[i].v]){
			d[edges[i].v]=d[x]+edges[i].cost;
			f[edges[i].v]=MIN(edges[i].cap,f[x]);
			p[edges[i].v]=i;
			if(!in[edges[i].v])
			{q.push(edges[i].v);in[edges[i].v]=1;}
		}
	}
	int x=t;
	if(d[t]>INF)return false;
	while(x!=s)
	{
		edges[p[x]].cap-=f[t];
		edges[p[x]^1].cap+=f[t];
		x=edges[p[x]].u;
	}
	res+=d[t]*f[t];
	return true;
}
inline void mcmf()
{
	res=0;
	while(spfa());
	res=-res;
}
int main()
{
//	freopen("test.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&k);
		init();
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d%d",&qj[i].u,&qj[i].v,&qj[i].w);
			ls[++lsnum]=qj[i].u;
			ls[++lsnum]=qj[i].v;
		}
		sort(ls+1,ls+lsnum+1);
		lsnum=unique(ls+1,ls+lsnum+1)-ls-1;
		for(int i=1;i<=lsnum;i++)map[ls[i]]=i;
		for(int i=1;i<=n;i++)
			addedge(map[qj[i].u],map[qj[i].v],1,-qj[i].w);
		for(int i=1;i<lsnum;i++)
		addedge(i,i+1,k,0);
		s=0;t=lsnum+1;
		addedge(s,1,k,0);addedge(lsnum,t,k,0);
		mcmf();
		printf("%d\n",res);
	}
	return 0;
}
