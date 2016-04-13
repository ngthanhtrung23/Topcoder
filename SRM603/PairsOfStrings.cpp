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

const int MN = 100111;
const ll MOD = 1e9 + 7;

ll x[MN], nx, f[MN];
ll power(ll x, ll k) {
	ll res = 1;
	while (k > 0) {
		if (k & 1) res = res * x % MOD;
		x = x * x % MOD;
		k >>= 1;
	}
	return res;
}

class PairsOfStrings {
public:
    int getNumber( int n, int k ) {
		nx = 0;
		for(int i = 1; i * i <= n; ++i) {
			if (n % i == 0) {
				x[++nx] = i;
				if (i * i != n) x[++nx] = n / i;
			}
		}
		sort(x+1, x+nx+1);

		FOR(i,1,nx) {
			f[i] = power(k, x[i]);
			FOR(j,1,i-1)
				if (x[i] % x[j] == 0) {
					f[i] = (f[i] - f[j] + MOD) % MOD;
				}
		}

		ll res = 0;
		FOR(i,1,nx) res = (res + f[i] * x[i]) % MOD;
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
			int n                     = 2;
			int k                     = 2;
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = PairsOfStrings().getNumber(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 3;
			int k                     = 2;
			int expected__            = 20;

			std::clock_t start__      = std::clock();
			int received__            = PairsOfStrings().getNumber(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 3;
			int k                     = 4;
			int expected__            = 184;

			std::clock_t start__      = std::clock();
			int received__            = PairsOfStrings().getNumber(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 6;
			int k                     = 2;
			int expected__            = 348;

			std::clock_t start__      = std::clock();
			int received__            = PairsOfStrings().getNumber(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int n                     = 100;
			int k                     = 26;
			int expected__            = 46519912;

			std::clock_t start__      = std::clock();
			int received__            = PairsOfStrings().getNumber(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int n                     = ;
			int k                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PairsOfStrings().getNumber(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int n                     = ;
			int k                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PairsOfStrings().getNumber(n, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int n                     = ;
			int k                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PairsOfStrings().getNumber(n, k);
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
