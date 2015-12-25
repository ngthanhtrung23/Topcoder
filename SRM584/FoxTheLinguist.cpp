// Div1 - 900
// Algo: Directed MST
// - Build graph with the following vertices:
//     - Root
//     - For each language, 10 vertices for 10 level
// - Edges:
//     - Root --> level 0 of each language, cost = 0
//     - Each language: level i --> level i-1, cost = 0
//     - Each course: edge between 2 corresponding vertices
// - Optimal solution == minimum directed MST

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

const int maxe = 100111;
const int maxv = 1011;

// Index from 0
// Running time O(E*V)
namespace chuliu {
    struct Cost;
    vector<Cost> costlist;

    struct Cost {
        int id, val, used, a, b, pos;
        Cost() { val = -1; used = 0; }
        Cost(int _id, int _val, bool temp) {
            a = b = -1; id = _id; val = _val; used = 0;
            pos = costlist.size(); costlist.push_back(*this);
        }
        Cost(int _a, int _b) {
            a = _a; b = _b; id = -1; val = costlist[a].val - costlist[b].val; 
            used = 0; pos = costlist.size(); costlist.push_back(*this);
        }
        void push() {
            if (id == -1) {
                costlist[a].used += used;
                costlist[b].used -= used;
            }
        }
    };

    struct Edge {
        int u, v;
        Cost cost;
        Edge() {}
        Edge(int id, int _u, int _v, int c) {
            u = _u; v = _v; cost = Cost(id, c, 0);
        }
    } edge[maxe];

    int n, m, root, pre[maxv], node[maxv], vis[maxv], best[maxv];

    void init(int _n) {
        n = _n; m = 0;
        costlist.clear();
    }

    void add(int id, int u, int v, int c) {
        edge[m++] = Edge(id, u, v, c);
    }

    int mst(int root) {
        int ret = 0;

        while (true) {
            REP(i, n) best[i] = -1;

            REP(e, m) {
                int u = edge[e].u, v = edge[e].v;
                if ((best[v] == -1 || edge[e].cost.val < costlist[best[v]].val) && u != v) {
                    pre[v] = u;
                    best[v] = edge[e].cost.pos;
                }
            }

            REP(i, n) if (i != root && best[i] == -1) return -1;

            int cntnode = 0;
            memset(node, -1, sizeof node); memset(vis, -1, sizeof vis);

            REP(i, n) if (i != root) {
                ret += costlist[best[i]].val;
                costlist[best[i]].used++;

                int v = i;
                while (vis[v] != i && node[v] == -1 && v != root) {
                    vis[v] = i;
                    v = pre[v];
                }

                if (v != root && node[v] == -1) {
                    for (int u = pre[v]; u != v; u = pre[u]) node[u] = cntnode;
                    node[v] = cntnode++;
                }
            }

            if (cntnode == 0) break;

            REP(i, n) if (node[i] == -1) node[i] = cntnode++;

            REP(e, m) {
                int v = edge[e].v;
                edge[e].u = node[edge[e].u];
                edge[e].v = node[edge[e].v];
                if (edge[e].u != edge[e].v) edge[e].cost = Cost(edge[e].cost.pos, best[v]);
            }

            n = cntnode;
            root = node[root];
        }

        return ret;
    }

    vector<int> trace() {
        vector<int> ret;
        FORD(i, costlist.size()-1,0) costlist[i].push();
        REP(i, costlist.size()) {
            Cost cost = costlist[i];
            if (cost.id != -1 && cost.used > 0) ret.push_back(cost.id);
        }
        return ret;
    }
}

int id[11][11];

