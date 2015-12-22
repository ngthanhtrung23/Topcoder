// Div1 - 500
// Algo: Greedy
// - First, notice that, there is optimal solution, in which each edge is switched
//   at most once. (if twice, then can remove it from solution & merge into 2 paths)
// - f(u) = <x, y>
//     - x = number of completed path in T(u)
//     - y = number of incompleted path in T(u), can be extended from u
// - To calculate f(u), just need to consider 3 cases:
//     - isImportant(e) = 1, initState(e) = 1 --> can not use the edge
//     - isImportant(e) = 1, initState(e) = 0 --> must use the edge (can either
//       extend path from v, or add new extendable path
//     - isImportant(e) = 0 --> can do whatever with this edge: can either ignore it
//       or extend a path from v
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

const int MN = 111;

vector< pair<int,int> > ke[MN];
int n;
pair<int,int> f[MN];
string initState, isImportant;

void dfs(int u, int fu) {
	f[u] = make_pair(0, 0);

	int up = 0;
	for(auto e : ke[u]) {
		int v = e.first;
		int id = e.second;
		if (v == fu) continue;

		dfs(v, u);

		if (isImportant[id] == '1') {
			if (initState[id] == '1') {
				f[u].first += f[v].first + f[v].second;
			}
			else {
				f[u].first += f[v].first;
				up += max(f[v].second, 1);
			}
		}
		else {
			f[u].first += f[v].first;
			up += f[v].second;
		}
	}
	f[u].first += up / 2;
	f[u].second = up % 2;
}

class TurnOnLamps {
public:
    int minimize( vector <int> roads, string initState, string isImportant ) {
		n = SZ(roads);
		REP(i,n) ke[i].clear();
		memset(f, -1, sizeof f);

		REP(i,n) {
			int u = i+1;
			int v = roads[i];
			ke[u].push_back(make_pair(v, i));
			ke[v].push_back(make_pair(u, i));
		}
		::initState = initState;
		::isImportant = isImportant;

		int res = 1e9;
		REP(i,n) {
			memset(f, -1, sizeof f);
			dfs(i, -1);
			res = min(res, f[i].first + f[i].second);
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
			int roads[]               = {0,0,1,1};
			string initState          = "0001";
			string isImportant        = "0111";
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = TurnOnLamps().minimize(vector <int>(roads, roads + (sizeof roads / sizeof roads[0])), initState, isImportant);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int roads[]               = {0,0,1,1};
			string initState          = "0000";
			string isImportant        = "0111";
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = TurnOnLamps().minimize(vector <int>(roads, roads + (sizeof roads / sizeof roads[0])), initState, isImportant);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int roads[]               = {0,0,1,1,4,4};
			string initState          = "000100";
			string isImportant        = "111111";
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = TurnOnLamps().minimize(vector <int>(roads, roads + (sizeof roads / sizeof roads[0])), initState, isImportant);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int roads[]               = {0,0,1,1,4,4};
			string initState          = "100100";
			string isImportant        = "011101";
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = TurnOnLamps().minimize(vector <int>(roads, roads + (sizeof roads / sizeof roads[0])), initState, isImportant);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int roads[]               = {0,0,2,2,3,1,6,3,1};
			string initState          = "010001110";
			string isImportant        = "000110100";
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = TurnOnLamps().minimize(vector <int>(roads, roads + (sizeof roads / sizeof roads[0])), initState, isImportant);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int roads[]               = {0,0,1,2,4,4,6,1,2,5,2,8,8,3,6,4,14,7,18,14,11,7,1,12,7,5,18,23,0,14,11,10,2,2,6,1,30,11,9,12,5,35,25,11,23,17,14,45,15};
			string initState          = "0000000000010000000000000010000010100000000000000";
			string isImportant        = "1010111111111011011111000110111111111111111110111";
			int expected__            = 14;

			std::clock_t start__      = std::clock();
			int received__            = TurnOnLamps().minimize(vector <int>(roads, roads + (sizeof roads / sizeof roads[0])), initState, isImportant);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int roads[]               = ;
			string initState          = ;
			string isImportant        = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TurnOnLamps().minimize(vector <int>(roads, roads + (sizeof roads / sizeof roads[0])), initState, isImportant);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int roads[]               = ;
			string initState          = ;
			string isImportant        = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TurnOnLamps().minimize(vector <int>(roads, roads + (sizeof roads / sizeof roads[0])), initState, isImportant);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int roads[]               = ;
			string initState          = ;
			string isImportant        = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = TurnOnLamps().minimize(vector <int>(roads, roads + (sizeof roads / sizeof roads[0])), initState, isImportant);
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
