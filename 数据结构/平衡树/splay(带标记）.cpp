/*
http://acm.pku.edu.cn/JudgeOnline/problem?id=3468
�������,�������
*/
#include <cstdio>
#define keyTree (ch[ ch[root][1] ][0])
const int maxn = 222222;
struct SplayTree{
	int sz[maxn];
	int ch[maxn][2];
	int pre[maxn];
	int root , top1 , top2;
	int ss[maxn] , que[maxn];
 
	inline void Rotate(int x,int f) {
		int y = pre[x];
		push_down(y);
		push_down(x);
		ch[y][!f] = ch[x][f];
		pre[ ch[x][f] ] = y;
		pre[x] = pre[y];
		if(pre[x]) ch[ pre[y] ][ ch[pre[y]][1] == y ] = x;
		ch[x][f] = y;
		pre[y] = x;
		push_up(y);
	}
	inline void Splay(int x,int goal) {
		push_down(x);
		while(pre[x] != goal) {
			if(pre[pre[x]] == goal) {
				Rotate(x , ch[pre[x]][0] == x);
			} else {
				int y = pre[x] , z = pre[y];
				int f = (ch[z][0] == y);
				if(ch[y][f] == x) {
					Rotate(x , !f) , Rotate(x , f);
				} else {
					Rotate(y , f) , Rotate(x , f);
				}
			}
		}
		push_up(x);
		if(goal == 0) root = x;
	}
	inline void RotateTo(int k,int goal) {//�ѵ�kλ����ת��goal�±�
		int x = root;
		push_down(x);
		while(sz[ ch[x][0] ] != k) {
			if(k < sz[ ch[x][0] ]) {
				x = ch[x][0];
			} else {
				k -= (sz[ ch[x][0] ] + 1);
				x = ch[x][1];
			}
			push_down(x);
		}
		Splay(x,goal);
	}
	inline void erase(int x) {//����xΪ���Ƚ��ɾ���Ž��ڴ��,�����ڴ�
		int father = pre[x];
		int head = 0 , tail = 0;
		for (que[tail++] = x ; head < tail ; head ++) {
			ss[top2 ++] = que[head];
			if(ch[ que[head] ][0]) que[tail++] = ch[ que[head] ][0];
			if(ch[ que[head] ][1]) que[tail++] = ch[ que[head] ][1];
		}
		ch[ father ][ ch[father][1] == x ] = 0;
		push_up(father);
	}
	//����һ�㲻�޸�//////////////////////////////////////////////////////////////////////////////
	void debug() {printf("%d\n",root);Treaval(root);}
	void Treaval(int x) {
		if(x) {
			Treaval(ch[x][0]);
			printf("���%2d:����� %2d �Ҷ��� %2d ����� %2d size = %2d ,val = %2d\n",x,ch[x][0],ch[x][1],pre[x],sz[x],val[x]);
			Treaval(ch[x][1]);
		}
	}
	//����Debug
 
 
	//��������Ŀ���ض�����:
	inline void NewNode(int &x,int c) {
		if (top2) x = ss[--top2];//��ջ�ֶ�ѹ���ڴ��
		else x = ++top1;
		ch[x][0] = ch[x][1] = pre[x] = 0;
		sz[x] = 1;
 
		val[x] = sum[x] = c;/*������Ŀ�ض�����*/
		add[x] = 0;
	}
 
	//���ӳٱ���Ƶ�����
	inline void push_down(int x) {/*������Ŀ�ض�����*/
		if(add[x]) {
			val[x] += add[x];
			add[ ch[x][0] ] += add[x];
			add[ ch[x][1] ] += add[x];
			sum[ ch[x][0] ] += (long long)sz[ ch[x][0] ] * add[x];
			sum[ ch[x][1] ] += (long long)sz[ ch[x][1] ] * add[x];
			add[x] = 0;
		}
	}
	//�Ѻ���״̬��������
	inline void push_up(int x) {
		sz[x] = 1 + sz[ ch[x][0] ] + sz[ ch[x][1] ];
		/*������Ŀ�ض�����*/
		sum[x] = add[x] + val[x] + sum[ ch[x][0] ] + sum[ ch[x][1] ];
	}
 
	/*��ʼ��*/
	inline void makeTree(int &x,int l,int r,int f) {
		if(l > r) return ;
		int m = (l + r)>>1;
		NewNode(x , num[m]);		/*num[m]Ȩֵ�ĳ���Ŀ�����*/
		makeTree(ch[x][0] , l , m - 1 , x);
		makeTree(ch[x][1] , m + 1 , r , x);
		pre[x] = f;
		push_up(x);
	}
	inline void init(int n) {/*������Ŀ�ض�����*/
		ch[0][0] = ch[0][1] = pre[0] = sz[0] = 0;
		add[0] = sum[0] = 0;
 
		root = top1 = 0;
		//Ϊ�˷��㴦��߽�,�������߽綥��
		NewNode(root , -1);
		NewNode(ch[root][1] , -1);
		pre[top1] = root;
		sz[root] = 2;
 
		for (int i = 0 ; i < n ; i ++) scanf("%d",&num[i]);
		makeTree(keyTree , 0 , n-1 , ch[root][1]);
		push_up(ch[root][1]);
		push_up(root);
	}
	/*����*/
	inline void update( ) {/*������Ŀ�ض�����*/
		int l , r , c;
		scanf("%d%d%d",&l,&r,&c);
		RotateTo(l-1,0);
		RotateTo(r+1,root);
		add[ keyTree ] += c;
		sum[ keyTree ] += (long long)c * sz[ keyTree ];
	}
	/*ѯ��*/
	inline void query() {/*������Ŀ�ض�����*/
		int l , r;
		scanf("%d%d",&l,&r);
		RotateTo(l-1 , 0);
		RotateTo(r+1 , root);
		printf("%lld\n",sum[keyTree]);
	}
 
 
	/*������Ŀ�ض�����*/
	int num[maxn];
	int val[maxn];
	int add[maxn];
	long long sum[maxn];
}spt;
 
 
int main() {
	int n , m;
	scanf("%d%d",&n,&m);
	spt.init(n);
	while(m --) {
		char op[2];
		scanf("%s",op);
		if(op[0] == 'Q') {
			spt.query();
		} else {
			spt.update();
		}
	}
	return 0;
}

