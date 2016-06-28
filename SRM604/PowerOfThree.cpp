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

#define YES "Possible"
#define NO "Impossible"

set<ll> get(ll x) {
	vector<int> t;
	for(ll p3 = 3486784401LL; p3 >= 1; p3 /= 3) {
		t.push_back(x / p3);
		x %= p3;
	}
	reverse(t.begin(), t.end());

	REP(i,SZ(t)) {
		if (t[i] == 2) {
			t[i] = -1;
			t[i+1]++;
		}
		else if (t[i] == 3) {
			t[i] = 0;
			t[i+1]++;
		}
	}
//	PR0(t, SZ(t));

	set<ll> res;
	int cur = 0;
	for(ll p3 = 1; p3 <= 3486784401LL; p3 *= 3) {
		if (t[cur++]) res.insert(p3);
	}
	return res;
}

class PowerOfThree {
public:
    string ableToGet( int x, int y ) {
		if (x < 0) x = -x;
		if (y < 0) y = -y;

		auto sx = get(x);
		auto sy = get(y);

//		for(auto t : sx) cout << t << ' '; cout << endl;
//		for(auto t : sy) cout << t << ' '; cout << endl;


		for(auto t : sx) if (sy.count(t)) return NO;
		auto all = sx;
		for(auto t : sy) all.insert(t);

		if (all.empty()) return YES;

		ll ln = *all.rbegin();
		for(ll p3 = 1; p3 <= ln; p3 *= 3)
			if (!all.count(p3)) return NO;
		return YES;
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
			int x                     = 1;
			int y                     = 3;
			string expected__         = "Possible";

			std::clock_t start__      = std::clock();
			string received__         = PowerOfThree().ableToGet(x, y);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int x                     = 0;
			int y                     = 2;
			string expected__         = "Possible";

			std::clock_t start__      = std::clock();
			string received__         = PowerOfThree().ableToGet(x, y);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int x                     = 1;
			int y                     = 9;
			string expected__         = "Impossible";

			std::clock_t start__      = std::clock();
			string received__         = PowerOfThree().ableToGet(x, y);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int x                     = 3;
			int y                     = 0;
			string expected__         = "Impossible";

			std::clock_t start__      = std::clock();
			string received__         = PowerOfThree().ableToGet(x, y);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int x                     = 1;
			int y                     = 1;
			string expected__         = "Impossible";

			std::clock_t start__      = std::clock();
			string received__         = PowerOfThree().ableToGet(x, y);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int x                     = -6890;
			int y                     = 18252;
			string expected__         = "Possible";

			std::clock_t start__      = std::clock();
			string received__         = PowerOfThree().ableToGet(x, y);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int x                     = 1000000000;
			int y                     = -1000000000;
			string expected__         = "Impossible";

			std::clock_t start__      = std::clock();
			string received__         = PowerOfThree().ableToGet(x, y);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 7: {
			int x                     = 0;
			int y                     = 0;
			string expected__         = "Possible";

			std::clock_t start__      = std::clock();
			string received__         = PowerOfThree().ableToGet(x, y);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 8: {
			int x                     = ;
			int y                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = PowerOfThree().ableToGet(x, y);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			int x                     = ;
			int y                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = PowerOfThree().ableToGet(x, y);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 10: {
			int x                     = ;
			int y                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = PowerOfThree().ableToGet(x, y);
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
