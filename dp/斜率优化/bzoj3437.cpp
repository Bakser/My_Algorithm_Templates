#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
typedef long long LL;
#define N 1000005
#define MAX(a,b) (((a)>(b))?(a):(b))
struct hh
{
	LL x,y;
	hh(LL _x=0,LL _y=0):x(_x),y(_y){}
}q[N];
LL n,a[N],b[N],sum[N],f[N],ans=0,sigma=0,head,tail;
inline LL calc(LL i,LL j)
{
	return f[j]+sum[i]*(j-i);
}
inline LL cross(const hh &o,const hh &a,const hh &b)
{
	return (a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);
}
int main()
{
	scanf("%lld",&n);
	for(LL i=0;i<n;i++)
		scanf("%lld",a+i);
	for(LL i=0;i<n;i++)
	{
		scanf("%lld",b+i);
		sigma+=b[i]*(n-i);
		sum[i]=(i?sum[i-1]:0)+b[i];
	}	
	head=0;tail=1;
	ans=f[n-1]=sum[n-1]-a[n-1];
	q[0]=hh(n-1,f[n-1]);
	for(LL i=n-2;i>=0;i--)
	{
		while(head<tail&&calc(i,q[head].x)<=calc(i,q[head+1].x))head++;
		f[i]=calc(i,q[head].x)-a[i];
		hh tmp(i,f[i]);
		while(tail-head>1&&cross(q[tail-2],q[tail-1],tmp)<=0)tail--;
		q[tail++]=tmp;
		ans=MAX(ans,f[i]);
	}
	printf("%lld\n",sigma-ans);
	return 0;
}
