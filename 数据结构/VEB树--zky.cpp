#include<bits/stdc++.h>
#define lowsqrt(u) (1<<(M[u]>>1))
#define low(u,x) (x%lowsqrt(u))
#define high(u,x) (x/lowsqrt(u))
#define indx(u,x,y) (x*lowsqrt(u)+y)
using namespace std;
map<int,int>M;
struct vEB{
	struct node{
		int Max,Min,u;
		node *Summ;
		vector<node*>clus;
		void build(int Bitsize){
			if(Bitsize<=1){
				Max=Min=-1;u=2;
				Summ=NULL;return;
			}
			Max=Min=-1;u=1<<Bitsize;
			int Nsize=(Bitsize>>1)+(Bitsize&1);
			Summ=new node();
			Summ->build(Nsize);
			clus.resize(1<<Nsize);
			for(int i=0;i<(1<<Nsize);i++){
				clus[i]=new node();
				clus[i]->build(Bitsize>>1);
			}				
		}
	}*root;
	void build(int size){		
		int L=0;for(size--;size;size>>=1,L++);
		root=new node();
		root->build(L);
	}
	int _Min(node *t){
		return t->Min;
	}
	int _Max(node *t){
		return t->Max;
	}
	void _insert(node *t,int x){
		if(t->Min==-1){
			t->Min=t->Max=x;
			return;
		}		
		if(x<t->Min)swap(x,t->Min);
		int H=high(t->u,x),L=low(t->u,x);
		if(t->u>2){
			if(_Min(t->clus[H])==-1){
				_insert(t->Summ,H);
				t->clus[H]->Min=L;
				t->clus[H]->Max=L;
			}else _insert(t->clus[H],L);			
		}
		if(x>t->Max)t->Max=x;
	}
	void _del(node *t,int x){
		if(t->Min==t->Max){
			t->Min=t->Max=-1;
		}else
		if(t->u==2)
			t->Max=t->Min=!x;			
		else{		
			if(x==t->Min){
				int fclus=_Min(t->Summ);
				x=indx(t->u,fclus,_Min(t->clus[fclus]));
				t->Min=x;				
			}int H=high(t->u,x),L=low(t->u,x);
			_del(t->clus[H],L);
			if(_Min(t->clus[H])==-1){
				_del(t->Summ,H);
				if(x==t->Max){
					int Smax=_Max(t->Summ);
					if(Smax==-1)
						t->Max=t->Min;
					else
						t->Max=indx(t->u,Smax,_Max(t->clus[Smax]));
				}				
			}else if(x==t->Max){
				t->Max=indx(t->u,H,_Max(t->clus[H]));
			}
		}
	}
	int _pred(node *t,int x){
		if(t->u==2){
			if(x==1&&t->Min==0)return 0;
			else return -1;
		}else if(t->Max!=-1&&x>t->Max)return t->Max;
		else{
			int H=high(t->u,x),L=low(t->u,x);
			int minhigh=_Min(t->clus[H]);
			if(minhigh!=-1&&L>minhigh){
				int offset=_pred(t->clus[H],L);
				return indx(t->u,H,offset);
			}else{
				int preclus=_pred(t->Summ,H);
				if(preclus==-1){
					if(t->Min!=-1&&x>t->Min)return t->Min;
					else return -1;
				}
				else{
					int offset=_Max(t->clus[preclus]);
					return indx(t->u,preclus,offset);					
				}
			}
		}
	}
	int _succ(node *t,int x){
		if(t->u==2){
			if(x==0&&t->Max==1)return 1;
			else return -1;
		}else if(t->Min!=-1&&x<t->Min)return t->Min;
		else{
			int H=high(t->u,x),L=low(t->u,x);
			int maxlow=_Max(t->clus[H]);
			if(maxlow!=-1&&L<maxlow){
				int offset=_succ(t->clus[H],L);
				return indx(t->u,H,offset);
			}else{
				int suclus=_succ(t->Summ,H);
				if(suclus==-1)return -1;
				else{
					int offset=_Min(t->clus[suclus]);
					return indx(t->u,suclus,offset);
				}
			}
		}
	}
	bool _exist(node *t,int x){
		if(x==t->Min||x==t->Max)return 1;
		else if(t->u==2)return 0;
		else return _exist(t->clus[high(t->u,x)],low(t->u,x));
	}
	int Min(){return _Min(root);}
	int Max(){return _Max(root);}
	void insert(int x){_insert(root,x);}
	void del(int x){_del(root,x);}
	int pred(int x){return _pred(root,x);}
	int succ(int x){return _succ(root,x);}
	bool exist(int x){return _exist(root,x);}
}T;
int n,m;
int getint(){
	int res=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=(res<<3)+(res<<1)+ch-'0',ch=getchar();
	return res;
}
void putint(int x){
	if(x<0)putchar('-'),x=-x;
	if(x<10)
		putchar(x+'0');
	else{
		putint(x/10);
		putchar(x%10+'0');
	}
}
int main(){
	for(int i=0;i<32;i++)M[1<<i]=i;
//	freopen("vEB.in","r",stdin);
//	freopen("vEB.out","w",stdout);
	 n=getint();m=getint();
	 T.build(n);int x;
//	 cerr<<(double)clock()/CLOCKS_PER_SEC<<endl;
	 while(m--){
	 	//if(m%1000==0)cerr<<m<<endl;
	 	int op=getint();
	 	switch(op){
			case 1:{
				x=getint();
				if(!T.exist(x))
				T.insert(x);
				break;
			}
			case 2:{
				x=getint();
				if(T.exist(x)) 
				T.del(x);
				break;
			}
			case 3:{
				putint(T.Min());puts("");
				break;
			}
			case 4:{
				putint(T.Max());puts("");
				break;
			}
			case 5:{
				x=getint();
				putint(T.pred(x));puts("");
				break;
			}
			case 6:{
				x=getint();
				putint(T.succ(x));puts("");
				break;
			}
			case 7:{
				x=getint();
				if(T.exist(x))puts("1");
				else puts("-1");
				break;
			}
		}
	 }	
//	 cerr<<(double)clock()/CLOCKS_PER_SEC<<endl;
	return 0;
}
