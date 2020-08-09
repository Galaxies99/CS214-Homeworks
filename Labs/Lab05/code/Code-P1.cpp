# include <stdio.h>
# include <string.h>
# include <iostream>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const int M = 2e3 + 10, inf = 1e9;

int n, t[M], w[M];
int f[M][M << 2]; 

int main() {
  freopen("../Lab05-TestCase/Data-P1.txt", "r", stdin);
  ios :: sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  
  cin >> n;
  for (int i = 1; i <= n; ++ i)
    cin >> t[i] >> w[i];
    
  int offset = (n << 1);
  
  for (int i = 0; i <= n; ++ i)
    for (int j = -(n << 1); j <= (n << 1); ++ j)
      f[i][j + offset] = inf;
  
  f[0][0 + offset] = 0;
  
  for (int i = 1; i <= n; ++ i)
    for (int j = -(n << 1); j <= (n << 1); ++ j) {
      if(j - t[i] >= -(n << 1)) f[i][j + offset] = min(f[i][j + offset], f[i - 1][j - t[i] + offset] + t[i]);
      if(j + w[i] <= (n << 1)) f[i][j + offset] = min(f[i][j + offset], f[i - 1][j + w[i] + offset]); 
    }
  
  int ans = inf;
  for (int j = 0; j <= (n << 1); ++ j) 
    ans = min(ans, f[n][j + offset]);
  
  cout << ans << endl;

  return 0;
}



