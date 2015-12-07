// Div1 - 500
// Algo:
// - Transform (x, y) --> (x+y, x-y)
//     - New distance: max(|x1-x2|, |y1-y2|)
//     - Only need to keep track of bounding box (minx, maxx, miny, maxy)
// - DP: f(x1, x2, y1, y2) = min cost to add all points outside of bounding box
//     - To calculate, add 1 point and extend the bounding box
//     - Worst case: 15^4 * 64^2, but very fast in reality
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

bool outside(int x, int minx, int maxx) {
	return x < minx || maxx < x;
}
bool outside(int x, int y, int minx, int maxx, int miny, int maxy) {
	return outside(x, minx, maxx) || outside(y, miny, maxy);
}
int max(int a, int b, int c, int d) {
	return max(max(a, b), max(c, d));
}

int f[22][22][22][22];
char a[22][22];

#define STATE minSum][maxSum][minDiff][maxDiff
int get(int minSum, int maxSum, int minDiff, int maxDiff) {
	if (f[STATE] >= 0) return f[STATE];

	int has = 0;
	int res = 1e9;

	REP(i,8) REP(j,8) if (a[i][j] == '#' && outside(i+j, i-j+7, minSum, maxSum, minDiff, maxDiff)) {
		int added = 0;
		has = 1;

		int minSum2 = min(minSum, i+j);
		int maxSum2 = max(maxSum, i+j);
		int minDiff2 = min(minDiff, i-j+7);
		int maxDiff2 = max(maxDiff, i-j+7);

		REP(u,8) REP(v,8)
			if (a[u][v] == '#'
					&& outside(u+v, u-v+7, minSum, maxSum, minDiff, maxDiff)
					&& !outside(u+v, u-v+7, minSum2, maxSum2, minDiff2, maxDiff2)) {
				added += max(
						abs(u+v - minSum2),
						abs(u+v - maxSum2),
						abs(u-v+7 - minDiff2),
						abs(u-v+7 - maxDiff2)
						);
			}

		res = min(res, get(minSum2, maxSum2, minDiff2, maxDiff2) + added);
	}

	if (!has) return f[STATE] = 0;
	return f[STATE] = res;
}

class EllysChessboard {
public:
    int minCost( vector <string> board ) {
		memset(f, -1, sizeof f);
		REP(i,8) REP(j,8) a[i][j] = board[i][j];

		int res = 1e9;
		REP(i,8) REP(j,8) {
				res = min(res, get(i+j, i+j, i-j+7, i-j+7));
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
			string board[]            = {"........",
 "........",
 "...#....",
 ".#......",
 ".......#",
 "........",
 "........",
 "........"};
			int expected__            = 10;

			std::clock_t start__      = std::clock();
			int received__            = EllysChessboard().minCost(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {"........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........"};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = EllysChessboard().minCost(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {".#......",
 "........",
 "..#..#.#",
 "...#..#.",
 "........",
 "...#...#",
 "...#...#",
 "........"};
			int expected__            = 58;

			std::clock_t start__      = std::clock();
			int received__            = EllysChessboard().minCost(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"##..####",
 "#####..#",
 "..#.#...",
 "#..##.##",
 ".#.###.#",
 "####.###",
 "#.#...#.",
 "##....#."};
			int expected__            = 275;

			std::clock_t start__      = std::clock();
			int received__            = EllysChessboard().minCost(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string board[]            = {"########",
 "########",
 "########",
 "########",
 "########",
 "########",
 "########",
 "########"};
			int expected__            = 476;

			std::clock_t start__      = std::clock();
			int received__            = EllysChessboard().minCost(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string board[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = EllysChessboard().minCost(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string board[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = EllysChessboard().minCost(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string board[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = EllysChessboard().minCost(vector <string>(board, board + (sizeof board / sizeof board[0])));
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
