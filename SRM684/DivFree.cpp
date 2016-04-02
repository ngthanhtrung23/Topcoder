// Div1 - 600
// Algo: DP
// - Let g(n) = number of good sequence of length n
// --> g(n)
// = g(n-1) * k
// - g(n-2) * (number of (x1, x2) s.t. x1 mod x2 == 0 and x1 > x2)
// + g(n-3) * (number of (x1, x2, x3) s.t. x1 mod x2 == 0 and x2 mod x3 == 0 and x1 > x2 > x3)
// - ...
// Number of divisible sequence can be calculated with brute force, since length <= 16

#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ','; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 50111;
const ll MOD = 1e9 + 7;

ll f[2][MN], g[MN];
ll cnt[20];

void attempt(int len, int cur, int k) {
	cnt[len]++;
	for(int x = cur + cur; x <= k; x += cur) {
		attempt(len+1, x, k);
	}
}

class DivFree {
public:
    int dfcount2( int n, int k ) {
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);

		FOR(i,1,k) f[1][i] = 1;
		g[0] = 1;
		g[1] = k;

		FOR(i,2,n) {
			int t = i % 2;
			memset(f[t], 0, sizeof f[t]);

			g[i] = 0;
			FOR(last,1,k) {
				f[t][last] = g[i-1];

				for(int x = last+last; x <= k; x += last) {
					f[t][last] -= f[1-t][x];
					if (f[t][last] < 0) f[t][last] += MOD;
				}

				g[i] = g[i] + f[t][last];
				if (g[i] >= MOD) g[i] -= MOD;
			}
		}
		return g[n];
    }

	int dfcount(int n, int k) {
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		memset(cnt, 0, sizeof cnt);

		FOR(start,1,k) attempt(1, start, k);
		PR(cnt, 17);

		g[0] = 1;
		FOR(i,1,n) {
			g[i] = 0;
			FOR(len,1,16) {
				int j = i - len; if (j < 0) continue;

				if (len % 2 == 1) g[i] = (g[i] + g[j] * cnt[len]) % MOD;
				else g[i] = ((g[i] - g[j] * cnt[len]) % MOD + MOD) % MOD;
			}
		}
		ll tmp = g[n];
//		assert(tmp == dfcount2(n, k));
		return g[n];
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
			int n                     = 2;
			int k                     = 2;
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = DivFree().dfcount(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 3;
			int k                     = 2;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = DivFree().dfcount(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 3;
			int k                     = 3;
			int expected__            = 15;

			std::clock_t start__      = std::clock();
			int received__            = DivFree().dfcount(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 1;
			int k                     = 107;
			int expected__            = 107;

			std::clock_t start__      = std::clock();
			int received__            = DivFree().dfcount(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int n                     = 5;
			int k                     = 6;
			int expected__            = 2292;

			std::clock_t start__      = std::clock();
			int received__            = DivFree().dfcount(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int n                     = 42;
			int k                     = 23;
			int expected__            = 301026516;

			std::clock_t start__      = std::clock();
			int received__            = DivFree().dfcount(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int n                     = 10000;
			int k                     = 50000;
			int expected__            = 541790233;

			std::clock_t start__      = std::clock();
			int received__            = DivFree().dfcount(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int n                     = ;
			int k                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = DivFree().dfcount(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int n                     = ;
			int k                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = DivFree().dfcount(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int n                     = ;
			int k                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = DivFree().dfcount(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


#include <cstdlib>
int main(int argc, char *argv[]) {
	DivFree sol;
	DEBUG(sol.dfcount(50000, 50000));
	return 0;
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(std::atoi(argv[i]));
	}
}
// END CUT HERE
