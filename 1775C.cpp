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

/* template end */

long long set_prefix_zero(long long x, int digs){
  long long y = ~0LL;

  for(int i = 0; i < digs; i++){
    y ^= 1LL << i;
  }

  return x & y;
}

void solve_case(){
  long long n, x;
  cin >> n >> x;

  bool had_one = false;
  long long m = n;
  bitset<100> used;

  for(int i = 0; (1LL << i) <= n; i++){
    int val = (n >> i) & 1LL;
    used[i] = val ^ 1;
  }
  
  for(int i = 0; n > 0; i++){
    int a = n & 1;
    int b = x & 1;

    // printf("comparing %3d: %3d %3d, %d\n", i, a, b, int(used[i]));

    if(a == 0 && b == 1){
      // printf("broke fir at i = %3d\n", i);
      cout << -1 << endl;
      return;
    }

    else if(a == 1 && b == 0 && used[i] == false){
      if(had_one){
        cout << -1 << endl;
        return;
      }

      for(int j = 0;; j++){
        n ^= 1LL << j;
        used[i+j] = true;

        // printf("updated idx = %3d, n = %20lld, m = %20lld\n", i+j, n, m);

        if(((n >> j) & 1LL) == 1LL){
          int digs = i+j;
          m = set_prefix_zero(m, i+j);
          m ^= 1LL << (i+j);

          break;
        }
      }
    }

    else if(a == 1 && b == 1 && used[i] == true){
      // printf("broke sec at i = %3d\n", i);
      cout << -1 << endl;
      return;
    }

    if(b == 1){
      had_one = true;
    }

    n >>= 1;
    x >>= 1;
  }

  if(x > 0){
    cout << -1 << endl;
    return;
  }

  cout << m << endl;
}

int main(){
  int test = 1;
  cin >> test;

  while(test--){
    solve_case();
  }

  return 0;
}