// Div1 - 500
// Algo: DP
// - 1st, observe that since K <= 7, the cycle must have form:
//	 u--v + (u, x) + x--y + (y, v) where u--v is some path in tree1 and x--y is some path in tree2
// - For each length l1, count how many path in tree1 with this length. Similarly for tree2.
// - Number of cycle where u--v has length l1 and x--y has length l2 is (N-2)! * 2 * count(tree1, l1) * count(tree2, l2)

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

int cnt[2][311];
int c[311][311];
int n;

class TreeUnion {
public:
    double expectedCycles( vector <string> tree1, vector <string> tree2, int K ) {
		if (K < 4) return 0.0;
		memset(cnt, 0, sizeof cnt);
		REP(turn,2) {
			string all = "";
			if (turn == 0) {
				for(auto s : tree1) all += s;
			}
			else {
				for(auto s : tree2) all += s;
			}
			stringstream ss(all);
			vector<int> x;
			int t;
			while (ss >> t) x.push_back(t);

//			PR0(x, SZ(x));

			n = SZ(x) + 1;
			REP(i,n) REP(j,n) c[i][j] = (i == j) ? 0 : 1e9;

			REP(i,SZ(x)) {
				int u = x[i], v = i+1;
				c[u][v] = c[v][u] = 1;
			}
			REP(k,n) REP(i,n) REP(j,n)
				c[i][j] = min(c[i][j], c[i][k] + c[k][j]);

			REP(i,n) FOR(j,i+1,n-1)
				cnt[turn][c[i][j]]++;

//			PR(cnt[turn], 2);
		}

		double res = 0.0;
		FOR(l1,1,K-3) {
			int l2 = K - 2 - l1;
			res += cnt[0][l1] * (double) cnt[1][l2] * 2.0;
		}
		return res / (double) n / (double) (n-1);
    }
};

// BEGIN CUT HERE
#include <algorithm>
#include <cmath>
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
	
	static const double MAX_DOUBLE_ERROR = 1e-9;
	static bool topcoder_fequ(double expected, double result) {
		if (std::isnan(expected)) {
			return std::isnan(result);
		} else if (std::isinf(expected)) {
			if (expected > 0) {
				return result > 0 && std::isinf(result);
			} else {
				return result < 0 && std::isinf(result);
			}
		} else if (std::isnan(result) || std::isinf(result)) {
			return false;
		} else if (std::fabs(result - expected) < MAX_DOUBLE_ERROR) {
			return true;
		} else {
			double mmin = std::min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR));
			double mmax = std::max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR));
			return result > mmin && result < mmax;
		}
	}
	double moj_relative_error(double expected, double result) {
		if (std::isnan(expected) || std::isinf(expected) || std::isnan(result) || std::isinf(result) || expected == 0) {
			return 0;
		}
		return std::fabs(result-expected) / std::fabs(expected);
	}
	
	int verify_case(int casenum, const double &expected, const double &received, std::clock_t elapsed) { 
		std::cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (topcoder_fequ(expected, received)) {
			verdict = "PASSED";
			double rerr = moj_relative_error(expected, received); 
			if (rerr > 0) {
				std::sprintf(buf, "relative error %.3e", rerr);
				info.push_back(buf);
			}
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
			string tree1[]            = {"0"};
			string tree2[]            = {"0"};
			int K                     = 4;
			double expected__         = 1.0;

			std::clock_t start__      = std::clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string tree1[]            = {"0 1"};
			string tree2[]            = {"0 1"};
			int K                     = 4;
			double expected__         = 1.3333333333333333;

			std::clock_t start__      = std::clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string tree1[]            = {"0 1"};
			string tree2[]            = {"0 1"};
			int K                     = 6;
			double expected__         = 0.3333333333333333;

			std::clock_t start__      = std::clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string tree1[]            = {"0 ", "1 1 1"};
			string tree2[]            = {"0 1 0 ", "1"};
			int K                     = 5;
			double expected__         = 4.0;

			std::clock_t start__      = std::clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string tree1[]            = {"0 1 2 0 1 2 0 1 2 5 6 1", "0 11", " 4"};
			string tree2[]            = {"0 1 1 0 2 3 4 3 4 6 6", " 10 12 12"};
			int K                     = 7;
			double expected__         = 13.314285714285713;

			std::clock_t start__      = std::clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string tree1[]            = ;
			string tree2[]            = ;
			int K                     = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string tree1[]            = ;
			string tree2[]            = ;
			int K                     = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string tree1[]            = ;
			string tree2[]            = ;
			int K                     = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = TreeUnion().expectedCycles(vector <string>(tree1, tree1 + (sizeof tree1 / sizeof tree1[0])), vector <string>(tree2, tree2 + (sizeof tree2 / sizeof tree2[0])), K);
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
