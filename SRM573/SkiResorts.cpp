// Div 1 - 450
// Algo: Dijkstra
// - Build graph (u, x): current at vertex u, height = c(x)
// - Can go from (u, x) to (v, y) if road(u, v) = Y and x >= y

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

ll f[55][55];
ll c[55], nc;

class SkiResorts {
public:
    long long minCost( vector <string> road, vector <int> altitude ) {
		nc = 0;
		for(int x : altitude) {
			c[++nc] = x;
		}
		sort(c+1, c+nc+1);
		nc = unique(c+1, c+nc+1) - c - 1;

		set< pair<ll, pair<int,int> > > all;
		int n = SZ(road);

		REP(i,n) FOR(j,0,nc) f[i][j] = 1000111000111000111LL;

		FOR(i,1,nc) {
			f[0][i] = abs(altitude[0] - c[i]);
			all.insert(make_pair(f[0][i], make_pair(0, i)));
		}

		while (!all.empty()) {
			ll l = all.begin()->first;
			int u = all.begin()->second.first;
			int x = all.begin()->second.second;
			all.erase(all.begin());

			if (l != f[u][x]) continue;

			if (u == n-1) return l;

			REP(v,n) if (road[u][v] == 'Y') {
				FOR(y,1,x) {
					ll cur = l + abs(altitude[v] - c[y]);
					if (f[v][y] > cur) {
						f[v][y] = cur;
						all.insert(make_pair(cur, make_pair(v, y)));
					}
				}
			}
		}
		return -1;
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
			string road[]             = {"NYN",
 "YNY",
 "NYN"};
			int altitude[]            = {30, 20, 10};
			long long expected__      = 0;

			std::clock_t start__      = std::clock();
			long long received__      = SkiResorts().minCost(vector <string>(road, road + (sizeof road / sizeof road[0])), vector <int>(altitude, altitude + (sizeof altitude / sizeof altitude[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string road[]             = {"NY",
 "YN"};
			int altitude[]            = {10, 20};
			long long expected__      = 10;

			std::clock_t start__      = std::clock();
			long long received__      = SkiResorts().minCost(vector <string>(road, road + (sizeof road / sizeof road[0])), vector <int>(altitude, altitude + (sizeof altitude / sizeof altitude[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string road[]             = {"NYN",
 "YNN",
 "NNN"};
			int altitude[]            = {573, 573, 573};
			long long expected__      = -1;

			std::clock_t start__      = std::clock();
			long long received__      = SkiResorts().minCost(vector <string>(road, road + (sizeof road / sizeof road[0])), vector <int>(altitude, altitude + (sizeof altitude / sizeof altitude[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string road[]             = {"NNYNNYYYNN",
 "NNNNYNYNNN",
 "YNNNNYYNNN",
 "NNNNNNYNYY",
 "NYNNNNNNYY",
 "YNYNNNNYNN",
 "YYYYNNNYNN",
 "YNNNNYYNNN",
 "NNNYYNNNNN",
 "NNNYYNNNNN"};
			int altitude[]            = {7, 4, 13, 2, 8, 1, 8, 15, 5, 15};
			long long expected__      = 12;

			std::clock_t start__      = std::clock();
			long long received__      = SkiResorts().minCost(vector <string>(road, road + (sizeof road / sizeof road[0])), vector <int>(altitude, altitude + (sizeof altitude / sizeof altitude[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string road[]             = ;
			int altitude[]            = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = SkiResorts().minCost(vector <string>(road, road + (sizeof road / sizeof road[0])), vector <int>(altitude, altitude + (sizeof altitude / sizeof altitude[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string road[]             = ;
			int altitude[]            = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = SkiResorts().minCost(vector <string>(road, road + (sizeof road / sizeof road[0])), vector <int>(altitude, altitude + (sizeof altitude / sizeof altitude[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string road[]             = ;
			int altitude[]            = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = SkiResorts().minCost(vector <string>(road, road + (sizeof road / sizeof road[0])), vector <int>(altitude, altitude + (sizeof altitude / sizeof altitude[0])));
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
