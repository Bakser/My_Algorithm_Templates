//bzoj2300
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<set>
using namespace std;
#define N 100100
#define Q 200100
typedef long double LD;
int sx,sy;
struct hh
{
	int x,y;
	LD rad;
	bool tag;
	hh(int _x=0,int _y=0):x(_x),y(_y){tag=0;}
	void out()
	{
		cout<<x<<" "<<y<<endl;
	}
	inline void calc()
	{
		rad=(LD)atan2(y-sy,x-sx);
	}
	bool operator<(const hh &b)const
	{
		return rad<b.rad;
	}
}p[N];
struct ques
{
	bool opt;
	int d;
}delta[Q];
typedef set<hh>::iterator iter;
set<hh> s;
int n,m,q,x,y,opt;
LD ans[Q],now;
inline LD sqr(LD x)
{
	return x*x*1.0;
}
inline LD dist(const hh &a,const hh &b)
{
	return (LD)sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}
inline iter pre(iter x)
{
	if(x==s.begin())x=s.end();
	return --x;
}
inline iter succ(iter x)
{
	if(++x==s.end())return s.begin();
	return x;
}
inline int cross(const hh &o,const hh &a,const hh &b)
{
	return (a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);
}
inline void insert(hh x)
{
	iter pos=pre(s.lower_bound(x));
	hh b=*pos;
	if(cross(b,x,*succ(pos))<0)return;
	iter l(pos),r(pos);
	while(cross(x,*succ(r),*r)>=0)r=succ(r);
	while(cross(x,*l,*pre(l))>=0)l=pre(l);
	hh t1,t2;
	for(iter it=l;it!=r;it=succ(it))
	{
		hh t1=*it;
		hh t2=*succ(it);
		now-=dist(t1,t2);
	}
	for(iter it=succ(l);it!=r;)
    {
        it=succ(it);
        s.erase(pre(it));
    }
    t1=*l;t2=*r;
    now+=dist(t1,x)+dist(x,t2);
	s.insert(x);
}
inline void init()
{
	scanf("%d%d%d",&n,&x,&y);
	sx=(n+x)/3.0;sy=y/3.0;
	p[0]=hh(0,0);
	p[1]=hh(n,0);
	p[2]=hh(x,y);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		p[i+2]=hh(x,y);
	}
	m+=3;
	for(int i=0;i<m;i++)p[i].calc();
	scanf("%d",&q);
	for(int i=0;i<q;i++)
	{
		int t;
		scanf("%d",&t);
		delta[i].opt=(!(t-1));
		if(delta[i].opt)scanf("%d",&delta[i].d),p[delta[i].d+2].tag=1;
	}
}
inline void solve()
{
	s.insert(p[0]);
	s.insert(p[1]);
	s.insert(p[2]);
	now=dist(p[0],p[2])+dist(p[1],p[2]);
	int cnt=0;
	for(int i=3;i<m;i++)if(!p[i].tag)insert(p[i]);
	for(int i=q-1;i>=0;i--)
	if(delta[i].opt)insert(p[delta[i].d+2]);
	else ans[cnt++]=now;
	for(int i=cnt-1;i>=0;i--)printf("%.2lf\n",(double)ans[i]);
}
int main()
{
	init();
	solve();
	return 0;
}

