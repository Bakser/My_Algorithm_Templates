//bzoj1901
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 20100
#define M 3000005 
#define lowbit(x) ((x)&(-x))
struct ques
{
	int tag,v,l,r;
}ques[N];
int a[N],T[N],hash[N],lson[M],rson[M],cnt[M],use[N],n,q,tot,num;
inline int find(int key)
{
	return lower_bound(hash,hash+num,key)-hash;
}
inline int build_empty(int l,int r)
{
	int root=++tot;
	cnt[root]=0;
	if(l!=r)
	{
		int mid=l+r>>1;
		lson[root]=build_empty(l,mid);
		rson[root]=build_empty(mid+1,r);
	}
	return root;
}
inline int update(int root,int pos,int val)
{
	int newr=++tot;
	int res=newr,l=0,r=num-1;
	cnt[newr]=cnt[root]+val;
	while(l<r)
	{
		int mid=l+r>>1;
		if(pos<=mid)
		{
			lson[newr]=++tot;
			rson[newr]=rson[root];
			newr=lson[newr];
			root=lson[root];
			r=mid;
		}
		else
		{
			rson[newr]=++tot;
			lson[newr]=lson[root];
			newr=rson[newr];
			root=rson[root];
			l=mid+1;
		}
		cnt[newr]=cnt[root]+val;
	}
	return res;
}
inline void modify(int x,int pos,int val)
{
	for(int i=x;i<=n;i+=lowbit(i))
	T[i]=update(T[i],pos,val);
}
inline int get_sum(int x)
{
	int res=0;
	for(int i=x;i;i-=lowbit(i))
	res+=cnt[lson[use[i]]];
	return res;
}
inline void build_tree()
{
	T[0]=build_empty(0,num-1);
	for(int i=1;i<=n;i++)T[i]=T[0];
	for(int i=1;i<=n;i++)modify(i,find(a[i]),1);
}
inline int query(int left,int right,int k)
{
	int l=0,r=num-1;
	while(l<r&&k)
	{
		int mid=l+r>>1;
		int tmp=get_sum(right)-get_sum(left-1);
		if(tmp>=k)
		{
			r=mid;
			for(int i=left-1;i;i-=lowbit(i))use[i]=lson[use[i]];
			for(int i=right;i;i-=lowbit(i))use[i]=lson[use[i]];
		}
		else
		{
			l=mid+1;
			k-=tmp;
			for(int i=left-1;i;i-=lowbit(i))use[i]=rson[use[i]];
			for(int i=right;i;i-=lowbit(i))use[i]=rson[use[i]];
		}
	}
	return l;
}
int main()
{
//	freopen("test.txt","r",stdin); 
	scanf("%d%d",&n,&q);
	tot=num=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		hash[num++]=a[i];
	}
	char str[10];
	int t1,t2,t3;
	for(int i=0;i<q;i++)
	{
		scanf("%s",str);
		scanf("%d%d",&ques[i].l,&ques[i].r);
		if(str[0]=='Q')ques[i].tag=0,scanf("%d",&ques[i].v);
		else ques[i].tag=1,hash[num++]=ques[i].r;
	}
	sort(hash,hash+num);
	num=unique(hash,hash+num)-hash;
	build_tree();
	for(int i=0;i<q;i++)
	{
		if(!ques[i].tag)printf("%d\n",hash[query(ques[i].l,ques[i].r,ques[i].v)]);
		else
		{
			modify(ques[i].l,find(a[ques[i].l]),-1);
			modify(ques[i].l,find(ques[i].r),1);
			a[ques[i].l]=ques[i].r;
		}
	}
	return 0;
}
