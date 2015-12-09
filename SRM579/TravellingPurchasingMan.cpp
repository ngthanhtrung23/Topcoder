// Div1 - 450
// Algo:
// - DP: f(S, x) = minimum cost to buy from all shops in set S & last shop is x
//     - Update: f(S, x) --> f(S + {y}, y)
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

const int MN = 55;
#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int c[MN][MN], n;
int f[TWO(16)][22];
int k, open[MN], close[MN], duration[MN];

void initStores(vector<string> interestingStores) {
	k = SZ(interestingStores);
	REP(i,k) {
		stringstream ss(interestingStores[i]);
		ss >> open[i] >> close[i] >> duration[i];
	}
}

void initGraph(vector<string> roads) {
	REP(i,n) REP(j,n) {
		c[i][j] = (i == j) ? 0 : 1e9;
	}
	REP(i,SZ(roads)) {
		stringstream ss(roads[i]);
		int u, v, l; ss >> u >> v >> l;
		c[u][v] = min(c[u][v], l);
		c[v][u] = c[u][v];
	}
	REP(k,n) REP(i,n) REP(j,n)
		c[i][j] = min(c[i][j], c[i][k] + c[k][j]);
}

const int INF = 1e9;

void update(int& x, int val) {
	x = min(x, val);
}
class TravellingPurchasingMan {
public:
    int maxStores( int N, vector <string> interestingStores, vector <string> roads ) {
		n = N;
		initStores(interestingStores);
		initGraph(roads);

		int res = 0;
		REP(mask,TWO(k)) REP(i,k) f[mask][i] = INF;
		REP(i,k) {
			int arrive = c[n-1][i];
			if (arrive <= close[i]) {
				f[TWO(i)][i] = max(open[i], arrive) + duration[i];
			}
		}
		REP(mask,TWO(k)) REP(last,k) if (f[mask][last] < INF) {
			res = max(res, __builtin_popcount(mask));
			REP(next,k) if (!CONTAIN(mask,next)) {
				int arrive = f[mask][last] + c[last][next];
				if (arrive <= close[next]) {
					update(f[mask + TWO(next)][next], max(open[next], f[mask][last] + c[last][next]) + duration[next]);
				}
			}
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
			int N                     = 3;
			string interestingStores[] = {"1 10 10" , "1 55 31", "10 50 100" };
			string roads[]            = {"1 2 10"};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = TravellingPurchasingMan().maxStores(N, vector <string>(interestingStores, interestingStores + (sizeof interestingStores / sizeof interestingStores[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 3;
			string interestingStores[] = {"1 10 10" , "1 55 30", "10 50 100" };
			string roads[]            = {"1 2 10"};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = TravellingPurchasingMan().maxStores(N, vector <string>(interestingStores, interestingStores + (sizeof interestingStores / sizeof interestingStores[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 5;
			string interestingStores[] = {"0 1000 17"};
			string roads[]            = {"2 3 400", "4 1 500", "4 3 300", "1 0 700", "0 2 400"};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = TravellingPurchasingMan().maxStores(N, vector <string>(interestingStores, interestingStores + (sizeof interestingStores / sizeof interestingStores[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 3: {
			int N                     = ;
			string interestingStores[] = ;
			string roads[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TravellingPurchasingMan().maxStores(N, vector <string>(interestingStores, interestingStores + (sizeof interestingStores / sizeof interestingStores[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 4: {
			int N                     = ;
			string interestingStores[] = ;
			string roads[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TravellingPurchasingMan().maxStores(N, vector <string>(interestingStores, interestingStores + (sizeof interestingStores / sizeof interestingStores[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int N                     = ;
			string interestingStores[] = ;
			string roads[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TravellingPurchasingMan().maxStores(N, vector <string>(interestingStores, interestingStores + (sizeof interestingStores / sizeof interestingStores[0])), vector <string>(roads, roads + (sizeof roads / sizeof roads[0])));
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
