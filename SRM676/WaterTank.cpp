// SRM 676 - 250
// Algo:
// - Binary search answer
// - Easily check in O(N)
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

vector<int> t, x;
int C;

bool check(double R) {
	double initial = 0.0;
	int n = SZ(t);
	REP(i,n) {
		double cur = initial + t[i] * (double) x[i] - t[i] * R;
		if (cur > C) return false;
		initial = max(0.0, cur);
	}
	return true;
}

class WaterTank {
public:
    double minOutputRate( vector <int> t, vector <int> x, int C ) {
		::t = t;
		::x = x;
		::C = C;

		double l = 0.0, r = 1e6;
		REP(turn,200) {
			double mid = (l + r) / 2.0;
			if (check(mid)) {
				r = mid;
			}
			else l = mid;
		}
		return r;
    }
};

// BEGIN CUT HERE
#include <algorithm>
#include <cmath>
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
	
	static const double MAX_DOUBLE_ERROR = 1e-9;
	static bool topcoder_fequ(double expected, double result) {
		if (std::isnan(expected)) {
			return std::isnan(result);
		} else if (std::isinf(expected)) {
			if (expected > 0) {
				return result > 0 && std::isinf(result);
			} else {
				return result < 0 && std::isinf(result);
			}
		} else if (std::isnan(result) || std::isinf(result)) {
			return false;
		} else if (std::fabs(result - expected) < MAX_DOUBLE_ERROR) {
			return true;
		} else {
			double mmin = std::min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR));
			double mmax = std::max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR));
			return result > mmin && result < mmax;
		}
	}
	double moj_relative_error(double expected, double result) {
		if (std::isnan(expected) || std::isinf(expected) || std::isnan(result) || std::isinf(result) || expected == 0) {
			return 0;
		}
		return std::fabs(result-expected) / std::fabs(expected);
	}
	
	int verify_case(int casenum, const double &expected, const double &received, std::clock_t elapsed) { 
		std::cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (topcoder_fequ(expected, received)) {
			verdict = "PASSED";
			double rerr = moj_relative_error(expected, received); 
			if (rerr > 0) {
				std::sprintf(buf, "relative error %.3e", rerr);
				info.push_back(buf);
			}
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
			int t[]                   = {3,3};
			int x[]                   = {1,2};
			int C                     = 3;
			double expected__         = 0.9999999999999999;

			std::clock_t start__      = std::clock();
			double received__         = WaterTank().minOutputRate(vector <int>(t, t + (sizeof t / sizeof t[0])), vector <int>(x, x + (sizeof x / sizeof x[0])), C);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int t[]                   = {1,2,3,4,5};
			int x[]                   = {5,4,3,2,1};
			int C                     = 10;
			double expected__         = 1.9999999999999996;

			std::clock_t start__      = std::clock();
			double received__         = WaterTank().minOutputRate(vector <int>(t, t + (sizeof t / sizeof t[0])), vector <int>(x, x + (sizeof x / sizeof x[0])), C);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int t[]                   = {5949,3198,376,3592,4019,3481,5609,3840,6092,4059};
			int x[]                   = {29,38,96,84,10,2,39,27,76,94};
			int C                     = 1000000000;
			double expected__         = 0.0;

			std::clock_t start__      = std::clock();
			double received__         = WaterTank().minOutputRate(vector <int>(t, t + (sizeof t / sizeof t[0])), vector <int>(x, x + (sizeof x / sizeof x[0])), C);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int t[]                   = {9,3,4,8,1,2,5,7,6};
			int x[]                   = {123,456,789,1011,1213,1415,1617,1819,2021};
			int C                     = 11;
			double expected__         = 2019.1666666666665;

			std::clock_t start__      = std::clock();
			double received__         = WaterTank().minOutputRate(vector <int>(t, t + (sizeof t / sizeof t[0])), vector <int>(x, x + (sizeof x / sizeof x[0])), C);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int t[]                   = {100};
			int x[]                   = {1000};
			int C                     = 12345;
			double expected__         = 876.55;

			std::clock_t start__      = std::clock();
			double received__         = WaterTank().minOutputRate(vector <int>(t, t + (sizeof t / sizeof t[0])), vector <int>(x, x + (sizeof x / sizeof x[0])), C);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int t[]                   = ;
			int x[]                   = ;
			int C                     = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = WaterTank().minOutputRate(vector <int>(t, t + (sizeof t / sizeof t[0])), vector <int>(x, x + (sizeof x / sizeof x[0])), C);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int t[]                   = ;
			int x[]                   = ;
			int C                     = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = WaterTank().minOutputRate(vector <int>(t, t + (sizeof t / sizeof t[0])), vector <int>(x, x + (sizeof x / sizeof x[0])), C);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int t[]                   = ;
			int x[]                   = ;
			int C                     = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = WaterTank().minOutputRate(vector <int>(t, t + (sizeof t / sizeof t[0])), vector <int>(x, x + (sizeof x / sizeof x[0])), C);
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
