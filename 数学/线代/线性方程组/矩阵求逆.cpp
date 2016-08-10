#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
const int MAXN(71);
typedef unsigned long long LL;
int n,p,inv[20002];
map<LL,int> mp;
inline void add(int &x,int y){
	x+=y;
	if(x>=p)x%=p;
}
struct hh{
	int a[MAXN][MAXN];
	inline int* operator[](int x){return a[x];}
	inline void get(){
		for(int i(1);i<=n;i++)
			for(int j(1);j<=n;j++)
				scanf("%d",&a[i][j]);
	}
	inline void clr(){memset(a,0,sizeof(a));}
	inline void setI(){
		for(int i(1);i<=n;i++)a[i][i]=1;
	}
	inline LL hash(){
		LL res(0);
		for(int i(1);i<=n;i++)
			for(int j(1);j<=n;j++)
				res=res*233+a[i][j];
		return res;
	}
	inline hh operator *(const hh &b){
		hh c;c.clr();
		for(int i(1);i<=n;i++)
			for(int j(1);j<=n;j++)
				for(int k(1);k<=n;k++)
					add(c[i][k],a[i][j]*b.a[j][k]);
		return c;
	}
}A,B,invA;
inline hh power(const hh &a,int k){
	hh x=a,res;res.clr();res.setI();
	for(;k;k>>=1){
		if(k&1)res=res*x;
		x=x*x;
	}
	return res;
}
//在原矩阵后面连上一个同样大小的单位矩阵,进行类似高斯消元的操作,把左边消成单位矩阵,右边就是逆矩阵了,消不下去说明不可逆.
inline void gauss(){
	int a[MAXN][MAXN*2],N=n<<1;
	memset(a,0,sizeof (a));
	for(int i(1);i<=n;i++)
		for(int j(1);j<=n;j++)
			a[i][j]=A[i][j];
	for(int i(1);i<=n;i++)a[i][i+n]=1;
	for(int i(1);i<=n;i++){
		int r=i;
		for(int j(i+1);j<=n;j++)if(a[j][i]>a[r][i])r=j;
		swap(a[i],a[r]);
		for(int j(i+1);j<=n;j++){
			int f=a[j][i]*inv[a[i][i]]%p;
			for(int k(i);k<=N;k++)
				a[j][k]=((a[j][k]-a[i][k]*f)%p+p)%p;
		}
	}
	for(int i(2);i<=n;i++)//把除了主对角线上的元素以外其他元素都消成0
		for(int j(i-1);j>=1;j--){
			int f=a[j][i]*inv[a[i][i]]%p;
			for(int k(i);k<=N;k++)
				a[j][k]=((a[j][k]-a[i][k]*f)%p+p)%p;
		}
	for(int i(1);i<=n;i++){//主对角线化为1
		int f=inv[a[i][i]];
		for(int j(i);j<=N;j++)
			a[i][j]=a[i][j]*f%p;
	}
	for(int i(1);i<=n;i++)
		for(int j(1);j<=n;j++)	
			invA[i][j]=a[i][j+n];
}
inline int BSGS(){
	if(A.hash()==B.hash())return 1;
	int m=1;LL t=0;hh C;
	for(;m*m<p;m++);
	mp[B.hash()]=0;
	for(int i(1);i<m;i++){
		B=B*invA;1
		if(mp.count(t=B.hash()))break;
		mp[t]=i;
	}
	A=power(A,m);C.clr();C.setI();
	for(int i(0);i<=m;i++){
		if(mp.count(t=C.hash()))return mp[t]+i*m;
		C=C*A;
	}
	return -1;
}
int main(){
//	freopen("test.txt","r",stdin);
	scanf("%d%d",&n,&p);
	inv[1]=1;for(int i(2);i<p;i++)inv[i]=(p-p/i)*inv[p%i]%p;
	A.get();B.get();
	gauss();
	printf("%d\n",BSGS());
	return 0;
}
