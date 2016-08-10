//poj2041&poj2761
#include<cstdio>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 100010
struct hh
{
	int val[N],num[N];
}tree[22];
struct hhh
{
	int l,r;
}db[N<<2];
int n,m,a[N],x,y,z;
inline void build(int dep,int left,int right,int pos)
{
	db[pos].l=left;
	db[pos].r=right;
	if(left==right)return;
	int mid=(left+right)>>1,lsame=mid-left+1;
	for(int i=left;i<=right;i++)
	if(tree[dep].val[i]<a[mid])lsame--;
	int lp=left,rp=mid+1,same=0;
	for(int i=left;i<=right;i++)
	{
		if(i==left)tree[dep].num[i]=0;
		else tree[dep].num[i]=tree[dep].num[i-1];
		if(tree[dep].val[i]<a[mid])
		{
			tree[dep].num[i]++;
			tree[dep+1].val[lp++]=tree[dep].val[i];
		}
		else if(tree[dep].val[i]>a[mid])
			tree[dep+1].val[rp++]=tree[dep].val[i];
		else
		{
			if(same<lsame)
			{
				same++;
				tree[dep].num[i]++;
				tree[dep+1].val[lp++]=tree[dep].val[i];
			}
			else
				tree[dep+1].val[rp++]=tree[dep].val[i];
		}
	}
	build(dep+1,left,mid,pos<<1);
	build(dep+1,mid+1,right,pos<<1^1);
}
inline int query(int pos,int dep,int l,int r,int k)
{
	if(db[pos].l==db[pos].r)return tree[dep].val[l];
	int s=0,ss=0,b=0,bb=0;//s:[a,b]进入左儿子的个数,ss：[left,a)中进入左儿子的个数 
	if(l==db[pos].l) ss=0;
	else ss=tree[dep].num[l-1];
	s=tree[dep].num[r]-ss;
	if(s>=k)return query(pos<<1,dep+1,db[pos].l+ss,db[pos].l+ss+s-1,k);
	else
	{
		int mid=(db[pos].l+db[pos].r)>>1;
		b=l-db[pos].l-ss;
		bb=r-l+1-s;
		return query(pos<<1^1,dep+1,mid+b+1,mid+b+bb,k-s);
	}
}
inline void init()
{
	memset(a,0,sizeof(a));
	memset(tree,0,sizeof(tree));
}
int main()
{
	while(~scanf("%d%d",&n,&m))
	{
		init();
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			tree[0].val[i]=a[i];
		}
		sort(a+1,a+n+1);
		build(0,1,n,1);
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			printf("%d\n",query(1,0,x,y,z));
		}
		printf("\n");
	}
	return 0;
}

