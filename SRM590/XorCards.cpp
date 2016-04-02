// Div1 - 500
// Algo:
// - Let S = sum xor of chosen elements
// - Let i = first different bit of S and limit
// --> all bits from 50 --> i+1 must be equal
//     bit i of S must be 0, bit i of limit must be 1
//     other bits can be anything
// --> build (50 - i + 1) equations of form sum(xi) = 0 / 1,
//     where xi = is i-th element chosen?
// --> result is sum of number of roots of each set of equations.

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

int c[55][55];
ll count(int nRow, int nCol) {
	int row = 0;
	REP(j,nCol) {
		int u = -1;
		FOR(i,row,nRow-1)
			if (c[i][j] == 1) {
				u = i;
				break;
			}
		if (u == -1) continue;

		// swap row u and 'row'
		REP(k,nCol+1) swap(c[u][k], c[row][k]);
		
		// clear other rows
		FOR(i,row+1,nRow-1) if (c[i][j] == 1) {
			REP(k,nCol+1)
				c[i][k] ^= c[row][k];
		}

		++row;
	}
	FOR(i,row,nRow-1) {
		if (c[i][nCol] == 1) return 0;
	}
	return 1LL << (nCol - row);
}

int getBit(ll x, ll k) {
	return (x >> k) & 1;
}

class XorCards {
public:
    long long numberOfWays( vector<long long> number, long long limit ) {
		ll res = 0;
		int n = SZ(number);

		const int NBIT = 50;

		FORD(equal,NBIT,0) {
			if (equal && getBit(limit, equal-1) == 0) continue;

			int row = 0;
			memset(c, 0, sizeof c);
			FORD(i,NBIT,max(0, equal-1)) {
				int need = getBit(limit, i);
				if (i < equal) --need;

				c[row][n] = need;

				REP(j,n) if (getBit(number[j], i) == 1)
					c[row][j] = 1;
				++row;
			}

//			DEBUG(equal);
//			REP(i,row) PR0(c[i], n+1);

			res += count(row, n);

//			cout << "---" << endl;
//			REP(i,row) PR0(c[i], n+1);
//			DEBUG(res);
//			cout << "---" << endl;
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
	
	int verify_case(int casenum, const long long &expected, const long long &received, std::clock_t elapsed) { 
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
			long long number[]        = {1, 2};
			long long limit           = 2;
			long long expected__      = 3;

			std::clock_t start__      = std::clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long number[]        = {5, 5};
			long long limit           = 3;
			long long expected__      = 2;

			std::clock_t start__      = std::clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long number[]        = {1, 2, 3, 4, 5, 6, 7};
			long long limit           = 5;
			long long expected__      = 96;

			std::clock_t start__      = std::clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long number[]        = {123, 456, 789, 147, 258, 369, 159, 357};
			long long limit           = 500;
			long long expected__      = 125;

			std::clock_t start__      = std::clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			long long number[]        = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			long long limit           = 1000000000000000LL;
			long long expected__      = 4294967296LL;

			std::clock_t start__      = std::clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			long long number[]        = {1000000000000000LL, 999999999999999LL};
			long long limit           = 65535;
			long long expected__      = 2;

			std::clock_t start__      = std::clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			long long number[]        = ;
			long long limit           = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			long long number[]        = ;
			long long limit           = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			long long number[]        = ;
			long long limit           = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = XorCards().numberOfWays(vector<long long>(number, number + (sizeof number / sizeof number[0])), limit);
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
