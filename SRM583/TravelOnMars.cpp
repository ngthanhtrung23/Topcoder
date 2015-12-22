// Div1 - 250
// Algo: Graph - Floyd
// - Build graph
// - Use Floyd to find min path between all pair of vertices (easiest to implement)
// - (Actually can do BFS, but Floyd should be more simple)

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
int c[55][55];

class TravelOnMars {
public:
    int minTimes( vector <int> range, int startCity, int endCity ) {
		int n = SZ(range);
		REP(i,n) REP(j,n) c[i][j] = (i == j) ? 0 : 1e9;
		REP(i,n) {
			FOR(j,i-range[i],i+range[i]) {
				int x = j % n; if (x < 0) x += n;
				c[i][x] = 1;
			}
		}
		REP(k,n) REP(i,n) REP(j,n)
			c[i][j] = min(c[i][j], c[i][k] + c[k][j]);
		return c[startCity][endCity];
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
			int range[]               = {2,1,1,1,1,1};
			int startCity             = 1;
			int endCity               = 4;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = TravelOnMars().minTimes(vector <int>(range, range + (sizeof range / sizeof range[0])), startCity, endCity);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int range[]               = {2,1,1,1,1,1};
			int startCity             = 4;
			int endCity               = 1;
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = TravelOnMars().minTimes(vector <int>(range, range + (sizeof range / sizeof range[0])), startCity, endCity);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int range[]               = {2,1,1,2,1,2,1,1};
			int startCity             = 2;
			int endCity               = 6;
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = TravelOnMars().minTimes(vector <int>(range, range + (sizeof range / sizeof range[0])), startCity, endCity);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int range[]               = {3,2,1,1,3,1,2,2,1,1,2,2,2,2,3};
			int startCity             = 6;
			int endCity               = 13;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = TravelOnMars().minTimes(vector <int>(range, range + (sizeof range / sizeof range[0])), startCity, endCity);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int range[]               = ;
			int startCity             = ;
			int endCity               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TravelOnMars().minTimes(vector <int>(range, range + (sizeof range / sizeof range[0])), startCity, endCity);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int range[]               = ;
			int startCity             = ;
			int endCity               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TravelOnMars().minTimes(vector <int>(range, range + (sizeof range / sizeof range[0])), startCity, endCity);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int range[]               = ;
			int startCity             = ;
			int endCity               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TravelOnMars().minTimes(vector <int>(range, range + (sizeof range / sizeof range[0])), startCity, endCity);
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
