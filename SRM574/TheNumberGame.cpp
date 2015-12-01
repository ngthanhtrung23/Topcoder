// Div 1 - 275
// Algo:
// - B wins if there exist x such that:
//     - B can go to x
//     - A can NOT go to x
//     - Notes that 1000 turns is more than enough for A to win (if he can)
// --> BFS from both player
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

int reverse(int x) {
	if (x == 0) return 0;
	int res = 0;
	while (x > 0) {
		res = res * 10 + x % 10;
		x /= 10;
	}
	return res;
}

set<int> bfs(int start) {
	queue<int> qu;
	set<int> res;

	qu.push(start);
	res.insert(start);
	
	while (!qu.empty()) {
		int u = qu.front(); qu.pop();
		int v = reverse(u);

		if (!res.count(v)) {
			res.insert(v);
			qu.push(v);
		}
		v = u / 10;
		if (!res.count(v)) {
			res.insert(v);
			qu.push(v);
		}
	}

	return res;
}

class TheNumberGame {
public:
    string determineOutcome( int A, int B ) {
		auto allB = bfs(B);
		auto allA = bfs(A);
		for(int x : allB)
			if (!allA.count(x)) return "Manao loses";
		return "Manao wins";
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
			int A                     = 45;
			int B                     = 4;
			string expected__         = "Manao wins";

			std::clock_t start__      = std::clock();
			string received__         = TheNumberGame().determineOutcome(A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int A                     = 45;
			int B                     = 5;
			string expected__         = "Manao wins";

			std::clock_t start__      = std::clock();
			string received__         = TheNumberGame().determineOutcome(A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int A                     = 99;
			int B                     = 123;
			string expected__         = "Manao loses";

			std::clock_t start__      = std::clock();
			string received__         = TheNumberGame().determineOutcome(A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int A                     = 2356236;
			int B                     = 5666;
			string expected__         = "Manao loses";

			std::clock_t start__      = std::clock();
			string received__         = TheNumberGame().determineOutcome(A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int A                     = ;
			int B                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = TheNumberGame().determineOutcome(A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int A                     = ;
			int B                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = TheNumberGame().determineOutcome(A, B);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int A                     = ;
			int B                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = TheNumberGame().determineOutcome(A, B);
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
