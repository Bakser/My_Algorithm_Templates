//bzoj3040 
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<ext/pb_ds/priority_queue.hpp>
using namespace std;
using namespace __gnu_pbds;
#define N 1000010
#define M 10000010
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define mp make_pair
typedef long long LL;
typedef pair<LL,int> pii;
template <class T>
T read(T &x)
{
	x=0;
	char c=0;
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')(x*=10)+=c-'0',c=getchar();
	return x;
}
typedef __gnu_pbds::priority_queue<pii,greater<pii>,thin_heap_tag > heap;
struct hh
{
	int v,val,next;
}edges[M];
int point[N],n,m,x=0,y=0,z=0,T,rxa,rxc,rya,ryc,rp,a(0),b(0);
LL dis[N];
heap q;
heap::point_iterator it[N];
inline void addedge(int u,int v,int val)
{
	static int en(0);
	edges[++en].next=point[u];
	edges[en].v=v;
	edges[en].val=val;
	point[u]=en;
}
int main()
{
	read(n);read(m);
	read(T);read(rxa);read(rxc);read(rya);read(ryc);read(rp);
	for(int i=1;i<=T;i++)
	{
		x=((LL)x*rxa+rxc)%rp;
		y=((LL)y*rya+ryc)%rp;
		a=MIN(x%n+1,y%n+1);
		b=MAX(y%n+1,y%n+1);
		addedge(a,b,100000000-100*a);
	}
	for(int i=1;i<=m-T;i++)
	{
		read(x);read(y);read(z);
		addedge(x,y,z);
	}
	memset(dis,0x7f,sizeof(dis));
	dis[1]=0;
	it[1]=q.push(mp(0LL,1));
	while(!q.empty())
	{
		pii t(q.top());q.pop();
		int u(t.second);
		it[u]=0;dis[u]=t.first;
		if(u==n)break;
		for(int i=point[u];i;i=edges[i].next)
		if(dis[u]+edges[i].val<dis[edges[i].v])
		{
			dis[edges[i].v]=dis[u]+edges[i].val;
			if(it[edges[i].v]==0)it[edges[i].v]=q.push(mp(dis[edges[i].v],edges[i].v));
			else q.modify(it[edges[i].v],mp(dis[edges[i].v],edges[i].v));	
		}
	}
	printf("%lld\n",dis[n]);
	return 0;
}
