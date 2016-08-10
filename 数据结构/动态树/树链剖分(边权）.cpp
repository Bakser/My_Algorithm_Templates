//轻重链剖分 
//维护，修改路径上的边权 。初始边权为0； 
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 100
#define M N<<1
struct hh 
{
	int v,next;
}edges[M];
struct seg
{
	int sum,cover;
}tree[N<<2];
int n,t,x1,y1,d,end,point[N],top[N],root,tid[N],fa[N],dep[N],size[N],u,v,en,son[N],deg[N];
inline void addedge(int u,int v)
{
	edges[++en].next=point[u];
	edges[en].v=v;
	point[u]=en;
}
inline void dfs(int x)
{
	size[x]=1;son[x]=0;
	for(int i=point[x];i!=-1;i=edges[i].next)
	if(edges[i].v!=fa[x])
	{
		fa[edges[i].v]=x;
		dep[edges[i].v]=dep[x]+1;
		dfs(edges[i].v);
		if(size[edges[i].v]>size[son[x]])son[x]=edges[i].v;
		size[x]+=size[edges[i].v];
	}
}
inline void push_down(int x,int l,int r)
{
	if(tree[x].cover)
	{
		tree[x<<1].cover+=tree[x].cover;
		tree[x<<1^1].cover+=tree[x].cover;
		int mid=l+r>>1;
		tree[x<<1].sum+=tree[x].cover*(mid-l+1);
		tree[x<<1^1].sum+=tree[x].cover*(r-mid);
		tree[x].cover=0;
	}
}
inline void push_up(int x)
{
	tree[x].sum=tree[x<<1].sum+tree[x<<1^1].sum;
}
inline void make(int x,int anc)
{
	tid[x]=++end;top[x]=anc;
	if(son[x])make(son[x],anc);
	for(int i=point[x];i!=-1;i=edges[i].next)
	if(edges[i].v!=fa[x]&&edges[i].v!=son[x])
	make(edges[i].v,edges[i].v);
}
inline void update(int x,int l,int r,int left,int right,int delta)
{
	if(l>=left&&r<=right)
	{
		tree[x].sum+=delta*(r-l+1);
		tree[x].cover+=delta;
		return;
	}
	push_down(x,l,r);
	int mid=l+r>>1;
	if(left<=mid)update(x<<1,l,mid,left,right,delta);
	if(right>mid)update(x<<1^1,mid+1,r,left,right,delta);
	push_up(x);
}
inline void change(int x,int y,int delta)
{
	int f1=top[x],f2=top[y];
	while(f1!=f2)
	{
		if(dep[f1]<dep[f2])
		{
			swap(x,y);swap(f1,f2);
		}
		update(1,0,end,tid[f1],tid[x],delta);
		x=fa[f1];f1=top[x];
	}
	if(x==y)return;
	if(dep[x]>dep[y])swap(x,y);
	update(1,0,end,tid[son[x]],tid[y],delta);
}
inline int query(int x,int l,int r,int left,int right)
{
	if(l>=left&&r<=right)return tree[x].sum;
	int mid=l+r>>1,res=0;
	push_down(x,l,r);
	if(left<=mid)res+=query(x<<1,l,mid,left,right);
	if(right>mid)res+=query(x<<1^1,mid+1,r,left,right);
	push_up(x);
	return res;
}
inline int ask(int x,int y)
{
	int f1=top[x],f2=top[y],res=0;
	while(f1!=f2)
	{
		if(dep[f1]<dep[f2]){swap(f1,f2);swap(x,y);}
		res+=query(1,0,end,tid[f1],tid[x]);
		x=fa[f1];f1=top[x];
	}
	if(x==y)return res;
	if(dep[x]>dep[y])swap(x,y);
	res+=query(1,0,end,tid[son[x]],tid[y]);
	return res;
}
inline void build(int x,int l,int r)
{
	tree[x].sum=tree[x].cover=0;
	if(l==r)return;
	int mid=l+r>>1;
	build(x<<1,l,mid);
	build(x<<1^1,mid+1,r);
}
int main()
{
	scanf("%d",&n);
	en=-1;
	memset(point,0xff,sizeof(point));
	memset(deg,0,sizeof(deg));
	memset(size,0,sizeof(size));
	memset(son,0,sizeof(son));
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		addedge(u,v);
		deg[v]++;
	}	
	for(int i=1;i<=n;i++)
	if(!deg[i])
	{
		fa[i]=dep[i]=0;
		dfs(i);
		root=i;
		break;
	}
	end=-1;
	make(root,root);
	build(1,0,end);
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&x1,&y1,&d);
		change(x1,y1,d);
	}
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&x1,&y1);
		printf("%d\n",ask(x1,y1));
	}
	return 0;
}
