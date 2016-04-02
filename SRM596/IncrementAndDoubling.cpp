// Div1 - 250
// Algo: Greedy
// - Convert all number to binary
// - Answer >= (total number of bit 1) + (length of max number)
// - Prove using greedy that we can achieve that answer

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

int cnt(int x) {
	int res = 0;
	while (x) x /= 2, res++;
	return res;
}

class IncrementAndDoubling {
public:
    int getMin( vector <int> desiredArray ) {
		int res = 0, ln = 0;
		for(int x : desiredArray) {
			res += __builtin_popcount(x);
			ln = max(ln, cnt(x));
		}
		return res + max(ln - 1, 0);
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
			int desiredArray[]        = {2, 1};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = IncrementAndDoubling().getMin(vector <int>(desiredArray, desiredArray + (sizeof desiredArray / sizeof desiredArray[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int desiredArray[]        = {16, 16, 16};
			int expected__            = 7;

			std::clock_t start__      = std::clock();
			int received__            = IncrementAndDoubling().getMin(vector <int>(desiredArray, desiredArray + (sizeof desiredArray / sizeof desiredArray[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int desiredArray[]        = {100};
			int expected__            = 9;

			std::clock_t start__      = std::clock();
			int received__            = IncrementAndDoubling().getMin(vector <int>(desiredArray, desiredArray + (sizeof desiredArray / sizeof desiredArray[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int desiredArray[]        = {0, 0, 1, 0, 1};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = IncrementAndDoubling().getMin(vector <int>(desiredArray, desiredArray + (sizeof desiredArray / sizeof desiredArray[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int desiredArray[]        = {123, 234, 345, 456, 567, 789};
			int expected__            = 40;

			std::clock_t start__      = std::clock();
			int received__            = IncrementAndDoubling().getMin(vector <int>(desiredArray, desiredArray + (sizeof desiredArray / sizeof desiredArray[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int desiredArray[]        = {7,5,8,1,8,6,6,5,3,5,5,2,8,9,9,4,6,9,4,4,1,9,9,2,8,4,7,4,8,8,6,3,9,4,3,4,5,1,9,8,3,8,3,7,9,3,8,4,4,7};
			int expected__            = 84;

			std::clock_t start__      = std::clock();
			int received__            = IncrementAndDoubling().getMin(vector <int>(desiredArray, desiredArray + (sizeof desiredArray / sizeof desiredArray[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int desiredArray[]        = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = IncrementAndDoubling().getMin(vector <int>(desiredArray, desiredArray + (sizeof desiredArray / sizeof desiredArray[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int desiredArray[]        = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = IncrementAndDoubling().getMin(vector <int>(desiredArray, desiredArray + (sizeof desiredArray / sizeof desiredArray[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int desiredArray[]        = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = IncrementAndDoubling().getMin(vector <int>(desiredArray, desiredArray + (sizeof desiredArray / sizeof desiredArray[0])));
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
