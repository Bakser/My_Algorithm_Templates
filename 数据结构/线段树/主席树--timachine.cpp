//poj2761 
#include<cstdio> 
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 100000+1;
const int TN = N*20;
const int M = 50000+1;
int n,m,data[N],input[N];
int tdata[TN],lson[TN],rson[TN],T[N],Tn;
void BuildHash(){
	sort(data+1,data+1+n);
	data[0]=unique(data+1,data+1+n)-data-1;
}
int Find(int x){
	int l=1,r=data[0];
	while(l<r){
		int mid=(l+r)/2;
		if(data[mid]==x)return mid;
		if(x<data[mid])
			r=mid;
		else
			l=mid+1;
	}
	return l;
}
int Build(int l,int r){
	int root=++Tn;
	if(l<r){
		int mid=(l+r)/2;
		lson[root]=Build(l,mid);
		rson[root]=Build(mid+1,r);
	}
	return root;
}
int Add(int root,int pos,int val){
	int newr=++Tn,re;re=newr;
	int l=1,r=data[0];
	tdata[newr]=tdata[root]+val;
	while(l<r){
		int mid=(l+r)/2;
		if(pos<=mid){
			rson[newr]=rson[root];
			lson[newr]=++Tn;
			newr=lson[newr];
			root=lson[root];
			r=mid;
		}
		else{
			lson[newr]=lson[root];
			rson[newr]=++Tn;
			newr=rson[newr];
			root=rson[root];
			l=mid+1;
		}
		tdata[newr]=tdata[root]+val;
	}
	return re;
}
int Ask(int lroot,int rroot,int k){
	int l=1,r=data[0];
	while(l<r&&k>=0){
		int mid=(l+r)/2;
		if(k<=tdata[lson[rroot]]-tdata[lson[lroot]]){
			lroot=lson[lroot];
			rroot=lson[rroot];
			r=mid;
		}
		else{
			k-=tdata[lson[rroot]]-tdata[lson[lroot]];
			lroot=rson[lroot];
			rroot=rson[rroot];
			l=mid+1;
		}
	}
	return data[l];
}
int main(){
	int i,j,a,b,c;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d",&input[i]);
		data[i]=input[i];
	}
	BuildHash();
	T[0]=Build(1,data[0]);
	for(i=1;i<=n;i++){
		int pos=Find(input[i]);
		T[i]=Add(T[i-1],pos,1);
	}
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		printf("%d\n",Ask(T[a-1],T[b],c));
	}
	
	return 0;
}
