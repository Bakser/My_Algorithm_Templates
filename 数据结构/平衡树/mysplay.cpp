//��������Kֵ 
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
#define N 200
typedef pair<int,int> pii;
int tot,n,size[N],pre[N],ch[N][2],val[N],root,map[N];
queue<int> pool;
inline void newnode(int &x,int fa,int key)//����һ���½ڵ㣨�������գ� 
{
	if(!pool.empty())x=pool.front(),pool.pop();
	else x=++tot;
	pre[x]=fa;
	ch[x][0]=ch[x][1]=0;
	size[x]=1;
	val[x]=key;
}
inline void push_up(int x)//���ӽڵ��ռ���Ϣ 
{
	size[x]=size[ch[x][0]]+size[ch[x][1]]+1;
}
inline void rotate(int x,int f)//��ת��f==1 ������0���� 
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
inline void splay(int x,int goal)//��x��ת��goal���� 
{
	while(pre[x]!=goal)
	{
		if(pre[pre[x]]==goal)rotate(x,ch[pre[x]][0]==x);
		else
		{
			int y=pre[x],f=(ch[pre[y]][0]==y);
			if(ch[y][f]==x)rotate(x,!f);
			else rotate(y,f);
			rotate(x,f);
		}
	}
	push_up(x);
	if(!goal)root=x;
}
inline int insert(int &root,int key)//����һ��ȨֵΪkey�ĵ� 
{
	if(!root)newnode(root,0,key);
	int x=root;
	while(ch[x][val[x]<key])
	{
		if(val[x]==key){splay(x,0);return 0;}
		x=ch[x][val[x]<key];
	}
	newnode(ch[x][val[x]<key],x,key);
	splay(ch[x][val[x]<key],0);
	return 1;
}
inline int find(int root,int key)//����һ��ȨֵΪkey�ĵ� 
{
	int x=root;
	while(ch[x][val[x]<key])
	{
		if(val[x]==key)return x;
		x=ch[x][val[x]<key];
	}
	if(val[x]==key)return x;
	return 0;
}
inline int get_pre(int x)//�ҽڵ�x��ǰ��
{
	if(!x)return -1;
	if(ch[x][0])x=ch[x][0];
	else return -1;
	while(ch[x][1])
		x=ch[x][1];
	return x;
}
inline void del(int &root,int key)//ɾ��һ��ȨֵΪkey�ĵ� 
{
	int x=find(root,key);
	if(!x)return;
	splay(x,0);
	if(ch[x][0]&&ch[x][1])
	{
		int tson=get_pre(x);
		splay(tson,x);
		ch[tson][1]=ch[x][1];
		pre[ch[x][1]]=tson;
		pre[tson]=0;
		root=tson;
	}
	else if(!ch[x][0]&&!ch[x][1])root=0;
	else pre[ch[x][ch[x][1]]]=0,root=ch[x][ch[x][1]];
	pool.push(x);
}
inline void split(int x)//�Խڵ�xΪ����ѳ�������
{
	splay(x,0);
	pre[ch[x][1]]=0;
	ch[x][1]=0;
}
inline void merge(int x,int y)//����ʽ�ϲ�x��y���ڵ��������� 
{
	splay(x,0);
	splay(y,0);
	if(size[x]>size[y])swap(x,y);
	queue<int> q;
	q.push(x);
	while(!q.empty())
	{
		int z=q.front();q.pop();
		if(ch[z][0])q.push(ch[z][0]);
		if(ch[z][1])q.push(ch[z][1]);
		pool.push(z);
		insert(y,val[z]);
	}
}
inline int select(int root,int k)
{
	int x=root;	
	while(x)
	{
		int tmp=size[ch[x][0]];
		if(k==tmp+1)break;
		else if(k<=tmp)x=ch[x][0];
		else k-=tmp+1,x=ch[x][1];
	}
	splay(x,0);
	return val[x];
}
//�������������
inline void del_range(int s,int t)
{
	splay(map[s-1],0);
	splay(map[t+1],map[s-1]);
	ch[map[t+1]][0]=0;
	int x=ch[map[t+1]][0];
	queue<int> q;
	q.push(x);
	while(!q.empty())
	{
		int y=q.front();q.pop();
		if(ch[y][0])q.push(ch[y][0]);
		if(ch[y][1])q.push(ch[y][1]);
		pool.push(y);
	}
}
int main()
{	
//	freopen("test.txt","r",stdin);
	tot=0;
	while(!pool.empty())pool.pop();
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int tmp;
		scanf("%d",&tmp);
		if(i==0)newnode(root,0,tmp);
		else insert(root,tmp);
	}
	int k,tmp;
	scanf("%d",&k);
	char c;
	while(k--)
	{
		while(c!='Q'&&c!='D'&&c!='I')c=getchar();
		scanf("%d",&tmp);
		if(c=='Q')printf("%d\n",select(root,tmp));
		else if(c=='D')del(root,tmp);
		else insert(root,tmp);
		c=0;
	}	
	return 0;
}
