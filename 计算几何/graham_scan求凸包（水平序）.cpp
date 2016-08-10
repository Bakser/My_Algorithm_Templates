//poj1113
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
#define PI acos(-1.0)
double res;
struct hh
{
	int x,y;
	friend bool operator<(const hh &a,const hh &b)//��ˮƽ������ 
	{
		if(a.y!=b.y)return a.y<b.y;
		return a.x<b.x;
	}
}point[1010],stack[1010];
int n,r,top;
inline double dist(hh a,hh b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
inline int det(int x1,int y1,int x2,int y2)
{
	return x1*y2-x2*y1;
}
inline int cross(hh o,hh a,hh b)//����жϷ���С��0˵��˳ʱ�� 
{
	return det(a.x-o.x,a.y-o.y,b.x-o.x,b.y-o.y);
}
inline void graham_scan()
{
	sort(point,point+n);
	top=0;
	for(int i=0;i<n;i++)
	{
		while(top>=2&&cross(stack[top-2],stack[top-1],point[i])<=0)//��Ҫ���ߵĵ�һ��������ѵȺ�ȥ�� 
			top--;
		stack[top++]=point[i];
	}
	int tmp=top+1;
	for(int i=n-2;i>=0;i--)
	{
		while(top>=tmp&&cross(stack[top-2],stack[top-1],point[i])<=0)
		top--;
		stack[top++]=point[i];
	}
}
int main()
{
	while(~scanf("%d%d",&n,&r))
	{
		for(int i=0;i<n;i++)
		scanf("%d%d",&point[i].x,&point[i].y);
		graham_scan();
		double ans=0.0;
		ans=2.0*PI*(double)r;
		for(int i=0;i<top-1;i++)
		ans+=dist(stack[i],stack[i+1]);
		printf("%d\n",(int)(ans+0.5));
	}
	return 0;
}
