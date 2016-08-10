//poj2396 不要在意建图 
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
#define N 220
#define MAXN 440
#define INF 0x3f3f3f3f
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
struct hh
{
	int u,v,cap,full,next;
}edges[(N*N)<<3];
struct limlits
{
	int c,b;
}lim[N][N];
int T,n,m,c,r,q,s,t,val,nv,sum,en;
int deg[MAXN],map[MAXN][MAXN],graph[MAXN][MAXN],point[MAXN],gap[MAXN],cur[MAXN],d[MAXN],p[MAXN];
char str[10];
bool db=false,fir=false;
inline void addedge(int u,int v,int cap)
{
	edges[++en].next=point[u];
	point[u]=en;
	edges[en].u=u;
	edges[en].v=v;
	edges[en].cap=edges[en].full=cap;
	edges[++en].next=point[v];
	point[v]=en;
	edges[en].u=v;
	edges[en].v=u;
	edges[en].cap=edges[en].full=0;
}
inline void predeal()
{
	db=false;sum=0;en=-1;
	memset(point,0xff,sizeof(point));
	memset(deg,0,sizeof(deg));
	for(int i=0;i<=n+1;i++)
	for(int j=0;j<=m+1;j++)
	if(!i&&!j)lim[i][j].c=0,lim[i][j].b=0;
	else lim[i][j].c=INF,lim[i][j].b=0;
}
inline void bfs()
{
	queue<int>q;
	memset(d,0x7f,sizeof(d));
	q.push(t);
	gap[d[t]=0]++;
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=point[x];i!=-1;i=edges[i].next)
		if(edges[i^1].cap&&d[edges[i^1].u]>INF){
			gap[d[edges[i^1].u]=d[x]+1]++;
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
	int x=s,res=0;
	memset(gap,0,sizeof(gap));
	memcpy(cur,point,(n+m+10)*sizeof(int));
	bfs();
	while(d[s]<nv)
	{
		if(x==t)
		{
			res+=augment();
			x=s;
		}
		bool flag=false;
		for(int i=cur[x];i!=-1;i=edges[i].next)
		if(edges[i].cap&&d[x]-1==d[edges[i].v]){
			flag=true;
			cur[x]=i;
			x=edges[i].v;
			p[x]=i;
			break;
		}
		if(!flag)
		{
			int delta=nv;
			for(int i=point[x];i!=-1;i=edges[i].next)
			if(edges[i].cap&&delta>d[edges[i].v])
			{
				delta=d[edges[i].v];
				cur[x]=i;
			}
			if(!(--gap[d[x]]))break;
			gap[d[x]=delta+1]++;
			if(x!=s)x=edges[p[x]].u;
		}
	}
	return res;
}
inline void init()
{
	scanf("%d%d",&n,&m);
	predeal();
	int tmp=0;
	for(int i=1;i<=n;i++)scanf("%d",&lim[i][0].b),lim[i][0].c=lim[i][0].b;
	for(int i=1;i<=m;i++)scanf("%d",&lim[0][i].b),lim[0][i].c=lim[0][i].b;
	scanf("%d",&c);
	while(c--)
	{
		scanf("%d%d%s%d",&r,&q,str,&val);
		if(db)continue;
		if(str[0]=='<')
		{
			val--;
			if(val<0){db=true;continue;}
			if(r&&q)
			{
				lim[r][q].c=MIN(lim[r][q].c,val);
				if(lim[r][q].c<lim[r][q].b)db=true;
			}
			if(!r&&!q)
			{
				for(int i=1;i<=n;i++)
				for(int j=1;j<=m;j++)
				{
					lim[i][j].c=MIN(lim[i][j].c,val);
					if(lim[i][j].c<lim[i][j].b)db=true;
				}
			}
			if(!r&&q)
			{
				for(int j=1;j<=n;j++)
				{
					lim[j][q].c=MIN(lim[j][q].c,val);
					if(lim[j][q].c<lim[j][q].b)db=true;
				}
			}
			if(r&&!q)
			{
				for(int i=1;i<=m;i++)
				{
					lim[r][i].c=MIN(lim[r][i].c,val);
					if(lim[r][i].c<lim[r][i].b)db=true;
				}
			}
		}
		if(str[0]=='>')
		{
			val++;
			if(r&&q) 
			{
				lim[r][q].b=MAX(lim[r][q].b,val);
				if(lim[r][q].c<lim[r][q].b)db=true;
			}
			if(!r&&!q)
			{
				for(int i=1;i<=n;i++)
				for(int j=1;j<=m;j++)
				{
					lim[i][j].b=MAX(lim[i][j].b,val);
					if(lim[i][j].b>lim[i][j].c)db=true;
				}
			}
			if(!r&&q)
			{
				for(int j=1;j<=n;j++)
				{
					lim[j][q].b=MAX(lim[j][q].b,val);
					if(lim[j][q].c<lim[j][q].b)db=true;
				}
			}
			if(r&&!q)
			{
				for(int i=1;i<=m;i++)
				{
					lim[r][i].b=MAX(lim[r][i].b,val);
					if(lim[r][i].c<lim[r][i].b)db=true;
				}
			}
		}
		if(str[0]=='='){
			if(r&&q)
			{
				if(val>=lim[r][q].b&&val<=lim[r][q].c)lim[r][q].c=lim[r][q].b=val;
				else db=true;
			}
			if(!r&&!q)
			{
				for(int i=1;i<=n;i++)
				for(int j=1;j<=m;j++)
				{
					if(val>=lim[i][j].b&&val<=lim[i][j].c)lim[i][j].c=lim[i][j].b=val;
					else db=true;
				}
			}
			if(!r&&q)
			{
				for(int j=1;j<=n;j++)
				{
					if(val>=lim[j][q].b&&val<=lim[j][q].c)lim[j][q].b=lim[j][q].c=val;
					else db=true;
				}
			}
			if(r&&!q)
			{
				for(int i=1;i<=m;i++)
				{
					if(val>=lim[r][i].b&&val<=lim[r][i].c)lim[r][i].c=lim[r][i].b=val;
					else db=true;
				}
			}
		}
	}
	if(db)return;
//	for(int i=0;i<=n;i++)
//	{
//		for(int j=0;j<=m;j++)
//		printf("<%d,%d> ",lim[i][j].b,lim[i][j].c);
//		printf("\n");
//	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		deg[i]-=lim[i][j].b;
		deg[n+j]+=lim[i][j].b;
		addedge(i,n+j,lim[i][j].c-lim[i][j].b);
		map[i][n+j]=en-1;
	}
	for(int i=1;i<=n;i++)  
    {  
        deg[i]+=lim[i][0].b;  
        deg[0]-=lim[i][0].b;  
        addedge(0,i,0);  
    }  
    for(int i=1;i<=m;i++)  
    {  
        deg[i+n]-=lim[0][i].b;  
        deg[n+m+1]+=lim[0][i].b;  
        addedge(i+n,n+m+1,0);  
    }
    //从这是亮点 
	s=n+m+2;t=n+m+3;nv=n+m+4;
	for(int i=0;i<=n+m+1;i++)
	{
		if(deg[i]>0){
			addedge(s,i,deg[i]);
			sum+=deg[i];
		}
		else addedge(i,t,-deg[i]);
	}
	addedge(n+m+1,0,INF);
	int hh=isap();
	if(hh!=sum){db=true;return;}
	for(int i=1;i<=n;i++)
	for(int j=n+1;j<=n+m;j++)
	{
		int tmp=lim[i][j-n].b;
		tmp+=edges[map[i][j]].full-edges[map[i][j]].cap;
		if(tmp<0){db=true;return;}
		graph[i][j-n]=tmp;
	}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		if(fir)printf("\n");
		else fir=true;
		init();
		if(db)printf("IMPOSSIBLE\n");
		else
		{
			for(int i=1;i<=n;i++)
			{
				for(int j=1;j<=m;j++)
				{
					printf("%d",graph[i][j]);
					if(j!=m)printf(" ");
				}
				printf("\n");
			}
		}
	}
	return 0;
}
