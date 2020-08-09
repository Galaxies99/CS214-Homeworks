# include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const int M = 5e5 + 10;
const int mod = 1e9 + 7;

inline int getint() {
  int x=0, f=1; char ch = getchar();
  while(ch < '0' || ch > '9') {
  	if(ch == '-') f = -1;
	  ch = getchar();
  }
  while(ch >= '0' && ch <= '9') {
  	x = (x<<3) + (x<<1) + ch - '0';
	  ch = getchar();
  }
  return x*f;
}

vector < pair <int, int> > E;

inline void getring(int beg, int end) {
  for (int i = beg; i <= end; ++ i) {
    int nxt = i + 1;
    if (i == end) nxt = beg;
    E.push_back(make_pair(i, nxt));
  }
  for (int i = 0; i <= 500; ++ i) {
    // [beg, end];
    int a = 1ll * rand() * rand() % (end - beg + 1) + beg;
    int b = 1ll * rand() * rand() % (end - beg + 1) + beg;
    E.push_back(make_pair(a, b));
  }
}

int main() {
  freopen("newSCC.in", "w", stdout);
  for (int i = 0; i < 10000; i += 100) {
    getring(i, i + 100 - 1);
    int nxt = i + 100;
    if(nxt == 10000)
      E.push_back(make_pair(0, i));
    else
      E.push_back(make_pair(i, nxt));
  }
  for (int i = 10000; i < 20000; i += 100) {
    getring(i, i + 100 - 1);
    if(i != 10000) E.push_back(make_pair(10000, i));
  }
  for (int i = 20000; i < 40000; i += 100) {
    getring(i, i + 100 - 1);
    int nxt = i + 100;
    if(nxt == 40000)
      E.push_back(make_pair(20000, i));
    else
      E.push_back(make_pair(i, nxt));
  }
  for (int i = 40000; i < 65000; i += 100) {
    getring(i, i + 100 - 1);
    int nxt = i + 100;
    if(nxt == 65000)
      E.push_back(make_pair(40000, i));
    else
      E.push_back(make_pair(i, nxt));
  }
  for (int i = 65000; i < 100000; i += 100) {
    getring(i, i + 100 - 1);
    int nxt = i + 100;
    if(nxt == 100000)
      E.push_back(make_pair(65000, i));
    else
      E.push_back(make_pair(i, nxt));
  }
  cout << 100000 << ' ' << E.size() << endl;
  for (int i = 0, s = E.size(); i < s; ++ i) 
    cout << E[i].first << ' ' << E[i].second << endl;
  return 0;
}



