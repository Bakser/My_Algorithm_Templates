//bzoj1005 
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
#define N 10100
#define MAX(a,b) (((a)>(b))?(a):(b))
typedef pair<int,int> pii;
struct hh
{
	int v,next;
}edges[2000100];
int n,m,point[N],seq[N],pos[N],label[N],ans;
bool used[N];
inline void addedge(int u,int v)
{
	static int en(0);
	edges[++en].next=point[u];
	edges[en].v=v;
	point[u]=en;
}
inline void mcs()
{
	static priority_queue<pii> q;
	for(int i=1;i<=n;i++)
		q.push(make_pair(0,i));
	for(int i=n;i>=1;i--)
	{
		while(used[q.top().second])q.pop();
		int u(q.top().second);
		seq[i]=u;pos[u]=i;used[u]=1;
		for(int i=point[u];i;i=edges[i].next)
			if(!used[edges[i].v])
				q.push(make_pair(++label[edges[i].v],edges[i].v));
	}
	for(int i=1;i<=n;i++)
	{
		int sum(0);
		for(int j=point[i];j;j=edges[j].next)
			if(pos[edges[j].v]>pos[i])
				sum++;
		ans=MAX(ans,sum+1);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0,u,v;i<m;i++)
	{
		scanf("%d%d",&u,&v);
		addedge(u,v);
		addedge(v,u);
	}
	mcs();
	printf("%d\n",ans);
	return 0;
}
