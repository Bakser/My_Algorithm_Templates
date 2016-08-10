//poj3698
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
#define N 20010 
#define M 200010
#define MIN(a,b) (((a)<(b))?(a):(b))
#define INF 0x3f3f3f3f
struct edge
{
	int next,u,v,cap;
}next[600300];
int n,m,a,b,c,s,t,res=0,level[N],cur[N],point[N],ednum;
queue<int> q;
bool bfs()
{
	memset(level,0xff,sizeof(level));
	while(!q.empty())q.pop();
	q.push(s);
	level[s]=0;
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=point[x];i!=-1;i=next[i].next)
		{
			if(level[next[i].v]==-1&&next[i].cap)
			{
				level[next[i].v]=level[x]+1;
				q.push(next[i].v);
			}
		}
	}
	return level[t]!=-1;
}
int dfs(int u,int a)
{
	if(u==t||a==0)return a;
	int w=0,temp;
	for(int& i=cur[u];i!=-1;i=next[i].next)
	{
		if(level[next[i].v]==level[u]+1&&(temp=dfs(next[i].v,MIN(next[i].cap,a))))
		{
			next[i].cap-=temp;
			w+=temp;
			a-=temp;
			next[i^1].cap+=temp;
			if(!a)break;
		}
	}
	if(!w)level[u]=-1;
	return w;
}
int dinic()
{
	int res=0,tmp=0;
	while(bfs())
	{
		memcpy(cur,point,(n+5)*sizeof(int));
		while((tmp=dfs(s,INF)))
		res+=tmp;
	}
	return res;
}
inline void addedge(int u,int v,int cap)
{
	next[++ednum].next=point[u];
	point[u]=ednum;
	next[ednum].u=u;
	next[ednum].v=v;
	next[ednum].cap=cap;
}
int main()
{
	while(~scanf("%d%d",&n,&m))
	{
		memset(point,0xff,sizeof(point));
		s=0;
		ednum=-1;
		t=n+1;
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&a,&b);
			addedge(s,i,a);
			addedge(i,s,0);
			addedge(i,t,b);
			addedge(t,i,0);
		}
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			addedge(a,b,c);
			addedge(b,a,c);
		}
		printf("%d\n",dinic());
	}
	return 0;
}
