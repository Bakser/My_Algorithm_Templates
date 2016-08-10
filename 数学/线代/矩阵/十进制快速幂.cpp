#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define N 100
#define MOD 10007
struct matrix
{
	int m[N][N];
}m,I;
int n,k;
inline matrix multi(matrix a,matrix b)//O(n^3)矩阵乘法 
{
	matrix c;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			c.m[i][j]=0;
			for(int k=0;k<n;k++)
				c.m[i][j]+=(a.m[i][k]%MOD)*(b.m[k][j]%MOD)%MOD;
		}
	return c;
}
inline matrix pow(matrix x,int k)//二分快速幂 
{
	matrix ans=I,p=x;
	while(k)
	{
		if(k&1)
		{
			ans=multi(ans,p);
			k^=1;
		}
		k>>=1;
		p=multi(p,p);
	}
	return ans;
}
inline matrix T_pow(matrix x,int k)//十进制快速幂 
{	
	matrix ans=I,p=x;
	while(k)
	{
		int t=k%10;
		ans=multi(ans,pow(p,t));
		p=pow(p,10);
		k/=10;
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&k);//n*n的矩阵，k次幂 
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
	{
		scanf("%d",&m.m[i][j]);
		if(i==j)I.m[i][j]=1;
		else I.m[i][j]=0;
	}
	matrix res=T_pow(m,k);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			printf("%d ",res.m[i][j]);
		puts("");
	}
	return 0;
}
