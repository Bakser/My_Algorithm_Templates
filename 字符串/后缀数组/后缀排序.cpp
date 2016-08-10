#include <bits/stdc++.h>
using namespace std;
const int N(1e5+200);
typedef long long LL;
int n,c[N*2],t1[N*2],t2[N*2],sa[N*2],h[N*2],rank[N*2];
char s[N*2];
inline bool cmp(int *y,int a,int b,int k){
	return y[a]==y[b]&&(a+k>=n?-1:y[a+k])==(b+k>=n?-1:y[b+k]);
}
inline void build_sa(){
	for(int i(0);i<n;i++)s[i]=s[i]-'a'+1;
	int *x=t1,*y=t2,m=27;
	for(int i(0);i<m;i++)c[i]=0;
	for(int i(0);i<n;i++)c[x[i]=s[i]]++;
	for(int i(1);i<m;i++)c[i]+=c[i-1];
	for(int i(n-1);i>=0;i--)
		sa[--c[x[i]]]=i;
	for(int k(1),p(0);p<n&&k<n;k<<=1,m=p){
		p=0;
		for(int i(n-k);i<n;i++)y[p++]=i;
		for(int i(0);i<n;i++)if(sa[i]>=k)y[p++]=sa[i]-k;
		for(int i(0);i<m;i++)c[i]=0;
		for(int i(0);i<n;i++)c[x[y[i]]]++;
		for(int i(1);i<m;i++)c[i]+=c[i-1];
		for(int i(n-1);i>=0;i--)sa[--c[x[y[i]]]]=y[i];
		swap(x,y);p=1;x[sa[0]]=0;
		for(int i(1);i<n;i++)x[sa[i]]=cmp(y,sa[i-1],sa[i],k)?p-1:p++;
	}
	for(int i(0);i<n;i++)rank[sa[i]]=i;
}
inline void get_height(){
	for(int i(0);i<n;i++)rank[sa[i]]=i;
	int k(0),j;
	for(int i(0);i<n;h[rank[i++]]=k)
		if(rank[i]-1<0)k=0;
		else for(k?k--:0,j=sa[rank[i]-1];s[j+k]==s[i+k];k++);
}
int main(){
	scanf("%s",s);n=strlen(s);
	build_sa();
	get_height();
	for(int i(0);i<n;i++)printf("%d ",sa[i]+1);puts("");
	for(int i(1);i<n;i++)printf("%d ",h[i]);puts("");
	return 0;
}

