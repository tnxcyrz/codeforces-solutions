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

void solve_case(){
  long long n, c;
  cin >> n >> c;

  vector<pair<long long, long long>> costs(n+1);

  for(long long i = 1; i <= n; i++){
    long long x;
    cin >> x;
    
    long long minn = min(i, n-i+1);
    costs[i] = {x + minn, x+i};
    // printf("costs %3lld: %lld %lld\n", i, costs[i].first, costs[i].second);
  }

  sort(costs.begin(), costs.end());

  vector<long long> sums = {0LL};

  for(long long i = 1LL; i <= n; i++){
    sums.push_back(sums.back() + costs[i].first);
  }

  // cout << vector_to_string(sums) << endl;

  int ans = 0LL;

  for(long long i = 1LL; i <= n; i++){
    long long rem = c - costs[i].second;

    if(rem < 0LL){
      continue;
    }

    int l = 0, r = n;

    while(l < r){
      int m = (l+r+1)/2;
      long long cost = sums[m];

      if(i <= m){
        cost -= costs[i].first;
      }

      if(cost <= rem){
        l = m;
      }

      else{
        r = m-1;
      }

      // printf("rem = %10lld, %3d %3d\n", rem, l, r);
    }

    int candidate = 1 + (i <= l ? l-1 : l);
    ans = max(ans, candidate);
    // printf("i = %3lld, costs: %10lld %10lld, add = %3d, ans = %3d\n", i, costs[i].first, costs[i].second, candidate, ans);
  }

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