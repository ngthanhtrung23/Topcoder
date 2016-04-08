// Div1 - 600
// Algo: brute force + DP
// - Let S = set of columns which must be palindrome (we don't care about columns that are not in
//   S). The number of elements in S must be at least columnCount
// - We use DP to calculate minimum cost to get all columns in S to be palindrome, and at least
//   rowCount rows to be palindrome
// - Consider the rows of the board, 2 rows at a time (i-th and (n-1-i)-th rows)
// - We can calculate the cost that 0/1/2 of the rows become palindrome

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

const int INF = 1000111;
int m, n;
int f[22][22];

void update(int& x, int val) {
	x = min(x, val);
}

int equal(vector<char> a) {
	int c0 = 0, c1 = 0;
	for(char x : a) if (x == '0') ++c0; else ++c1;
	return min(c0, c1);
}

class PalindromeMatrix {
public:
    int minChange( vector <string> A, int rowCount, int columnCount ) {
		m = SZ(A);
		n = SZ(A[0]);

		int res = m*n;
		REP(mask,TWO(n)) if (__builtin_popcount(mask) >= columnCount) {
			FOR(i,0,m) FOR(j,0,m) f[i][j] = INF;

			f[0][0] = 0;
			FOR(i,0,m/2-1) FOR(j,0,i*2) if (f[i][j] < INF) {
				string r1 = A[i];
				string r2 = A[m - i - 1];

				int cost0 = 0, cost1 = INF, cost2 = 0;

				// cost0 --> make sure palin columns
				REP(j,n) if (CONTAIN(mask,j)) {
					cost0 += equal(vector<char> {r1[j], r2[j]});
				}
				// cost1 --> make r1 palindrome?
				int cur = 0;
				for(int j1 = 0, j2 = n-1; j1 < j2; ++j1, --j2) {
					if (CONTAIN(mask,j1) && CONTAIN(mask,j2)) {
						cur += equal(vector<char> {r1[j1], r1[j2], r2[j1], r2[j2]});
					}
					else if (CONTAIN(mask,j1)) {
						cur += equal(vector<char> {r1[j1], r1[j2], r2[j1]});
					}
					else if (CONTAIN(mask,j2)) {
						cur += equal(vector<char> {r1[j1], r1[j2], r2[j2]});
					}
					else {
						cur += equal(vector<char> {r1[j1], r1[j2]});
					}
				}
				update(cost1, cur);
				cur = 0;
				for(int j1 = 0, j2 = n-1; j1 < j2; ++j1, --j2) {
					if (CONTAIN(mask,j1) && CONTAIN(mask,j2)) {
						cur += equal(vector<char> {r1[j1], r1[j2], r2[j1], r2[j2]});
					}
					else if (CONTAIN(mask,j1)) {
						cur += equal(vector<char> {r2[j1], r2[j2], r1[j1]});
					}
					else if (CONTAIN(mask,j2)) {
						cur += equal(vector<char> {r2[j1], r2[j2], r1[j2]});
					}
					else {
						cur += equal(vector<char> {r2[j1], r2[j2]});
					}
				}
				update(cost1, cur);
				
				// cost2 --> make sure both r1, r2 becomes palindrome, and palin columns
				for(int j1 = 0, j2 = n-1; j1 < j2; ++j1, --j2) {
					if (CONTAIN(mask,j1) || CONTAIN(mask,j2)) {
						cost2 += equal(vector<char> {r1[j1], r1[j2], r2[j1], r2[j2]});
					}
					else {
						cost2 += equal(vector<char> {r1[j1], r1[j2]})
							+ equal(vector<char> {r2[j1], r2[j2]});
					}
				}

				update(f[i+1][j], f[i][j] + cost0);
				update(f[i+1][j+1], f[i][j] + cost1);
				update(f[i+1][j+2], f[i][j] + cost2);
			}

			FOR(r,rowCount,m) update(res, f[m/2][r]);
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
			string A[]                = {"0000"
,"1000"
,"1100"
,"1110"};
			int rowCount              = 2;
			int columnCount           = 2;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string A[]                = {"0000"
,"1000"
,"1100"
,"1110"};
			int rowCount              = 3;
			int columnCount           = 2;
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string A[]                = {"01"
,"10"};
			int rowCount              = 1;
			int columnCount           = 1;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string A[]                = {"1110"
,"0001"};
			int rowCount              = 0;
			int columnCount           = 0;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string A[]                = {"01010101"
,"01010101"
,"01010101"
,"01010101"
,"01010101"
,"01010101"
,"01010101"
,"01010101"};
			int rowCount              = 2;
			int columnCount           = 3;
			int expected__            = 8;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string A[]                = {"000000000000"
,"011101110111"
,"010001010101"
,"010001010101"
,"011101010101"
,"010101010101"
,"010101010101"
,"011101110111"
,"000000000000"
,"000000000000"};
			int rowCount              = 5;
			int columnCount           = 9;
			int expected__            = 14;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string A[]                = {"11111101001110"
,"11000111111111"
,"00010101111001"
,"10110000111111"
,"10000011010010"
,"10001101101101"
,"00101010000001"
,"10111010100100"
,"11010011110111"
,"11100010110110"
,"00100101010100"
,"01001011001000"
,"01010001111010"
,"10100000010011"};
			int rowCount              = 6;
			int columnCount           = 8;
			int expected__            = 31;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 7: {
			string A[]                = {"00", "01", "00", "01"};
			int rowCount              = 4;
			int columnCount           = 2;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 8: {
			string A[]                = ;
			int rowCount              = ;
			int columnCount           = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string A[]                = ;
			int rowCount              = ;
			int columnCount           = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PalindromeMatrix().minChange(vector <string>(A, A + (sizeof A / sizeof A[0])), rowCount, columnCount);
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
