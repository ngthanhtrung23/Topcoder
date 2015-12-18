// SRM676 - 500
// Algo:
// - Draw on paper --> prove that grundy has cycle = 2, starting from k = 2
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

char a[111][111];
int g[11][111][111];

const int di[4] = {-1,1,0,0};
const int dj[4] = {0,0,-1,1};

class BoardEscape {
public:
    string findWinner( vector <string> s, int k ) {
		if (k > 4) k = 4 + k % 4;
		int m = SZ(s);
		int n = SZ(s[0]);
		memset(a, '#', sizeof a);
		FOR(i,1,m) FOR(j,1,n) a[i][j] = s[i-1][j-1];

		FOR(t,0,8) {
			if (t == 0) {
				FOR(i,1,m) FOR(j,1,n) g[t][i][j] = 0;
			}
			else {
				FOR(i,1,m) FOR(j,1,n) {
					set<int> all;
					REP(dir,4) {
						int ii = i + di[dir], jj = j + dj[dir];
						if (a[ii][jj] == '#') continue;
						if (a[ii][jj] == 'E') all.insert(0);
						else all.insert(g[t-1][ii][jj]);
					}
					int res = 0;
					while (all.count(res)) ++res;
					g[t][i][j] = res;
				}
			}
		}
		int res = 0;
		FOR(i,1,m) FOR(j,1,n) if (a[i][j] == 'T') {
			res ^= g[k][i][j];
		}
		if (res) return "Alice"; else return "Bob";
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
			string s[]                = {"TE"};
			int k                     = 2;
			string expected__         = "Alice";

			std::clock_t start__      = std::clock();
			string received__         = BoardEscape().findWinner(vector <string>(s, s + (sizeof s / sizeof s[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string s[]                = {"E#E",
 "#T#",
 "E#E"};
			int k                     = 1000000;
			string expected__         = "Bob";

			std::clock_t start__      = std::clock();
			string received__         = BoardEscape().findWinner(vector <string>(s, s + (sizeof s / sizeof s[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string s[]                = {"T.T.T.",
 ".E.E.E"};
			int k                     = 1;
			string expected__         = "Alice";

			std::clock_t start__      = std::clock();
			string received__         = BoardEscape().findWinner(vector <string>(s, s + (sizeof s / sizeof s[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string s[]                = {"TTE"};
			int k                     = 6;
			string expected__         = "Alice";

			std::clock_t start__      = std::clock();
			string received__         = BoardEscape().findWinner(vector <string>(s, s + (sizeof s / sizeof s[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string s[]                = {"..........................",
 "......TTT..TTT..T...T.....",
 ".....T.....T..T.TT.TT.....",
 "......TTT..TTT..T.T.T.....",
 ".........T.T.T..T...T.....",
 "......TTT..T..T.T...T.....",
 "..........................",
 "...E#E#E#E#E#E#E#E#E#E#...",
 "..........................",
 "......TTT..TTT...TTT......",
 ".....T........T.T.........",
 "......TTT.....T..TTT......",
 ".....T...T...T..T...T.....",
 "......TTT....T...TTT......",
 "..........................",
 "...#E#E#E#E#E#E#E#E#E#E...",
 "..........................",
 "....TT...T...T..T.TTT.T...",
 "...T.....T...T..T.T...T...",
 "...T.TT..T...TTTT.TT..T...",
 "...T..T..T...T..T.T.......",
 "....TT...TTT.T..T.T...T...",
 ".........................."};
			int k                     = 987654321;
			string expected__         = "Bob";

			std::clock_t start__      = std::clock();
			string received__         = BoardEscape().findWinner(vector <string>(s, s + (sizeof s / sizeof s[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string s[]                = ;
			int k                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = BoardEscape().findWinner(vector <string>(s, s + (sizeof s / sizeof s[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string s[]                = ;
			int k                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = BoardEscape().findWinner(vector <string>(s, s + (sizeof s / sizeof s[0])), k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string s[]                = ;
			int k                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = BoardEscape().findWinner(vector <string>(s, s + (sizeof s / sizeof s[0])), k);
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
