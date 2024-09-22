#include <bits/stdc++.h>

using namespace std;
#define task "mdance"

typedef long long ll;

const int ar = 100000;
const ll mod = 1e9+7;
const int oo = 1e9;

int n, m;
bitset <ar> b[26];
string s;
map <string, int> mp;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }

	cin >> n >> m;
	cin >> s;
	for(int i = 0; i < n; ++i) 
		b[s[i] - 'a'][i] = 1;
	while(m--) {
		cin >> s;
		if(mp.find(s) != mp.end()) {
			cout << mp[s] << '\n'; 
			continue;
		}
		bitset <100000> res;
		res = b[s[0] - 'a'];
		for(int i = 1; i < s.size(); ++i)
			res &= (b[s[i] - 'a'] >> i);
		int cnt = ar, ans = 0;
		for(int i = 0; i < ar; ++i) {
			if(res[i] == 1) 
				if(cnt >= s.size()) ans++, cnt = 0;
			cnt++;
		}
		cout << (mp[s] = ans) << '\n';
	}

    return 0;
}
