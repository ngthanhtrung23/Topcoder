// Div1 - 450
// Algo:
// - First, notice that if we can ignore the restriction that all chosen gears rotate.
//   If all gears of same color rotate in same direction, that this condition is
//   already satisfied.
// - Now, assume that we fix direction of each color, then if 2 gears connect to each
//   other and their direction does not match, we can't choose both gear at the
//   same time
// --> maximum independent set.
// 
// - Since graph is bipartite (no 2 gears of same color are connected), we can solve
//   using max matching

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

const int inf = 1000111;
struct Matching {
    int n;
    vector<int> matchL, matchR, dist;
    vector<bool> seen;
    vector< vector<int> > ke;

    Matching(int n) : n(n), matchL(n+1), matchR(n+1), dist(n+1), seen(n+1, false), ke(n+1) {}

    void addEdge(int u, int v) {
        ke[u].push_back(v);
    }

    bool bfs() {
        queue<int> qu;
        for(int u = 1; u <= n; ++u)
            if (!matchL[u]) {
                dist[u] = 0;
                qu.push(u);
            } else dist[u] = inf;
        dist[0] = inf;

        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            for(__typeof(ke[u].begin()) v = ke[u].begin(); v != ke[u].end(); ++v) {
                if (dist[matchR[*v]] == inf) {
                    dist[matchR[*v]] = dist[u] + 1;
                    qu.push(matchR[*v]);
                }
            }
        }
        return dist[0] != inf;
    }

    bool dfs(int u) {
        if (u) {
            for(__typeof(ke[u].begin()) v = ke[u].begin(); v != ke[u].end(); ++v)
                if (dist[matchR[*v]] == dist[u] + 1 && dfs(matchR[*v])) {
                    matchL[u] = *v;
                    matchR[*v] = u;
                    return true;
                }
            dist[u] = inf;
            return false;
        }
        return true;
    }

    int match() {
        int res = 0;
        while (bfs()) {
            for(int u = 1; u <= n; ++u)
                if (!matchL[u])
                    if (dfs(u)) ++res;
        }
        return res;
    }
};

int n;

int colorId(char c) {
	if (c == 'R') return 0;
	if (c == 'G') return 1;
	return 2;
}

int rotate(int c, int bad, int turn) {
	if (c == bad) return turn;
	if (c == (bad + 1) % 3) return 0;
	return 1;
}

class GearsDiv1 {
public:
    int getmin( string color, vector <string> graph ) {
		n = SZ(color);
		int res = n;
		REP(bad,3) {
			REP(turn,2) {
				Matching mat(n);
				REP(i,n) REP(j,n) if (graph[i][j] == 'Y') {
					int ci = colorId(color[i]);
					int cj = colorId(color[j]);

					int roti = rotate(ci, bad, turn);
					int rotj = rotate(cj, bad, turn);

					if (roti == rotj) {
						if (ci == bad) mat.addEdge(i+1, j+1);
						else mat.addEdge(j+1, i+1);
					}
				}
				int cur = mat.match();
				res = min(res, cur);
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
			string color              = "RGB";
			string graph[]            = {"NYY","YNY","YYN"};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string color              = "RGBR";
			string graph[]            = {"NNNN","NNNN","NNNN","NNNN"};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string color              = "RGBR";
			string graph[]            = {"NYNN","YNYN","NYNY","NNYN"};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string color              = "RRRRRGRRBGRRGBBGGGBRRRGBRGRRGG";
			string graph[]            = {"NNNNNYNNNYNNYNNNYNNNNNNNNYNNYY",
 "NNNNNNNNYNNNYNYNNYNNNNYNNYNNYY",
 "NNNNNYNNNNNNNNNNNNYNNNNNNYNNNY",
 "NNNNNNNNNYNNYNNYYYNNNNYNNYNNNN",
 "NNNNNNNNNYNNYNNYYYNNNNYNNNNNNN",
 "YNYNNNYYYNNYNYYNNNNNYYNYNNYYNN",
 "NNNNNYNNNNNNNNNYYYNNNNYNNYNNYY",
 "NNNNNYNNNNNNNNNYNNNNNNNNNNNNYN",
 "NYNNNYNNNYNNYNNYYYNNNNYNNYNNYY",
 "YNNYYNNNYNNNNYYNNNYNYYNYNNNNNN",
 "NNNNNNNNNNNNYNNYNYNNNNYNNNNNNY",
 "NNNNNYNNNNNNYNNYYYNNNNNNNNNNYN",
 "YYNYYNNNYNYYNYYNNNYNYNNYNNNNNN",
 "NNNNNYNNNYNNYNNYYYNNNNYNNYNYYY",
 "NYNNNYNNNYNNYNNYYYNNNNYNNYNNYY",
 "NNNYYNYYYNYYNYYNNNYNYNNYYNYYNN",
 "YNNYYNYNYNNYNYYNNNYNNNNYYNNYNN",
 "NYNYYNYNYNYYNYYNNNNYYNNYYNYNNN",
 "NNYNNNNNNYNNYNNYYNNNNNYNNYNNNY",
 "NNNNNNNNNNNNNNNNNYNNNNYNNYNNNY",
 "NNNNNYNNNYNNYNNYNYNNNNYNNNNNYY",
 "NNNNNYNNNYNNNNNNNNNNNNYNNNNNNN",
 "NYNYYNYNYNYNNYYNNNYYYYNYYNYNNN",
 "NNNNNYNNNYNNYNNYYYNNNNYNNNNNNY",
 "NNNNNNNNNNNNNNNYYYNNNNYNNYNNYY",
 "YYYYNNYNYNNNNYYNNNYYNNNNYNYYNN",
 "NNNNNYNNNNNNNNNYNYNNNNYNNYNNYN",
 "NNNNNYNNNNNNNYNYYNNNNNNNNYNNYY",
 "YYNNNNYYYNNYNYYNNNNNYNNNYNYYNN",
 "YYYNNNYNYNYNNYYNNNYYYNNYYNNYNN"};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string color              = ;
			string graph[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string color              = ;
			string graph[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string color              = ;
			string graph[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = GearsDiv1().getmin(color, vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
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
