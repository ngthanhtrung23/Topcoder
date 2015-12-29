// Div1 - 1000
// Algo: Max flow
// - Construct a max-flow graph with:
//     - Nodes:
//         - Source s, Sink t
//         - M nodes for M horizontal lines
//         - N nodes for N horizontal lines
//         - cnt(#) nodes for each # cells
//     - Edges:
//         - cap(s, hor) = INF
//         - cap(ver, t) = INF
//         - When there are 2 # cells next to each other, connect them with cap = 1
//         - When there are 1 . cells and 1 # cell next to each other, connect
//           hor(i) and id(i, j) or ver(j) and id(i, j)
// - The flow can flow like following:
//     - S --> hor[i] --> go through some connected # cells --> ver[j] --> T
//     - A minimum cut will prevent all path of above type, which will effectively
//       equivalent to a board that have all cells covered by hor / ver lines

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

const int INF = 1000000000;
 
struct Edge {
    int a, b, cap, flow;
};

struct MaxFlow {
    int n, s, t;
    vector<int> d, ptr, q;
    vector< Edge > e;
    vector< vector<int> > g;

    MaxFlow(int n) : n(n), d(n), ptr(n), q(n), g(n) {
        e.clear();
        REP(i,n) {
            g[i].clear();
            ptr[i] = 0;
        }
    }

    void addEdge(int a, int b, int cap) {
        Edge e1 = { a, b, cap, 0 };
        Edge e2 = { b, a, 0, 0 };
        g[a].push_back( (int) e.size() );
        e.push_back(e1);
        g[b].push_back( (int) e.size() );
        e.push_back(e2);
    }
    int getMaxFlow(int _s, int _t) {
        s = _s; t = _t;
        int flow = 0;
        for (;;) {
            if (!bfs()) break;
            REP(i,n) ptr[i] = 0;
            while (int pushed = dfs(s, INF))
                flow += pushed;
        }
        return flow;
    }

private:
    bool bfs() {
        int qh = 0, qt = 0;
        q[qt++] = s;
        REP(i,n) d[i] = -1;
        d[s] = 0;

        while (qh < qt && d[t] == -1) {
            int v = q[qh++];
            REP(i,g[v].size()) {
                int id = g[v][i], to = e[id].b;
                if (d[to] == -1 && e[id].flow < e[id].cap) {
                    q[qt++] = to;
                    d[to] = d[v] + 1;
                }
            }
        }
        return d[t] != -1;
    }

    int dfs (int v, int flow) {
        if (!flow) return 0;
        if (v == t) return flow;
        for (; ptr[v] < (int)g[v].size(); ++ptr[v]) {
            int id = g[v][ptr[v]],
                to = e[id].b;
            if (d[to] != d[v] + 1) continue;
            int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
            if (pushed) {
                e[id].flow += pushed;
                e[id^1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
};

char a[55][55];
int m, n;

int id[55][55];
int hor[55], ver[55];

const int di[4] = {-1,1,0,0};
const int dj[4] = {0,0,-1,1};

class BoardPainting {
public:
    int minimalSteps( vector <string> target ) {
		m = SZ(target);
		n = SZ(target[0]);

		memset(a, '.', sizeof a);
		FOR(i,1,m) FOR(j,1,n) a[i][j] = target[i-1][j-1];

		int cur = 0;
		FOR(i,1,m) hor[i] = ++cur;
		FOR(j,1,n) ver[j] = ++cur;

		FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '#') {
			id[i][j] = ++cur;
		}
		int source = 0, sink = ++cur;
		MaxFlow flow(cur + 1);

		FOR(i,1,m) flow.addEdge(source, hor[i], 100111);
		FOR(j,1,n) flow.addEdge(ver[j], sink, 100111);

		FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '#') {
			REP(dir,4) {
				int ii = i + di[dir], jj = j + dj[dir];
				if (a[ii][jj] == '#') {
					int u = id[i][j], v = id[ii][jj];
					flow.addEdge(u, v, 1);
				}
				else {
					if (ii == i) {
						flow.addEdge(hor[i], id[i][j], 1);
					}
					if (jj == j) {
						flow.addEdge(id[i][j], ver[j], 1);
					}
				}
			}
		}

		return flow.getMaxFlow(source, sink) / 2;
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
			string target[]           = {"#####"};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string target[]           = {"#####",
 ".....",
 "#####",
 ".....",
 "#####"};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string target[]           = {"..#..",
 "..#..",
 "#####",
 "..#..",
 "..#.."};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string target[]           = {"#####",
 "..#..",
 "#####",
 "..#..",
 "#####"};
			int expected__            = 5;

			std::clock_t start__      = std::clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string target[]           = {".#.#.",
 "#####",
 ".#.#.",
 "#####",
 ".#.#."};
			int expected__            = 8;

			std::clock_t start__      = std::clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string target[]           = {".##.####.####.#########.##..",
 "##.#.####################.##",
 ".##.###.##.###.###.###.###..",
 "#..###..#########..###.##.##",
 "####..#######.#.#####.######",
 "##.######.#..#.#############",
 "##.######.###########.######",
 "#######.#######.#..###.#.###",
 "#####..#######.#####.#.###.#",
 "#..#################.#.####.",
 "##.######..#.#####.######.##",
 "..#.#############.#.##....#.",
 "....##..##..#.#####.#.###.##",
 "##.#########...#..#.#.######",
 "##.#..###########..#..####.#",
 "#.####.###.########.########",
 "#####.#########.##.##.######",
 ".##.####..###.###...######.#"};
			int expected__            = 88;

			std::clock_t start__      = std::clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string target[]           = {"...................."};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

        case 7: {
			string target[]           = {"##"};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 8: {
			string target[]           = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string target[]           = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = BoardPainting().minimalSteps(vector <string>(target, target + (sizeof target / sizeof target[0])));
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
