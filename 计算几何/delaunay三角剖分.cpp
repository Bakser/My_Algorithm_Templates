#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <list>
#include <cmath>
#include <cstdlib>
using namespace std;
#define sqr(x) ((x)*(x))
typedef long long LD;
const LD eps(1e-6);
const int N(1e5+20);
const int D(19);
inline int dcmp(LD x){
	return x>0?1:x<0?-1:0;
}
int n,m;
template<class T>
inline void read(T &x){
	char c=0;
	for(;c<'0'||c>'9';c=getchar());
	for(x=0;c>='0'&&c<='9';c=getchar())x=x*10+(c-'0');
}
namespace Graph{
	struct edge{
		int u,v,next;LD w;
		inline bool operator <(const edge &b)const{
			return w<b.w;
		}
	}e[N*20],edges[N*2];
	int en=0,point[N],fa[N],en2=0,dep[N],f[N][D+1];
	LD mx[N][D+1];
	inline void add(int u,int v,LD w){
		e[++en].u=u;e[en].v=v;e[en].w=w;
	}
	inline void addedge(int u,int v,LD w){
		edges[++en2]=(edge){u,v,point[u],w};
		point[u]=en2;
	}
	inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
	inline void krusal(){
		sort(e+1,e+en+1);
		int cnt=0;
		for(int i(1);i<=en;i++){
			int p(find(e[i].u)),q(find(e[i].v));
			if(p!=q){
				addedge(e[i].u,e[i].v,e[i].w);
				addedge(e[i].v,e[i].u,e[i].w);
				fa[p]=q;
			}
		}
	}
	inline void dfs(int x,int fa){
		for(int i(1);i<=D;i++)f[x][i]=f[f[x][i-1]][i-1],mx[x][i]=max(mx[x][i-1],mx[f[x][i-1]][i-1]);
		for(int i(point[x]),v;i;i=edges[i].next)
			if((v=edges[i].v)!=fa){
				f[v][0]=x;
				mx[v][0]=edges[i].w;
				dep[v]=dep[x]+1;
				dfs(v,x);
			}
	}
	inline LD query(int x,int y){
		if(dep[x]<dep[y])swap(x,y);
		LD res(0.0);
		for(int i(D);i>=0;i--)
			if(dep[f[x][i]]>=dep[y])
				res=max(res,mx[x][i]),x=f[x][i];
		if(x==y)return res;
		for(int i(D);i>=0;i--)
			if(f[x][i]!=f[y][i])
				res=max(res,max(mx[x][i],mx[y][i])),x=f[x][i],y=f[y][i];
		return max(res,max(mx[x][0],mx[y][0]));
	}
	inline void prepare(){
		for(int i(1);i<=n;i++)fa[i]=i;
		krusal();
		dfs(dep[1]=1,0);
	}
}
namespace delaunay{
	struct edge{
		int v;
		list<edge>::iterator rev;
		edge(){}
		edge(int _v=0):v(_v){}
	};
	list<edge> e[N];
	typedef list<edge>::iterator iter;
	int s[N],top;
	struct point{
		LD x,y;int p;
		point(LD _x=0,LD _y=0):x(_x),y(_y){}
		inline bool operator <(const point &b)const{return dcmp(x-b.x)?dcmp(x-b.x)<0:dcmp(y-b.y)<0;}
		inline point operator -(const point &b)const{return point(x-b.x,y-b.y);} 
	}p[N];
	struct point3{
		LD x,y,z;
		point3(LD _x=0,LD _y=0,LD _z=0):x(_x),y(_y),z(_z){}
		point3(const point& b){x=b.x;y=b.y;z=sqr(x)+sqr(y);}
		inline point3 operator -(const point3 &b)const{return point3(x-b.x,y-b.y,z-b.z);}
	};
	#define P2 const point&
	#define P3 const point3&
	inline LD det(P2 a,P2 b){return a.x*b.y-b.x*a.y;}
	inline LD dot(P2 a,P2 b){return a.x*b.x+a.y*b.y;}
	inline point3 det(P3 a,P3 b){return point3(a.y*b.z-b.y*a.z,a.z*b.x-b.z*a.x,a.x*b.y-b.x*a.y);}
	inline LD dot(P3 a,P3 b){return a.x*b.x+a.y*b.y+a.z*b.z;}
	inline LD cross(P2 o,P2 a,P2 b){
		return det(a-o,b-o);
	}
	inline bool in_cir(point a,point b,point c,point d){
		if(cross(a,b,c)<0)swap(b,c);
		point3 o(a),x(b),y(c),z(d);
		return dcmp(dot(z-o,det(x-o,y-o)))<0;
	}
	inline bool inter(P2 a,P2 b,P2 c,P2 d){
		return (dcmp(cross(a,b,c))*dcmp(cross(a,b,d))<0)&&(dcmp(cross(c,d,a))*dcmp(cross(c,d,b))<0);
	}
	inline iter deledge(int p,iter x){
		iter t=x;
		t++;
		e[x->v].erase(x->rev);
		e[p].erase(x);
		return t;
	}
	inline void addedge(int u,int v){
		e[u].push_front(v);e[v].push_front(u);
		e[u].begin()->rev=e[v].begin();e[v].begin()->rev=e[u].begin();
	}
	inline void solve(int l,int r){
		if(r-l<=2){
			for(int i(l);i<=r;i++)
				for(int j(i+1);j<=r;j++)
					addedge(i,j);
			return;
		}
		int mid(l+r>>1),L(0),R(0);
		solve(l,mid);
		solve(mid+1,r);
		top=0;
		for(int i(l);i<=r;i++){
			while(top>1&&dcmp(cross(p[s[top-1]],p[s[top]],p[i]))<0)top--;
			s[++top]=i;
		}
		for(int i(1);i<=top;i++)
			if(s[i]<=mid&&s[i+1]>mid){
				L=s[i];R=s[i+1];break;
			}
		addedge(L,R);
		while(1){
			int nxt(0),op(0);
			for(iter i=e[L].begin();i!=e[L].end();i++){
				int v=i->v;
				if(dcmp(cross(p[L],p[R],p[v]))>0&&(!nxt||in_cir(p[L],p[R],p[nxt],p[v]))){
					nxt=v,op=1;
				}
			}
			for(iter i=e[R].begin();i!=e[R].end();i++){
				int v=i->v;
				if(dcmp(cross(p[R],p[L],p[v]))<0&&(!nxt||in_cir(p[L],p[R],p[nxt],p[v]))){
					nxt=v,op=-1;
				}
			}
			if(!nxt)break;
			if(op==1){
				for(iter i=e[L].begin();i!=e[L].end();)
					if(inter(p[R],p[nxt],p[L],p[i->v]))i=deledge(L,i);
					else i++;
				L=nxt;
			}
			else{
				for(iter i=e[R].begin();i!=e[R].end();)
					if(inter(p[L],p[nxt],p[R],p[i->v]))i=deledge(R,i);
					else i++;
				R=nxt;
			}
			addedge(L,R);
		}
	}
	inline void prepare(){
		for(int i(1);i<=n;i++)read(p[i].x),read(p[i].y),p[i].p=i;
		sort(p+1,p+n+1);
		solve(1,n);
		for(int i(1);i<=n;i++)
			for(iter j=e[i].begin();j!=e[i].end();j++)
				Graph::add(p[i].p,p[j->v].p,sqr(p[i].x-p[j->v].x)+sqr(p[i].y-p[j->v].y));
	}
}
int main(){
	read(n);
	delaunay::prepare();
	Graph::prepare();
	read(m);
	for(int i(1),u,v;i<=m;i++){
		read(u);read(v);
		printf("%.6lf\n",sqrt((double)Graph::query(u,v)));
	}
	return 0;
}

