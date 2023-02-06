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
  
vector<long long> sieve(long long n){
  vector<long long> res;
  vector<bool> valid(n+1, true);

  long long until = 2;

  while(until * until < n){
    until++;
  }
  
  for(long long i = 2; i <= until; i++){
    if(valid[i]){
      res.push_back(i);
    }
  
    for(long long j = i; j <= n; j += i){
      valid[j] = false;
    }
  }

  for(long long i = until+1; i <= n; i++){
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

map<long long, long long> factorize(long long n, vector<long long> &primes){
  map<long long, long long> res;

  for(long long p: primes){
    while(n % p == 0LL){
      res[p]++;
      n /= p;
    }
  }

  if(n != 1LL){
    res[n]++;
  }

  return res;
}

/* template end */

int get_val(int x){
  int res = 0;

  while(x > 0){
    res += x % 10;
    x /= 10;
  }

  return res;
}

void solve_case(){
  int n, q;
  cin >> n >> q;

  vector<int> v(n);
  set<int> st;

  for(int i = 0; i < n; i++){
    cin >> v[i];
    st.insert(i);
  }

  while(q--){
    int p;
    cin >> p;

    if(p == 2){
      int x;
      cin >> x;

      cout << v[x-1] << endl;
      continue;
    }

    int l, r;
    cin >> l >> r;

    int curr = l-1;

    while(true){
      auto it = st.lower_bound(curr);

      if(it == st.end() || *it > r-1){
        break;
      }

      int x = *it;
      st.erase(it);

      v[x] = get_val(v[x]);

      if(v[x] > 9){
        st.insert(x);
      }

      curr = x+1;
    }
  }
}

int main(){
  int test = 1;
  cin >> test;

  while(test--){
    solve_case();
  }

  return 0;
}