#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 10000
#define MAX(a,b) (((a)>(b))?(a):(b))
typedef int ld;
const ld eps(1e-10);
template<class T>
T abs(T a)
{
	return a>0?a:(-a);
}
inline ld add(ld a,ld b)
{
	if(abs(a+b)<eps*(abs(a)+abs(b)))return 0;
	return (a+b);
}
struct point
{
	ld x,y;
	point(ld _x=0,ld _y=0):x(_x),y(_y){
	}
	friend bool operator<(const point &a,const point &b)
	{
		if(a.x!=b.x)return a.x<b.x;
		return a.y<b.y;
	}
}p[N],s[N];
inline point operator+(const point &a,const point &b)
{
	return point(add(a.x,b.x),add(a.y,b.y));
}
inline point operator-(const point &a,const point &b)
{
	return point(add(a.x,-b.x),add(a.y,-b.y));
}
inline ld cross(const point &a,const point &b)
{
	return add(a.x*b.y,-b.x*a.y);
}
inline ld sqr(ld x)
{
	return x*x*1.0;
}
inline ld dist(const point &a,const point &b)
{
	return add(sqr(a.x-b.x),sqr(a.y-b.y));
}
int top,n;
inline void graham_scan()
{
	sort(p,p+n);
	top=0;
	for(int i=0;i<n;i++)
	{
		while(top>=2&&cross(s[top-1]-s[top-2],p[i]-s[top-2])<=0)top--;
		s[top++]=p[i];
	}
	int tmp=top+1;
	for(int i=n-2;i>=0;i--)
	{
		while(top>=tmp&&cross(s[top-1]-s[top-2],p[i]-s[top-2])<=0)top--;
		s[top++]=p[i];
	}
	top--;
}
inline ld rotating_calipers()
{
	if(top==2)return dist(s[0],s[1]);
	int i=0,j=0;
	for(int k=0;k<top;k++)
	{
		if(!(s[i]<s[k]))i=k;
		if(s[j]<s[k])j=k;
	}
	ld res=0;
	int si=i,sj=j;
	while(i!=sj||j!=si)
	{
		res=MAX(res,dist(s[i],s[j]));
		if(cross(s[(i+1)%top]-s[i],s[(j+1)%top]-s[j])<0)(i+=1)%=top;
		else (j+=1)%=top;
	}
	return res;
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	scanf("%d%d",&p[i].x,&p[i].y);
	graham_scan();
	ld ans=rotating_calipers();
	printf("%d\n",ans);
	return 0;
}
