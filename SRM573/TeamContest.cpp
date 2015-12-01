// Div 1 - 250:
// Algo: Greedy:
// - For each person with highest rating, take other 2 with as small rating as possible

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

class TeamContest {
public:
    int worstRank( vector <int> strength ) {
		int res = 1;
		multiset<int> all;

		vector<int> my;
		REP(i,SZ(strength)) {
			if (i >= 3) all.insert(strength[i]);
			else my.push_back(strength[i]);
		}
		sort(my.begin(), my.end());
		int myTeam = my[0] + my[2];
		while (!all.empty()) {
			auto it = all.end(); --it;
			int largest = *it; all.erase(it);
			
			while (!all.empty() && *all.begin() + largest <= myTeam) {
				all.erase(all.begin());
			}
			if (all.size() > 1 && *all.begin() + largest > myTeam) {
				all.erase(all.begin());
				all.erase(all.begin());
				++res;
			}
			else break;
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
			int strength[]            = {5, 7, 3, 5, 7, 3, 5, 7, 3};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = TeamContest().worstRank(vector <int>(strength, strength + (sizeof strength / sizeof strength[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int strength[]            = {5, 7, 3} ;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = TeamContest().worstRank(vector <int>(strength, strength + (sizeof strength / sizeof strength[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int strength[]            = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = TeamContest().worstRank(vector <int>(strength, strength + (sizeof strength / sizeof strength[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int strength[]            = {3,9,4,6,2,6,1,6,9,1,4,1,3,8,5} ;
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = TeamContest().worstRank(vector <int>(strength, strength + (sizeof strength / sizeof strength[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int strength[]            = {53,47,88,79,99,75,28,54,65,14,22,13,11,31,43} ;
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = TeamContest().worstRank(vector <int>(strength, strength + (sizeof strength / sizeof strength[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int strength[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TeamContest().worstRank(vector <int>(strength, strength + (sizeof strength / sizeof strength[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int strength[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TeamContest().worstRank(vector <int>(strength, strength + (sizeof strength / sizeof strength[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int strength[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TeamContest().worstRank(vector <int>(strength, strength + (sizeof strength / sizeof strength[0])));
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
