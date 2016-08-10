#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long LL;
const LL MOD(1004535809);
const int MAXN(100000);
LL a[MAXN],b[MAXN],N,K,G[MAXN],nG[MAXN],rev[MAXN],itwo[MAXN];
inline LL power(LL x,LL k){
	LL res(1);
	for(;k;k>>=1){
		if(k&1)res=res*x%MOD;
		x=x*x%MOD;
	}
	return res;
}
inline void NTT(LL *a,int n,int f){
	for(int i(0);i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int i(1),c(1);i<n;i<<=1,c++){
		LL wn=f==1?G[c]:nG[c];
		for(int j(0);j<n;j+=i<<1){
			LL w=1;
			for(int k(0);k<i;k++,w=w*wn%MOD){
				LL x=a[j+k],y=w*a[j+k+i]%MOD;
				a[j+k]=(x+y)%MOD;a[j+k+i]=(x-y+MOD)%MOD;
			}
		}
	}
}
int main(){
	int n;
	cin>>n;
	for(N=1,K=0;N<=(n<<1);N<<=1,K++);//注意n<<1
	G[K]=power(3,(MOD-1)/N);nG[K]=power(G[K],MOD-2);
	for(int i(K-1);i>=0;i--)G[i]=G[i+1]*G[i+1]%MOD,nG[i]=nG[i+1]*nG[i+1]%MOD;//预处理单位根
	for(int i(1);i<N;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(K-1));
	itwo[1]=power(2,MOD-2);
	itwo[0]=1;	
	for(int i(2);i<N;i++)itwo[i]=itwo[i-1]*itwo[1]%MOD;//预处理2的幂的逆元
	for(int i(0);i<n;i++)cin>>a[i];
	for(int i(0);i<n;i++)cin>>b[i];
	NTT(a,N,1);NTT(b,N,1);
	for(int i(0);i<N;i++)a[i]=a[i]*b[i]%MOD;
	NTT(a,N,-1);
	for(int i(0);i<N;i++)cout<<a[i]*itwo[K]%MOD<<" ";//IDFT完了以后每个数都要除以2^k
	return 0;
}
