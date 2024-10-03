#include <bits/stdc++.h>
#define all(s) s.begin(), s.end()
#define lb(s, a) lower_bound(all(s), (a)) - s.begin()

using namespace std;

typedef long long ll;

const int ar = 1e6;
const ll mod = 1e9+7;
const int oo = 1e9;

string s;
int n, a[ar + 5];
vector <int> pos[2 * ar + 10];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "5C"
    if(fopen(task".inp", "r")) {
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    }
    cin >> s;
    n = s.size(); s = ' ' + s;
    int res = 0, cnt = 0;
    stack <int> st;
    pos[ar].push_back(0);
    for(int i = 1; i <= n; ++i) {
        if(s[i] == '(') a[i] = a[i - 1] + 1;
        else a[i] = a[i - 1] - 1;
        pos[a[i] + ar].push_back(i);
        while(st.size() && a[st.top()] >= a[i])
            st.pop();
        int p = 0;
        if(st.size()) p = st.top();
        st.push(i);

        p = pos[a[i] + ar][lb(pos[a[i] + ar], p)];
//        cout << a[i] << ' ' << p << '\n';
        if(i - p == res) cnt++;
        else if(i - p > res) res = i - p, cnt = 1;
    }
    if(res == 0) cout << "0 1";
    else cout << res << ' ' << cnt;

}

