#include<cstdio>
#include<algorithm>
#include<cstring>
#include<climits>
#include<cstdlib>
using namespace std;
const int MAXL=1e5+100;
const int B_SIZE=400;
const int B_NUM=MAXL/B_SIZE*2+100;
struct node
{
	int index,key;
}data[B_NUM][B_SIZE];
int n,m,curindex[MAXL],Pool[B_NUM],next[B_NUM],cursize[B_NUM],blocknum,lazy[B_NUM];
node str[MAXL];
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
void Addnewblock(int curblock,int nextblock,int num,node str[])
{
	if(nextblock!=-1)
	{
		next[nextblock]=next[curblock];
		cursize[nextblock]=num;
		memcpy(data[nextblock],str,num*sizeof(node));
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
	memcpy(data[curblock]+cursize[curblock],data[nextblock],cursize[nextblock]*sizeof(node));
	cursize[curblock]+=cursize[nextblock];
	next[curblock]=next[nextblock];
	B_Delete(nextblock);
}
bool cmp(node x,node y)
{
	return x.key<y.key;
}
void MaintainBlock(int curblock)
{
	sort(data[curblock],data[curblock]+cursize[curblock],cmp);
	for(int i=0;i<cursize[curblock];++i)
	  curindex[data[curblock][i].index]=i;
}
void MaintainList()
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
void Insert(int pos,int num,node str[])
{
	int curblock=Getcurblock(pos);
	Split(curblock,pos);
	int index=0;
	while(index+B_SIZE<=num)
	{
		int newblock=Getnew();
		Addnewblock(curblock,newblock,B_SIZE,str+index);
		index+=B_SIZE;
		curblock=newblock;
	}
	if(num-index)
	{
		int newblock=Getnew();
		Addnewblock(curblock,newblock,num-index,str+index);
	}
	MaintainList();
	for(int p=0;p!=-1;p=next[p])
	  MaintainBlock(p);
}
int Query(int curblock,int v)
{
	int l=0,r=cursize[curblock]-1,ans=-1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(v>data[curblock][mid].key) {
			ans=mid; l=mid+1;
		}
		else r=mid-1;
	}
	return ans+1;
}
void Update(int l,int r,int d)
{
	int temL=l,temR=r;
	int blockL=Getcurblock(temL),blockR=Getcurblock(temR);
	if(blockL==blockR)
	{
		for(int p=l;p<=r;++p)
		  data[blockL][curindex[p]].key+=d;
		MaintainBlock(blockL);
	}
	else {
		for(int p=next[blockL];p!=blockR;p=next[p])
		{
			lazy[p]+=d;
		}
		temL=cursize[blockL]-temL+1;
		for(int i=0;i<temL;++i)
		  data[blockL][curindex[l+i]].key+=d;
		for(int i=0;i<temR;++i)
		  data[blockR][curindex[r-i]].key+=d;
		MaintainBlock(blockL);
		MaintainBlock(blockR);
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	prepare();
	for(int i=0;i<n;++i)
	{
		scanf("%d",&str[i].key);
		str[i].index=i+1;
	}
	Insert(0,n,str);
	for(int i=0;i<m;++i)
	{
		int flag;
		scanf("%d",&flag);
		if(flag==1)
		{
			int l,r,v;
			scanf("%d%d%d",&l,&r,&v);
			Update(l,r,v);
		}
		else
		{
			int ans=0,v; scanf("%d",&v);
			for(int p=0;p!=-1;p=next[p])
			  ans+=Query(p,v-lazy[p]);
			printf("%d\n",ans);
		}
	}
    return 0;
}
