#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <queue>
using namespace std;
const int N(1e5);
const int M(70000);
const int MAXN(2.3e7);
const double alpha((double)3/4);
const double Dlim(log(4)-log(3));
struct seg_node{
	int cnt,used;
	seg_node *l,*r;
}*Nul1,node1[MAXN],*tai1=node1,*rots[N];
queue<seg_node*> p1;
inline seg_node* new_1(int _cnt=0,int _used=1){
	seg_node* x;
	if(!p1.empty())x=p1.front(),p1.pop();
	else x=tai1++;
	x->cnt=_cnt;x->used=_used;x->l=x->r=Nul1;
	return x;
}
inline seg_node* add(seg_node* p,const int &l,const int &r,const int &P,const int &d){
	seg_node* x=new_1(p->cnt+d);
	if(l==r)return x;
	int mid(l+r>>1);
	if(P<=mid)x->l=add(p->l,l,mid,P,d),(x->r=p->r)->used++;
	if(P>mid)x->r=add(p->r,mid+1,r,P,d),(x->l=p->l)->used++;
	return x;
}
//merge segment tree
inline seg_node* merge(seg_node* x,seg_node* y){
	if(x==Nul1)return y->used++,y;
	if(y==Nul1)return x->used++,x;
	seg_node* p=new_1(x->cnt+y->cnt);
	if(x->l!=Nul1||x->r!=Nul1){
		p->l=merge(x->l,y->l);
		p->r=merge(x->r,y->r);
	}
	return p;
}
inline void recover(seg_node* x){
	if(x==Nul1)return; 
	if((--x->used)<=0){
		p1.push(x);
		recover(x->l);
		recover(x->r);
	}
}
struct scap_node{
	int val,sz;
	seg_node* rot;
	scap_node *l,*r;
	inline void upd(){
		sz=l->sz+r->sz+1;
		seg_node* t=merge(l->rot,r->rot);
		rot=add(t,0,M,val,1);
		recover(t);
	}
}*Nul2,node2[N],*tai2=node2,*root;
queue<scap_node*>p2;
int n,Q,P,D,K,ans(0),a[N],tot,tot2,mxdep,num[N];
char op[20];
inline scap_node* new_2(int val=0,int sz=1){
	scap_node* x;
	if(!p2.empty())x=p2.front(),p2.pop();
	else x=tai2++;
	x->val=val;x->sz=sz;x->l=x->r=Nul2;x->rot=Nul1;
	return x;
}
inline scap_node* build_scap(int l,int r){
	if(l==r){
		scap_node* x=new_2(a[l]);
		x->rot=add(Nul1,0,M,a[l],1);
		return x;
	}
	int mid(l+r>>1);
	scap_node* x=new_2(a[mid]);
	if(l<mid)x->l=build_scap(l,mid-1);
	if(r>mid)x->r=build_scap(mid+1,r);
	x->upd();
	return x;
}
inline void dfs(scap_node* x){
	if(x==Nul2)return;
	dfs(x->l);
	recover(x->rot);
	a[++tot]=x->val;
	p2.push(x);
	dfs(x->r);
}
inline scap_node* rebuild(scap_node* x){
	tot=0;dfs(x);
	return build_scap(1,x->sz);
}
inline void read(int &x){
	char c=0;
	for(;c<'0'||c>'9';c=getchar());
	for(x=0;c>='0'&&c<='9';c=getchar())x=x*10+(c-'0');
}
inline seg_node* Add(seg_node* x,const int &p,const int &d){
	seg_node* t=x;
	x=add(t,0,M,p,d);
	recover(t);
	return x;
}
inline bool insert(scap_node* &x,const int &k,const int & v,int dep){
	if(x==Nul2){
		x=new_2(v);
		x->rot=add(Nul1,0,M,v,1);
		return dep<=mxdep;
	}
	x->rot=Add(x->rot,v,1);x->sz++;
	bool f=(k<=x->l->sz+1)?insert(x->l,k,v,dep+1):insert(x->r,k-x->l->sz-1,v,dep+1);
	int sz=x->sz*alpha;
	if(f&&(x->l->sz>sz||x->r->sz>sz))return x=rebuild(x),0;
	return f;
}
inline void Ins(const int &k,const int &v){
	mxdep=log(root->sz)/Dlim+1;
	insert(root,k,v,0);
}
inline int modify(scap_node* x,const int &p,const int &v){
	int sz=x->l->sz,last;
	if(p<=sz)last=modify(x->l,p,v);
	else if(p==sz+1)last=x->val,x->val=v;
	else last=modify(x->r,p-sz-1,v);
	x->rot=Add(x->rot,last,-1);
	x->rot=Add(x->rot,v,1);
	return last;
}
inline void query(scap_node* x,int l,int r){
	if(l<=1&&x->sz<=r)return void(rots[++tot]=x->rot);
	int mid(x->l->sz+1);
	if(l<=mid&&mid<=r)num[++tot2]=x->val;
	if(l<mid)query(x->l,l,r);
	if(r>mid)query(x->r,l-mid,r-mid);
}
inline int Query(int l,int r,int k){
	tot=tot2=0;query(root,l,r);
	for(l=0,r=M;l<r;){
		int mid(l+r>>1),sz=0;
		for(int i(1);i<=tot;i++)sz+=rots[i]->l->cnt;
		for(int i(1);i<=tot2;i++)sz+=(num[i]>=l&&num[i]<=mid);
		if(k<=sz){
			for(int i(1);i<=tot;i++)rots[i]=rots[i]->l;
			r=mid;
		}
		else{
			for(int i(1);i<=tot;i++)rots[i]=rots[i]->r;
			l=mid+1;k-=sz;
		}
	}
	return l;
}
int main(){
	Nul1=tai1++;Nul1->cnt=Nul1->used=0;Nul1->l=Nul1->r=Nul1;
	read(n);
	for(int i(1);i<=n;i++)read(a[i]);
	Nul2=tai2++;Nul2->val=Nul2->sz=0;Nul2->l=Nul2->r=Nul2;Nul2->rot=Nul1;
	root=build_scap(1,n);
	for(read(Q);Q--;){
		scanf("%s",op);
		read(P);P^=ans;read(D);D^=ans;
		if(op[0]=='Q')read(K),K^=ans,printf("%d\n",ans=Query(P,D,K));
		else if(op[0]=='I')Ins(P,D);
		else if(op[0]=='M')modify(root,P,D);
	}
	return 0;
 }
