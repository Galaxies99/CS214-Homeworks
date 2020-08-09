# include <map>
# include <stdio.h>
# include <string.h>
# include <iostream>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const int M = 2e5 + 10, inf = 1e9;

int n, m, new_n = 0;
char s[M], t[M];              // two RNA sequences
char ans_s[M], ans_t[M];      // the answer RNA sequences
int f[2][M];                  // the DP array
int enter[M], leave[M];       // when to enter the row and when to leave the row
map <char, int> id;           // map 'A', 'T', 'G', 'C' to 1~4
int cost_matrix[5][5] = {     // the given cost matrix
  {0, 1, 2, 1, 3},
  {1, 0, 1, 5, 1},
  {2, 1, 0, 9, 1},
  {1, 5, 9, 0, 1},
  {3, 1, 1, 1, 0}
};


int* dp1(int bx, int by, int ex, int ey) {
  // perform dynamic programming from (bx, by) to (ex, ey), where bx <= ex and by <= ey
  int pre = 0, cur = 1;
  for (int j = by; j <= ey; ++ j) {
    for (int i = bx; i <= ex; ++ i) { 
      if (j == by && i == bx) f[cur][i] = 0;
      else f[cur][i] = inf;
      
      if (i != bx) f[cur][i] = min(f[cur][i], f[cur][i-1] + cost_matrix[id[s[i]]][0]);
      if (j != by) f[cur][i] = min(f[cur][i], f[pre][i] + cost_matrix[0][id[t[j]]]);
      if (i != bx && j != by) f[cur][i] = min(f[cur][i], f[pre][i-1] + cost_matrix[id[s[i]]][id[t[j]]]);
    } 
    swap(cur, pre);
  }
  return f[pre];
}

int* dp2(int bx, int by, int ex, int ey) {
  // perform dynamic programming from (ex, ey) to (bx, by), where bx <= ex and by <= ey
  int pre = 0, cur = 1;
  for (int j = ey; j >= by; -- j) {
    for (int i = ex; i >= bx; -- i) { 
      if (j == ey && i == ex) f[cur][i] = 0;
      else f[cur][i] = inf;
      
      if (i != ex) f[cur][i] = min(f[cur][i], f[cur][i+1] + cost_matrix[id[s[i+1]]][0]);
      if (j != ey) f[cur][i] = min(f[cur][i], f[pre][i] + cost_matrix[0][id[t[j+1]]]);
      if (i != ex && j != ey) f[cur][i] = min(f[cur][i], f[pre][i+1] + cost_matrix[id[s[i+1]]][id[t[j+1]]]);
    } 
    swap(cur, pre);
  }
  return f[pre];
}

int rec1[M], rec2[M];       // temporarily record the DP result
void solve(int bx, int by, int ex, int ey) {
  if(ey - by <= 1) return;
  
  int mid = (by + ey) >> 1, *p;
  p = dp1(bx, by, ex, mid);
  for (int i = bx; i <= ex; ++ i) rec1[i] = p[i];
  p = dp2(bx, mid, ex, ey);
  for (int i = bx; i <= ex; ++ i) rec2[i] = p[i];
  
  // calculate the minimum q 
  int pos = 0, cur = inf;
  for (int i = bx; i <= ex; ++ i)
    if(rec1[i] + rec2[i] < cur) {
      cur = rec1[i] + rec2[i];
      pos = i;
    }
  
  // q is the enter point, we have to calculate the leave point q'
  enter[mid] = leave[mid] = pos;
  for (int i = pos + 1, sum = 0; i <= ex; ++ i) {
    sum += cost_matrix[id[s[i]]][0];
    if(sum + rec2[i] != rec2[pos]) break;
    leave[mid] = i;
  }
  
  // divide and solve
  solve(bx, by, enter[mid], mid);
  solve(leave[mid], mid, ex, ey);
}

int main() {
  ios :: sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  
  id['A'] = 1; id['T'] = 2; id['G'] = 3; id['C'] = 4; id['_'] = 0;
  s[0] = t[0] = '_';
  
// # define TEST_SMALL_DATA
  
# ifdef TEST_SMALL_DATA
  scanf("%s%s", s + 1, t + 1);
# endif

# ifndef TEST_SMALL_DATA
  FILE *fp;
  fp = fopen("Data-P2a.txt", "r");
  fscanf(fp, "%s", s + 1);
  fclose(fp);
  fp = fopen("Data-P2b.txt", "r");
  fscanf(fp, "%s", t + 1);
  fclose(fp);
  
  freopen("result.res", "w", stdout);
# endif
  
  n = strlen(s + 1), m = strlen(t + 1);
  
  solve(0, 0, n, m);
  
  // calculate leave[0]
  enter[0] = 0;
  if(enter[1] == 0) leave[0] = 0;
  else {
    int c = enter[1];
    if (cost_matrix[id[s[c]]][id[t[1]]] < cost_matrix[id[s[c]]][0] + cost_matrix[0][id[t[1]]])
      leave[0] = c - 1;
    else leave[0] = c;
  }
  
  // calculate enter[m]
  leave[m] = n;
  if(leave[m - 1] == n) enter[m] = n;
  else {
    int c = leave[m - 1];
    if (cost_matrix[id[s[c + 1]]][id[t[m]]] < cost_matrix[id[s[c + 1]]][0] + cost_matrix[0][id[t[m]]]) 
      enter[m] = c + 1;
    else enter[m] = c;
  }
  
  // get output
  for (int i = 0; i <= m; ++ i) {
    for (int j = enter[i]; j < leave[i]; ++ j) ans_s[new_n] = s[j + 1], ans_t[new_n] = '_', ++ new_n;
    if(i != m) {
      if (leave[i] == enter[i + 1]) ans_s[new_n] = '_', ans_t[new_n] = t[i + 1], ++ new_n;
      else ans_s[new_n] = s[enter[i + 1]], ans_t[new_n] = t[i + 1], ++ new_n;
    } 
  } 
  
  // calculate minimum cost
  int minimum_cost = 0;
  for (int i = 0; i < new_n; ++ i)
    minimum_cost += cost_matrix[id[ans_s[i]]][id[ans_t[i]]];
    
# define OUTPUT_COST
# define OUTPUT_ANSWER

# ifdef OUTPUT_COST 
  cout << "Minimum Cost = " << minimum_cost << "\n\n";
# endif

# ifdef OUTPUT_ANSWER
  cout << ans_s << endl;
  cout << ans_t << endl;
# endif

  return 0;
}



