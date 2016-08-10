#include <cstdio>
using namespace std;
const int maxn=100001;
int f[maxn],son[maxn][2],num[maxn],sum[maxn],n,root,tot,a[maxn];
void rotate(int x,int w)
{
    int y=f[x];
    if (f[y]) if (y==son[f[y]][0]) son[f[y]][0]=x; else son[f[y]][1]=x;
    f[x]=f[y];
    if (son[x][w]) f[son[x][w]]=y;
    son[y][1-w]=son[x][w];
    f[y]=x;
    son[x][w]=y;
    sum[y]=sum[son[y][0]]+sum[son[y][1]]+num[y];
}
void splay(int x,int w)
{
    int y;
    while (f[x]!=w)
    {
        y=f[x];
        if (f[y]==w) if (x==son[y][0]) rotate(x,1); else rotate(x,0);
        else if (y==son[f[y]][0]) if (x==son[y][0]) {rotate(y,1); rotate(x,1);} else {rotate(x,0); rotate(x,1);}
                else if (x==son[y][0]) {rotate(x,1); rotate(x,0);} else {rotate(y,0); rotate(x,0);}
    }
    sum[x]=sum[son[x][0]]+sum[son[x][1]]+num[x];
    if (w==0) root=x;
}
void insert(int value)
{
    if (root==0)
    {
        a[++tot]=value;
        root=tot;
        sum[tot]=num[tot]=1;
        return;
    }
    int x=root;
    while (a[x]!=value)
        if (a[x]>value) if (son[x][0]) x=son[x][0]; else break;
            else if (son[x][1]) x=son[x][1]; else break;
    if (a[x]==value) {num[x]++; splay(x,0); return;}
    a[++tot]=value;
    f[tot]=x;
    num[tot]=sum[tot]=1;
    if (a[x]>value) son[x][0]=tot; else son[x][1]=tot;
    splay(x,0);
}
void del(int value)
{
    int x=root;
    while (a[x]!=value)
        if (a[x]>value) if (son[x][0]) x=son[x][0]; else break;
            else if (son[x][1]) x=son[x][1]; else break;
    splay(x,0);
    if (num[x]>1) {num[x]--; return;}
    if (!son[x][1]) {root=son[x][0]; f[son[x][0]]=0; return;}
    int y=son[x][1];
    while (son[y][0]) y=son[y][0];
    splay(y,x);
    son[y][0]=son[x][0];
    f[son[x][0]]=y;
    root=y;
    f[y]=0;
    sum[y]=sum[son[y][0]]+sum[son[y][1]]+num[y];
}
int getrank(int value)
{
    int x=root;
    while (a[x]!=value)
        if (a[x]>value) if (son[x][0]) x=son[x][0]; else break;
            else if (son[x][1]) x=son[x][1]; else break;
    splay(x,0);
    return (sum[son[x][0]]+1);
}
int paiming(int k)
{
    int x=root;
    while (true)
        if (sum[son[x][0]]>=k) x=son[x][0];
        else if (sum[son[x][0]]+num[x]>=k) return a[x];
            else {k-=sum[son[x][0]]+num[x]; x=son[x][1];}
}
int pre(int value)
{
    int x=root;
    while (a[x]!=value)
        if (a[x]>value) if (son[x][0]) x=son[x][0]; else break;
            else if (son[x][1]) x=son[x][1]; else break;
    if (a[x]==value)
    {
        splay(x,0);
        for (x=son[x][0];son[x][1];x=son[x][1]);
        return a[x];
    }
    while (a[x]>value) x=f[x];
    return (a[x]);
}
int succ(int value)
{
    int x=root;
    while (a[x]!=value)
        if (a[x]>value) if (son[x][0]) x=son[x][0]; else break;
            else if (son[x][1]) x=son[x][1]; else break;
    if (a[x]==value)
    {
        splay(x,0);
        for (x=son[x][1];son[x][0];x=son[x][0]);
        return a[x];
    }
    while (a[x]<value) x=f[x];
    return (a[x]);
}
int main()
{
    scanf("%d",&n);
    int i,kind,x;
    for (i=1;i<=n;i++)
    {
        scanf("%d%d",&kind,&x);
        if (kind==1) {insert(x); continue;}
        if (kind==2) {del(x); continue;}
        if (kind==3) {printf("%d\n",getrank(x)); continue;}
        if (kind==4) {printf("%d\n",paiming(x)); continue;}
        if (kind==5) printf("%d\n",pre(x)); else printf("%d\n",succ(x));
    }
    return 0;
}
