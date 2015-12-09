// Div1 - 250
// Algo: Basic implementation problem
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

class UndoHistory {
public:
    int minPresses( vector <string> lines ) {
		set<string> all;
		int res = 0;
		int n = SZ(lines);
		res += n; // enter
		all.insert("");
		string buffer = "";
		REP(i,n) {
			string cur = lines[i];

			int t = 2;
			FORD(i,SZ(cur),0) {
				if (all.count(cur.substr(0, i))) {
					t += SZ(cur) - i;
					break;
				}
			}
			if (SZ(cur) >= SZ(buffer) && buffer == cur.substr(0, SZ(buffer))) {
				t = min(t, SZ(cur) - SZ(buffer));
			}

			REP(i,SZ(cur) + 1) {
				all.insert(cur.substr(0, i));
			}

			buffer = cur;
			res += t;
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
			string lines[]            = {"tomorrow", "topcoder"};
			int expected__            = 18;

			std::clock_t start__      = std::clock();
			int received__            = UndoHistory().minPresses(vector <string>(lines, lines + (sizeof lines / sizeof lines[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string lines[]            = {"a","b"};
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = UndoHistory().minPresses(vector <string>(lines, lines + (sizeof lines / sizeof lines[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string lines[]            = {"a", "ab", "abac", "abacus" };
			int expected__            = 10;

			std::clock_t start__      = std::clock();
			int received__            = UndoHistory().minPresses(vector <string>(lines, lines + (sizeof lines / sizeof lines[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string lines[]            = {"pyramid", "sphinx", "sphere", "python", "serpent"};
			int expected__            = 39;

			std::clock_t start__      = std::clock();
			int received__            = UndoHistory().minPresses(vector <string>(lines, lines + (sizeof lines / sizeof lines[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string lines[]            = {"ba","a","a","b","ba"}
;
			int expected__            = 13;

			std::clock_t start__      = std::clock();
			int received__            = UndoHistory().minPresses(vector <string>(lines, lines + (sizeof lines / sizeof lines[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

        case 5: {
			string lines[]            = {"abc", "a", "ab"};
			int expected__            = 9;

			std::clock_t start__      = std::clock();
			int received__            = UndoHistory().minPresses(vector <string>(lines, lines + (sizeof lines / sizeof lines[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 6: {
			string lines[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = UndoHistory().minPresses(vector <string>(lines, lines + (sizeof lines / sizeof lines[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string lines[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = UndoHistory().minPresses(vector <string>(lines, lines + (sizeof lines / sizeof lines[0])));
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
