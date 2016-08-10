#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long double LD;
#define MAXSIZE 100000
template <class T>
T abs(const T &x)
{
	return x<0?-x:x;
}
const LD eps(1e-15);
int head,tail,lnum;
inline int cmp(LD x)
{
	if(x<-eps)return -1;
	if(x>eps)return 1;
	return 0;
}
struct point
{
	LD x,y;
	point(LD _x=0.0,LD _y=0.0):x(_x),y(_y){}
	point operator +(point a)
	{
		return point(x+a.x,y+a.y);
	}
	point operator -(point a)
	{
		return point(x-a.x,y-a.y);
	}
	point operator *(LD a)
	{
		return point(x*a,y*a);
	}
}p[MAXSIZE];
inline LD cross(const point &a,const point &b)
{
	return a.x*b.y-a.y*b.x;
}
inline LD angle(point x)
{
	LD t(atan2(x.y,x.x));
	if(t<0)t+=acos(0.0)*4.0;
	return t;
}
struct line 
{
	point u,v;
	LD ang;
	line(){}
	line(point a,point b)
	{
		v=b-a;
		u=a;
		ang=angle(v);
	}
	bool operator <(const line &a)const
	{
		return ang<a.ang;
	}
}lines[MAXSIZE],deq[MAXSIZE];
inline bool onleft(line l,point p)
{
	return cmp(cross(l.v,p-l.u))>0;
}
inline point intersection(line a,line b)
{
	point u=a.u-b.u;
	LD t(cross(a.v,u)/cross(a.v,b.v));
	return b.u+(b.v*t);
}
inline int Half_planar_intersection()
{
	sort(lines,lines+lnum);
	deq[head=tail=0]=lines[0];
	for(int i=1;i<lnum;i++)
	{
		while(head<tail&&!onleft(lines[i],p[tail-1]))tail--;
		while(head<tail&&!onleft(lines[i],p[head]))head++;
		if(cmp(lines[i].ang-deq[tail].ang)==0){if(!onleft(lines[i],deq[tail].u))deq[tail]=lines[i];}
		else deq[++tail]=lines[i];
		if(head<tail)p[tail-1]=intersection(deq[tail-1],deq[tail]);
	}
	while(head<tail&&!onleft(deq[head],p[tail-1]))tail--;
	if(tail-head<=1)return 0;
	p[tail]=intersection(deq[tail],deq[head]);
	return tail-head+1;
}

