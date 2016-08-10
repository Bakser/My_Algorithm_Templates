//poj3468 
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 100010
typedef long long ll;
ll tree[N<<2],n,q,h,M,s,t,l[N<<2],r[N<<2],tag[N<<2],dep[N<<2];
char c;
ll x;
inline void init()
{
	memset(tree,0,sizeof(tree));
	memset(tag,0,sizeof(tag));
	memset(dep,0,sizeof(dep));
	h=M=0;
}
inline void refresh(ll now,ll x)
{
	tree[now]+=x*(r[now]-l[now]+1);
	tag[now]+=x;
}
inline void push_son(ll x)
{
	if(!tag[x])return;
	refresh(x<<1,tag[x]);
	refresh(x<<1^1,tag[x]);
	tag[x]=0;
}
inline void push_all(ll x)
{
	for(int i=dep[x]-1;i>=1;i--)
	push_son(x>>i);
}
inline void change(ll l,ll r,ll x)
{
	l=l+M-1;
	r=r+M+1;
	push_all(l);
	push_all(r);
	ll tl=l;
	ll tr=r;
	for(;tl^tr^1;tl>>=1,tr>>=1)
	{
		if(~tl&1)refresh(tl^1,x);
		if(tr&1)refresh(tr^1,x);
	}
	for(int i=1;i<=h-1;i++)
	{
		l>>=1;r>>=1;
		tree[l]=tree[l<<1]+tree[l<<1^1];
		tree[r]=tree[r<<1]+tree[r<<1^1];
	}
}
inline ll query(ll s,ll t)
{
	ll res=0;
	s=s+M-1;
	t=t+M+1;
	push_all(s);
	push_all(t);
	for(;s^t^1;s>>=1,t>>=1)
	{
		if(~s&1)res+=tree[s^1];
		if(t&1)res+=tree[t^1];
	}
	return res;
}
int main()
{
//	freopen("test.txt","r",stdin);
	while(~scanf("%lld%lld",&n,&q))
	{
		init();
		while((1<<h)-2<n)h++;
		M=(1<<h)-1;
		for(int i=M+1;i<M+n+1;i++)
		{
			scanf("%lld",&tree[i]);
			dep[i]=h;
			l[i]=i-M;
			r[i]=i-M;
		}
		for(int i=M;i>=1;i--)
		{
			tree[i]=tree[i<<1]+tree[i<<1^1];
			dep[i]=dep[i<<1]-1;
			l[i]=l[i<<1];
			r[i]=r[i<<1^1];
		}
		c=0;
		for(int i=1;i<=q;i++)
		{
			while(c!='C'&&c!='Q')c=getchar();
			if(c=='C')
			{
				scanf("%lld%lld%lld",&s,&t,&x);
				change(s,t,x);	
			}
			else if(c=='Q')
			{
				scanf("%lld%lld",&s,&t);
				printf("%lld\n",query(s,t));
			}
			c=0;
		}
//		printf("\n");
	}
	return 0;
}
 
