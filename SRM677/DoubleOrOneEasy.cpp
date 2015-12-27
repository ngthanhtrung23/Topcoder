// Div1 - 300
// Algo:
// - Let's say the transformation looks like below:
//	 a' = ((a + k1) * 2 + k2) * 2 + k3 ...
//      = a*2^t + k1*2^t + k2*2^(t-1) + ...
// - Thus:
//     - If we fix t, we can find the optimal sequence k1, k2, ...
//     - a' - a*2^t == b' - b*2^t
// - The 2 above observation are enough for full solution

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

ll INF = 1e15;

ll get(ll val, ll t) {
	ll res = val / (1LL<<t);
	val %= (1LL<<t);
	FORD(i,t-1,0) {
		if (val >= (1<<i)) {
			++res;
			val -= 1<<i;
		}
	}
	return res;
}

int solve(ll a, ll b, ll newA, ll newB) {
	ll res = INF;
	for(ll t=0, aa=a; aa <= newA; ++t, aa *= 2) {
		ll bb = (b << t);
		if (bb > newB || aa > newA) continue;

		if (newB - bb == newA - aa) {
			ll cur = t + get(newA - aa, t);
			res = min(res, cur);
		}
	}
	if (res == INF) res = -1;
	return (int) res;
}

class DoubleOrOneEasy {
public:
    int minimalSteps( int a, int b, int newA, int newB ) {
		return solve(a, b, newA, newB);
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
			int a                     = 100;
			int b                     = 1000;
			int newA                  = 101;
			int newB                  = 1001;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = DoubleOrOneEasy().minimalSteps(a, b, newA, newB);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int a                     = 100;
			int b                     = 1000;
			int newA                  = 202;
			int newB                  = 2002;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = DoubleOrOneEasy().minimalSteps(a, b, newA, newB);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int a                     = 2;
			int b                     = 2;
			int newA                  = 1;
			int newB                  = 1;
			int expected__            = -1;

			std::clock_t start__      = std::clock();
			int received__            = DoubleOrOneEasy().minimalSteps(a, b, newA, newB);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int a                     = 1;
			int b                     = 111111111;
			int newA                  = 8;
			int newB                  = 888888888;
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = DoubleOrOneEasy().minimalSteps(a, b, newA, newB);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int a                     = 1;
			int b                     = 111111111;
			int newA                  = 9;
			int newB                  = 999999999;
			int expected__            = -1;

			std::clock_t start__      = std::clock();
			int received__            = DoubleOrOneEasy().minimalSteps(a, b, newA, newB);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

        case 5: {
			int a                     = 7;
			int b                     = 77;
			int newA                  = 7;
			int newB                  = 77;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = DoubleOrOneEasy().minimalSteps(a, b, newA, newB);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
        case 6: {
			int a                     = 7;
			int b                     = 77;
			int newA                  = 8;
			int newB                  = 77;
			int expected__            = -1;

			std::clock_t start__      = std::clock();
			int received__            = DoubleOrOneEasy().minimalSteps(a, b, newA, newB);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 7: {
			int a                     = ;
			int b                     = ;
			int newA                  = ;
			int newB                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = DoubleOrOneEasy().minimalSteps(a, b, newA, newB);
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