class FoxTheLinguist {
public:
    int minimalHours( int n, vector <string> courseInfo ) {
		int root = 0, cnt = 1;
		FOR(i,1,n) {
			FOR(j,0,9) id[i][j] = cnt++;
		}
		chuliu::init(cnt);
		int m = 0;
		// up edge
		FOR(i,1,n) {
			chuliu::add(m++, 0, id[i][0], 0);

			FOR(j,1,9)
				chuliu::add(m++, id[i][j], id[i][j-1], 0);
		}
		string all = "";
		for(string s : courseInfo) all += s;
		stringstream ss(all);
		string t;
		while (ss >> t) {
			stringstream ss2(t);
			char c1, c2, t;
			int l1, l2;
			int cost;
			ss2 >> c1 >> l1 >> t >> t >> c2 >> l2 >> t >> cost;

			int i1 = c1 - 'A' + 1;
			int i2 = c2 - 'A' + 1;

			chuliu::add(m++, id[i1][l1], id[i2][l2], cost);
		}
		return chuliu::mst(0);
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
			int n                     = 1;
			string courseInfo[]       = {"A0->A9:1000 A0->A6:0300 A3->A9:0600"};
			int expected__            = 900;

			std::clock_t start__      = std::clock();
			int received__            = FoxTheLinguist().minimalHours(n, vector <string>(courseInfo, courseInfo + (sizeof courseInfo / sizeof courseInfo[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 2;
			string courseInfo[]       = {"A0->A9:1000 B0->B9:1000 A1->B9:0300 B1->A9:0200"};
			int expected__            = 1200;

			std::clock_t start__      = std::clock();
			int received__            = FoxTheLinguist().minimalHours(n, vector <string>(courseInfo, courseInfo + (sizeof courseInfo / sizeof courseInfo[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 3;
			string courseInfo[]       = {"C0->A6:00", "01 A3", "->B9:0001 A3->C6:000", "1",
" C3->A9:0001 A9->C9:0001 A0->A9:9999",
" B0->B9:9999 C0->C9:9999 A6->A9:9999"};
			int expected__            = 5;

			std::clock_t start__      = std::clock();
			int received__            = FoxTheLinguist().minimalHours(n, vector <string>(courseInfo, courseInfo + (sizeof courseInfo / sizeof courseInfo[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 4;
			string courseInfo[]       = {"A0->A6:6666 A0->A9:9999",
" B0->B6:6666 B0->B9:9999",
" C0->C6:6666 C0->C9:9999",
" D0->D6:6666 D0->D9:9999",
" A6->B6:0666 B6->C6:0666",
" C6->D6:0666 D6->A6:0666",
" A9->B9:0099 B9->C9:0099",
" C9->D9:0099 D9->A9:0099"};
			int expected__            = 10296;

			std::clock_t start__      = std::clock();
			int received__            = FoxTheLinguist().minimalHours(n, vector <string>(courseInfo, courseInfo + (sizeof courseInfo / sizeof courseInfo[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int n                     = 1;
			string courseInfo[]       = {"A0->A9:9999 A0->A9:8888"};
			int expected__            = 8888;

			std::clock_t start__      = std::clock();
			int received__            = FoxTheLinguist().minimalHours(n, vector <string>(courseInfo, courseInfo + (sizeof courseInfo / sizeof courseInfo[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int n                     = 1;
			string courseInfo[]       = {"A9->A9:0000",
" A9->A0:0000"};
			int expected__            = -1;

			std::clock_t start__      = std::clock();
			int received__            = FoxTheLinguist().minimalHours(n, vector <string>(courseInfo, courseInfo + (sizeof courseInfo / sizeof courseInfo[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int n                     = ;
			string courseInfo[]       = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = FoxTheLinguist().minimalHours(n, vector <string>(courseInfo, courseInfo + (sizeof courseInfo / sizeof courseInfo[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int n                     = ;
			string courseInfo[]       = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = FoxTheLinguist().minimalHours(n, vector <string>(courseInfo, courseInfo + (sizeof courseInfo / sizeof courseInfo[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int n                     = ;
			string courseInfo[]       = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = FoxTheLinguist().minimalHours(n, vector <string>(courseInfo, courseInfo + (sizeof courseInfo / sizeof courseInfo[0])));
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
