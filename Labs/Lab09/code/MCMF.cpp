# include <queue>
# include <stdio.h>
# include <assert.h>
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
  struct heap_element {
    int node;
    int dis;
    
    heap_element() {}
    heap_element(int node, int dis) : node(node), dis(dis) {}
    
    bool operator < (const heap_element &rhs) const {
      return dis < rhs.dis;
    }
    
    bool operator > (const heap_element &rhs) const {
      return dis > rhs.dis;
    }
  };
  
  priority_queue <heap_element, vector <heap_element>, greater <heap_element> > heap;
  
  int phi[N]; 
  int d[N];
  int pre[N];
  bool inS[N];
  
  inline int reweight(int u, int v, int ori_w) {
    return ori_w + phi[u] - phi[v];
  }
  
  // Dijkstra Algorithm
  inline bool dijkstra() {
    while (! heap.empty()) heap.pop();
    for (int i = 1; i <= n; ++ i) d[i] = INF, inS[i] = false, pre[i] = 0;
    d[S] = 0;    
    heap.push(heap_element(S, 0));
    while (! heap.empty()) {
      heap_element top = heap.top(); heap.pop();
      if (inS[top.node] == true) continue;
      inS[top.node] = true;
      for (int i = head[top.node]; i; i = nxt[i])
        if (cap[i] && d[to[i]] > d[top.node] + reweight(top.node, to[i], w[i])) {  
          d[to[i]] = d[top.node] + reweight(top.node, to[i], w[i]);
          pre[to[i]] = i;                            // memorize the previous edge
          heap.push(heap_element(to[i], d[to[i]]));
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
    for (int i = 1; i <= n; ++ i) phi[i] = 0;
    while(dijkstra()) {
      pair <int, ll> res = cost_flow();
      flow += res.first;
      cost += res.second;
      for (int i = 1; i <= n; ++ i) phi[i] += d[i];
    }
    return make_pair(flow, cost);
  }
} 

int main() {
  freopen("MCMF.in", "r", stdin);
  freopen("MCMF.out", "w", stdout);
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



