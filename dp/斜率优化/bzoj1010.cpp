//bzoj1010 toy
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
#define N 50100
struct hh
{
	ll x,y;
}q[N],now;
int n,l;
ll c[N],head,tail;
inline ll det(ll x1,ll y1,ll x2,ll y2)
{
	return x1*y2-x2*y1;
}
inline ll cross(hh o,hh a,hh b)
{
	return det(a.x-o.x,a.y-o.y,b.x-o.x,b.y-o.y);
}
inline ll sqr(ll a)
{
	return a*a;
}
int main()
{
	scanf("%d%d",&n,&l);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&c[i]);
		c[i]+=c[i-1];
	}
	head=tail=0;
	for(int i=1;i<=n;i++)
	{
		while(head<tail&&q[head].y-2*(i+c[i]-l-1)*q[head].x>=q[head+1].y-2*(i+c[i]-l-1)*q[head+1].x)head++;
		now.x=i+c[i];
		now.y=q[head].y-2*(i+c[i]-l-1)*q[head].x+sqr(i+c[i]-l-1)+sqr(i+c[i]);
		while(head<tail&&cross(q[tail-1],q[tail],now)<=0)tail--;
		q[++tail]=now;
	}
	printf("%lld\n",q[tail].y-sqr(n+c[n]));
	return 0;
}
