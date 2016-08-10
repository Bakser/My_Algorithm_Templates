//小Z的袜子 
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
#define N 55100
ll n,m,s,a[N];
ll cnt[N],tmp;
inline ll gcd(ll a,ll b)
{
	if(b==0)return a;
	return gcd(b,a%b);
}
struct question
{
	ll l,r,rank;
}q[N];
struct ANS
{
	ll a,b;
	inline void reduce()
	{
		ll g=gcd(a,b);
		a/=g;
		b/=g;
	}
}ans[N];
inline bool cmp(const question &a,const question &b)
{
	if((a.l/s)!=(b.l/s))return (a.l/s)<(b.l/s);//分块 
	else return a.r<b.r;
}
int main()
{
	while(scanf("%I64d%I64d",&n,&m)==2)
	{
		for(int i=1;i<=n;i++)scanf("%I64d",&a[i]);
		for(int i=0;i<m;i++)
		{
			scanf("%I64d%I64d",&q[i].l,&q[i].r);
			q[i].rank=i;
		}	
		s=(int)(sqrt(n));
		sort(q,q+m,cmp);
		ll l=0,r=-1;tmp=0;
		memset(cnt,0,sizeof(cnt));
		for(int i=0;i<m;i++)
		{
			while(r<q[i].r)
			{
				r++;
				tmp-=(ll)cnt[a[r]]*cnt[a[r]];
				cnt[a[r]]++;
				tmp+=(ll)cnt[a[r]]*cnt[a[r]];
			}
			while(r>q[i].r)
			{
				tmp-=(ll)cnt[a[r]]*cnt[a[r]];
				cnt[a[r]]--;
				tmp+=(ll)cnt[a[r]]*cnt[a[r]];
				r--;
			}
			while(l<q[i].l)
			{
				tmp-=(ll)cnt[a[l]]*cnt[a[l]];
				cnt[a[l]]--;
				tmp+=(ll)cnt[a[l]]*cnt[a[l]];
				l++;
			}
			while(l>q[i].l)
			{
				l--;
				tmp-=(ll)cnt[a[l]]*cnt[a[l]];
				cnt[a[l]]++;
				tmp+=(ll)cnt[a[l]]*cnt[a[l]];
			}
			ans[q[i].rank].a=tmp-(r-l+1);
			ans[q[i].rank].b=(ll)((r-l+1)*(r-l));
			ans[q[i].rank].reduce();
		}
		for(int i=0;i<m;i++)
		printf("%I64d/%I64d\n",ans[i].a,ans[i].b);
	}
	return 0;
}

