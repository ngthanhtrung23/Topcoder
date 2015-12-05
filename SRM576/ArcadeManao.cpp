// Div 1 - 250
// Algo:
// - Binary search answer (actually can just loop through all values)
// - For each length L, do BFS.
// - (i, j) --> (i, j+1), (i, j-1)
// - (i, j) --> (i', j) where |i - i'| <= L

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

char a[55][55];
int m, n;
bool visited[55][55];
int targetu, targetv;
queue<int> qu, qv;

void go(int u, int v) {
	if (a[u][v] == 'X' && !visited[u][v]) {
		visited[u][v] = true;
		qu.push(u);
		qv.push(v);
	}
}

bool check(int h) {
	memset(visited, 0, sizeof visited);
	while (!qu.empty()) qu.pop();
	while (!qv.empty()) qv.pop();

	FOR(j,1,n) {
		qu.push(m);
		qv.push(j);
		visited[m][j] = true;
	}
	while (!qu.empty()) {
		int u = qu.front(); qu.pop();
		int v = qv.front(); qv.pop();

		if (u == targetu && v == targetv) return true;

		go(u, v-1);
		go(u, v+1);
		FOR(uu,1,m) if (abs(uu - u) <= h) go(uu, v);
	}
	return false;
}

class ArcadeManao {
public:
    int shortestLadder( vector <string> level, int coinRow, int coinColumn ) {
		targetu = coinRow, targetv = coinColumn;

		memset(a, '.', sizeof a);
		m = SZ(level), n = SZ(level[0]);
		REP(i,m) REP(j,n)
			a[i+1][j+1] = level[i][j];
		int l = 0, r = m, res = m;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				res = mid;
				r = mid - 1;
			}
			else l = mid + 1;
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
			string level[]            = {"XXXX....",
 "...X.XXX",
 "XXX..X..",
 "......X.",
 "XXXXXXXX"};
			int coinRow               = 2;
			int coinColumn            = 4;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = ArcadeManao().shortestLadder(vector <string>(level, level + (sizeof level / sizeof level[0])), coinRow, coinColumn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string level[]            = {"XXXX",
 "...X",
 "XXXX"};
			int coinRow               = 1;
			int coinColumn            = 1;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = ArcadeManao().shortestLadder(vector <string>(level, level + (sizeof level / sizeof level[0])), coinRow, coinColumn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string level[]            = {"..X..",
 ".X.X.",
 "X...X",
 ".X.X.",
 "..X..",
 "XXXXX"};
			int coinRow               = 1;
			int coinColumn            = 3;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = ArcadeManao().shortestLadder(vector <string>(level, level + (sizeof level / sizeof level[0])), coinRow, coinColumn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string level[]            = {"X"};
			int coinRow               = 1;
			int coinColumn            = 1;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = ArcadeManao().shortestLadder(vector <string>(level, level + (sizeof level / sizeof level[0])), coinRow, coinColumn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string level[]            = {"XXXXXXXXXX",
 "...X......",
 "XXX.......",
 "X.....XXXX",
 "..XXXXX..X",
 ".........X",
 ".........X",
 "XXXXXXXXXX"};
			int coinRow               = 1;
			int coinColumn            = 1;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = ArcadeManao().shortestLadder(vector <string>(level, level + (sizeof level / sizeof level[0])), coinRow, coinColumn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string level[]            = ;
			int coinRow               = ;
			int coinColumn            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ArcadeManao().shortestLadder(vector <string>(level, level + (sizeof level / sizeof level[0])), coinRow, coinColumn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string level[]            = ;
			int coinRow               = ;
			int coinColumn            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ArcadeManao().shortestLadder(vector <string>(level, level + (sizeof level / sizeof level[0])), coinRow, coinColumn);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string level[]            = ;
			int coinRow               = ;
			int coinColumn            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ArcadeManao().shortestLadder(vector <string>(level, level + (sizeof level / sizeof level[0])), coinRow, coinColumn);
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
