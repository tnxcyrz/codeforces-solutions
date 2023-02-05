#include <bits/stdc++.h>
  
using namespace std;
  
/* template start */
  
template <typename T>
string vector_to_string(vector<T> vec, char delim=' '){
  string res = "";
  
  for(int i = 0; i < vec.size(); i++){
    if(i > 0){
      res += delim;
    }
  
    res += to_string(vec[i]);
  }
  
  return res;
}
  
// Call build_segtree(_, _, 1, 0, n-1) to build.
void build_segtree(vector<int> &a, vector<int> &t, int v, int tl, int tr) {
  if (tl == tr) {
    t[v] = a[tl];
  } else {
    int tm = (tl + tr) / 2;
    build_segtree(a, t, v*2, tl, tm);
    build_segtree(a, t, v*2+1, tm+1, tr);
    t[v] = t[v*2] + t[v*2+1];
  }
}
  
int query_segtree(vector<int> &t, int v, int tl, int tr, int l, int r) {
  if (l > r)
    return 0;
  if (l == tl && r == tr) {
    return t[v];
  }
  int tm = (tl + tr) / 2;
  return query_segtree(t, v*2, tl, tm, l, min(r, tm))
          + query_segtree(t, v*2+1, tm+1, tr, max(l, tm+1), r);
}
  
void update_segtree(vector<int> &t, int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
      t[v] += new_val;
    } else {
      int tm = (tl + tr) / 2;
      if (pos <= tm)
          update_segtree(t, v*2, tl, tm, pos, new_val);
      else
          update_segtree(t, v*2+1, tm+1, tr, pos, new_val);
      t[v] = t[v*2] + t[v*2+1];
    }
}
  
pair<vector<int>, vector<int>> make_sets(int n){
  vector<int> res(n);
  vector<int> szs(n, 1);
  
  for(int i = 0; i < n; i++){
    res[i] = i;
  }
  
  return make_pair(res, szs);
}
  
int find_set(vector<int> &dsu, int v) {
  if (v == dsu[v])
    return v;
  return dsu[v] = find_set(dsu, dsu[v]);
}
  
void union_sets(vector<int> &dsu, vector<int>& szs, int a, int b) {
  a = find_set(dsu, a);
  b = find_set(dsu, b);
  if (a != b) {
    if (szs[a] < szs[b])
      swap(a, b);
    dsu[b] = a;
    szs[a] += szs[b];
  }
}
  
int count_sets(vector<int> &dsu){
  int res = 0;
  
  for(int i = 0; i < dsu.size(); i++){
    if(dsu[i] == i){
      res++;
    }
  }
  
  return res;
}
  
vector<vector<long long>> floyd_warshall(vector<vector<long long>> &g){
  int n = g.size();
  auto dists = g;
  
  for(int k = 0; k < n; k++){
    for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
        long long candidate = dists[i][k] + dists[k][j];
        dists[i][j] = min(dists[i][j], candidate);
      }
    }
  }
  
  return dists;
}
  
vector<int> sieve(int n){
  vector<int> res;
  vector<bool> valid(n+1, true);

  int until = 2;

  while(until * until < n){
    until++;
  }
  
  for(int i = 2; i <= until; i++){
    if(valid[i]){
      res.push_back(i);
    }
  
    for(int j = i; j <= n; j += i){
      valid[j] = false;
    }
  }

  for(int i = until+1; i <= n; i++){
    if(valid[i]){
      res.push_back(i);
    }
  }

  return res;
}

long long fast_pow(long long a, long long b, long long m){
    long long ans = 1LL;

    while(b > 0){
      if(b & 1LL){
        ans *= a;
        ans %= m;
      }
      a *= a;
      a %= m;
      b >>= 1;
    }

    return ans;
}

/* template end */

bool is_valid(char a, char b, int msk, vector<char> &p){
  if(a == b){
    return true;
  }

  int idx = find(p.begin(), p.end(), a) - p.begin();

  return (msk & (1 << idx));
}

void solve_case(){
  int n, k;
  cin >> n >> k;

  string a, b;
  cin.ignore();
  cin >> a >> b;

  vector<char> p;

  for(char c: a){
    if(find(p.begin(), p.end(), c) == p.end()){
      p.push_back(c);
    }
  }

  int m = (int) p.size();
  k = min(k, m);
  int upto = 1 << m;

  long long ans = 0LL;

  // cout << "k = " << k << endl;

  for(int i = 0; i < upto; i++){
    if(__builtin_popcount(i) != k){
      continue;
    }

    int u = 0;
    long long candidate = 0LL;

    while(u < n){
      if(!is_valid(a[u], b[u], i, p)){
        u++;
        continue;
      }

      int v = u+1;

      while(v < n){
        if(!is_valid(a[v], b[v], i, p)){
          break;
        }

        v++;
      }

      long long x = v - u;
      candidate += x * (x+1LL) / 2LL;

      // printf("k = %3d, mask = %10d, u = %3d, v = %3d\n", k, i, u, v);

      u = v;
    }

    ans = max(ans, candidate);
  }

  // cout << vector_to_string(p) << endl;
  cout << ans << endl;
}

int main(){
  int test = 1;
  cin >> test;

  while(test--){
    solve_case();
  }

  return 0;
}