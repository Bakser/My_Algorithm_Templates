#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
#define NODE 10000
#define EDGE 100000
#define QUESTION 1000
#define iter vector<int>::iterator
typedef pair<int,int> pii;
vector<int>tree[NODE],ques[NODE];
map<pii,int>hash;
int n,m,q,rd[NODE],s,t,fa[NODE],ans[QUESTION];
bool vis[NODE];
inline void init()
{
	memset(ans,0,sizeof(ans));
	hash.clear();
	for(int i=0;i<=n;i++)
	{
		tree[i].clear();
		ques[i].clear();
		fa[i]=i;
		rd[i]=0;
		vis[i]=false;
	}
}
inline int find(int x)
{
	if(fa[x]==x)return x;
	else return fa[x]=find(fa[x]);
}
inline void unionn(int x,int y)
{
	int fx=find(x),fy=find(y);
	fa[fy]=fx;
}
inline void tarjan(int u)
{
	vis[u]=true;
	for(iter it=ques[u].begin();it!=ques[u].end();it++) 
		if(vis[*it])
			ans[hash[make_pair(u,*it)]]=find(*it);
	for(iter it=tree[u].begin();it!=tree[u].end();it++)
		if(!vis[*it])tarjan(*it),unionn(u,*it);
}
int main()
{
//	freopen("test.txt","r",stdin);
	while(~scanf("%d%d%d",&n,&m,&q))
	{
		init();
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&s,&t);
			tree[s].push_back(t);
			rd[t]++;
		}
		for(int i=1;i<=q;i++)
		{
			scanf("%d%d",&s,&t);
			ques[s].push_back(t);
			ques[t].push_back(s);
			hash[make_pair(s,t)]=i;
			hash[make_pair(t,s)]=i;
		}
		for(int i=1;i<=n;i++)
		if(!rd[i])
		{
			tarjan(i);
			break;
		}
		for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
	}
	return 0;
}
