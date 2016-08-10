#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N=100005;
const int INF=0x3f3f3f3f;
int pre[N],key[N],ch[N][2],root,tot1;
//分别表示父结点，键值，左右孩子（0左1右），根结点，结点数量
int n;
//新建一个结点
void NewNode(int &r,int father,int k)
{
    r=++tot1;
    pre[r]=father;
    key[r]=k;
    ch[r][0]=ch[r][1]=0;//左右孩子为空
}
//旋转，kind为1是右旋，为0是左旋
void Rotate(int x,int kind)
{
    int y=pre[x];
    ch[y][!kind]=ch[x][kind];
    pre[ch[x][kind]]=y;
    if(pre[y])
      ch[pre[y]][ch[pre[y]][1]==y]=x;
    pre[x]=pre[y];
    ch[x][kind]=y;
    pre[y]=x;
}
//Splay调整，将结点r调整到goal下面
void Splay(int r,int goal)
{
    while(pre[r]!=goal)
    {
        if(pre[pre[r]]==goal)Rotate(r,ch[pre[r]][0]==r);
        else
        {
            int y=pre[r];
            int kind=ch[pre[y]][0]==y;
            if(ch[y][kind]==r)
            {
                Rotate(r,!kind);
                Rotate(r,kind);
            }
            else
            {
                Rotate(y,kind);
                Rotate(r,kind);
            }
        }
    }
    //更新根结点
    if(goal==0)root=r;
}
int Insert(int k)
{
    int r=root;
    while(ch[r][key[r]<k])
    {
        //不重复插入
        if(key[r]==k)
        {
            Splay(r,0);
            return 0;
        }
        r=ch[r][key[r]<k];
    }
    NewNode(ch[r][key[r]<k],r,k);
    Splay(ch[r][key[r]<k],0);
    return 1;
}
//找前驱
int get_pre(int x)
{
    int tmp=ch[x][0];
    if(tmp==0)return INF;
    while(ch[tmp][1])
      tmp=ch[tmp][1];
    return key[x]-key[tmp];
}
//找后继
int get_next(int x)
{
    int tmp=ch[x][1];
    if(0==tmp) return INF;
    while(ch[tmp][0])
      tmp=ch[tmp][0];
    return key[tmp]-key[x];
}
int main()
{
    while(scanf("%d",&n)==1)
    {
        root=tot1=0;
        int ans=0;
        for(int i=1;i<=n;i++)
        {
            int num;
            if(scanf("%d",&num)==EOF)num=0;//这是变态之处==
            if(i==1)
            {
                ans+=num;
                NewNode(root,0,num);
                continue;
            }
            if(Insert(num)==0)continue;
            int a=get_pre(root);
            int b=get_next(root);
            ans+=min(a,b);
        }
        printf("%d\n",ans);
    }
    return 0;
}
