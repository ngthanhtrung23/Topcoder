// Div1 - 250
// Algo:
// - Max difference = largest number - smallest number
// - Min difference = min(difference of 2 consecutive numbers)
// --> sort the array
// - Let i & j be the indices of smallest & largest number
// --> now we know the max difference
// - Greedily choose numbers between i & j, so that the min difference * k >= max difference
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

class CliqueParty {
public:
    int maxsize( vector <int> a, int k ) {
		int n = SZ(a);
		sort(a.begin(), a.end());

		ll res = 2; // select 2 elements

		REP(i,n) FOR(j,i+1,n-1) {
			ll ln = a[j] - a[i];
			ll nn = ln / k;
			while (nn * k < ln) ++nn;

			ll cur = 2;
			ll last = a[i];
			FOR(x,i+1,j-1) {
				if (a[x] - a[i] >= nn && a[x] - last >= nn && a[j] - a[x] >= nn) {
					last = a[x];
					++cur;
				}
			}
			res = max(res, cur);
		}

		return (int) res;
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
			int a[]                   = {1,2,3};
			int k                     = 2;
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = CliqueParty().maxsize(vector <int>(a, a + (sizeof a / sizeof a[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int a[]                   = {1,2,3};
			int k                     = 1;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = CliqueParty().maxsize(vector <int>(a, a + (sizeof a / sizeof a[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int a[]                   = {4,10,5,6};
			int k                     = 2;
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = CliqueParty().maxsize(vector <int>(a, a + (sizeof a / sizeof a[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int a[]                   = {1,2,3,4,5,6};
			int k                     = 3;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = CliqueParty().maxsize(vector <int>(a, a + (sizeof a / sizeof a[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int a[]                   = {10,9,25,24,23,30};
			int k                     = 7;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = CliqueParty().maxsize(vector <int>(a, a + (sizeof a / sizeof a[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int a[]                   = ;
			int k                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = CliqueParty().maxsize(vector <int>(a, a + (sizeof a / sizeof a[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int a[]                   = ;
			int k                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = CliqueParty().maxsize(vector <int>(a, a + (sizeof a / sizeof a[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int a[]                   = ;
			int k                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = CliqueParty().maxsize(vector <int>(a, a + (sizeof a / sizeof a[0])), k);
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
