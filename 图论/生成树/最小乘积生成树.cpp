#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;
const int N = 300;
const int M = 4010;
const int INF  = ((unsigned int)1 << 31) - 1;
typedef long long LL;
struct hh
{
	LL x,y;
	hh(int _x=0,int _y=0):x(_x),y(_y){}
	hh operator-(const hh &b)
	{
		return hh(x-b.x,y-b.y);
	}
}res;
struct edge
{
	int next,v;
	LL w,c,t;
}edges[M];
int n,m,point[N],en,vis[N],cnt,pre[N];
LL d[N],ans;
inline hh prim()
{
	memset(d,0x7f,sizeof(d));
	cnt++;
	d[1]=0;
	LL sumc(0),sumt(0);
	for(int i(1);i<=n;i++)
	{
		LL minn(INF);int x(0);
		for(int j(1);j<=n;j++)
			if(vis[j]!=cnt&&d[j]<minn)
				minn=d[j],x=j;
		vis[x]=cnt;
		if(x)sumc+=edges[pre[x]].c,sumt+=edges[pre[x]].t;
		for(int j(point[x]);j;j=edges[j].next)
			if(vis[edges[j].v]!=cnt&&edges[j].w<d[edges[j].v])
				d[edges[j].v]=edges[j].w,pre[edges[j].v]=j;
	}
	if(sumc*sumt<ans||(sumc*sumt==ans&&sumc<res.x))
	{
		ans=sumc*sumt;
		res.x=sumc;
		res.y=sumt;
	}
	return hh(sumc,sumt);
}
inline LL cross(hh a,hh b)
{
	return (a.x*b.y-b.x*a.y);
}
inline void solve(hh l,hh r)
{
	LL dc(r.x-l.x),dt(l.y-r.y);
	for(int i(1);i<=en;i++)
		edges[i].w=dt*edges[i].c+dc*edges[i].t;
	hh p=prim();
	if(cross(r-p,l-r)<=0)return;
	solve(l,p);
	solve(p,r);
}
inline void addedge(int u,int v,int c,int t)
{
	edges[++en].next=point[u];point[u]=en;edges[en].v=v;
	edges[en].c=c;edges[en].t=t;
}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int x, y, _c, _t;
		scanf("%d%d%d%d", &x, &y, &_c, &_t);
		addedge(x, y, _c , _t);
		addedge(y, x, _c , _t);
	}
	ans=INF;
	res.x = INF, res.y = INF;
	for(int i(1);i<=en;i++)
	edges[i].w=edges[i].c;
	hh minc=prim();
	for(int i(1);i<=en;i++)
	edges[i].w=edges[i].t;
	hh mint=prim();
	solve(minc,mint);
	printf("%lld ",res.x,res.y);
	printf("%lld\n",res.y);
}
