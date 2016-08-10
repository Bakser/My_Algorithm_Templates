#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;
const int N(120);
struct hh{
	int u,v,w;
	bool operator <(const hh &b)const{
		return w<b.w;
	}
}edges[N*N];
int n,m,num,fa[N],ans,cnt;
inline int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
int main(){
	while(~scanf("%d",&n)){
		num=ans=cnt=0;
		for(int i(1);i<=n;i++)fa[i]=i;
		for(int i(1);i<=n;i++)
			for(int j(1),w;j<=n;j++){
					scanf("%d",&w);
					if(i<j)edges[num++]=(hh){i,j,w};
					
				}
		sort(edges,edges+num);
		for(int i(0);i<num;i++)
			if(find(edges[i].u)!=find(edges[i].v)){
				ans+=edges[i].w;
				fa[find(edges[i].v)]=find(edges[i].u);
				if((++cnt)==n-1)break;
			}
		printf("%d\n",ans);
	}
	return 0;
}
 
