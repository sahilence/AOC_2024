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

void dfs(vector<string> &v, int i, int j){
    if(v[i][j] == '^'){
        if(i){
            if(v[i - 1][j] == '#'){
                v[i][j] = '>';
                dfs(v, i, j);
            }
            else{
                v[i][j] = 'X';
                v[i - 1][j] = '^';
                dfs(v, i - 1, j);
            }
        }
        else{
            v[i][j] = 'X';
        }
    }
    else if(v[i][j] == '>'){
        if(j + 1 < v[0].size()){
            if(v[i][j + 1] == '#'){
                v[i][j] = 'v';
                dfs(v, i, j);
            }
            else{
                v[i][j] = 'X';
                v[i][j + 1] = '>';
                dfs(v, i, j + 1);
            }
        }
        else{
            v[i][j] = 'X';
        }
    }
    else if(v[i][j] == 'v'){
        if(i + 1 < v.size()){
            if(v[i + 1][j] == '#'){
                v[i][j] = '<';
                dfs(v, i, j);
            }
            else{
                v[i][j] = 'X';
                v[i + 1][j] = 'v';
                dfs(v, i + 1, j);
            }
        }
        else{
            v[i][j] = 'X';
        }
    }
    else if(v[i][j] == '<'){
        if(j){
            if(v[i][j - 1] == '#'){
                v[i][j] = '^';
                dfs(v, i, j);
            }
            else{
                v[i][j] = 'X';
                v[i][j - 1] = '<';
                dfs(v, i, j - 1);
            }
        }
        else{
            v[i][j] = 'X';
        }
    }
}

bool dfs(vector<string> &v, int i, int j, set<pair<pair<int,int>,char>> &vis){
    bool ok = 0;
    if(vis.find({{i,j},v[i][j]}) != vis.end()) return 1;
    vis.insert({{i,j},v[i][j]});
    if(v[i][j] == '^'){
        if(i){
            if(v[i - 1][j] == '#'){
                v[i][j] = '>';
                ok = dfs(v, i, j, vis);
            }
            else{
                v[i][j] = 'X';
                v[i - 1][j] = '^';
                ok = dfs(v, i - 1, j, vis);
            }
        }
    }
    else if(v[i][j] == '>'){
        if(j + 1 < v[0].size()){
            if(v[i][j + 1] == '#'){
                v[i][j] = 'v';
                ok = dfs(v, i, j, vis);
            }
            else{
                v[i][j] = 'X';
                v[i][j + 1] = '>';
                ok = dfs(v, i, j + 1, vis);
            }
        }
    }
    else if(v[i][j] == 'v'){
        if(i + 1 < v.size()){
            if(v[i + 1][j] == '#'){
                v[i][j] = '<';
                ok = dfs(v, i, j, vis);
            }
            else{
                v[i][j] = 'X';
                v[i + 1][j] = 'v';
                ok = dfs(v, i + 1, j, vis);
            }
        }
    }
    else if(v[i][j] == '<'){
        if(j){
            if(v[i][j - 1] == '#'){
                v[i][j] = '^';
                ok = dfs(v, i, j, vis);
            }
            else{
                v[i][j] = 'X';
                v[i][j - 1] = '<';
                ok = dfs(v, i, j - 1, vis);
            }
        }
    }
    return ok;
}

int solve(vector<string> &v){
    int n = v.size(), m = v[0].size();
    int x , y;
    fr(i,0,n){
        fr(j,0,m){
            if(v[i][j] == '^'){
                x = i, y = j;
                dfs(v, i, j);
                v[i][j] = '^';
            }
        }
    }
    int ans = 0;
    fr(i,0,n){
        fr(j,0,m){
            if(v[i][j] == 'X'){
                set<pair<pair<int,int>,char>> vis;
                vector<string> temp = v;
                temp[i][j] = '#';
                ans += dfs(temp, x, y, vis);
            }
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
    string s;
    vector<string> v;
    while(getline(cin, s)){
        stringstream ss(s);
        string word;
        while(ss >> word){
            v.pb(word);
        }
    }
    cout << solve(v) << "\n";
    return 0;
}