#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long double LD;
#define N 100100
#define MAX(a,b) (((a)>(b))?(a):(b)) 
struct hh
{
	LD x,y;
	bool operator<(const hh &b)const
	{
		if(x!=b.x)return x<b.x;
		return y<b.y;
	}
}p[N],tmp[N];
int n,pos[N],q[N];
LD ans,a[N],rate[N],b[N],k[N],rmb[N];
double t1,t2,t3;
inline LD cross(const hh &o,const hh &a,const hh &b)
{
	return (a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);
}
inline bool cmp_pos(int a,int b)
{
	return k[a]<k[b];
}
inline LD calc(hh &x,int i)
{
	return x.x*a[i]+x.y*b[i];
}
inline void solve(int l,int r)
{
	if(l==r)
	{
		ans=MAX(ans,rmb[l]);
		p[l].y=ans/(a[l]*rate[l]+b[l]);
		p[l].x=p[l].y*rate[l];
		return; 
	}
	int mid(l+r>>1),left(l-1),right(mid);
	memcpy(q+l,pos+l,(r-l+1)*sizeof(int));
	for(int i=l;i<=r;i++)(q[i]<=mid?pos[++left]:pos[++right])=q[i];
	solve(l,mid);
	int top(0);
	for(int i=l;i<=mid;i++)
	{
		while(top>1&&cross(p[q[top-2]],p[q[top-1]],p[i])>=0)top--;
		q[top++]=i;
	}
	for(int i=mid+1;i<=r;i++)
	{
		while(top>1&&calc(p[q[top-2]],pos[i])>calc(p[q[top-1]],pos[i]))top--;
		rmb[pos[i]]=MAX(rmb[pos[i]],calc(p[q[top-1]],pos[i]));
	}
	solve(mid+1,r);
	merge(p+l,p+mid+1,p+mid+1,p+r+1,tmp+l);
	memcpy(p+l,tmp+l,(r-l+1)*sizeof(hh));
}
int main()
{
	scanf("%d%lf",&n,&t1);
	ans=t1;
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf%lf",&t1,&t2,&t3);
		a[i]=t1;b[i]=t2;rate[i]=t3;
		k[i]=-t1/t2;
		pos[i]=i;
	}
	sort(pos+1,pos+n+1,cmp_pos);
	solve(1,n);
	printf("%.3lf\n",(double)ans);
	return 0;
}

