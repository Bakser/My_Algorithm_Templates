#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
#define rep(i,n) for(int i=0;i<n;i++)
#define tr(e,x) for(it e=x.begin();e!=x.end();e++)
#define pb push_back
const int maxn=30000,inf=~0U>>1;
using namespace std;
vector<int> E[maxn],Et[maxn];
typedef vector<int>::iterator it;
int n,q,w[maxn],L,D[maxn],F[maxn];
int own[maxn],M[maxn],S[maxn]={};
void Build(int t,int f,int d)
{
	D[t]=d;F[t]=f;
	int tmp=own[t];
	tr(e,E[t])
	if(*e!=f)
	{
		if(S[tmp]++<L)Et[t].pb(*e),own[*e]=tmp;
		Build(*e,t,d+1);
	}
}
void Dfs(int t,int s,int m)
{
	S[t]=s+=w[t];M[t]=m>?=w[t];
	tr(e,Et[t])Dfs(*e,s,m);
}
void Change(int t,int u)
{
	w[t]=u;
	if(t==own[t])Dfs(t,0,-inf);
	else Dfs(t,S[F[t]],M[F[t]]);
}
void Query(int a,int b,int&s,int&m)
{
	s=0;m=-inf;
	while(a!=b)
	{
		if(D[a]<D[b])swap(a,b);
		if(own[a]==own[b])
		s+=w[a],m>?=w[a],a=F[a];
		else
		{
			if(D[own[a]]<D[own[b]])swap(a,b);
			s+=S[a],m>?=M[a],a=F[own[a]];
		}
	}
	m>?=w[a];s+=w[a];
}
int main()
{
	scanf("%d",&n);int s,t;L=sqrt(n)+1;
	for(int i=0;i<n-1;i++)
		scanf("%d%d",&s,&t),--s,--t,E[s].pb(t),E[t].pb(s);
	for(int i=0;i<n;i++)
	scanf("%d",w+i),own[i]=i;
	Build(0,-1,0);
	for(int i=0;i<n;i++)
	if(own[i]==i)Dfs(i,0,-inf);
	scanf("%d",&q);
	char cmd[100];int S,M;
	for(int i=0;i<q;i++)
	{
		scanf(" ");
		scanf("%s%d%d",cmd,&s,&t);
		if(cmd[0]=='C')Change(s-1,t);
		else
		{
			Query(s-1,t-1,S,M);
			if(cmd[1]=='S')printf("%d\n",S);
			else printf("%d\n",M);
		}
	}
}
