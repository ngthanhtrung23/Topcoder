// Div 1 - 500
// Algo:
// - First, we need to view the problem as:
//     - Find some segments of length <= L
//     - Each set of consecutive segments must have one with length = L
//     - Other segments can be below it.
// - DP: f(i, j, s):
//	   - i: from position 1 --> i
//	   - j: already created j segments
//	   - s: 0 / 1 / 2:
//	       - 0: we're in middle of empty space
//	       - 1: we're in middle of some consecutive segments, but don't have segment of length L yet
//	       - 2: we're in middle of some consecutive segments and already have segment of length L
//	   - Transition: Add new segment / add empty space

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

const int MN = 311;
const int MOD = 1e9 + 9;
int n, x[MN], sum[MN];
int A, B, L;
int f[MN][MN][3];

bool can(int u, int v) {
	int cur = sum[v] - sum[u-1];
	return A <= cur && cur <= B;
}

void add(int& x, int val) {
	x += val;
	if (x >= MOD) x -= MOD;
}

class TheExperiment {
public:
    int countPlacements( vector <string> intensity, int M, int L, int A, int B ) {
		::A = A;
		::B = B;
		::L = L;

		string all = "";
		for(auto s : intensity) all += s;
		n = SZ(all);
		FOR(i,1,n) x[i] = all[i-1] - '0';
		FOR(i,1,n) sum[i] = sum[i-1] + x[i];

		PR(x, n);
		memset(f, 0, sizeof f);
		f[0][0][0] = 1;
		FOR(i,0,n-1) FOR(j,0,M) REP(t,3) {
			int val = f[i][j][t];
			if (!val) continue;

			// do not use i+1
			if (t == 0 || t == 2) 
				add(f[i+1][j][0], val);

			// use i+1, with length x
			FOR(x,1,L) if (i+x <= n) {
				int tt = t;
				if (tt == 0) tt = 1;
				if (tt == 1 && x == L) tt = 2;

				if (can(i+1, i+x)) {
					add(f[i+x][j+1][tt], val);
				}
			}
		}
		return (f[n][M][0] + f[n][M][2]) % MOD;
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
			string intensity[]        = {"341156"};
			int M                     = 3;
			int L                     = 3;
			int A                     = 6;
			int B                     = 10;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string intensity[]        = {"999112999"};
			int M                     = 2;
			int L                     = 4;
			int A                     = 21;
			int B                     = 30;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string intensity[]        = {"111"};
			int M                     = 2;
			int L                     = 2;
			int A                     = 2;
			int B                     = 3;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string intensity[]        = {"59059", "110", "1132230231"};
			int M                     = 1;
			int L                     = 5;
			int A                     = 10;
			int B                     = 20;
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string intensity[]        = {"111111111111111111111111", "111111111111111111111111111", "11111111111111111111111"};
			int M                     = 12;
			int L                     = 8;
			int A                     = 4;
			int B                     = 2700;
			int expected__            = 418629948;

			std::clock_t start__      = std::clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string intensity[]        = ;
			int M                     = ;
			int L                     = ;
			int A                     = ;
			int B                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string intensity[]        = ;
			int M                     = ;
			int L                     = ;
			int A                     = ;
			int B                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string intensity[]        = ;
			int M                     = ;
			int L                     = ;
			int A                     = ;
			int B                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TheExperiment().countPlacements(vector <string>(intensity, intensity + (sizeof intensity / sizeof intensity[0])), M, L, A, B);
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
