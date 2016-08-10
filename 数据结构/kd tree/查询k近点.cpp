#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXD(6);
const int N(5e4+200);
#define kd(x) (tree+(x))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
int n,m,D,tot,now,k,top;
struct point{
	LL d[MAXD];
	inline bool operator<(const point &b)const{
		return d[now]<b.d[now];
	}
}p[N],P,tmp[20];
struct pii{
	LL dis;
	point p;
	pii(){}
	pii(LL _dis,point _p):dis(_dis),p(_p){};
	inline bool operator<(const pii &b)const{
		return dis<b.dis;
	}
};
priority_queue<pii> q;
inline LL sqr(LL x){
	return x*x;
}
struct node{
	point p;
	LL mn[MAXD],mx[MAXD];
	node *s[2];
	inline void operator =(const point &b){
		p=b;
		for(int i(0);i<D;i++)
			mn[i]=mx[i]=b.d[i];
	}
	inline LL judge_dis(){
		LL res(0);
		for(int i(0);i<D;i++)
			res+=sqr(MIN(abs(mn[i]-P.d[i]),abs(mx[i]-P.d[i])));
		return res;
	}
	inline void upd(){
		for(int i(0);i<2;i++)
			if(s[i])
				for(int j(0);j<D;j++)
					mn[j]=MIN(mn[j],s[i]->mn[j]),mx[j]=MAX(mx[j],s[i]->mx[j]);
	}
}tree[N],*root;
inline void newnode(node* &x){
	x=kd(++tot);
	for(int i(0);i<D;i++)
		x->mn[i]=x->mx[i]=x->p.d[i]=0;
	x->s[0]=x->s[1]=NULL;
}
inline void build(node* &x,int l,int r,int _d){
	newnode(x);
	now=_d;int mid((l+r)>>1);
	nth_element(p+l,p+mid,p+r+1);
	(*x)=p[mid];
	if(l<mid)build(x->s[0],l,mid-1,(_d+1)%D);
	if(mid<r)build(x->s[1],mid+1,r,(_d+1)%D);
	x->upd();
}
inline LL dis(const point &a,const point &b){
	LL res(0);
	for(int i(0);i<D;i++)
		res+=sqr(abs(a.d[i]-b.d[i]));
	return res;
}
inline void query(node* x,int _d){
	pii t(dis(x->p,P),x->p),g;
	bool ok(0);
	if(q.size())g=q.top();
	if(q.size()<k)
		q.push(t),ok=1;
	else if(t<q.top()){
		q.pop(),q.push(t);
	}	
	int f(P.d[_d]>=x->p.d[_d]);
	if(x->s[f])query(x->s[f],(_d+1)%D);
	if((sqr(P.d[_d]-x->p.d[_d])<q.top().dis))ok=1;
	if(x->s[!f]&&ok)query(x->s[!f],(_d+1)%D);
}
template <class T>
inline void read(T &x){
	char c=0;int f(1);
	for(;c<'0'||c>'9';c=getchar())if(c=='-')f=-1;
	for(x=0;c>='0'&&c<='9';c=getchar())(x*=10)+=(c-'0');
	x*=f;
}
int main(){
	while(~scanf("%d%d",&n,&D)){
		for(int i(1);i<=n;i++)
			for(int j(0);j<D;j++)
				read(p[i].d[j]);
		tot=0;
		memset(tree,0,sizeof(tree));
		build(root,1,n,0);
		for(read(m);m--;){
			for(int i(0);i<D;i++)
				read(P.d[i]);
			read(k);
			query(root,0);
			for(top=0;!q.empty();q.pop())tmp[++top]=q.top().p;
			printf("the closest %d points are:\n",k);
			for(int i(top);i>=1;i--){
				for(int j(0);j<D;j++){
					printf("%lld",tmp[i].d[j]);
					if(j!=D-1)printf(" ");
				}	
				puts("");
			}
		}
	}
	return 0;
}
