// Div 1 - 850
// Algo:
// - In 1D: easy to solve:
//     - To go from 0 --> x in m moves --> C(m, (m-x) / 2)
// - 2D --> 1D:
//     - use transformation (x, y) --> (x+y, x-y)
//     - Now each moves change both dimension --> can calculate independently

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

const ll MOD = 1e9 + 7;
const int MN = 100111;
ll gt[MN], inv_gt[MN];

ll power(ll x, ll k) {
	if (k == 0) return 1;
	if (k == 1) return x % MOD;
	ll mid = power(x, k >> 1);
	mid = mid * mid % MOD;

	if (k & 1) return mid * x % MOD;
	else return mid;
}

ll inverse(ll x) {
	return power(x, MOD - 2);
}

ll C(int n, int k) {
	assert(k >= 0 && k <= n);
	return gt[n] * inv_gt[k] % MOD * inv_gt[n - k] % MOD;
}

void init() {
	gt[0] = 1;
	FOR(i,1,MN - 1) gt[i] = gt[i-1] * i % MOD;

	REP(i,MN) inv_gt[i] = inverse(gt[i]);
}

ll solve(int n, vector<int> z, int m) {
	ll res = 0;
	int minz = *min_element(z.begin(), z.end());

	FOR(t,minz-m,minz+m) {
		ll cur = 1;
		REP(i,n) {
			int need = abs(z[i] - t);
			if (need > m || (m - need) % 2) {
				cur = 0;
				break;
			}
			int rr = (m - need) / 2;
			cur = cur * C(m, rr) % MOD;
		}
		res = (res + cur) % MOD;
	}
	return res;
}

class WolfPack {
public:
    int calc( vector <int> x, vector <int> y, int m ) {
		init();
		int n = SZ(x);
		vector<int> z;
		z.resize(n);

		REP(i,n) z[i] = x[i] + y[i];
		ll res = solve(n, z, m);

		REP(i,n) z[i] = x[i] - y[i];
		res = res * solve(n, z, m) % MOD;

		return (int) res;
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
			int x[]                   = {3,5};
			int y[]                   = {0,0};
			int m                     = 1;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = WolfPack().calc(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), m);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int x[]                   = {0,0};
			int y[]                   = {0,1};
			int m                     = 1;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = WolfPack().calc(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), m);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int x[]                   = {0,2,4};
			int y[]                   = {0,0,0};
			int m                     = 2;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = WolfPack().calc(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), m);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int x[]                   = {7,8};
			int y[]                   = {8,7};
			int m                     = 1;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = WolfPack().calc(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), m);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int x[]                   = {-2,-2,-2,0,0,0,2,2,2};
			int y[]                   = {-2,0,2,-2,0,2,-2,0,2};
			int m                     = 1000;
			int expected__            = 387540818;

			std::clock_t start__      = std::clock();
			int received__            = WolfPack().calc(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), m);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int x[]                   = ;
			int y[]                   = ;
			int m                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = WolfPack().calc(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), m);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int x[]                   = ;
			int y[]                   = ;
			int m                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = WolfPack().calc(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), m);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int x[]                   = ;
			int y[]                   = ;
			int m                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = WolfPack().calc(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), m);
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
