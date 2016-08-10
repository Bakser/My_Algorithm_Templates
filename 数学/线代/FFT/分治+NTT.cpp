#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MOD(1004535809);
const int N(530500);
const int g(3);
inline int kpm(int x,LL k){
	int res(1);
	for(;k;k>>=1){
		if(k&1)res=(LL)res*x%MOD;
		x=(LL)x*x%MOD;
	}
	return res;
}
int T[N],a[N],b[N],f[N],inv[N],itwo[N],fac[N],ifac[N],G[N],nG[N];
int n,rev[N];
inline void NTT(int *a,int n,int f){
	for(int i(0);i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int i(1),c(1);i<n;i<<=1,c++){
		int wn=f==1?G[c]:nG[c];
		for(int j(0);j<n;j+=i<<1){
			int w=1;
			for(int k(0);k<i;w=(LL)w*wn%MOD,k++){
				int x=a[j+k],y=(LL)a[j+k+i]*w%MOD;
				a[j+k]=((LL)x+y)%MOD;a[j+k+i]=((LL)x-y+MOD)%MOD;
			}
		}
	}
}
inline void solve(int l,int r){
	if(l==r){f[l]=((LL)T[l]-(LL)fac[l-1]*f[l]%MOD+MOD)%MOD;return;}
	int mid(l+r>>1),n=max(mid-l+1,r-mid),K,N;
	solve(l,mid);
	for(N=1,K=0;N<=(n<<1);N<<=1,K++);
	for(int i(1);i<N;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(K-1));
	for(int i(0);i<N;i++)a[i]=b[i]=0;
	for(int i(l);i<=mid;i++)a[i-l]=(LL)ifac[i-1]*f[i]%MOD;
	for(int i(1);i<=r-l;i++)b[i]=(LL)T[i]*ifac[i]%MOD;
	NTT(a,N,1);
	NTT(b,N,1);
	for(int i(0);i<N;i++)a[i]=(LL)a[i]*b[i]%MOD;
	NTT(a,N,-1);
	for(int i(mid+1);i<=r;i++)f[i]=((LL)f[i]+(LL)a[i-l]*itwo[K]%MOD)%MOD;
	solve(mid+1,r);
}
int main(){
	//freopen("test.txt","r",stdin);
	scanf("%d",&n);
	int N,K;
	for(N=1,K=0;N<=(n<<1);K++,N<<=1);
	nG[K]=kpm(G[K]=kpm(g,(MOD-1)/N),MOD-2);
	for(int i(K-1);i>=0;i--)G[i]=(LL)G[i+1]*G[i+1]%MOD,nG[i]=(LL)nG[i+1]*nG[i+1]%MOD;//处理单位根。
	for(int i(1);i<=n;i++)inv[i]=kpm(i,MOD-2);
	itwo[0]=1;itwo[1]=kpm(2,MOD-2);
	for(int i(2);i<=K;i++)itwo[i]=(LL)itwo[i-1]*itwo[1]%MOD;
	fac[0]=ifac[0]=1;
	for(int i(1);i<=n;i++)fac[i]=(LL)fac[i-1]*i%MOD,ifac[i]=(LL)ifac[i-1]*inv[i]%MOD;
	T[1]=1;
	for(int i(2);i<=n;i++)T[i]=kpm(2,(LL)i*(i-1)>>1);
	solve(1,n);
	printf("%d\n",f[n]);
	return 0;
}
