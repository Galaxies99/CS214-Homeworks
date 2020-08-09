#include <vector>
#include <iostream>
#include <fstream>
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

void dfs(const vector < vector <int> > &E, int x, vector <int> &dfn, vector <int> &out, int &idx) {
  dfn[x] = ++idx; 
  for (auto &dest: E[x]) 
    if (! dfn[dest]) dfs(E, dest, dfn, out, idx);
  out[x] = ++idx;
}

int SCC (int n, vector < pair <int, int> > &edge) {
  vector < vector <int> > E, Er;
  vector <int> dfn, out;
  vector <int> order; 
  int idx, scc;
  
  E.resize(n);
  Er.resize(n);
  dfn.resize(n);
  out.resize(n);
  order.resize(n << 1);
  
  for (auto &edge_list: E) edge_list.clear();
  for (auto &edge_list: Er) edge_list.clear();
  
  for (auto &e: edge) {
    E[e.first].push_back(e.second);
    Er[e.second].push_back(e.first);
  }
  
  idx = 0;
  for (auto &d: dfn) d = 0;
  for (int i = 0; i < n; ++ i)
    if(! dfn[i]) dfs(Er, i, dfn, out, idx);
  
  for (auto &o: order) o = -1;
  for (int i = 0; i < n; ++ i) order[out[i] - 1] = i;
  
  scc = 0;
  idx = 0;
  for (auto &d: dfn) d = 0;
  for (int i = (n << 1) - 1; ~i; -- i)
    if(order[i] != -1 && ! dfn[order[i]]) {
      ++ scc;
      dfs(E, order[i], dfn, out, idx);
    }
  return scc;
}

//Please do NOT modify anything in main(). Thanks!
int main()
{
    int m,n;
    vector<pair<int,int>> edge;
    ifstream fin;
    ofstream fout;
    fin.open("SCC.in");
    fin>>n>>m;
    int tmp1,tmp2;
    for(int i=0;i<m;i++)
    {
        fin>>tmp1>>tmp2;
        edge.push_back(pair<int,int>(tmp1,tmp2));
    }
    fin.close();
    int ans=SCC(n,edge);
    fout.open("SCC.out");
    fout<<ans<<'\n';
    fout.close();
    return 0;
}
