// Div1 - 500
// Algo: DP
// - Let f(i, j) = number of ways to use all numbers 0..i, and creating j tracks
//   (1 track is 1 strictly increasing sequence)
// - See code on more details on how to calculate f

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

ll c[1511][1511], f[55][1511];
int sum[55];

void update(ll& x, ll val) {
	x = (x + val) % MOD;
}

class LISNumber {
public:
    int count( vector <int> cardsnum, int K ) {
		memset(c, 0, sizeof c);
		REP(i,1500) FOR(j,0,i) {
			if (j == 0) c[i][j] = 1;
			else c[i][j] = (c[i-1][j-1] + c[i-1][j]) % MOD;
		}
		int n = SZ(cardsnum);

		sum[0] = cardsnum[0];
		FOR(i,1,n-1) sum[i] = sum[i-1] + cardsnum[i];

		memset(f, 0, sizeof f);
		f[0][cardsnum[0]] = 1;
		FOR(i,0,n-2) FOR(j,0,K) if (f[i][j]) {
			// currently, we already placed numbers 0..i, and made j tracks

			FOR(u,0,min(j,cardsnum[i+1])) {
				// now we place u * (i+1) on top of j existing tracks
				ll add = f[i][j] * c[j][u] % MOD;

				// add use v * (i+1) numbers to create v more tracks
				int v = cardsnum[i+1] - u;
				
				// the positions that we can put these v numbers
				int positions = sum[i] - j + 1 + u;

				// since we can put 2 numbers at same position --> C(positions + v - 1, v)
				add = add * c[positions + v - 1][v];

				update(f[i+1][j + v], add);
			}
		}
		return f[n-1][K];
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
			int cardsnum[]            = {1, 1, 1};
			int K                     = 2;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = LISNumber().count(vector <int>(cardsnum, cardsnum + (sizeof cardsnum / sizeof cardsnum[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int cardsnum[]            = {2};
			int K                     = 1;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = LISNumber().count(vector <int>(cardsnum, cardsnum + (sizeof cardsnum / sizeof cardsnum[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int cardsnum[]            = {36, 36, 36, 36, 36};
			int K                     = 36;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = LISNumber().count(vector <int>(cardsnum, cardsnum + (sizeof cardsnum / sizeof cardsnum[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int cardsnum[]            = {3, 2, 11, 5, 7};
			int K                     = 20;
			int expected__            = 474640725;

			std::clock_t start__      = std::clock();
			int received__            = LISNumber().count(vector <int>(cardsnum, cardsnum + (sizeof cardsnum / sizeof cardsnum[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int cardsnum[]            = {31, 4, 15, 9, 26, 5, 35, 8, 9, 7, 9, 32, 3, 8, 4, 6, 26};
			int K                     = 58;
			int expected__            = 12133719;

			std::clock_t start__      = std::clock();
			int received__            = LISNumber().count(vector <int>(cardsnum, cardsnum + (sizeof cardsnum / sizeof cardsnum[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int cardsnum[]            = {27, 18, 28, 18, 28, 4, 5, 9, 4, 5, 23, 5, 36, 28, 7, 4, 7, 13, 5, 26, 6, 24, 9, 7, 7, 5, 7, 24, 7, 9, 36, 9, 9, 9, 5, 9};
			int K                     = 116;
			int expected__            = 516440918;

			std::clock_t start__      = std::clock();
			int received__            = LISNumber().count(vector <int>(cardsnum, cardsnum + (sizeof cardsnum / sizeof cardsnum[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int cardsnum[]            = ;
			int K                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = LISNumber().count(vector <int>(cardsnum, cardsnum + (sizeof cardsnum / sizeof cardsnum[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int cardsnum[]            = ;
			int K                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = LISNumber().count(vector <int>(cardsnum, cardsnum + (sizeof cardsnum / sizeof cardsnum[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int cardsnum[]            = ;
			int K                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = LISNumber().count(vector <int>(cardsnum, cardsnum + (sizeof cardsnum / sizeof cardsnum[0])), K);
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
