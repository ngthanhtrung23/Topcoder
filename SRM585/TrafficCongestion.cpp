// Div1 - 250
// Algo:
// - Let f(h) = minimum number of paths to cover tree with depth h
// - Observe that:
//     - For 2 consecutive leaves, if we connect them together (instead of 1 path
//       going up & the other path has only length = 0), it is at least as good
// - Thus, f(N) = f(N-2) + 2^(N-1)

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

ll power(ll x, ll k) {
	ll res = 1;
	while (k > 0) {
		if (k & 1) res = res * x % MOD;
		x = x * x % MOD;
		k >>= 1;
	}
	return res;
}

ll f[1000111];

class TrafficCongestion {
public:
    int theMinCars( int treeHeight ) {
		f[0] = f[1] = 1;
		FOR(i,2,1000 * 1000) {
			f[i] = (f[i-2] + power(2, i-1)) % MOD;
		}
		return f[treeHeight];
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
			int treeHeight            = 1;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = TrafficCongestion().theMinCars(treeHeight);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int treeHeight            = 2;
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = TrafficCongestion().theMinCars(treeHeight);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int treeHeight            = 3;
			int expected__            = 5;

			std::clock_t start__      = std::clock();
			int received__            = TrafficCongestion().theMinCars(treeHeight);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int treeHeight            = 585858;
			int expected__            = 548973404;

			std::clock_t start__      = std::clock();
			int received__            = TrafficCongestion().theMinCars(treeHeight);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int treeHeight            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TrafficCongestion().theMinCars(treeHeight);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int treeHeight            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TrafficCongestion().theMinCars(treeHeight);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int treeHeight            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TrafficCongestion().theMinCars(treeHeight);
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
