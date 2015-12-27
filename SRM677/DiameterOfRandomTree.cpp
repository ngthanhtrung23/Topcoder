// Div1 - 500
// Algo:
// - Fix diameter D. Calculate the probability that tree have diameter <= D
// - Let F(u, d) = probability that in T(u), the maximum path starting from u is d,
//                 and the tree has diameter at most D (which is constant)
// - To calculate F, at each vertex u, we calculate all F(v, d'), and then calculate
//   F using extra function g(x) = F(u, x) after we added some vertices v

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

double f[55][111], g[111], h[111], res[111];
vector<int> ke[55];
int n, D;
int c[55][55];

void dfs(int u, int fu) {
	for(int v : ke[u]) {
		if (v == fu) continue;
		dfs(v, u);
	}
	
	memset(g, 0, sizeof g);
	g[0] = 1.0;
	for(int v : ke[u]) {
		if (v == fu) continue;

		memset(h, 0, sizeof h);
		FOR(cur,0,D) {
			FOR(x,0,D-cur) {
				FOR(add,1,2) {
					if (cur + x + add > D) continue;

					int next = max(cur, x + add);
					h[next] += 0.5 * g[cur] * f[v][x];
				}
			}
		}

		FOR(i,0,D) g[i] = h[i];
	}

	FOR(i,0,D) f[u][i] = g[i];
}

class DiameterOfRandomTree {
public:
    double getExpectation( vector <int> a, vector <int> b ) {
		memset(f, 0, sizeof f);
		n = SZ(a) + 1;
		REP(i,n) ke[i].clear();

		REP(i,n) REP(j,n) c[i][j] = (i == j) ? 0 : 1e9;
		REP(i,n-1) {
			int u = a[i], v = b[i];
			ke[u].push_back(v);
			ke[v].push_back(u);
			c[u][v] = c[v][u] = 1;
		}

		REP(k,n) REP(i,n) REP(j,n)
			c[i][j] = min(c[i][j], c[i][k] + c[k][j]);

		int l = 0;
		REP(i,n) REP(j,n) l = max(l, c[i][j]);

		memset(res, 0, sizeof res);
		FOR(diam,l,2*l) {
			res[diam] = 0.0;
			D = diam;

			dfs(0, -1);
			FOR(maxdepth,0,100)
				res[diam] += f[0][maxdepth];
		}
		FORD(i,2*l,l) res[i] -= res[i-1];
		double sum = 0.0;
		FOR(i,l,2*l) sum += i * res[i];
		return sum;
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
			int a[]                   = {0,1,2,3};
			int b[]                   = {1,2,3,4};
			double expected__         = 6.0;

			std::clock_t start__      = std::clock();
			double received__         = DiameterOfRandomTree().getExpectation(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int a[]                   = {0,0,0};
			int b[]                   = {1,2,3};
			double expected__         = 3.375;

			std::clock_t start__      = std::clock();
			double received__         = DiameterOfRandomTree().getExpectation(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int a[]                   = {0,0,0,1,4};
			int b[]                   = {1,2,3,4,5};
			double expected__         = 6.25;

			std::clock_t start__      = std::clock();
			double received__         = DiameterOfRandomTree().getExpectation(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int a[]                   = {0,0,0,0,0,0,0,0};
			int b[]                   = {1,2,3,4,5,6,7,8};
			double expected__         = 3.9609375;

			std::clock_t start__      = std::clock();
			double received__         = DiameterOfRandomTree().getExpectation(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int a[]                   = {0,0,0,1,2,3,5,6,8};
			int b[]                   = {1,2,3,4,5,6,7,8,9};
			double expected__         = 10.53125;

			std::clock_t start__      = std::clock();
			double received__         = DiameterOfRandomTree().getExpectation(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int a[]                   = ;
			int b[]                   = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = DiameterOfRandomTree().getExpectation(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int a[]                   = ;
			int b[]                   = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = DiameterOfRandomTree().getExpectation(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int a[]                   = ;
			int b[]                   = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = DiameterOfRandomTree().getExpectation(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
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
