//WC2008游览计划
//f[i][s]表示以i为根,关键点联通状况为s的最小代价
//f[i][s]=min(f[i][s],f[i][s']+f[i][s-s'])(s'是s的子集)这一部分转移通过枚举子集实现
//f[i][s]=min(f[i][s],f[i'][s]+w(i',i))(存在边i'-i)这一部分转移对于每个s做一遍spfa实现
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int N(12);
const int ALL(1<<11);
const int INF(0x3f3f3f3f);
const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};
int n,m,num,mp[N][N],sta[N][N],f[N][N][ALL];
bool vis[N][N];
struct hh{
	int x,y,s;
	hh(int _x=0,int _y=0,int _s=0):x(_x),y(_y),s(_s){}
}pre[N][N][ALL];
typedef pair<int,int> pii;
queue<pii> q;
inline void spfa(int S){
	memset(vis,0,sizeof(vis));
	for(;!q.empty();){
		int x=q.front().first,y=q.front().second;q.pop();
		vis[x][y]=0;
		for(int i(0);i<4;i++){
			int tx=dx[i]+x,ty=dy[i]+y;
			if(tx<=0||ty<=0||tx>n||ty>m)continue;
			if(f[x][y][S]+mp[tx][ty]<f[tx][ty][S]){
				f[tx][ty][S]=f[x][y][S]+mp[tx][ty];
				pre[tx][ty][S]=hh(x,y,S);
				if(!vis[tx][ty])q.push(pii(tx,ty)),vis[tx][ty]=1;
			}
		}
	}
}
inline void find(int x,int y,int s){
	if(x==INF||!pre[x][y][s].s)return;
	vis[x][y]=1;hh tmp=pre[x][y][s];
	find(tmp.x,tmp.y,tmp.s);
	if(tmp.x==x&&tmp.y==y)find(x,y,s-tmp.s);
}
int main(){
	scanf("%d%d",&n,&m);
	memset(f,0x3f,sizeof(f));
	for(int i(1);i<=n;i++)
		for(int j(1);j<=m;j++){
			scanf("%d",&mp[i][j]);
			if(!mp[i][j])
				f[i][j][1<<(num++)]=0;
		}
	for(int S(1);S<(1<<num);S++){
		for(int i(1);i<=n;i++)
			for(int j(1);j<=m;j++){
				for(int s((S-1)&S);s;s=(s-1)&S)
					if(f[i][j][S]>f[i][j][s]+f[i][j][S-s]-mp[i][j]){
						f[i][j][S]=f[i][j][s]+f[i][j][S-s]-mp[i][j];
						pre[i][j][S]=hh(i,j,s);
					}
				if(f[i][j][S]<INF)q.push(pii(i,j)),vis[i][j]=1;	
			}
		spfa(S);
	}
	memset(vis,0,sizeof(vis));
	bool flag=0;
	for(int i(1);i<=n&&!flag;i++)
		for(int j(1);j<=m&&!flag;j++)
			if(!mp[i][j]){
				find(i,j,(1<<num)-1);
				printf("%d\n",f[i][j][(1<<num)-1]);
				flag=1;
			}
	for(int i(1);i<=n;i++){
		for(int j(1);j<=m;j++){
			if(!mp[i][j])putchar('x');
			else putchar(vis[i][j]?'o':'_');
		}
		puts("");
	}
	return 0;
}
