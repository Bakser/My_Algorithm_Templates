#include<cstdio>
#include<algorithm>
#include<climits>
#include<cstring>
using namespace std;
const int MAXL=2*1024*1024+100;
const int B_SIZE=5000;
const int B_NUM=MAXL/B_SIZE*2+100;
int Pool[B_NUM],blocknum,next[B_NUM],cursize[B_NUM];
char data[B_NUM][B_SIZE],cmd[20],str[MAXL];

void prepare()
{
	for(int i=1;i<B_NUM;++i)
	  Pool[i]=i;
	blocknum=1;
	next[0]=-1;
	cursize[0]=0;
}
int Getnew()
{
	return Pool[blocknum++];
}
void B_Delete(int x)
{
	Pool[--blocknum]=x;
}
int Getcurblock(int &pos)
{
	int curblock=0;
	while(curblock!=-1 && pos>cursize[curblock])
	{
		pos-=cursize[curblock]; curblock=next[curblock];
	}
	return curblock;
}
void Addnewblock(int curblock,int nextblock,int num,char ch[])
{
	if(nextblock!=-1)
	{
		next[nextblock]=next[curblock];
		cursize[nextblock]=num;
		memcpy(data[nextblock],ch,num);
	}
	next[curblock]=nextblock;
}
void Split(int curblock,int pos)
{
	if(curblock==-1 || pos==cursize[curblock]) return;
	int newblock=Getnew();
	Addnewblock(curblock,newblock,cursize[curblock]-pos,data[curblock]+pos);
	cursize[curblock]=pos;
}
void Merge(int curblock,int nextblock)
{
	memcpy(data[curblock]+cursize[curblock],data[nextblock],cursize[nextblock]);
	next[curblock]=next[nextblock];
	cursize[curblock]+=cursize[nextblock];
	B_Delete(nextblock);
}
void Maintain()
{
	int curblock=0;
	while(curblock!=-1)
	{
		int nextblock=next[curblock];
		while(nextblock!=-1 && cursize[curblock]+cursize[nextblock]<=B_SIZE)
		{
			Merge(curblock,nextblock);
			nextblock=next[curblock];
		}
		curblock=next[curblock];
	}
}
void Insert(int pos,int num,char ch[])
{
	int curblock=Getcurblock(pos);
	Split(curblock,pos);
	int curnum=0;
	while(curnum+B_SIZE<=num)
	{
		int newblock=Getnew();
		Addnewblock(curblock,newblock,B_SIZE,ch+curnum);
		curblock=newblock;
		curnum+=B_SIZE;
	}
	if(num-curnum)
	{
		int newblock=Getnew();
		Addnewblock(curblock,newblock,num-curnum,ch+curnum);
	}
	Maintain();
}
void Erase(int pos,int num)
{
	int curblock=Getcurblock(pos);
	Split(curblock,pos);
	int nextblock=next[curblock];
	while(nextblock!=-1 && num>cursize[nextblock])
	{
		num-=cursize[nextblock];
		nextblock=next[nextblock];
	}
	Split(nextblock,num);
	nextblock=next[nextblock];
	for(int p=next[curblock];p!=nextblock;p=next[curblock])
	{
		next[curblock]=next[p]; B_Delete(p);
	}
	Maintain();
}
void Getdata(int pos,int num,char ch[])
{
	int curblock=Getcurblock(pos);
	int index=cursize[curblock]-pos;
	if(index>num) index=num;
	memcpy(ch,data[curblock]+pos,index);
	int nextblock=next[curblock];
	while(nextblock!=-1 && index+cursize[nextblock]<=num)
	{
		memcpy(ch+index,data[nextblock],cursize[nextblock]);
		index+=cursize[nextblock];
		nextblock=next[nextblock];
	}
	if(num-index && nextblock!=-1)
	  memcpy(ch+index,data[nextblock],num-index);
	ch[num]=0;
}
int main()
{
    prepare();
    int now=0,n,num; char key;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%s",cmd);
        if(cmd[0]=='M') scanf("%d",&now);
        else if(cmd[0]=='I')
        {
            scanf("%d",&num);
            for(int j=0;j<num;++j)
            {
                scanf("%c",&key);
                str[j]=key;
                if(key<32 || key>126) --j;
            }
            Insert(now,num,str);
        }
        else if(cmd[0]=='D'){
            scanf("%d",&num);
            Erase(now,num);
        }
        else if(cmd[0]=='G')
        {
            scanf("%d",&num);
            Getdata(now,num,str);
            printf("%s\n",str);
        }
        else if(cmd[0]=='P') --now;
        else ++now;
    }
    return 0;
}
