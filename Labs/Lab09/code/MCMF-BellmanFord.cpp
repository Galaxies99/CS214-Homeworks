# include <queue>
# include <stdio.h>
# include <string.h>
# include <iostream>
# include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const int N = 1e4 + 10, M = 3e5 + 10, INF = 1e9;

int n, m;
int S, T;       // Source & Sink
int head[N], nxt[M], to[M], cap[M], w[M];
                // edge link list
int tot = 1;

inline void add(int u, int v, int _cap, int _w) {
  ++ tot; nxt[tot] = head[u]; head[u] = tot;
  to[tot] = v; cap[tot] = _cap; w[tot] = _w;
}
inline void adde(int u, int v, int _cap, int _w) {
  add(u, v, _cap, _w);
  add(v, u, 0, -_w);
}

namespace MCMF {
  queue <int> q;
  int d[N];
  int pre[N];
  bool inq[N];
  
  // SPFA Algorithm - An improved algorithm based on Bellman-Ford Algorithm
  inline bool spfa() {
    while(!q.empty()) q.pop();
    for (int i = 1; i <= n; ++ i) inq[i] = false, d[i] = INF;
    d[S] = 0; inq[S] = true;
    q.push(S);
    while(!q.empty()) {
      int top = q.front(); q.pop();
      inq[top] = false;
      for (int i = head[top]; i; i = nxt[i])
        if (d[to[i]] > d[top] + w[i] && cap[i]) {    // relax operation
          d[to[i]] = d[top] + w[i];
          pre[to[i]] = i;                            // memorize the previous edge
          if(! inq[to[i]]) {
            q.push(to[i]);
            inq[to[i]] = true;
          }
        } 
    }
    return d[T] < INF;                               // if there is a feasible flow
  } 
  
  inline pair <int, ll> cost_flow() {
    int flow = INF;
    ll cost = 0;
    for (int i = pre[T]; i; i = pre[to[i ^ 1]])
      flow = min(flow, cap[i]);
    for (int i = pre[T]; i; i = pre[to[i ^ 1]]) {
      cap[i] -= flow;
      cap[i ^ 1] += flow;                            // back edge
      cost += 1ll * flow * w[i];
    }
    return make_pair(flow, cost);
  }
  
  inline pair <int, ll> MCMF() {
    int flow = 0;
    ll cost = 0;
    while(spfa()) {
      pair <int, ll> res = cost_flow();
      flow += res.first;
      cost += res.second;
    }
    return make_pair(flow, cost);
  }
} 

int main() {
  freopen("MCMF_1.in", "r", stdin);
//  freopen("MCMF.out", "w", stdout);
  
  ios :: sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> n >> m >> S >> T;
  for (int i = 1, u, v, _cap, _w; i <= m; ++ i) {
    cin >> u >> v >> _cap >> _w;
    adde(u, v, _cap, _w);
  }
  
  pair <int, ll> ans = MCMF :: MCMF();
  
  cout << "Max Flow = " << ans.first << '\n';
  cout << "Min Cost (under max flow) = " << ans.second << '\n';
  
  return 0;
}



