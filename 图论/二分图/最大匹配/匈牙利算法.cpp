//bzoj1433 
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 110
int in[N],left[N],T,n,res[N],sum,ans;
bool map[N][N],vis[N];
inline bool find(int x)
{
	for(int i=1;i<=n+n;i++)
	if(map[x][i]&&!vis[i])
	{
		vis[i]=true;
		if(res[i]==-1||find(res[i]))
		{
			res[i]=x;
			return true;
		}
	}
	return false;
}
inline void MaxMatch()
{
	ans=0;
	memset(res,0xff,sizeof(res));
	for(int i=1;i<=n+n;i++)
	{
		memset(vis,0,sizeof(vis));
		if(find(i))ans++;
	}
}
int main()
{
//	freopen("test.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		memset(map,0,sizeof(map));
		memset(in,0,sizeof(in));
		memset(left,0,sizeof(left));
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		scanf("%d",&in[i]);
		sum=n;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&left[i]);
			if(in[i]&&left[i])sum--;
		}
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			int hh;
			scanf("%d",&hh);
			if(in[i]&&left[i])continue;
			if(i==j&&in[i])
			map[i][i+n]=true;
			else if(hh&&in[j])
				map[i][j+n]=true;
		}
		MaxMatch();
		if(ans==sum)printf("^_^\n");
		else printf("T_T\n");
	}
	return 0;
}
