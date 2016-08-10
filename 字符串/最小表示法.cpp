#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N(6e7+20);
int n;
unsigned char s[N];
int main(){
//	freopen("test.txt","r",stdin);
	scanf("%d",&n);scanf(" ");
	for(int i(0);i<n;i++)scanf("%c",s+i);
	for(int i(0);i<n;i++)s[i+n]=s[i];
	int p1=0,p2=1,k=0;
	for(;p1<n&&p2<n&&k<n;){
		k=0;
		while(k<n&&s[p1+k]==s[p2+k])k++;
		if(s[p1+k]>s[p2+k])p1+=k+1;
		if(s[p1+k]<s[p2+k])p2+=k+1;
		if(p1==p2)p2++;
	}
	if(p1>p2)swap(p1,p2);
	for(int i(0);i<n;i++)
		printf("%c",s[p1+i]);
	puts("");
	return 0;
}
