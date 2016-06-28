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

ll f[55][2222];
ll x[55];

void update(ll&x, ll val) {
	x = max(x, val);
}

class TypoCoderDiv1 {
public:
    int getmax( vector <int> D, int X ) {
		int n = SZ(D);
		FOR(i,1,n) x[i] = D[i-1];
		++n;
		x[n] = 1000111000;

		FOR(i,0,n) FOR(j,0,2220) f[i][j] = -1000111;
		f[0][X] = 0;

		FOR(i,0,n-1) FOR(j,0,2199) {
			int val = f[i][j];
			if (val < 0) continue;

			// dec rating
			update(f[i+1][j - min((ll) j, x[i+1])], val);

			// inc rating, but still < 2200
			if (j + x[i+1] < 2200) {
				update(f[i+1][j + x[i+1]], val);
			}
			else {
				if (i + 2 <= n) {
					ll next = j + x[i+1];
					next -= min(next, x[i+2]);

					if (next < 2200) {
						ll newVal = val + 1;
						if (i + 2 < n) ++newVal;

						update(f[i+2][next], newVal);
					}
				}
			}
		}

		ll res = 0;
		FOR(r,0,2199) update(res, f[n][r]);
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
			int D[]                   = {100,200,100,1,1};
			int X                     = 2000;
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = TypoCoderDiv1().getmax(vector <int>(D, D + (sizeof D / sizeof D[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int D[]                   = {0,0,0,0,0};
			int X                     = 2199;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = TypoCoderDiv1().getmax(vector <int>(D, D + (sizeof D / sizeof D[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int D[]                   = {90000,80000,70000,60000,50000,40000,30000,20000,10000};
			int X                     = 0;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = TypoCoderDiv1().getmax(vector <int>(D, D + (sizeof D / sizeof D[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int D[]                   = {1000000000,1000000000,10000,100000,2202,1};
			int X                     = 1000;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = TypoCoderDiv1().getmax(vector <int>(D, D + (sizeof D / sizeof D[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int D[]                   = {2048,1024,5012,256,128,64,32,16,8,4,2,1,0};
			int X                     = 2199;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = TypoCoderDiv1().getmax(vector <int>(D, D + (sizeof D / sizeof D[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int D[]                   = {61,666,512,229,618,419,757,217,458,883,23,932,547,679,565,767,513,798,870,31,379,294,929,892,173,127,796,353,913,115,802,803,948,592,959,127,501,319,140,694,851,189,924,590,790,3,669,541,342,272};
			int X                     = 1223;
			int expected__            = 29;

			std::clock_t start__      = std::clock();
			int received__            = TypoCoderDiv1().getmax(vector <int>(D, D + (sizeof D / sizeof D[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int D[]                   = {34,64,43,14,58,30,2,16,90,58,35,55,46,24,14,73,96,13,9,42,64,36,89,42,42,64,52,68,53,76,52,54,23,88,32,52,28,96,70,32,26,3,23,78,47,23,54,30,86,32};
			int X                     = 1328;
			int expected__            = 20;

			std::clock_t start__      = std::clock();
			int received__            = TypoCoderDiv1().getmax(vector <int>(D, D + (sizeof D / sizeof D[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			int D[]                   = ;
			int X                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TypoCoderDiv1().getmax(vector <int>(D, D + (sizeof D / sizeof D[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int D[]                   = ;
			int X                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TypoCoderDiv1().getmax(vector <int>(D, D + (sizeof D / sizeof D[0])), X);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			int D[]                   = ;
			int X                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TypoCoderDiv1().getmax(vector <int>(D, D + (sizeof D / sizeof D[0])), X);
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
