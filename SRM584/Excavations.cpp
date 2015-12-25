// Div1 - 600
// Algo:
// Consider 2 cases:
// - All the kinds of the excavated buildings are in `found`.
//     - In this case, the max depth D can be any value, and we just need to count
//       the number of different sets
//     - Let xi = number of buildings of i-th kind that we excavated, then:
//     - sum(xi) = K
//     - 1 <= xi <= number of buildings of i-th kind (let's call this cnt[i])
//     - The result is sum( C(cnt[i], x[i]) ) over all possible sets x[i], which
//       can be calculated using simple DP
// - There is at least 1 of the excavated sites which is a building of not found type
//     - Let `bad` be the 1st excavated site, that is not in found
//     - We can excavate other sites with depth > depth[bad] (broken ties by index)
//     - Now we can transform the problem to same problem above, but some types of
//       building have lower bound 0

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

bool isFound[55];
ll f[111][111];
ll c[55][55];

int cnt[111], lb[111];

ll solve(int K) {
	memset(f, 0, sizeof f);
	f[0][0] = 1;

	FOR(i,0,99) FOR(j,0,K)
		if (f[i][j]) {
			FOR(add,lb[i+1],cnt[i+1]) {
				f[i+1][j+add] += f[i][j] * c[cnt[i+1]][add];
			}
		}
	return f[100][K];
}

class Excavations {
public:
    long long count( vector <int> kind, vector <int> depth, vector <int> found, int K ) {
		FOR(i,0,50) {
			FOR(j,0,i) {
				if (j == 0) c[i][j] = 1;
				else c[i][j] = c[i-1][j] + c[i-1][j-1];
			}
		}

		int n = SZ(kind);

		memset(isFound, 0, sizeof isFound);
		for(int x : found) isFound[x] = true;

		ll res = 0;
		// no bad building
		memset(lb, 0, sizeof lb);
		FOR(i,1,50) if (isFound[i]) lb[i] = 1;

		memset(cnt, 0, sizeof cnt);
		REP(i,n) if (isFound[kind[i]]) {
			cnt[kind[i]]++;
		}
//		cout << "No bad" << endl;
		res += solve(K);

		// first bad building is `bad`
		REP(bad,n) if (!isFound[kind[bad]]) {
//			DEBUG(bad);
			int D = depth[bad];
			memset(cnt, 0, sizeof cnt);
			REP(i,n) {
				if (isFound[kind[i]]) {
					if (depth[i] < D) {
						cnt[kind[i]] += 1;
					}
					else {
						cnt[kind[i] + 50] += 1;
					}
				}
				else {
					if (make_pair(depth[i], i) > make_pair(depth[bad], bad)) {
						cnt[kind[i]] += 1;
					}
				}
			}
			res += solve(K - 1);
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
	
	int verify_case(int casenum, const long long &expected, const long long &received, std::clock_t elapsed) { 
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
			int kind[]                = {1, 1, 2, 2};
			int depth[]               = {10, 15, 10, 20};
			int found[]               = {1};
			int K                     = 2;
			long long expected__      = 3;

			std::clock_t start__      = std::clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int kind[]                = {1, 1, 2, 2};
			int depth[]               = {10, 15, 10, 20};
			int found[]               = {1, 2};
			int K                     = 2;
			long long expected__      = 4;

			std::clock_t start__      = std::clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int kind[]                = {1, 2, 3, 4};
			int depth[]               = {10, 10, 10, 10};
			int found[]               = {1, 2};
			int K                     = 3;
			long long expected__      = 0;

			std::clock_t start__      = std::clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int kind[]                = {1, 2, 2, 3, 1, 3, 2, 1, 2};
			int depth[]               = {12512, 12859, 125, 1000, 99, 114, 125, 125, 114};
			int found[]               = {1, 2, 3};
			int K                     = 7;
			long long expected__      = 35;

			std::clock_t start__      = std::clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int kind[]                = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50};
			int depth[]               = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3};
			int found[]               = {50};
			int K                     = 18;
			long long expected__      = 9075135300LL;

			std::clock_t start__      = std::clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int kind[]                = ;
			int depth[]               = ;
			int found[]               = ;
			int K                     = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int kind[]                = ;
			int depth[]               = ;
			int found[]               = ;
			int K                     = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int kind[]                = ;
			int depth[]               = ;
			int found[]               = ;
			int K                     = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = Excavations().count(vector <int>(kind, kind + (sizeof kind / sizeof kind[0])), vector <int>(depth, depth + (sizeof depth / sizeof depth[0])), vector <int>(found, found + (sizeof found / sizeof found[0])), K);
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
