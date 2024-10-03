#include <bits/stdc++.h>

using namespace std;
#define task "code"

typedef long long ll;

const int ar = 1e6+2;
const ll mod = 1e9+7;
const int oo = 1e9;

struct Node {
	int res = 0, ope = 0, clo = 0;
	
	Node operator + (const Node &b) const {
		Node c;
		
		int t = min(ope, b.clo);
		c.res = res + b.res + t;
		c.ope = ope + b.ope - t;
		c.clo = clo + b.clo - t;
		return c;
	}
} st[1 << 22];

string s;
int n;

void build(int id, int l, int r) {
	if(l == r) {
		st[id] = {0, s[l] == '(', s[l] == ')'};
		return;
	}
	
	int mid = l + r >> 1;
	build(id << 1, l, mid);
	build(id << 1 | 1, mid + 1, r);
	
	st[id] = st[id << 1] + st[id << 1 | 1];
}

Node get(int id, int l, int r, int u, int v) {
	if(l >= u && r <= v) return st[id];
	
	int mid = l + r >> 1;
	if(mid >= u) {
		if(mid + 1 <= v)
			return get(id << 1, l, mid,u, v) + get(id << 1 | 1, mid + 1, r,u ,v);
		return get(id << 1, l, mid,u, v);
	}
	return get(id << 1 | 1, mid + 1, r, u, v);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	if(fopen(task".inp", "r")) 
		freopen(task".inp", "r", stdin);
	if(fopen(task".out", "w"))
		freopen(task".out", "w", stdout);
	
	cin >> s;
	n = s.size(); s = ' ' + s;
	build(1, 1, n);
	
	int q;
	cin >> q;
	while(q--) {
		int l, r;
		cin >> l >> r;
		cout << (get(1, 1, n, l, r).res << 1) << '\n';
	}
	
	return 0;
}