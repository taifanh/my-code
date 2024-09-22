#include <bits/stdc++.h>
using namespace std;

bool hoi(string s) {
    cout << "? " << s << '\n';
    fflush(stdout);
    int res;
    cin >> res;
    if(res == -1) assert(1);
    return res;
}

void in(string s) {
    cout << "! " << s << '\n';
}

void solve() {
    int n;
    cin >> n;
    string s = "";
    while(s.size() < n) {
        if(s.empty()) {
            s += '0';
            if(hoi(s)) continue;
            string res = "";
            for(int i = 1; i <= n; ++i)
                res += '1';
            in(res);
            return;
        }
        s += '0';
        if(hoi(s)) continue;
        s[s.size() - 1] = '1';
        if(hoi(s)) continue;
        s.pop_back();
        break;
    }
    while(s.size() < n) {
        string tmp = '0' + s;
        if(hoi(tmp)) {
            s = tmp;
            continue;
        }
        s = '1' + s;
    }
    in(s);
}

signed main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}

