#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath> 
using namespace std;
typedef double LD;
const LD eps(1e-13);
const int N(50);
inline int dcmp(LD x){return x>eps?1:(x<-eps?-1:0);}
int c,n;
LD ans; 
struct point
{
	LD x,y;
	point(){};
	point(LD _x,LD _y):x(_x),y(_y){};
	friend inline point operator+(const point &a,const point &b){return point(a.x+b.x,a.y+b.y);}
	friend inline point operator-(const point &a,const point &b){return point(a.x-b.x,a.y-b.y);}
	friend inline point operator*(const point &a,LD b){return point(a.x*b,a.y*b);}
	friend inline point operator/(const point &a,LD b){return point(a.x/b,a.y/b);}
	friend inline bool operator==(const point &a,const point &b){return !dcmp(b.x-a.x)&&!dcmp(b.y-a.y);}
}s[N];
struct seg
{
	point s,t;
	seg(){};
	seg(const point &a,const point &b):s(a),t(b){};
};
queue<seg> q;
inline LD dot(const point &a,const point &b){return a.x*b.x+b.y*a.y;}
inline LD len(const point &a){return sqrt(dot(a,a));}
inline LD cross(const point &a,const point &b){return a.x*b.y-b.x*a.y;}
inline point normal(const point &a){return point(-a.y,a.x);}//法向量 
inline bool on_seg(const point &p,const seg &s)//判断点在线段上 
{
	return !dcmp(cross(s.s-p,s.t-p))&&dcmp((p.x-s.s.x)*(p.x-s.t.x))<=0&&dcmp((p.y-s.s.y)*(p.y-s.t.y))<=0;
}
inline bool inter(const seg &a,const seg &b)//判断线段是否相交 
{
	return dcmp(cross(b.s-a.s,a.t-a.s)*cross(b.t-a.s,a.t-a.s))<=0&&dcmp(cross(a.s-b.s,b.t-b.s)*cross(a.t-b.s,b.t-b.s))<=0;
}
struct poly 
{
	point p[N];
	int sz;
	poly(){};
	inline bool in(point &x)//判断点在多边形内部 射线法 
	{
		for(int i(1);i<=sz;i++)
			if(on_seg(x,seg(p[i],p[i%sz+1])))
				return 1;
		point ray(-10100,x.y+0.1);
		x.y+=0.1;
		int tot(0);
		for(int i(1);i<=sz;i++)
			tot+=inter(seg(ray,x),seg(p[i],p[i%sz+1]));
		x.y-=0.1;
		return tot&1;
	}
}land[N];
struct Ans
{
	point p;
	LD dis;
	Ans(){};
	Ans(const point &_p,const LD &_d):p(_p),dis(_d){};
}; 
point getinter(const seg &a,const seg &b)//线段交点 
{
	point u(a.s-b.s);
	LD t(cross(b.t,u)/cross(a.t,b.t));
	return a.s+((a.t)*t);
}
inline Ans dist(const point &p,const seg& s)//点到线段的距离 
{
	if(s.s==s.t)return Ans(s.s,len(s.s-p));
	point v1(s.t-s.s),v2(p-s.s),v3(p-s.t);
	if(dcmp(dot(v1,v2))<=0)return Ans(s.s,len(v2));
	if(dcmp(dot(v1,v3))>=0)return Ans(s.t,len(v3));
	point v(normal(s.s-s.t));
	point ans(getinter(seg(p,v),seg(s.s,v1)));
	return Ans(ans,len(p-ans));
}
inline Ans calc(point &p)
{
	for(int i(1);i<=c;i++)
		if(land[i].in(p))
			return Ans(p,0);
	Ans ans1;
	ans1.dis=1<<30;
	for(int i(1);i<=c;i++)
		for(int j(1);j<=land[i].sz;j++)
		{
			Ans now(dist(p,seg(land[i].p[j],land[i].p[j%land[i].sz+1])));
			if(dcmp(ans1.dis-now.dis)>=0)ans1=now;
		}
	ans=max(ans,ans1.dis);
	return ans1;
}
int main()
{
	scanf("%d%d",&c,&n);
	for(int i(1);i<=n;i++)
		scanf("%lf%lf",&s[i].x,&s[i].y);
	for(int i(1);i<=c;i++)
		{
			scanf("%d",&land[i].sz);
			for(int j(1);j<=land[i].sz;j++)
				scanf("%lf%lf",&land[i].p[j].x,&land[i].p[j].y);
		}
	for(int i(1);i<n;i++)
		q.push(seg(s[i],s[i+1])),calc(s[i]);
	calc(s[n]);
	while(!q.empty())
	{
		seg x(q.front());q.pop();
		point p1(calc(x.s).p),p2(calc(x.t).p),l(x.s),r(x.t);
		while(len(r-l)>1e-4)
		{
			point mid((l+r)/2);
			if(len(mid-p1)<len(mid-p2))l=mid;
			else r=mid;
		}
		LD nans(max(len(l-p1),len(l-p2)));
		calc(l);
		if(ans+0.004<nans)q.push(seg(x.s,l)),q.push(seg(l,x.t));
	}
	printf("%.2lf\n",ans);*/
	return 0;
}

