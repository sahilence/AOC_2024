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

bool rec(vi &v, int idx, int tot, int sum){
    if(idx == v.size()){
        return sum == tot;
    }
    int s = tot;
    int x = v[idx];
    while(tot < sum && x){
        tot *= 10;
        x /= 10;
    }
    if(tot > sum) return rec(v, idx + 1, s + v[idx], sum) || rec(v, idx + 1, s * v[idx], sum);
    return rec(v, idx + 1, s + v[idx], sum) || rec(v, idx + 1, s * v[idx], sum) || rec(v, idx + 1, tot + v[idx], sum);
}

int str_to_int(string s){
    int ans = 0;
    fr(i,0,s.size()){
        ans = ans * 10 + (s[i] - '0');
    }
    return ans;
}

int solve(vector<string> &v){
    v[0].pop_back();
    vi a;
    int tot = 0;
    for(auto i: v){
        a.pb(str_to_int(i));
    }
    tot = a[0];
    a.erase(a.begin());
    return rec(a, 0, 0, tot) ? tot : 0;
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifdef mlocal
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    string s;
    int ans = 0;
    while(getline(cin, s)){
        stringstream ss(s);
        string word;
        vector<string> v;
        while(ss >> word){
            v.pb(word);
        }
        ans += solve(v);
    }
    cout << ans << "\n";
    return 0;
}