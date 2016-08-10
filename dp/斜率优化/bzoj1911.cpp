#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define N 1000100
ll s[N],a,b,c,n,head,tail,q[N],f[N];
inline ll sqr(ll x)
{
	return x*x;
}
inline ll F(int x)
{
	return f[x]+a*sqr(s[x])-b*s[x];
}
inline ll X(int x1,int x2)
{
	return (F(x1)-F(x2))/(s[x1]-s[x2]);
}
int main()
{
	scanf("%lld",&n);
	scanf("%lld%lld%lld",&a,&b,&c);
	s[0]=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&s[i]);
		s[i]+=s[i-1];
	}
	head=tail=q[0]=f[0]=0;
	for(int i=1;i<=n;i++)
	{
		while(head<tail&&X(q[head],q[head+1])>2*a*s[i])head++;
		f[i]=f[q[head]]+a*sqr(s[i]-s[q[head]])+b*(s[i]-s[q[head]])+c;
		while(head<tail&&X(q[tail],i)>X(q[tail-1],q[tail]))tail--;
		q[++tail]=i;
	}
	printf("%lld\n",f[n]);
	return 0;
}
