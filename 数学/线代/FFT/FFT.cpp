#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef double LD;
const int MAXN(5e5);
const LD pi(acos(-1.0));
struct cp{
	LD r,i;
	cp(LD _r=0,LD _i=0):r(_r),i(_i){}
	inline cp operator +(const cp &b)const{return cp(r+b.r,i+b.i);}
	inline cp operator -(const cp &b)const{return cp(r-b.r,i-b.i);}
	inline cp operator *(const cp &b)const{return cp(r*b.r-i*b.i,r*b.i+i*b.r);}
}a[MAXN],b[MAXN],c[MAXN];
int n,m,N,rev[MAXN],len,bitlen;
inline int read(){
	char c=0;int x=0,f=1;
	for(;c<'0'||c>'9';c=getchar())if(c=='-')f=-1;
	for(x=0;c>='0'&&c<='9';c=getchar())x=x*10+(c-'0');
	return x*f;
}
inline void FFT(cp *a,int n,int f){
	for(int i(0);i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int i(1);i<n;i<<=1){
		cp wn(cos(pi/i),f*sin(pi/i));
		for(int j(0);j<n;j+=i<<1){
			cp w(1,0);
			for(int k(0);k<i;k++,w=w*wn){
				cp x=a[j+k],y=w*a[j+k+i];
				a[j+k]=x+y;a[j+k+i]=x-y;
			}
		}
	}
	if(f==-1)for(int i(0);i<n;i++)a[i].r/=n;
}
int main(){
	freopen("test.txt","r",stdin);
	n=read();m=read();len=n+m+1;
	for(N=1,bitlen=0;N<len;N<<=1,bitlen++);
	for(int i(1);i<N;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(bitlen-1));
	for(int i(0);i<=n;i++)a[i].r=read();
	for(int i(0);i<=m;i++)b[i].r=read();
	FFT(a,N,1);FFT(b,N,1);
	for(int i(0);i<N;i++)c[i]=a[i]*b[i];
	FFT(c,N,-1);
	for(int i(0);i<len;i++)printf("%d ",int(c[i].r+0.5));
	return 0;
}
