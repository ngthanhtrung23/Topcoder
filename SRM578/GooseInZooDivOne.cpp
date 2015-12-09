// Div1 - 250
// Algo: Basic BFS
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 55;
const ll MOD = 1e9 + 7;
char a[MN][MN];
int m, n, dist;
bool visited[MN][MN];

const int di[4] = {-1,1,0,0};
const int dj[4] = {0,0,-1,1};

int bfs(int u, int v) {
	queue<int> qu, qv;
	qu.push(u);
	qv.push(v);
	visited[u][v] = true;

	int res = 0;
	while (!qu.empty()) {
		int u = qu.front(), v = qv.front();
		qu.pop(); qv.pop();
		++res;

		FOR(uu,1,m) FOR(vv,1,n) if (!visited[uu][vv] && a[uu][vv] == 'v' && abs(u - uu) + abs(v - vv) <= dist) {
			qu.push(uu);
			qv.push(vv);
			visited[uu][vv] = true;
		}
	}
	return res;
}

ll c[2511][2511];

class GooseInZooDivOne {
public:
    int count( vector <string> field, int dist ) {
		::dist = dist;
		m = SZ(field); n = SZ(field[0]);
		FOR(i,1,m) FOR(j,1,n) a[i][j] = field[i-1][j-1];
		memset(visited, 0, sizeof visited);

		int even = 0, odd = 0;
		FOR(i,1,m) FOR(j,1,n) if (a[i][j] == 'v' && !visited[i][j]) {
			int x = bfs(i, j);
			if (x % 2 == 0) ++even;
			else ++odd;
		}

		FOR(i,0,2500) FOR(j,0,i) {
			if (j == 0) c[i][j] = 1;
			else c[i][j] = (c[i-1][j-1] + c[i-1][j]) % MOD;
		}

		ll res = 0;
		FOR(x,0,even) FOR(y,0,odd) if (x || y) {
			if (y % 2 == 1) continue;

			res = (res + c[even][x] * c[odd][y]) % MOD;
		}
		return res;
    }
};

// BEGIN CUT HERE
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
namespace moj_harness {
	using std::string;
	using std::vector;
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				std::cerr << "Illegal input! Test case " << casenum << " does not exist." << std::endl;
			}
			return;
		}
		
		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}
		
		if (total == 0) {
			std::cerr << "No test cases run." << std::endl;
		} else if (correct < total) {
			std::cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << std::endl;
		} else {
			std::cerr << "All " << total << " tests passed!" << std::endl;
		}
	}
	
	int verify_case(int casenum, const int &expected, const int &received, std::clock_t elapsed) { 
		std::cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}
		
		std::cerr << verdict;
		if (!info.empty()) {
			std::cerr << " (";
			for (size_t i=0; i<info.size(); ++i) {
				if (i > 0) std::cerr << ", ";
				std::cerr << info[i];
			}
			std::cerr << ")";
		}
		std::cerr << std::endl;
		
		if (verdict == "FAILED") {
			std::cerr << "    Expected: " << expected << std::endl; 
			std::cerr << "    Received: " << received << std::endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string field[]            = {"vvv"};
			int dist                  = 0;
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = GooseInZooDivOne().count(vector <string>(field, field + (sizeof field / sizeof field[0])), dist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string field[]            = {"."};
			int dist                  = 100;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = GooseInZooDivOne().count(vector <string>(field, field + (sizeof field / sizeof field[0])), dist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string field[]            = {"vvv"};
			int dist                  = 1;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = GooseInZooDivOne().count(vector <string>(field, field + (sizeof field / sizeof field[0])), dist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string field[]            = {"v.v..................v............................"
,".v......v..................v.....................v"
,"..v.....v....v.........v...............v......v..."
,".........vvv...vv.v.........v.v..................v"
,".....v..........v......v..v...v.......v..........."
,"...................vv...............v.v..v.v..v..."
,".v.vv.................v..............v............"
,"..vv.......v...vv.v............vv.....v.....v....."
,"....v..........v....v........v.......v.v.v........"
,".v.......v.............v.v..........vv......v....."
,"....v.v.......v........v.....v.................v.."
,"....v..v..v.v..............v.v.v....v..........v.."
,"..........v...v...................v..............v"
,"..v........v..........................v....v..v..."
,"....................v..v.........vv........v......"
,"..v......v...............................v.v......"
,"..v.v..............v........v...............vv.vv."
,"...vv......v...............v.v..............v....."
,"............................v..v.................v"
,".v.............v.......v.........................."
,"......v...v........................v.............."
,".........v.....v..............vv.................."
,"................v..v..v.........v....v.......v...."
,"........v.....v.............v......v.v............"
,"...........v....................v.v....v.v.v...v.."
,"...........v......................v...v..........."
,"..........vv...........v.v.....................v.."
,".....................v......v............v...v...."
,".....vv..........................vv.v.....v.v....."
,".vv.......v...............v.......v..v.....v......"
,"............v................v..........v....v...."
,"................vv...v............................"
,"................v...........v........v...v....v..."
,"..v...v...v.............v...v........v....v..v...."
,"......v..v.......v........v..v....vv.............."
,"...........v..........v........v.v................"
,"v.v......v................v....................v.."
,".v........v................................v......"
,"............................v...v.......v........."
,"........................vv.v..............v...vv.."
,".......................vv........v.............v.."
,"...v.............v.........................v......"
,"....v......vv...........................v........."
,"....vv....v................v...vv..............v.."
,".................................................."
,"vv........v...v..v.....v..v..................v...."
,".........v..............v.vv.v.............v......"
,".......v.....v......v...............v............."
,"..v..................v................v....v......"
,".....v.....v.....................v.v......v......."};
			int dist                  = 3;
			int expected__            = 898961330;

			std::clock_t start__      = std::clock();
			int received__            = GooseInZooDivOne().count(vector <string>(field, field + (sizeof field / sizeof field[0])), dist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string field[]            = ;
			int dist                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GooseInZooDivOne().count(vector <string>(field, field + (sizeof field / sizeof field[0])), dist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string field[]            = ;
			int dist                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GooseInZooDivOne().count(vector <string>(field, field + (sizeof field / sizeof field[0])), dist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string field[]            = ;
			int dist                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GooseInZooDivOne().count(vector <string>(field, field + (sizeof field / sizeof field[0])), dist);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


#include <cstdlib>
int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(std::atoi(argv[i]));
	}
}
// END CUT HERE
