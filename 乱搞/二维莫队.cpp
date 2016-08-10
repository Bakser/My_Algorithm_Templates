 #include <cstdio>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;

typedef long long LL;

#define rep(I,L,R) for(int I=(L),I##__E=(R);I<=I##__E;++I)
#define repd(I,R,L) for(int I=(R),I##__E=(L);I>=I##__E;--I)
#define for_(it,W) for(__typeof(W.begin())it=W.begin();it!=W.end();++it)

const int N = 233, MXQ = 233333;

int A[N][N], bID[N][N];

struct query { int x1, y1, x2, y2, i; } Q[MXQ];
bool operator< (const query &a, const query &b) {
	if (bID[a.x1][a.y1] == bID[b.x1][b.y1])
		return bID[a.x2][a.y2] < bID[b.x2][b.y2];
	else
		return bID[a.x1][a.y1] < bID[b.x1][b.y1];
}

int freq[N * N], vis[N][N], n, m;
long long res, ans[MXQ];

inline void add (int x, int y) {
	if (!vis[x][y]) {
		int z = ++freq[A[x][y]];
		res += (z << 1) - 1;
		vis[x][y] = 1;
	}
}
inline void del (int x, int y) {
	if (vis[x][y]) {
		int z = freq[A[x][y]]--;
		res -= (z << 1) - 1;
		vis[x][y] = 0;
	}
}

void transmit (const query &a, const query &b) { // a->b !
	rep(x, b.x1, min(a.x1 - 1, b.x2)) rep(y, b.y1, b.y2) add(x, y);
	rep(x, max(b.x1, a.x2 + 1), b.x2) rep(y, b.y1, b.y2) add(x, y);
	rep(y, b.y1, min(a.y1 - 1, b.y2)) rep(x, b.x1, b.x2) add(x, y);
	rep(y, max(b.y1, a.y2 + 1), b.y2) rep(x, b.x1, b.x2) add(x, y);
	rep(x, a.x1, min(b.x1 - 1, a.x2)) rep(y, a.y1, a.y2) del(x, y);
	rep(x, max(a.x1, b.x2 + 1), a.x2) rep(y, a.y1, a.y2) del(x, y);
	rep(y, a.y1, min(b.y1 - 1, a.y2)) rep(x, a.x1, a.x2) del(x, y);
	rep(y, max(a.y1, b.y2 + 1), a.y2) rep(x, a.x1, a.x2) del(x, y);
}

struct discreteliber {
	map<int, int> f;
	void add (int x) { f[x] = 1; }
	int roll () {
		int cnt = 0;
		for_(it, f) it->second = ++cnt;
		return cnt;
	}
	int operator[] (int x) { return f[x]; }
} C;

int q;

inline void reset (const query &a) {
	rep(i, 1, n) rep(j, 1, m) {
		vis[i][j] = 0;
		freq[A[i][j]] = 0;
	} res = 0;
	rep(x, a.x1, a.x2) rep(y, a.y1, a.y2) {
		add(x, y);
	}
}

int main () {
	scanf("%d%d", &n, &m);
	//
	int sqn = ceil(sqrt(n)), sqm = ceil(sqrt(m));
	rep(i, 1, n) rep(j, 1, m) {
		int xp = ((i - 1) / sqn) + 1, yp = ((j - 1) / sqm) + 1;
		bID[i][j] = (xp - 1) * sqm + yp;
	}
	//
	rep(i, 1, n) rep(j, 1, m) {
		scanf("%d", &A[i][j]);
		C.add(A[i][j]);
	}
	C.roll();
	rep(i, 1, n) rep(j, 1, m) {
		A[i][j] = C[A[i][j]];
	}
	//
	scanf("%d", &q);
	rep(i, 1, q) {
		scanf("%d%d%d%d", &Q[i].x1, &Q[i].y1, &Q[i].x2, &Q[i].y2);
		if (Q[i].x1 > Q[i].x2) swap(Q[i].x1, Q[i].x2);
		if (Q[i].y1 > Q[i].y2) swap(Q[i].y1, Q[i].y2);
		Q[i].i = i;
	}
	sort(Q + 1, Q + 1 + q);
	//
	reset(Q[1]);
	ans[Q[1].i] = res;
	rep(i, 2, q) {
		transmit(Q[i], Q[i - 1]);
		ans[Q[i].i] = res;
	}
	//
	rep(i, 1, q) {
		printf("%lld\n", ans[i]);
	}
	return 0;
}
