#include<bits/stdc++.h>
using namespace std;
const int N(1e5+200);
typedef long long LL;
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define kd(x) (tree+x)
#define INF 0x7f7f7f7f
#define MAXD 2
int n,m,now,tot,D,k;
struct point{
    LL d[MAXD];
	int pos;
    bool operator<(const point &b)const{
        return d[now]<b.d[now];
    }
}p[N],P;
struct node{
    LL d[MAXD],mn[MAXD],mx[MAXD];
	int pos;
    node *s[MAXD];
    inline void operator=(const point &b){
        pos=b.pos;
        for(int i(0);i<D;i++)
            d[i]=mn[i]=mx[i]=b.d[i];
    }
    inline void upd(){
        for(int i(0);i<D;i++)
            for(int j(0);j<2;j++)
                if(s[j])
					mn[i]=MIN(mn[i],s[j]->mn[i]),mx[i]=MAX(mx[i],s[j]->mx[i]);
    }
}tree[N],*root;
struct pii{
	LL dis;int pos;
	pii(LL _fir=0,LL _pos=0):dis(_fir),pos(_pos){}
	bool operator<(const pii &b)const{
		return (dis>b.dis||(dis==b.dis&&pos<b.pos));
	}
};
priority_queue<pii> q;
inline void newnode(node* &x){
    x=kd(++tot);
    for(int i(0);i<D;i++)
        x->d[i]=x->mn[i]=x->mx[i]=0;
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
inline void insert(node* &x,int _d){
    int f(P.d[_d]>=x->d[_d]);
    if(x->s[f])insert(x->s[f],(_d+1)%D);
    else{
        newnode(x->s[f]);
        *(x->s[f])=P;
    }
    x->upd();
}
inline LL sqr(LL x){
	return x*x;
}
inline LL dis(const node* a,const point &b){
    LL res(0);
    for(int i(0);i<D;i++)
        res+=sqr(a->d[i]-b.d[i]);
    return res;
}
inline LL judge_dist(node *x){
    if(!x)return -1;
    LL res(0);
    for(int i(0);i<D;i++)
        res+=sqr(max(abs(P.d[i]-x->mn[i]),abs(x->mx[i]-P.d[i])));
    return res;
}
inline void query(node* x,int _d){
	pii t=pii(dis(x,P),x->pos);
	if(q.size()<k)q.push(t);
	else if(t<q.top())q.pop(),q.push(t);
	int f(P.d[_d]<x->d[_d]);
	if(x->s[f]!=NULL&&(q.size()<k||judge_dist(x->s[f])>=q.top().dis))query(x->s[f],(_d+1)%D);
	if(x->s[!f]!=NULL&&(q.size()<k||judge_dist(x->s[!f])>=q.top().dis))query(x->s[!f],(_d+1)%D);
}
template<class T>
inline void read(T &x){
    char c(0);int d(1);
    for(;c<'0'||c>'9';c=getchar())if(c=='-')d=-1;
    for(x=0;c>='0'&&c<='9';c=getchar())(x*=10)+=(c-'0');
    x*=d;
}
int main (){
    D=2;
    read(n);
    for(int i=1;i<=n;i++){
        for(int j=0;j<D;j++)
            read(p[i].d[j]);
        p[i].pos=i;
    }
    build(root,1,n,0);
	for(read(m);m--;){
		for(int i(0);i<D;i++)
			read(P.d[i]);
		read(k);
		query(root,0);
		printf("%d\n",q.top().pos);
		for(;!q.empty();q.pop());
	}
    return 0;
}
