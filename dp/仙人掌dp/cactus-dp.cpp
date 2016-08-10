//bzoj1023
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N(50100);
#define MIN(a,b) (((a)<(b))?(a):(b)) 
#define MAX(a,b) (((a)>(b))?(a):(b))
typedef pair<int,int> pii;
struct edge{int v,next;}edges[N<<2];
int n,m,ans,point[N],tot,cir[N<<1],f[N],fa[N],fe[N],dfn[N],low[N],num,head,tail;
pii s[N<<1];
inline void read(int &x){
	char c=0;
	for(;c<'0'||c>'9';c=getchar());
	for(x=0;c>='0'&&c<='9';c=getchar())(x*=10)+=(c-'0');
}
inline void addedge(int u ,int v){
	static int en(-1);
	edges[++en].next=point[u];point[u]=en;edges[en].v=v;
}
inline void dp(){
	head=tail=1;for(int i(1);i<=tot;i++)cir[i+tot]=cir[i];
	s[1].first=1;s[1].second=f[cir[1]]-1;
	for(int i(2);i<=(tot<<1);i++){
		for(;i-s[head].first>(tot>>1);head++);
		ans=MAX(ans,f[cir[i]]+i+s[head].second);
		int x(f[cir[i]]-i);
		for(;tail>head&&s[tail-1].second<x;tail--);
		s[tail++]=pii(i,x);
	}
}
inline void tarjan(int x){
	dfn[x]=low[x]=++num;
	for(int i(point[x]),v;i!=-1,v=i!=-1?edges[i].v:0;i=edges[i].next)
		if(i!=fe[x]){
			if(dfn[v])low[x]=MIN(low[x],dfn[v]);
			else fa[v]=x,fe[v]=i^1,tarjan(v),low[x]=MIN(low[x],low[v]);
		}
	for(int i(point[x]),v;i!=-1,v=i!=-1?edges[i].v:0;i=edges[i].next){
			if(i==(fe[v]^1)&&low[v]>dfn[x])//是割边，tree-dp 
				ans=MAX(ans,f[x]+f[v]+1),f[x]=MAX(f[v]+1,f[x]);
			if(i!=(fe[v]^1)&&dfn[x]<dfn[v]){//是返祖边的反边，x是环上的最高点。 
				tot=0;
				for(int t(v);t!=fa[x];t=fa[t])cir[++tot]=t;
				dp();
				for(int t=1;t<tot;t++)f[x]=MAX(f[x],f[cir[t]]+MIN(t,tot-t));
			}
		}
}
int main(){
	read(n);read(m);
	memset(point,0xff,sizeof(point));
	memset(fe,0xff,sizeof(fe));
	for(int i(1),t,u,v;i<=m;i++){
		read(t);read(u);
		for(int i(1);i<t;i++)
			read(v),addedge(u,v),addedge(v,u),u=v;
	}
	tarjan(1);
	printf("%d\n",ans);
	return 0;
}

