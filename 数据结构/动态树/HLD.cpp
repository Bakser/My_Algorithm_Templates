#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N(1e5+200);
#define lson x<<1,l,mid
#define rson x<<1|1,mid+1,r
struct hh{
	int next,v,w;
}edges[N<<1];
struct seg_node{
	int mx,cover,add;
}tree[N<<2];
int n,en=1,sz[N],tot,son[N],dep[N],fa[N],top[N],tid[N],val[N],point[N],pos[N],L,R,cov,add;
inline void read(int &x){
	char c=0;int f=1;
	for(;c<'0'||c>'9';c=getchar())if(c=='-')f=-1;
	for(x=0;c>='0'&&c<='9';c=getchar())x=x*10+(c-'0');
	x*=f;
}
inline void addedge(int u,int v,int w){
	edges[++en]=(hh){point[u],v,w};point[u]=en;
}
inline void dfs(int x){
	sz[x]=1;son[x]=0;
	for(int i(point[x]),v;i;i=edges[i].next)
		if((v=edges[i].v)!=fa[x]){
			fa[v]=x;dep[v]=dep[x]+1;
			dfs(v);sz[x]+=sz[v];
			if(sz[v]>sz[son[x]])son[x]=v;
			pos[i>>1]=v;
		}
}
inline void make(int x,int anc){
	top[x]=anc;tid[x]=++tot;
	if(son[x])make(son[x],anc);
	for(int i(point[x]);i;i=edges[i].next)
		if(edges[i].v!=fa[x]&&edges[i].v!=son[x])
			make(edges[i].v,edges[i].v);
}
inline void refresh_cov(int x,int cov){
	tree[x].cover=tree[x].mx=cov;tree[x].add=0;
}
inline void refresh_add(int x,int add){
	tree[x].mx+=add;
	tree[x].cover!=-1?tree[x].cover+=add:tree[x	].add+=add;
}
inline void refresh(int x,int cov,int add){
	if(cov!=-1)refresh_cov(x,cov);
	if(add)refresh_add(x,add);
}
inline void push_down(int x){
	//refresh(x<<1,tree[x].cover,tree[x].add);
	//refresh(x<<1|1,tree[x].cover,tree[x].add);
	if(tree[x].cover!=-1)refresh_cov(x<<1,tree[x].cover),refresh_cov(x<<1|1,tree[x].cover),tree[x].cover=-1;
	if(tree[x].add)refresh_add(x<<1,tree[x].add),refresh_add(x<<1|1,tree[x].add),tree[x].add=0;
	//tree[x].cover=-1;tree[x].add=0;
}
inline void push_up(int x){
	tree[x].mx=max(tree[x<<1].mx,tree[x<<1|1].mx);
}
inline void build(int x,int l,int r){
	tree[x].cover=-1;
	if(l==r)return void(tree[x].mx=val[l]);
	int mid(l+r>>1);
	build(lson);build(rson);
	push_up(x);
}
inline int query(int x,int l,int r){
	if(l>=L&&r<=R)return tree[x].mx;
	int mid(l+r>>1),res(0);
	push_down(x);
	if(L<=mid)res=max(res,query(lson));
	if(R>mid)res=max(res,query(rson));
	push_up(x);
	return res;
}
inline void change(int x,int l,int r){
	if(l>=L&&r<=R)return refresh(x,cov,add);
	push_down(x);
	int mid(l+r>>1);
	if(L<=mid)change(lson);
	if(R>mid)change(rson);
	push_up(x);
}
inline int ask(int x,int y){
	int ans(0);
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		L=tid[top[x]];
		R=tid[x];
		ans=max(ans,query(1,1,tot));
		x=fa[top[x]];
	}
	if(x==y)return ans;
	if(dep[x]>dep[y])swap(x,y);
	L=tid[son[x]];R=tid[y];ans=max(ans,query(1,1,tot));
	return ans;
}
inline void modify(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		L=tid[top[x]];R=tid[x];change(1,1,tot);x=fa[top[x]];
	}
	if(x==y)return;
	if(dep[x]>dep[y])swap(x,y);
	L=tid[son[x]];R=tid[y];change(1,1,tot);
}
int main(){
	read(n);
	for(int i(1),u,v,w;i<n;i++){
		read(u);read(v);read(w);
		addedge(u,v,w);
		addedge(v,u,w);
	}
	dfs(1);
	make(1,1);
	for(int i(2);i<=en;i+=2)val[tid[pos[i>>1]]]=edges[i].w;
	build(1,1,tot);
	char s[20];
	for(scanf("%s",s);s[0]!='S';scanf("%s",s)){
		int u,v;
		read(u);read(v);
		if(s[0]=='M')printf("%d\n",ask(u,v));
		else if(s[0]=='A')cov=-1,read(add),modify(u,v);
		else if(s[0]=='C'&&s[1]=='o')add=0,read(cov),modify(u,v);
		else cov=v,add=0,L=R=tid[pos[u]],change(1,1,tot);
	}
	return 0;
}
