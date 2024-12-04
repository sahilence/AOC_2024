#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>
#define vi vector<int>
#define vvi vector<vi>
#define mi map<int, int>
#define ll long long
#define vl vector<ll>
#define vvl vector<vl>
#define ml map<ll, ll>
#define fr(i, a, b) for (int i = a; i < b; i++)
#define frr(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define yesno(x) cout << (x ? "YES" : "NO") << "\n"
#define int ll

struct DSU {
    vector<int> e;
    DSU(int n) : e(n, -1) {}
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        e[a] += e[b];
        e[b] = a;
        return true;
    }
};

void print(vi &a){
    for(auto x : a){
        cerr << x << " ";
    }
    cerr << "\n";
}

void print(int &a){
    cerr << a << " ";
}

void print(string &s){
    cerr << s << " ";
}

void print(pair<int,int> &p){
    cerr << p.first << " " << p.second << "\n";
}

const int mod = 1e9 + 7;
void addself(int &a, int b){
    a += b;
    if(a >= mod) a -= mod;
}

void subself(int &a, int b){
    a -= b;
    a = ((a%mod) + mod)%mod;
}

void mulself(int &a, int b){
    a *= b;
    a %= mod;
}

int binexp(int a, int b){
    int res = 1;
    a %= mod;
    while(b > 0){
        if(b & 1){
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

int modinv(int a){
    return binexp(a, mod - 2);
}

int gcd(int a, int b){
    if(b == 0) return a;
    return gcd(b, a%b);
}

struct M{
    vvi t;
    int n;
    M(int n){
        this->n = n;
        t.resize(n, vi(n,0));
    }
    M operator* (const M& b){
        M c(n);
        fr(i,0,n){
            fr(j,0,n){
                fr(k,0,n){
                    c.t[i][j] += t[i][k] * b.t[k][j];
                    c.t[i][j] %= mod;
                }
            }
        }
        return c;
    }
};

int solve(string &s, bool &ok){
    int n = s.size();
    int ans = 0;
    fr(i,0,n - 3){
        if(s[i] == 'd' && s[i + 1] == 'o'){
            if(i + 3 < n && s[i + 2] == '(' && s[i + 3] == ')'){
                ok = 1;
            }
            else if(i + 6 < n && s[i + 2] == 'n' && s[i + 3] == '\'' && s[i + 4] == 't' && s[i + 5] == '(' && s[i + 6] == ')'){
                ok = 0;
            }
        }
        if(!ok) continue;
        if(s[i] == 'm' && s[i + 1] == 'u' && s[i + 2] == 'l' && s[i + 3] == '('){
            int j = i + 4;
            int num1 = 0, num2 = 0;
            while(j < n && s[j] <= '9' && s[j] >= '0'){
                num1 = num1 * 10 + (s[j] - '0');
                j++;
            }
            if(j == n || s[j] != ','){
                continue;
            }
            j++;
            int k = j;
            while(k < n && s[k] <= '9' && s[k] >= '0'){
                num2 = num2 * 10 + (s[k] - '0');
                k++;
            }
            if(k == n || s[k] != ')'){
                continue;
            }
            ans += num1 * num2;
        }
    }
    return ans;
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifdef mlocal
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    int ans = 0;
    string s;
    bool ok = 1;
    while(getline(cin, s)){
        stringstream ss(s);
        string word;
        while(ss >> word){
            ans += solve(word, ok);
        }
    }
    cout << ans << "\n";
    int t = 1;
    // cin >> t;
    fr(i,1,t + 1){
        // cout << "Case #" << i << ": ";
        // solve();
        // cout << "\n";
    }
    return 0;
}