//bzoj2049
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define N 100000
int pre[N],son[N][2],rev[N],n,m;
inline void push_down(int x)
{
	if(!x)return;
	if(rev[x])
	{
		rev[son[x][0]]^=1;
		rev[son[x][1]]^=1;
		rev[x]=0;
		swap(son[x][0],son[x][1]);
	}
}
inline bool not_root(int x)
{
	return (pre[x]!=0&&(son[pre[x]][0]==x||son[pre[x]][1]==x));
}
inline void rotate(int x,int f)
{
	int y=pre[x];
	son[y][!f]=son[x][f];
	if(son[x][f])pre[son[x][f]]=y;
	pre[x]=pre[y];
	if(not_root(y))son[pre[y]][son[pre[y]][1]==y]=x;
	son[x][f]=y;
	pre[y]=x;
}
inline void splay(int x)
{
	push_down(x);
	while(not_root(x))
	{
		if(!not_root(pre[x]))push_down(pre[x]),push_down(x),rotate(x,son[pre[x]][0]==x);
		else
		{
			int y=pre[x];
			push_down(pre[y]);push_down(y);push_down(x);
			int f(son[pre[y]][0]==y);
			if(son[y][f]==x)rotate(x,!f);
			else rotate(y,f);
			rotate(x,f);
		}
	}
}
inline int access(int x)
{
	int v=0;
	for(;x!=0;x=pre[x])
	{
		splay(x);
		son[x][1]=v;
		v=x;
	}	
	return v;
}
inline int find_root(int x)
{
	for(x=access(x);push_down(x),son[x][0]!=0;x=son[x][0]);
	return x;
}
inline void evert(int x)
{
	rev[access(x)]^=1;
	splay(x);
}
inline void link(int x,int y)
{
	evert(x);
	pre[x]=y;
}
inline void cut(int x,int y)
{
	evert(x);
//	access(y);
	splay(y);
	push_down(y);
	pre[son[y][0]]=0;
	son[y][0]=0;
}
int main()
{
	scanf("%d%d",&n,&m);
	while(m--)
	{
		char s[10];
		int x,y;
		scanf("%s%d%d",s,&x,&y);
		if(s[0]=='C')link(x,y);
		else if(s[0]=='D')cut(x,y);
		else puts(find_root(x)==find_root(y)?"Yes":"No");
	}
	return 0;
}
