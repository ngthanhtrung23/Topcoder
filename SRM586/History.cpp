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

struct Dyn {
	vector< pair<int,int> > monarch;
} dyn[111];
int n;

int lb[111][111], ub[111][111];

void parseSingle(const string& s, pair<int,int>& a) {
	char c;
	sscanf(s.c_str(), "%c%d", &c, &a.second);
	a.first = c - 'A';
}

void parse(const string& s, pair<int,int>& a, pair<int,int>& b) {
	string left = s.substr(0, s.find('-'));
	string right = s.substr(s.find('-') + 1);

	parseSingle(left, a);
	parseSingle(right, b);
}

class History {
public:
    string verifyClaims( vector <string> dynasties, vector <string> battles, vector <string> queries ) {
		n = SZ(dynasties);
		REP(i,n) {
			stringstream ss(dynasties[i]);
			vector<int> cur;
			int t;
			while (ss >> t) cur.push_back(t);

			dyn[i].monarch.clear();
			REP(j,SZ(cur)-1) {
				dyn[i].monarch.push_back(make_pair(cur[j], cur[j+1] - 1));
			}

//			cout << "Dyn: " << (char) ('A' + i) << endl;
//			for(auto p : dyn[i].monarch) {
//				cout << p.first << ' ' << p.second << endl;
//			}
		}
		REP(i,n) REP(j,n) {
			lb[i][j] = (i == j) ? 0 : -1e9;
			ub[i][j] = (i == j) ? 0 : 1e9;
		}

//		cout << "Constraints: " << endl;
		string allBattles = "";
		for(string s : battles) allBattles += s;
		stringstream ss(allBattles);

		string s;
		while (ss >> s) {
			pair<int,int> a, b;
			parse(s, a, b);
//			cout << a.first << ' ' << a.second << "   " << b.first << ' ' << b.second << endl;

			int u = a.first, v = b.first;
			lb[u][v] = max(lb[u][v],
					dyn[u].monarch[a.second].first - dyn[v].monarch[b.second].second);

			ub[u][v] = min(ub[u][v],
					dyn[u].monarch[a.second].second - dyn[v].monarch[b.second].first);

//			cout << u << ' ' << v << ":   ";
//			cout << lb[u][v] << '-' << ub[u][v] << endl;

			lb[v][u] = -ub[u][v];
			ub[v][u] = -lb[u][v];
		}

		REP(k,n) REP(i,n) REP(j,n) {
			lb[i][j] = max(lb[i][j], lb[i][k] + lb[k][j]);
			ub[i][j] = min(ub[i][j], ub[i][k] + ub[k][j]);
		}

		string res = "";
		for(string q : queries) {
			pair<int,int> a, b;
			parse(q, a, b);
			
			int u = a.first, v = b.first;
			int from = dyn[u].monarch[a.second].first - dyn[v].monarch[b.second].second;
			int to   = dyn[u].monarch[a.second].second - dyn[v].monarch[b.second].first;

			if (to < lb[u][v] || from > ub[u][v]) res += 'N';
			else res += 'Y';
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
	
	int verify_case(int casenum, const string &expected, const string &received, std::clock_t elapsed) { 
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
			std::cerr << "    Expected: \"" << expected << "\"" << std::endl; 
			std::cerr << "    Received: \"" << received << "\"" << std::endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string dynasties[]        = {"1 2 4",
 "1 2 3"};
			string battles[]          = {"A1-B0"};
			string queries[]          = {"A0-B0",
 "A0-B1",
 "A1-B0",
 "A1-B1"};
			string expected__         = "NNYY";

			std::clock_t start__      = std::clock();
			string received__         = History().verifyClaims(vector <string>(dynasties, dynasties + (sizeof dynasties / sizeof dynasties[0])), vector <string>(battles, battles + (sizeof battles / sizeof battles[0])), vector <string>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string dynasties[]        = {"1000 2000 3000 10000",
 "600 650 2000",
 "1 1001 20001"};
			string battles[]          = {"B1-C0 A0-B0 A2-C1 B1-C1"};
			string queries[]          = {"A0-B1",
 "A1-B1",
 "A2-B1",
 "C0-A0",
 "B0-A2",
 "C1-B0"};
			string expected__         = "YYYYNN";

			std::clock_t start__      = std::clock();
			string received__         = History().verifyClaims(vector <string>(dynasties, dynasties + (sizeof dynasties / sizeof dynasties[0])), vector <string>(battles, battles + (sizeof battles / sizeof battles[0])), vector <string>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string dynasties[]        = {"1 4 5",
 "10 13 17"};
			string battles[]          = {"A0-B0 A0-B0 B0-A0"};
			string queries[]          = {"A1-B0",
 "A0-B1",
 "A1-B1"};
			string expected__         = "YYY";

			std::clock_t start__      = std::clock();
			string received__         = History().verifyClaims(vector <string>(dynasties, dynasties + (sizeof dynasties / sizeof dynasties[0])), vector <string>(battles, battles + (sizeof battles / sizeof battles[0])), vector <string>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string dynasties[]        = {"1 5 6",
 "1 2 5"};
			string battles[]          = {"A0",
 "-B0 A",
 "1-B1"};
			string queries[]          = {"A0-B0",
 "A1-B0",
 "A0-B1",
 "A1-B1"};
			string expected__         = "YNYY";

			std::clock_t start__      = std::clock();
			string received__         = History().verifyClaims(vector <string>(dynasties, dynasties + (sizeof dynasties / sizeof dynasties[0])), vector <string>(battles, battles + (sizeof battles / sizeof battles[0])), vector <string>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string dynasties[]        = {"2294 7344","366 384 449 965 1307 1415","307 473 648 688 1097","1145 1411 1569 2606","87 188 551 598 947 998 1917 1942"}
;
			string battles[]          = {"A0-B4 B4-E2 B3-E2 D2-E4 A0-E4 B1-C3 A0-E3 A0-E6 D0","-E2 B2-E1 B4-E3 B4-D0 D0-E3 A0-D1 B2-C3 B1-C3 B4-E","3 D0-E1 B3-D0 B3-E2"}
;
			string queries[]          = {"A0-C2","E6-C2","A0-E4","B3-C1","C0-D2","B0-C1","D1-C3","C3-D0","C1-E3","D1-A0"};
			string expected__         = "YNYNNYNNNY";

			std::clock_t start__      = std::clock();
			string received__         = History().verifyClaims(vector <string>(dynasties, dynasties + (sizeof dynasties / sizeof dynasties[0])), vector <string>(battles, battles + (sizeof battles / sizeof battles[0])), vector <string>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string dynasties[]        = ;
			string battles[]          = ;
			string queries[]          = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = History().verifyClaims(vector <string>(dynasties, dynasties + (sizeof dynasties / sizeof dynasties[0])), vector <string>(battles, battles + (sizeof battles / sizeof battles[0])), vector <string>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string dynasties[]        = ;
			string battles[]          = ;
			string queries[]          = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = History().verifyClaims(vector <string>(dynasties, dynasties + (sizeof dynasties / sizeof dynasties[0])), vector <string>(battles, battles + (sizeof battles / sizeof battles[0])), vector <string>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string dynasties[]        = ;
			string battles[]          = ;
			string queries[]          = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = History().verifyClaims(vector <string>(dynasties, dynasties + (sizeof dynasties / sizeof dynasties[0])), vector <string>(battles, battles + (sizeof battles / sizeof battles[0])), vector <string>(queries, queries + (sizeof queries / sizeof queries[0])));
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
