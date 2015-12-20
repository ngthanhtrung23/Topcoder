// Div1 - 900
// Algo: Brute force
// - Observation: Assume we know for all (0, j) whether operation flip(0, j) is applied,
//   then, we can deduce whether each operations of following rows are applied.
// - If we do brute force for each rows:
//     - For each 1st cell and 1st column, there are 3 choices
//     - For each cell from 2nd row, there are at most 2 choices (which operation type)
//     - For entire 1st row, there are only 1 + 2^N + 2^N choices (1: not doing anything, 2^N for each type of operations)
//     - Assume the cells without operation flip (0, j) form set S, then for each column in this set, there are at most 2 choices
//     --> In total there are 3^N choices.
// --> Brute force works fast enough, just need to check which rows and which columns already have some operation applied, and
//     check if at any point, the board is invalid

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

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int a[15][15], m, n, rows[15], cols[15], res;

const int di[4] = {-1,1,0,0};
const int dj[4] = {0,0,-1,1};

bool outside(int i, int j) {
	return i < 0 || i >= m || j < 0 || j >= n;
}
void flip(int i, int j, int typ) { // typ = 1 or 2
	if (typ == 0) return ;
	REP(dir,4) {
		int ii = i + di[dir], jj = j + dj[dir];
		if (outside(ii, jj)) continue;

		a[ii][jj] ^= 1;
	}
	if (typ == 2) a[i][j] ^= 1;
}

bool check() {
	REP(i,m) REP(j,n) if (a[i][j] == 0) return false;
	return true;
}

void attempt(int i, int j, int cnt) {
	if (i == m) {
		if (check()) res = min(res, cnt);
		return ;
	}
	int ii = i, jj = j + 1;
	if (jj == n) {
		ii++;
		jj = 0;
	}

	// attempt cell (i, j)
	FOR(move,0,2) {
		if (move) {
			if (rows[i] && rows[i] != move) continue;
			if (cols[j] && cols[j] != move) continue;
		}

		int saveRow = rows[i], saveCol = cols[j];
		if (move) {
			rows[i] = move;
			cols[j] = move;
		}
		flip(i, j, move);

		if (i == 0 || a[i-1][j] == 1) {
			attempt(ii, jj, cnt + (move > 0));
		}

		flip(i, j, move);
		rows[i] = saveRow, cols[j] = saveCol;
	}
}

class YetAnotherBoardGame {
public:
    int minimumMoves( vector <string> board ) {
		m = SZ(board);
		n = SZ(board[0]);
		REP(i,m) REP(j,n) {
			if (board[i][j] == 'B') a[i][j] = 1;
			else a[i][j] = 0;
		}
		res = 1e9;
		memset(rows, 0, sizeof rows);
		memset(cols, 0, sizeof cols);
		attempt(0, 0, 0);
		if (res > m*n) res = -1;
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
			string board[]            = {
 "BBBBBBBBB",
 "BBWBBBBBB",
 "BWWWBBBBB",
 "BBWBBBWBB",
 "BBBBBWBWB",
 "BBBBBBWBB"};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {
 "BBW",
 "WWW",
 "BWW"};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {
 "WBW",
 "BBW",
 "WBW"};
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"BBBB",
 "WBWB",
 "BBBB",
 "BBBB"};
			int expected__            = -1;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string board[]            = {"WWWWWBW",
 "WBWBWBW",
 "BBWBBWW"};
			int expected__            = 7;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string board[]            = {"WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW"}
;
			int expected__            = 30;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string board[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string board[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string board[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherBoardGame().minimumMoves(vector <string>(board, board + (sizeof board / sizeof board[0])));
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
