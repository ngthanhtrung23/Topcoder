// Div 1 - 900
// Algo: math
// - Combine 2 rows --> 1 single unit --> we have 3 new colors: RG, RB, GB.
//   Call these 3 new colors A, B, C
// - We can easily calculate number of unit of each color
// --> problem becomes: given 3 colors with amount A, B, C. Calculate how many
//     ways to arrange in a row, such that no 2 consecutive positions have same color

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

const int MN = 3000111;
const ll MOD = 1e9 + 7;

ll power(ll x, ll k) {
	if (k == 0) return 1;
	if (k == 1) return x % MOD;
	ll mid = power(x, k >> 1);
	mid = mid * mid % MOD;

	if (k & 1) return mid * x % MOD;
	return mid;
}

ll gt[MN], inv_gt[MN];

void init() {
	gt[0] = 1; FOR(i,1,MN-1) gt[i] = gt[i-1] * i % MOD;
	REP(i,MN) inv_gt[i] = power(gt[i], MOD - 2);
}

ll Cnk(int n, int k) {
	if (n < 0 || k < 0 || k > n) return 0;
	return gt[n] * inv_gt[k] % MOD * inv_gt[n-k] % MOD;
}

ll solve0(int a, int b, int c) {
	if (a == 0 && b == 0 && c == 0) return 1;
	if (a == 0 && b == 0) return c == 1;
	if (b == 0 && c == 0) return a == 1;
	if (c == 0 && a == 0) return b == 1;

	if (b == 0) swap(a, b);
	if (c == 0) swap(a, c);

	if (b == c) return 2;
	if (abs(b - c) == 1) return 1;
	return 0;
}

ll solve(int A, int C, int M) {
	if (A == 0 || C == 0 || M == 0) {
		return solve0(A, C, M);
	}
	ll res = 0;
	FOR(x,0,A) {
		FOR(y,x-1,x+1) {
			if (y < 0 || y > C) continue;
			ll cur = 0;

			if (x == y) cur = 2; else cur = 1;

			cur = cur * Cnk(A-1, x-1) % MOD;
			cur = cur * Cnk(C-1, y-1) % MOD;

			cur = cur * Cnk(A+C+1 - (A-x) - (C-y), M - (A-x) - (C-y)) % MOD;

			cout << x << ' ' << y << ' ' << cur << endl;
			res = (res + cur) % MOD;
		}
	}
	return res;
}

class LittleElephantAndBoard {
public:
    int getNumber( int M, int R, int G, int B ) {
		init();
		int c = M - R;
		int b = M - G;
		int a = M - B;
		return 2 * solve(a, b, c) % MOD;
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
			int M                     = 2;
			int R                     = 2;
			int G                     = 1;
			int B                     = 1;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = LittleElephantAndBoard().getNumber(M, R, G, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int M                     = 2;
			int R                     = 2;
			int G                     = 2;
			int B                     = 0;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = LittleElephantAndBoard().getNumber(M, R, G, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int M                     = 10;
			int R                     = 7;
			int G                     = 7;
			int B                     = 6;
			int expected__            = 496;

			std::clock_t start__      = std::clock();
			int received__            = LittleElephantAndBoard().getNumber(M, R, G, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int M                     = 474;
			int R                     = 250;
			int G                     = 300;
			int B                     = 398;
			int expected__            = 969878317;

			std::clock_t start__      = std::clock();
			int received__            = LittleElephantAndBoard().getNumber(M, R, G, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 4: {
			int M                     = 1000000;
			int R                     = 500000;
			int G                     = 1000000;
			int B                     = 500000;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = LittleElephantAndBoard().getNumber(M, R, G, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 5: {
			int M                     = ;
			int R                     = ;
			int G                     = ;
			int B                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = LittleElephantAndBoard().getNumber(M, R, G, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int M                     = ;
			int R                     = ;
			int G                     = ;
			int B                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = LittleElephantAndBoard().getNumber(M, R, G, B);
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
