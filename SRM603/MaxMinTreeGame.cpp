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

const int MN = 55;
int deg[MN];

class MaxMinTreeGame {
public:
    int findend( vector <int> edges, vector <int> costs ) {
		memset(deg, 0, sizeof deg);

		int n = SZ(edges) + 1;
		FOR(u,1,n-1) {
			int v = edges[u-1];
			++deg[u];
			++deg[v];
		}

		int res = 0;
		REP(i,n) if (deg[i] == 1) res = max(res, costs[i]);
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
			int edges[]               = {0};
			int costs[]               = {4,6};
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = MaxMinTreeGame().findend(vector <int>(edges, edges + (sizeof edges / sizeof edges[0])), vector <int>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int edges[]               = {0,1};
			int costs[]               = {4,6,5};
			int expected__            = 5;

			std::clock_t start__      = std::clock();
			int received__            = MaxMinTreeGame().findend(vector <int>(edges, edges + (sizeof edges / sizeof edges[0])), vector <int>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int edges[]               = {0,1,2,3};
			int costs[]               = {0,1,0,1,0};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = MaxMinTreeGame().findend(vector <int>(edges, edges + (sizeof edges / sizeof edges[0])), vector <int>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int edges[]               = {0,0,0};
			int costs[]               = {5,1,2,3};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = MaxMinTreeGame().findend(vector <int>(edges, edges + (sizeof edges / sizeof edges[0])), vector <int>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int edges[]               = {0,0};
			int costs[]               = {3,2,5};
			int expected__            = 5;

			std::clock_t start__      = std::clock();
			int received__            = MaxMinTreeGame().findend(vector <int>(edges, edges + (sizeof edges / sizeof edges[0])), vector <int>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int edges[]               = ;
			int costs[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = MaxMinTreeGame().findend(vector <int>(edges, edges + (sizeof edges / sizeof edges[0])), vector <int>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int edges[]               = ;
			int costs[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = MaxMinTreeGame().findend(vector <int>(edges, edges + (sizeof edges / sizeof edges[0])), vector <int>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int edges[]               = ;
			int costs[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = MaxMinTreeGame().findend(vector <int>(edges, edges + (sizeof edges / sizeof edges[0])), vector <int>(costs, costs + (sizeof costs / sizeof costs[0])));
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
