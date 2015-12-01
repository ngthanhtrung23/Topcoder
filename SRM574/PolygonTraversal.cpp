// Div 1 - 450
// Algo: Basic DP
// - Let f(S, u) = number of ways going through all vertices in S, last vertex = u
// - Transition: f(S, u) --> f(S + {v}, v) if:
//     - v is not in S
//     - v is not neighbor of u
//     - on both half circle u --> v and v --> u, there are some vertex in S
// - Complexity: O(2^N * N^2)

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

ll f[TWO(18)][20];
int has[20];

#define next next___
#define prev prev___

int n;
int next(int u) {
	return (u + 1) % n;
}
int prev(int u) {
	return (u + n - 1) % n;
}

bool good(int u, int v) {
	if (v == next(u)) return false;
	if (v == prev(u)) return false;

	if (u > v) swap(u, v);
	int left = has[v-1] - has[u];
	int right = has[n-1] - has[v] + has[u-1];
	return left > 0 && right > 0;
}

class PolygonTraversal {
public:
    long long count( int N, vector <int> points ) {
		n = N;
		for(int& x : points) --x;

		memset(f, 0, sizeof f);
		int start = 0;
		for(int x : points) start += TWO(x);
		f[start][points.back()] = 1;

		for(int s = start; s < TWO(N); ++s)
			REP(u,N) {
				if (f[s][u] == 0) continue;

				REP(i,N) if (CONTAIN(s,i)) has[i] = 1; else has[i] = 0;
				REP(i,N) if (i > 0) has[i] += has[i-1];

				REP(v,N) if (v != u && !CONTAIN(s,v)) {
					if (good(u, v)) {
						f[TWO(v) + s][v] += f[s][u];
					}
				}
			}

		ll res = 0;
		int from = points[0];
		REP(u,N) {
			if (f[TWO(N)-1][u] && u != from && u != next(from) && u != prev(from)) {
				res += f[TWO(N) - 1][u];
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
			int N                     = 5;
			int points[]              = {1, 3, 5};
			long long expected__      = 1;

			std::clock_t start__      = std::clock();
			long long received__      = PolygonTraversal().count(N, vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 6;
			int points[]              = {1, 4, 2};
			long long expected__      = 1;

			std::clock_t start__      = std::clock();
			long long received__      = PolygonTraversal().count(N, vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 7;
			int points[]              = {2, 4, 7};
			long long expected__      = 2;

			std::clock_t start__      = std::clock();
			long long received__      = PolygonTraversal().count(N, vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 7;
			int points[]              = {1, 2, 3, 4, 6, 5};
			long long expected__      = 0;

			std::clock_t start__      = std::clock();
			long long received__      = PolygonTraversal().count(N, vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 18;
			int points[]              = {1, 7, 18};
			long long expected__      = 4374612736LL;

			std::clock_t start__      = std::clock();
			long long received__      = PolygonTraversal().count(N, vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int N                     = ;
			int points[]              = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = PolygonTraversal().count(N, vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int N                     = ;
			int points[]              = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = PolygonTraversal().count(N, vector <int>(points, points + (sizeof points / sizeof points[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int N                     = ;
			int points[]              = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = PolygonTraversal().count(N, vector <int>(points, points + (sizeof points / sizeof points[0])));
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
