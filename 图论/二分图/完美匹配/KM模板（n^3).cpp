//poj3686
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define XN 55
#define YN XN*XN
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
int n,m,xn,yn,T,w[XN][XN],map[XN][YN],lx[XN],ly[YN],res[YN],slack[YN];
bool visx[XN],visy[YN];
inline void init()
{
	memset(w,0,sizeof(w));
	memset(map,0,sizeof(map));
	memset(res,-1,sizeof(res));
}
inline void build_graph()
{
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	for(int k=1;k<=n;k++)
	map[i][(j-1)*n+k]=-w[i][j]*k;
	xn=n;
	yn=m*n;
}
inline bool find(int x)
{
	visx[x]=true;
	for(int i=1;i<=yn;i++)
	if(!visy[i])
	{
		int t=lx[x]+ly[i]-map[x][i];
		if(!t)
		{
			visy[i]=true;
			if(res[i]==-1||find(res[i]))
			{
				res[i]=x;
				return true;
			}
		}
		else slack[i]=MIN(slack[i],t);
	}
	return false;
}
inline int KM()
{
	memset(lx,0xaf,sizeof(lx));
	memset(ly,0,sizeof(ly));
	for(int i=1;i<=xn;i++)
	for(int j=1;j<=yn;j++)
	lx[i]=MAX(lx[i],map[i][j]);
	for(int i=1;i<=xn;i++)
	{
		memset(slack,0x7f,sizeof(slack));
		while(1)
		{
			memset(visx,0,sizeof(visx));
			memset(visy,0,sizeof(visy));
			if(find(i))break;
			int d=0x7fffffff;
			for(int i=1;i<=yn;i++)
			if(!visy[i])d=MIN(d,slack[i]);
			for(int i=1;i<=xn;i++)
			if(visx[i])lx[i]-=d;
			for(int i=1;i<=yn;i++)
			if(visy[i])ly[i]+=d;
			else slack[i]-=d;
		}
	}
	int ret=0;
	for(int i=1;i<=yn;i++)
	if(res[i]!=-1)ret-=map[res[i]][i];
	return ret;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		init();
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		scanf("%d",&w[i][j]);
		build_graph();
		printf("%.6f\n",(double)KM()/(double)n);;
	}
	return 0;
}
