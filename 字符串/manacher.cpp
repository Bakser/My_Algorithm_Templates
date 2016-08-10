#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N(2e5+200);
char a[N],s[N];
int n,len,f[N],l[N],r[N];
int main(){
	freopen("test.txt","r",stdin);
	scanf("%s",a+1);
	len=strlen(a+1);
	s[0]='/';
	s[1]='#';
	for(int i(1);i<=len;i++){
		s[i<<1]=a[i];
		s[i<<1|1]='#';
	}
	s[(len+1)<<1]='-';
	n=len<<1|1;//将字符串处理
	f[1]=1;int mxid=2,id=1;//mxid表示目前找到的回文串的最靠右的端点，id表示这个回文串的中心
	for(int i(2);i<=n;i++){
		f[i]=mxid>i?min(f[2*id-i],mxid-i):1;//对称过去
		for(;s[i+f[i]]==s[i-f[i]];f[i]++){//暴力扩展
			l[i+f[i]-1]=max(l[i+f[i]-1],f[i]-1);//顺便维护每个点为左右端点的最长回文串。
			r[i-f[i]+1]=max(r[i-f[i]+1],f[i]-1);
		}
		l[i+f[i]-1]=max(l[i+f[i]-1],f[i]-1);
		r[i-f[i]+1]=max(r[i-f[i]+1],f[i]-1);
		if(i+f[i]>mxid)mxid=i+f[i],id=i;//更新
	}
	int ans(0);
	for(int i(2);i<n;i++)ans=max(ans,l[i]+r[i]);
	printf("%d\n",ans);
	return 0;
}
