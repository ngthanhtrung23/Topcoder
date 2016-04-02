// Div1 - 1000
// Algo: math
// - Area(polygon) = sum(area of directed triangle)
// --> for each triangle (O, a[i], a[j]), calculate probability that
//     edge (a[i], a[j]) belongs to convex hull and multiply with directed area
// - Probability = p[i] * p[j] * (probability that all other points are in same half-plane and
//   no point is in between a[i] and a[j])
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

struct Point {
	ll x, y;
	Point() { x = y = 0; }
	Point(ll x, ll y) : x(x), y(y) {}

	Point operator - (const Point& a) const { return Point(x-a.x, y-a.y); }
	ll operator * (const Point& a) const { return x*a.x + y*a.y; }
	ll operator % (const Point& a) const { return x*a.y - y*a.x; }
} a[55];

bool order(const Point& a, const Point& b, const Point& c) {
	return min(a.x, c.x) <= b.x && b.x <= max(a.x, c.x)
		&& min(a.y, c.y) <= b.y && b.y <= max(a.y, c.y);
}

int ccw(const Point& a, const Point& b, const Point& c) {
	ll t = (b - a) % (c - a);
	if (t == 0) return 0;
	if (t < 0) return -1;
	return 1;
}
int n;
double p[55];

class Constellation {
public:
    double expectation( vector <int> x, vector <int> y, vector <int> prob ) {
		n = SZ(x);
		FOR(i,1,n) {
			a[i] = Point(x[i-1], y[i-1]);
			p[i] = prob[i-1] / 1000.0;
		}

		double res = 0.0;
		FOR(i,1,n) FOR(j,1,n) if (i != j) {
			double prob = p[i] * p[j];

			FOR(k,1,n) if (k != i && k != j) {
				int t = ccw(a[i], a[j], a[k]);
				if (t < 0) prob *= 1 - p[k];
				else if (t == 0) {
					if (order(a[i], a[k], a[j])) prob *= 1 - p[k];
				}
			}

			res += prob * (a[i] % a[j]);
		}
		return res / 2.0;
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
			int x[]                   = {0,0,1};
			int y[]                   = {0,1,0};
			int prob[]                = {500,500,500};
			double expected__         = 0.0625;

			std::clock_t start__      = std::clock();
			double received__         = Constellation().expectation(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int x[]                   = {0,1,0,1};
			int y[]                   = {0,0,1,1};
			int prob[]                = {1000,1000,400,800};
			double expected__         = 0.6000000000000001;

			std::clock_t start__      = std::clock();
			double received__         = Constellation().expectation(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int x[]                   = {-1,-1,-1,0,0,0,1,1,1};
			int y[]                   = {-1,0,1,-1,0,1,-1,0,1};
			int prob[]                = {500,500,500,500,500,500,500,500,500};
			double expected__         = 1.9375;

			std::clock_t start__      = std::clock();
			double received__         = Constellation().expectation(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int x[]                   = {0,0,1,2,2};
			int y[]                   = {0,1,2,1,0};
			int prob[]                = {1000,500,200,500,1000};
			double expected__         = 1.3;

			std::clock_t start__      = std::clock();
			double received__         = Constellation().expectation(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int x[]                   = {1,5,5,8,2,6,9};
			int y[]                   = {3,6,4,2,5,7,9};
			int prob[]                = {100,400,200,1000,400,900,600};
			double expected__         = 12.888936;

			std::clock_t start__      = std::clock();
			double received__         = Constellation().expectation(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int x[]                   = {-100,100,-100,100,-42,57,-34,76,35,-75,-54,10,43};
			int y[]                   = {-100,-100,100,100,52,-57,-84,63,-43,50,63,10,-44};
			int prob[]                = {1000,1000,1000,1000,342,747,897,325,678,34,53,6,253};
			double expected__         = 40000.0;

			std::clock_t start__      = std::clock();
			double received__         = Constellation().expectation(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int x[]                   = ;
			int y[]                   = ;
			int prob[]                = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = Constellation().expectation(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int x[]                   = ;
			int y[]                   = ;
			int prob[]                = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = Constellation().expectation(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int x[]                   = ;
			int y[]                   = ;
			int prob[]                = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = Constellation().expectation(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])), vector <int>(prob, prob + (sizeof prob / sizeof prob[0])));
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
