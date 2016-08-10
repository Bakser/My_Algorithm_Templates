//分治法，复杂度O（nlogn） 
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long LL;
const int N(1e5+200);
const LL inf = 1e18;
struct hh
{
	LL x,y;
	int id;
	bool operator<(const hh &b)const
	{
		return y!=b.y?y<b.y:x<b.x;
	}
}p[N],tmp[N];
LL sum;
int n;
inline void read(int &x)
{
	char c(0);bool flag(0);
	for(;c<'0'||c>'9';c=getchar())flag|=(c=='-');
	for(x=0;c>='0'&&c<='9';c=getchar())(x*=10)+=(c-'0');
	if(flag)x*=-1;
}
bool cmp(const hh &x,const hh &y)
{
	return (x.x!=y.x?x.x<y.x:x.y<y.y);
}
inline LL dis(const hh &a,const hh &b)
{
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
inline LL solve(int l,int r)
{
	LL res(inf);
	if(r-l<3)
	{
		for(int i(l);i<r;i++)
			for(int j(i+1);j<=r;j++)
				res=min(res,dis(p[i],p[j]));
		return res;
	}
	int mid(l+r>>1),c1(l-1),c2(mid),c(l-1);
	LL mid_x;
	memcpy(tmp+l,p+l,sizeof(hh)*(r-l+1));//按x划分 
	for(int i(l);i<=r;i++)
	{
		p[tmp[i].id<=mid?++c1:++c2]=tmp[i];
		if(tmp[i].id==mid)mid_x=tmp[i].x;
	}
	res=min(solve(l,mid),solve(mid+1,r));//这里不要宏定义 
	merge(p+l,p+mid+1,p+mid+1,p+r+1,tmp+l);//再归并得到y有序的点 
	memcpy(p+l,tmp+l,sizeof(hh)*(r-l+1));
	for(int i(l);i<=r;i++)
		if(abs(p[i].x-mid_x)<=res)
			tmp[++c]=p[i];
	for(int i(l);i<=c;i++)
		for(int j(i+1);j<=(i+8)&&j<=c;j++)//只需检查8个 
			res=min(res,dis(tmp[i],tmp[j]));
	return res;
}
int main()
{
	read(n);
	for(int i(1),a;i<=n;i++)
		scanf("%I64d%I64d",p[i].x,p[i].y);
	sort(p+1,p+n+1,cmp);//先按x排序 
	for(int i(1);i<=n;i++)
		p[i].id=i;
	sort(p+1,p+n+1);//再按y排序 
	printf("%I64d\n",solve(1,n));
	return 0;
}

