#include <bits/stdc++.h>
using namespace std;
//Please put this source code in the same directory with SCC.in
//And do NOT change the file name.
/*
This function computes the number of Strongly Connected Components in a graph
Args:
    n: The number of nodes in the graph. The nodes are indexed as 0~n-1
    edge: The edges in the graph. For each element (a,b) in edge, it means
          there is a directed edge from a to b
          Notice that there may exists multiple edge and self-loop
Return:
    The number of strongly connected components in the graph.
*/ 

vector <int> bel;
map < pair<int, int>, int> mp;

void tarjan(vector < vector <int> > &E, int x, vector <int> &dfn, vector <int> &low, vector <int> &instack, stack <int> &sta, int &idx, int &scc) {
  dfn[x] = low[x] = ++idx;
  sta.push(x); 
  instack[x] = 1;
  
  for (auto &dest: E[x]) {
    if(! dfn[dest]) {
      tarjan(E, dest, dfn, low, instack, sta, idx, scc);
      low[x] = min(low[dest], low[x]);
    } else if (instack[dest]) low[x] = min(low[x], dfn[dest]);
  }
  
  if(dfn[x] == low[x]) {
    while(true) {
      int y = sta.top();
      bel[y] = scc;
      sta.pop(); instack[y] = 0;
      if (y == x) break;
    }
    ++ scc;
  }
} 
  
int SCC (int n, vector < pair <int, int> > &edge) {
  vector < vector <int> > E;
  vector <int> dfn, low;
  vector <int> instack;
  stack <int> sta; 
  int idx, scc;
  
  E.resize(n);
  dfn.resize(n);
  low.resize(n);
  bel.resize(n);
  instack.resize(n);
  while(!sta.empty()) sta.pop();
  
  for (auto &edge_list: E) edge_list.clear();
  
  for (auto &e: edge) 
    E[e.first].push_back(e.second);
    
  scc = 0;
  idx = 0; 
  for (auto &d: dfn) d = 0;
  for (auto &in: instack) in = 0;
  for (int i = 0; i < n; ++ i)
    if(! dfn[i]) tarjan(E, i, dfn, low, instack, sta, idx, scc);
    
  return scc;
}

//Please do NOT modify anything in main(). Thanks!
int main()
{
    int m,n;
    vector<pair<int,int>> edge;
    ifstream fin;
    ofstream fout;
    fin.open("newSCC.in");
    fin>>n>>m;
    int tmp1,tmp2;
    for(int i=0;i<m;i++)
    {
        fin>>tmp1>>tmp2;
        edge.push_back(pair<int,int>(tmp1,tmp2));
    }
    fin.close();
    int ans=SCC(n,edge);
    fout.open("newSCC.csv");
    fout << "source, target, \n";
    for (int i = 0; i < edge.size(); ++ i) {
      pair <int, int> e = edge[i];
      e.first = bel[e.first];
      e.second = bel[e.second];
      if(e.first == e.second) continue;
      if(mp[e] == 0) {
        mp[e] = 1;
        fout << e.first << ',' << e.second << ",\n";
      }
    }
    fout.close();
    return 0;
}
