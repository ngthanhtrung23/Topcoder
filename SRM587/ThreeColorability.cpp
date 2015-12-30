// Div1 - 900
// Algo: greedy
// Observation:
// - If we fix the 1st row, then all remaining rows can either be equal to first row,
//   or equal to negate of first row
// Thus, we can fix the first row (one character at a time), and check if the board
// still satisfies.

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

vector<string> res, cells, empty;
int m, n;

string rev(string s) {
	string res = "";
	for(char c : s) {
		if (c == '?') res += '?';
		else res += (char) ('Z' + 'N' - c);
	}
	return res;
}

bool match(string a, string b) {
	REP(i,n) {
		if (a[i] == '?' || b[i] == '?') continue;
		if (a[i] != b[i]) return false;
	}
	return true;
}

bool xuoi[55], nguoc[55];
bool can() {
	FOR(i,1,m-1) xuoi[i] = nguoc[i] = true;
	REP(turn,n) {
		FOR(i,1,m-1) {
			REP(j,n) {
				if (res[i][j] == '?' || res[0][j] == '?') continue;

				if (res[i][j] != res[0][j]) xuoi[i] = false;
				if (res[i][j] == res[0][j]) nguoc[i] = false;
			}
			if (!xuoi[i] && !nguoc[i]) return false;
		}
		FOR(i1,1,m-1) FOR(i2,i1+1,m-1) {
			REP(j,n) {
				if (res[i1][j] == '?' || res[i2][j] == '?') continue;

				if (res[i1][j] == res[i2][j]) {
					if (!xuoi[i1]) xuoi[i2] = false;
					if (!xuoi[i2]) xuoi[i1] = false;

					if (!nguoc[i1]) nguoc[i2] = false;
					if (!nguoc[i2]) nguoc[i1] = false;
				}

				if (res[i1][j] != res[i2][j]) {
					if (!xuoi[i1]) nguoc[i2] = false;
					if (!xuoi[i2]) nguoc[i1] = false;

					if (!nguoc[i1]) xuoi[i2] = false;
					if (!nguoc[i2]) xuoi[i1] = false;
				}
			}
		}
		FOR(i,1,m-1) {
			if (!xuoi[i] && !nguoc[i]) return false;
		}
	}
	return true;
}

class ThreeColorability {
public:
    vector <string> lexSmallest( vector <string> cells ) {
		::cells = cells;

		m = SZ(cells);
		n = SZ(cells[0]);

		res = cells;
		if (!can()) return empty;

		// first row
		REP(j,n) {
			if (res[0][j] == '?') {
				res[0][j] = 'N';
				if (can()) continue;

				res[0][j] = 'Z';
				if (!can()) return empty;
			}
		}

		string a = res[0], b = rev(res[0]);
		string c = min(a, b);
		FOR(i,1,m-1) {
			bool can1 = match(res[i], a);
			bool can2 = match(res[i], b);
			if (can1 && can2) res[i] = c;
			else if (can1) res[i] = a;
			else res[i] = b;
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
	
	template<typename T> std::ostream& operator<<(std::ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }
	template<> std::ostream& operator<<(std::ostream &os, const vector<string> &v) { os << "{"; for (vector<string>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " \"" << *vi << "\""; } os << " }"; return os; }

	int verify_case(int casenum, const vector <string> &expected, const vector <string> &received, std::clock_t elapsed) { 
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
			string cells[]            = {"Z"};
			string expected__[]       = {"Z" };

			std::clock_t start__      = std::clock();
			vector <string> received__ = ThreeColorability().lexSmallest(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			string cells[]            = {"??", "?N"};
			string expected__[]       = {"NN", "NN" };

			std::clock_t start__      = std::clock();
			vector <string> received__ = ThreeColorability().lexSmallest(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			string cells[]            = {"ZZZ", "ZNZ"};
			string expected__[]       = { };

			std::clock_t start__      = std::clock();
			vector <string> received__ = ThreeColorability().lexSmallest(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			string cells[]            = {"N?N??NN","??ZN??Z","NN???Z?","ZZZ?Z??","Z???NN?","N?????N","ZZ?N?NN"};
			string expected__[]       = { };

			std::clock_t start__      = std::clock();
			vector <string> received__ = ThreeColorability().lexSmallest(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			string cells[]            = {"ZZZZ","ZZZZ","ZZZZ"};
			string expected__[]       = {"ZZZZ", "ZZZZ", "ZZZZ" };

			std::clock_t start__      = std::clock();
			vector <string> received__ = ThreeColorability().lexSmallest(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

      case 5: {
			string cells[]            = {"ZZN", "??Z"}	;
			string expected__[]       = {"ZZN", "NNZ"}	;

			std::clock_t start__      = std::clock();
			vector <string> received__ = ThreeColorability().lexSmallest(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
      case 6: {
			string cells[]            = {"N??N", "?ZZ?", "?ZNZ"};
			string expected__[]       = {};

			std::clock_t start__      = std::clock();
			vector <string> received__ = ThreeColorability().lexSmallest(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
      case 7: {
			string cells[]            = 	{"?ZZZN", "??Z?N", "NN?Z?", "ZZ?ZN"};
			string expected__[]       = {};

			std::clock_t start__      = std::clock();
			vector <string> received__ = ThreeColorability().lexSmallest(vector <string>(cells, cells + (sizeof cells / sizeof cells[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
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
