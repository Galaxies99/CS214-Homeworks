# include <string>
# include <conio.h>
# include <stdio.h>
# include <string.h>
# include <iostream>
# include <windows.h>
# include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

struct State {
  string state_name;
  State() {}
  State(string state_name) : state_name(state_name) {}
  State(const State& rhs) : state_name(rhs.state_name) {}
  void input() {
    cin >> state_name;
  }
  bool operator == (const State &rhs) const {
    return state_name == rhs.state_name;
  }
  bool operator != (const State &rhs) const {
    return state_name != rhs.state_name;
  }
} qs, qh;

struct Trans {
  State s1, s2;
  char c1, c2;
  char dir;
  Trans() {}
  Trans(State s1, State s2, char c1, char c2, char dir) :
    s1(s1), s2(s2), c1(c1), c2(c2), dir(dir) {}
  void input() {
    static char buf[20];
    s1.input(); 
    scanf("%s", buf); c1 = buf[0];
    s2.input();
    scanf("%s", buf); c2 = buf[0];
    scanf("%s", buf); dir = buf[0];
  }
} * T;
int m;

string tape;
State st;
int pos;

void output_tape() {
  cout << st.state_name << endl; 
  cout << tape << endl;
  for (int i = 0; i < pos; ++ i) cout << " ";
  cout << "-" << endl << endl;
}

void turing_machine() {
  int count = 0;
  qs.state_name = "qs";
  qh.state_name = "qh";
  st = qs;
  while(st != qh) {
    ++ count;
    bool ok = 0;
    for (int i = 0; i < m; ++ i) {
      if(T[i].s1 == st && T[i].c1 == tape[pos]) {
        tape[pos] = T[i].c2;
        st = T[i].s2;
        if(T[i].dir == 'R') ++ pos;
        else if(T[i].dir == 'L') -- pos;
        ok = 1;
        break;
      }
    }
    if(!ok) {
      cerr << "Error! No transition found.\n";
      exit(1);
    }
    cout << "Step " << count << ": \n";
    output_tape();
    getch();
  }
}

int main() {
  cout << "Please input the number of the transitions: ";
  cin >> m;
  T = new Trans[m];
  cout << "Please input the transitions: \n";
  cout << "  (qs - start state, qh - halt state, L/R/S: left/right/stay)\n";
  for (int i = 0; i < m; ++ i) {
    cout << "Transition " << i << ": ";
    T[i].input();
  }
  cout << "Please input the tape: \n";
  cin >> tape;
  cout << "Please input the initial position of the cursor: ";
  cin >> pos;
  cout << "Begin simulation, initial tape: \n";
  output_tape();
  
  turing_machine();
  
  cout << "End of simulation, final Tape: \n";
  output_tape();
  
  delete [] T;
  return 0;
}



