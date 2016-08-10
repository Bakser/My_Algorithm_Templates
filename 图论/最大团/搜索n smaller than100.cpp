//f[i]表示1-n的点形成的最大团（不一定有i）
//q[i]表示当前最大团大小是i且与i个点都有边的点
#include<cstdio>
const int N(101);
int n,map[N][N],f[N],q[N][N],ans,tot;
inline void dfs(int dep,int num)
{
	if(!num)return (void)(dep>ans?ans=dep:0);
	for(int i(1),x,tot(0);i<=num;tot=0,i++)
	{
		if(num-i+1+dep<=ans||dep+f[x=q[dep][i]]<=ans)return;//剪枝 
		for(int j(i+1);j<=num;j++)
			if(map[q[dep][i]][q[dep][j]])
				q[dep+1][++tot]=q[dep][j];
		dfs(dep+1,tot);
	}
}
int main()
{
	scanf("%d",&n);
	for(int a,b;~scanf("%d%d",&a,&b);map[a][b]=map[b][a]=1);
	for(int i(n);i;tot=0,i--)
	{
		for(int j(i+1);j<=n;j++)
			if(map[i][j])
				q[1][++tot]=j;
		dfs(1,tot);
		f[i]=ans;
	}
	printf("%d\n",ans);
	return 0;
}

