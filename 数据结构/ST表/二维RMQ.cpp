//poj2019 
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
#define N 255
#define DEG 9
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
typedef short int hh;
hh n,b,q,maxf[N][N][DEG][DEG],minf[N][N][DEG][DEG],x,y;
inline int log_2(int x)
{
	return (int)(log((double)x)/log(2.0));
}
inline void prepare()
{
	for(int i=0;(1<<i)<=n;i++)
	for(int j=0;(1<<j)<=n;j++)
	if(j||i)
	for(int x=1;x+(1<<i)-1<=n;x++)
	for(int y=1;y+(1<<j)-1<=n;y++)
	if(!i)
	{
		maxf[x][y][i][j]=MAX(maxf[x][y][i][j-1],maxf[x][y+(1<<(j-1))][i][j-1]);
		minf[x][y][i][j]=MIN(minf[x][y][i][j-1],minf[x][y+(1<<(j-1))][i][j-1]);
	}
	else 
	{
		maxf[x][y][i][j]=MAX(maxf[x][y][i-1][j],maxf[x+(1<<(i-1))][y][i-1][j]);
		minf[x][y][i][j]=MIN(minf[x][y][i-1][j],minf[x+(1<<(i-1))][y][i-1][j]);
	}
}
inline int query(int x1,int y1,int x2,int y2)
{
	int minn=9999,maxx=-1000,r=log_2(x2-x1+1),t=log_2(y2-y1+1);
	minn=MIN(minf[x1][y1][r][t],minf[x2-(1<<r)+1][y1][r][t]);
	minn=MIN(minn,MIN(minf[x1][y2-(1<<t)+1][r][t],minf[x2-(1<<r)+1][y2-(1<<t)+1][r][t]));
	maxx=MAX(maxf[x1][y1][r][t],maxf[x2-(1<<r)+1][y1][r][t]);
	maxx=MAX(maxx,MAX(maxf[x1][y2-(1<<t)+1][r][t],maxf[x2-(1<<r)+1][y2-(1<<t)+1][r][t]));
	return (maxx-minn);
	
}
int main()
{
	scanf("%d%d%d",&n,&b,&q);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{
		scanf("%d",&maxf[i][j][0][0]);
		minf[i][j][0][0]=maxf[i][j][0][0];
	}
	prepare();
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d",&x,&y);
		printf("%d\n",query(x,y,x+b-1,y+b-1));
	}
	return 0;
}
