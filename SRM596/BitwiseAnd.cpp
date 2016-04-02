// Div1 - 500
// Algo: greedy
// - Greedily add number one by one to the subset
// - To add each new number:
//   1. For each existing number, we must find a unique bit, add it to current new number
//   2. Let t = how many numbers we still need to add after current new number --> need to
//      add t unique bit to current new number

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

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) (S & TWO(X))

class BitwiseAnd {
public:
    vector<long long> lexSmallest( vector<long long> subset, int N ) {
		vector<ll> res;
		for(auto x : subset)
			if (x > (1LL<<60))
				return res;
		REP(i,SZ(subset))
			FOR(j,i+1,SZ(subset)-1)
				if ((subset[i] & subset[j]) == 0)
					return res;
		REP(i,SZ(subset))
			FOR(j,i+1,SZ(subset)-1)
				FOR(k,j+1,SZ(subset)-1)
					if ((subset[i] & subset[j] & subset[k]) > 0)
						return res;

		while (SZ(subset) < N) {
			ll x = 0;
			// for each number, find a unique bit
			REP(i,SZ(subset)) {
				bool found = false;

				auto cur = subset[i];
				REP(bit,60) if (CONTAIN(cur,bit)) {
					int can = 1;
					REP(j,SZ(subset)) if (j != i && CONTAIN(subset[j],bit)) {
						can = 0;
						break;
					}
					if (can) {
						found = true;
						x += TWO(bit);
						break;
					}
				}

				if (!found) return res;
			}
			int need = N - SZ(subset) - 1;
			REP(turn,need) {
				bool found = false;
				REP(bit,60) if (!CONTAIN(x,bit)) {
					int can = 1;
					REP(i,SZ(subset)) if (CONTAIN(subset[i], bit)) {
						can = 0;
						break;
					}
					if (can) {
						found = true;
						x += TWO(bit);
						break;
					}
				}
				if (!found) return res;
			}
			subset.push_back(x);
		}

		sort(subset.begin(), subset.end());
		return subset;
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
	
	template<typename T> std::ostream& operator<<(std::ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

	int verify_case(int casenum, const vector<long long> &expected, const vector<long long> &received, std::clock_t elapsed) { 
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
			long long subset[]        = {14, 20};
			int N                     = 3;
			long long expected__[]    = {14, 18, 20};

			std::clock_t start__      = std::clock();
			vector<long long> received__ = BitwiseAnd().lexSmallest(vector<long long>(subset, subset + (sizeof subset / sizeof subset[0])), N);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			long long subset[]        = {11, 17, 20};
			int N                     = 4;
			long long expected__[]    = {};

			std::clock_t start__      = std::clock();
			vector<long long> received__ = BitwiseAnd().lexSmallest(vector<long long>(subset, subset + (sizeof subset / sizeof subset[0])), N);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			long long subset[]        = {99, 157};
			int N                     = 4;
			long long expected__[]    = {99, 157, 262, 296};

			std::clock_t start__      = std::clock();
			vector<long long> received__ = BitwiseAnd().lexSmallest(vector<long long>(subset, subset + (sizeof subset / sizeof subset[0])), N);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			long long subset[]        = {1152921504606846975LL};
			int N                     = 3;
			long long expected__[]    = {};

			std::clock_t start__      = std::clock();
			vector<long long> received__ = BitwiseAnd().lexSmallest(vector<long long>(subset, subset + (sizeof subset / sizeof subset[0])), N);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			long long subset[]        = {};
			int N                     = 5;
			long long expected__[]    = {15, 113, 402, 676, 840};

			std::clock_t start__      = std::clock();
			vector<long long> received__ = BitwiseAnd().lexSmallest(vector<long long>(subset, subset + (sizeof subset / sizeof subset[0])), N);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 5: {
			long long subset[]        = {1, 3, 5, 7, 9, 11};
			int N                     = 6;
			long long expected__[]    = {};

			std::clock_t start__      = std::clock();
			vector<long long> received__ = BitwiseAnd().lexSmallest(vector<long long>(subset, subset + (sizeof subset / sizeof subset[0])), N);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 6: {
			long long subset[]        = {};
			int N                     = 3;
			long long expected__[]    = {3,5,6};

			std::clock_t start__      = std::clock();
			vector<long long> received__ = BitwiseAnd().lexSmallest(vector<long long>(subset, subset + (sizeof subset / sizeof subset[0])), N);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 7: {
			long long subset[]        = {3};
			int N                     = 5;
			long long expected__[]    = {3,5,6};

			std::clock_t start__      = std::clock();
			vector<long long> received__ = BitwiseAnd().lexSmallest(vector<long long>(subset, subset + (sizeof subset / sizeof subset[0])), N);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
/*      case 8: {
			long long subset[]        = ;
			int N                     = ;
			long long expected__[]    = ;

			std::clock_t start__      = std::clock();
			vector<long long> received__ = BitwiseAnd().lexSmallest(vector<long long>(subset, subset + (sizeof subset / sizeof subset[0])), N);
			return verify_case(casenum__, vector<long long>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
