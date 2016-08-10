#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
#define N 1011000
int n,tot,root,tag,pre[N],val[N],ch[N][2],tmp,size[N],cnt[N];
queue<int> pool;
inline void push_up(int x)
{
	size[x]=size[ch[x][0]]+size[ch[x][1]]+cnt[x];
}
inline void newnode(int &x,int fa,int key)
{
	x=++tot;
	pre[x]=fa;
	val[x]=key;
	ch[x][0]=ch[x][1]=0;
	size[x]=cnt[x]=1;
}
inline void rotate(int x,int f)
{
	int y=pre[x];
	ch[y][!f]=ch[x][f];
	pre[ch[x][f]]=y;
	if(pre[y])ch[pre[y]][ch[pre[y]][1]==y]=x;
	pre[x]=pre[y];
	ch[x][f]=y;
	pre[y]=x;
	push_up(y);
}
inline void splay(int x,int goal)
{
	if(!x)return;
	while(pre[x]!=goal)
	{
		if(pre[pre[x]]==goal)rotate(x,ch[pre[x]][0]==x);
		else
		{
			int y=pre[x],f=ch[pre[y]][0]==y;
			if(ch[y][f]==x)rotate(x,!f);
			else rotate(y,f);
			rotate(x,f);
		}
	}
	push_up(x);
	if(!goal)root=x;
}
inline int find(int key)
{
	int x=root;
	while(val[x]!=key)
	if(ch[x][val[x]<=key])x=ch[x][val[x]<=key];
	else break;
	return x;
}
inline int get_pre(int key)
{
	int x=find(key);
	if(val[x]==key)
	{
		splay(x,0);
		for(x=ch[x][0];ch[x][1];x=ch[x][1]);
		return val[x];
	}
	while(val[x]>key&&pre[x])x=pre[x];
	return val[x];
}
inline int get_next(int key)
{
	int x=find(key);
	if(val[x]==key)
	{
		splay(x,0);
		for(x=ch[x][1];ch[x][0];x=ch[x][0]);
		return val[x];
	}
	while(val[x]<key&&pre[x])x=pre[x];
	return val[x];
}
inline void insert(int key)
{
	if(!root){newnode(root,0,key);return;}
	int x=find(key);
	if(val[x]==key){cnt[x]++;splay(x,0);return;}
	newnode(ch[x][val[x]<key],x,key);
    splay(ch[x][val[x]<key],0);
}
inline void del(int key)
{
	int x=find(key);
	splay(x,0);
	if(cnt[x]>1){cnt[x]--;push_up(x);return;}
	if(!ch[x][1]){root=ch[x][0];pre[ch[x][0]]=0;return;}
	int y=ch[x][1];
	while(ch[y][0])y=ch[y][0];
	splay(y,x);
	ch[y][0]=ch[x][0];
	pre[ch[x][0]]=y;
	root=y;
	pre[y]=0;
	push_up(y);
}
inline int find_rank(int key)
{
	int x=find(key);
	splay(x,0);
	return size[ch[x][0]]+1;
}
inline int select(int k)
{
	int x=root;
	while(1)
	{
		int t=size[ch[x][0]];
		if(k<=t)x=ch[x][0];
		else if(k<=t+cnt[x])return val[x];
		else k-=t+cnt[x],x=ch[x][1];
	}
}
int main()
{
	tot=root=0;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d%d",&tag,&tmp);
		if(tag==1)insert(tmp);
		else if(tag==2)del(tmp);
		else if(tag==3)printf("%d\n",find_rank(tmp));
		else if(tag==4)printf("%d\n",select(tmp));
		else if(tag==5)printf("%d\n",get_pre(tmp));
		else printf("%d\n",get_next(tmp));
	}
	return 0;
}
