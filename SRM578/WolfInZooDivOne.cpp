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

const int MN = 311;
const int MOD = 1e9 + 7;

ll f[MN][MN];

#define left left___
#define right right___
int left[MN], right[MN];
bool bad[MN][MN];

void add(ll& res, ll x) {
	res = (res + x) % MOD;
}

class WolfInZooDivOne {
public:
    int count( int N, vector <string> L, vector <string> R ) {
		ll res = 0;
		add(res, 1); // place 0
		add(res, N); // place 1

		string all = ""; for(string s : L) all += s;
		stringstream ss1(all);
		int k = 0, x;
		while (ss1 >> x) left[++k] = x + 1;
		k = 0;
		all = ""; for(string s : R) all += s;
		stringstream ss2(all);
		while (ss2 >> x) right[++k] = x + 1;

		memset(bad, 0, sizeof bad);
		FOR(i,1,k) {
			FOR(x,left[i],right[i])
				FOR(y,x,right[i])
					bad[x][y] = true;
		}

		memset(f, 0, sizeof f);
		FOR(x,1,N) FOR(y,x+1,N) {
			add(f[x][y], 1);
			FOR(z,y+1,N)
				if (!bad[x][z])
					add(f[y][z], f[x][y]);

			add(res, f[x][y]);
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
			int N                     = 5;
			string L[]                = {"0"};
			string R[]                = {"4"};
			int expected__            = 16;

			std::clock_t start__      = std::clock();
			int received__            = WolfInZooDivOne().count(N, vector <string>(L, L + (sizeof L / sizeof L[0])), vector <string>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 5;
			string L[]                = {"0 1"};
			string R[]                = {"2 4"};
			int expected__            = 21;

			std::clock_t start__      = std::clock();
			int received__            = WolfInZooDivOne().count(N, vector <string>(L, L + (sizeof L / sizeof L[0])), vector <string>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 10;
			string L[]                = {"0 4 2 7"};
			string R[]                = {"3 9 5 9"};
			int expected__            = 225;

			std::clock_t start__      = std::clock();
			int received__            = WolfInZooDivOne().count(N, vector <string>(L, L + (sizeof L / sizeof L[0])), vector <string>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 100;
			string L[]                = {"0 2 2 7 10 1","3 16 22 30 33 38"," 42 44 49 51 57 60 62"," 65 69 72 74 77 7","8 81 84 88 91 93 96"};
			string R[]                = {"41 5 13 22 12 13 ","33 41 80 47 40 ","4","8 96 57 66 ","80 60 71 79"," 70 77 ","99"," 83 85 93 88 89 97 97 98"};
			int expected__            = 6419882;

			std::clock_t start__      = std::clock();
			int received__            = WolfInZooDivOne().count(N, vector <string>(L, L + (sizeof L / sizeof L[0])), vector <string>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int N                     = ;
			string L[]                = ;
			string R[]                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = WolfInZooDivOne().count(N, vector <string>(L, L + (sizeof L / sizeof L[0])), vector <string>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int N                     = ;
			string L[]                = ;
			string R[]                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = WolfInZooDivOne().count(N, vector <string>(L, L + (sizeof L / sizeof L[0])), vector <string>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int N                     = ;
			string L[]                = ;
			string R[]                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = WolfInZooDivOne().count(N, vector <string>(L, L + (sizeof L / sizeof L[0])), vector <string>(R, R + (sizeof R / sizeof R[0])));
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
