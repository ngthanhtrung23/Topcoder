// Div1 - 250
// Algo: Case observing
// - For each position, check if:
//     - It can be seen by some camera: Check all segments containing this position, and see if there
//       is some camera with same number of boxes.
//     - It can be seen by NO camera: Get all other ranges that does not contain this position, and
//       check if reports is subset of it

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

int a[111];

int get(int l, int r) {
	return a[r] - a[l-1];
}

bool contains(vector<int> reports, int x) {
	for(int r : reports)
		if (r == x) return true;
	return false;
}

class SurveillanceSystem {
public:
    string getContainerInfo( string containers, vector <int> reports, int L ) {
		int n = SZ(containers);
		FOR(i,1,n)
			if (containers[i-1] == 'X') a[i] = 1;
			else a[i] = 0;
		FOR(i,1,n) a[i] += a[i-1];

		string res = "";
		FOR(i,1,n) {
			bool canPositive = false;
			FOR(l,i-L+1,i) {
				if (l < 1) continue;
				int r = l + L - 1;
				if (r > n) continue;
				if (contains(reports, get(l, r))) {
					canPositive = true;
					break;
				}
			}
			bool canNegative = true;
			multiset<int> all;
			FOR(l,1,n-L+1) {
				int r = l + L - 1;
				if (l <= i && i <= r) continue;

				all.insert(get(l, r));
			}
			for(int r : reports) {
				if (all.empty() || !all.count(r)) {
					canNegative = false;
					break;
				}
				all.erase(all.find(r));
			}

			if (canPositive && canNegative) res += '?';
			else if (canPositive) res += '+';
			else res += '-';
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
	
	int verify_case(int casenum, const string &expected, const string &received, std::clock_t elapsed) { 
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
			std::cerr << "    Expected: \"" << expected << "\"" << std::endl; 
			std::cerr << "    Received: \"" << received << "\"" << std::endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string containers         = "-X--XX";
			int reports[]             = {1, 2};
			int L                     = 3;
			string expected__         = "??++++";

			std::clock_t start__      = std::clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string containers         = "-XXXXX-";
			int reports[]             = {2};
			int L                     = 3;
			string expected__         = "???-???";
			DEBUG(expected__);

			std::clock_t start__      = std::clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string containers         = "------X-XX-";
			int reports[]             = {3, 0, 2, 0};
			int L                     = 5;
			string expected__         = "++++++++++?";

			std::clock_t start__      = std::clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string containers         = "-XXXXX---X--";
			int reports[]             = {2, 1, 0, 1};
			int L                     = 3;
			string expected__         = "???-??++++??";

			std::clock_t start__      = std::clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string containers         = "-XX--X-XX-X-X--X---XX-X---XXXX-----X";
			int reports[]             = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
			int L                     = 7;
			string expected__         = "???++++?++++++++++++++++++++??????--";

			std::clock_t start__      = std::clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string containers         = ;
			int reports[]             = ;
			int L                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string containers         = ;
			int reports[]             = ;
			int L                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string containers         = ;
			int reports[]             = ;
			int L                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = SurveillanceSystem().getContainerInfo(containers, vector <int>(reports, reports + (sizeof reports / sizeof reports[0])), L);
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
