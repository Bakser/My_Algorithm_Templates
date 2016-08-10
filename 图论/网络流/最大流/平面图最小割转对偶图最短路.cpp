//bzoj1001 
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<cctype>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef pair<int,int> pii;
#define M 3500000
#define N 2000000
#define INF 0x3f3f3f3f
#define MIN(a,b) (((a)<(b))?(a):(b))
struct hh
{
	int next,v,val;
}edges[M];
int point[N],d[N],n,m,tmp,ans,s,t,en=-1;
__gnu_pbds::priority_queue< pii , greater<pii > ,pairing_heap_tag> q;
inline int getint()
{
	char c=0;
	while(c<'0'||c>'9')c=getchar();
	int res=0;
	while(c>='0'&&c<='9'){res*=10;res+=c-'0';c=getchar();}
	return res;
}
inline void addedge(int u,int v,int val)
{
	edges[++en].next=point[u];
	point[u]=en;
	edges[en].val=val;
	edges[en].v=v;
}
inline void build_graph()
{
	s=0;t=(n-1)*(m-1)*2+1;
	for(int i=1;i<m;i++)
	addedge(i<<1,t,getint());
	for(int i=1;i<n-1;i++)
	for(int j=1;j<m;j++)
	addedge(i*(m-1)*2+j*2,(i-1)*(m-1)*2+j*2-1,getint());
	for(int i=1;i<m;i++)
	addedge(s,(n-2)*(m-1)*2+i*2-1,getint());
	for(int i=0;i<n-1;i++)
	{
		addedge(s,i*(m-1)*2+1,getint());
		for(int j=1;j<=m-2;j++)addedge(i*(m-1)*2+j*2,i*(m-1)*2+j*2+1,getint());
		addedge((i+1)*(m-1)*2,t,getint());
	}
	for(int i=0;i<n-1;i++)
	for(int j=1;j<m;j++)
	addedge(i*(m-1)*2+j*2-1,i*(m-1)*2+j*2,getint());
}
inline int dijkstra()
{
	memset(d,0x7f,sizeof(d));
	d[s]=0;
	q.push(make_pair(d[s],s));
	while(!q.empty())
	{
		pii u=q.top();q.pop();
		int x=u.second;
		if(d[x]!=u.first)continue;
		if(x==t)break;
		for(int i=point[x];i!=-1;i=edges[i].next)
		if(d[edges[i].v]>d[x]+edges[i].val){
			d[edges[i].v]=d[x]+edges[i].val;
			q.push(make_pair(d[edges[i].v],edges[i].v));
		}
	}
	return d[t];
}
int main()
{
	n=getint();m=getint();
	memset(point,0xff,sizeof(point));
	if(n==1||m==1)
	{
		ans=INF;
		for(int i=1;i<=n*(m-1)+(n-1)*(m-1)+(n-1)*m;i++)
		{
			tmp=getint();
			ans=MIN(ans,tmp);
		}
		printf("%d\n",ans);
		return 0;
	}
	build_graph();
	printf("%d\n",dijkstra());
	return 0;
}
