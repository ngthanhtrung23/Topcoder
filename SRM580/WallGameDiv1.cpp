// Div1 - 1000
// Algo: DP + game theory
// We have 2 player:
// - Blocking player (add walls): need to maximize
// - Moving player (move around): need to minimize
//
// Thus, we need some form of DP like this:
// - f(u) = max( g(v) )
// - g(u) = min( f(u) )
// where v are reachable states from u
//       f: optimal strategy for max player
//       g: minimum strategy for min player
// 
// Observations:
// - When moving player can move down, he must do so, otherwise, the blocking
//   player can just block all options, forcing moving player to go back to that
//   same place and move down
// - Blocking player should delay his move as late as possible, to disclose as
//   little as possible about his strategy
//
// Based on the above observations:
// - Moving player always have following choices:
//     - Must move down if can
//     - Otherwise, either go left or right
// - Blocking player can choose either block or not block going down from this cell
//
// This also means that, the cells that are blocked are always consecutive.
// Thus, we can represent the state of the game as:
// - (turn, i, j, u, v) where (i, j) is the current cell and [u, v] are the cells
//   that are blocked
//
// State transitions:
// - To avoid cycles, in each turn of moving player, he must go outside of the range
//   [u, v].
// Thus:
// - Blocking player:
//   (turn, i, j, u, v) --> (1-turn, i, j, u, v)                 - do not block
//                      --> (1-turn, i, j, min(u, j), max(v, j)) - block. This case can only happen
//                                                                 if [u', v'] != [1, n] (avoid no move)
// - Moving player:
//   (turn, i, j, u, v) --> (1-turn, i+1, j, 0, 0)               - move down, only if j is outside [u, v]
//                      --> (1-turn, i, u-1, u, v)               - move left
//                      --> (1-turn, i, v+1, u, v)               - move right

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

const int INF = 1e6;
int m, n;
int a[55][55], sum[55][55];

// f(t, i, j, u, v) = optimal value if:
// - we start at this state, only consider weights that we jump into
// - t = 0/1: 1st player turn or 2nd player turn
// - (i, j) = current position
// - in row i, cell u --> v is blocked

int encode(int t, int i, int j, int u, int v) {
	return (v-1) + (u-1) * 52 + (j-1) * 2704 + (i-1) * 140608 + t * 7311616;
}
map<int,int> f;

int get(int t, int i, int j, int u, int v) {
	if (i == m) return 0;

	int hash = encode(t, i, j, u, v);
	if (f.count(hash)) return f[hash];

	int res;
	if (t == 0) {
		// blocking player
		// need to maximize
		res = -INF;

		// do not block
		res = max(res, get(1, i, j, u, v));

		// block below cell (i, j)
		int uu = u, vv = v;

		if (uu == 0) uu = vv = j;
		else {
			uu = min(u, j);
			vv = max(v, j);
		}
		if (uu > 1 || vv < n) {
			res = max(res, get(1, i, j, uu, vv));
		}
	}
	else {
		// moving player
		// need to minimize
		res = INF;

		// if can move down, then must
		if (j < u || v < j) res = a[i+1][j] + get(0, i+1, j, 0, 0);
		else {
			if (j > 1 && u > 1) {
				res = min(res, sum[i][j-1] - sum[i][u-2] + get(0, i, u-1, u, v));
			}
			if (j < n && v < n) {
				res = min(res, sum[i][v+1] - sum[i][j] + get(0, i, v+1, u, v));
			}
		}
	}
	return f[hash] = res;
}

class WallGameDiv1 {
public:
    int play( vector <string> costs ) {
		m = SZ(costs);
		n = SZ(costs[0]);
		FOR(i,1,m) FOR(j,1,n) {
			a[i][j] = costs[i-1][j-1] - '0';
			sum[i][j] = sum[i][j-1] + a[i][j];
		}

		f.clear();

		int res = INF;
		FOR(j,1,n)
			res = min(res, get(0, 1, j, 0, 0) + a[1][j]);
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
			string costs[]            = {"12"
,"34"};
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = WallGameDiv1().play(vector <string>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string costs[]            = {"99999"
,"99999"
,"99999"};
			int expected__            = 99;

			std::clock_t start__      = std::clock();
			int received__            = WallGameDiv1().play(vector <string>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string costs[]            = {"11111"
,"90005"};
			int expected__            = 10;

			std::clock_t start__      = std::clock();
			int received__            = WallGameDiv1().play(vector <string>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string costs[]            = {"4417231387449337370319219832088987579792"
,"3117295688208899006196193430472892512797"
,"0835796222361526836944954410684516919758"
,"1988200069973565052900745230547016216225"
,"8080511471118865780390486996601082102418"
,"4229084185957675819725844582167613108400"
,"9068653877952162764545674979144308771754"
,"8551565425951612499712254182109991511690"
,"7090525592007482152807163656647658543093"
,"9198968742256995592729889137556032960142"
,"2071864379877766468141740053503050313101"
,"1055375249261868472993219156394129253481"
,"2461178270502857106406495509025426298874"
,"8216781259733537757203421037984512664825"
,"4693452554407216935375049784445568498482"
,"2709693439640250842244170297203200674391"
,"5122217695676372684217182241705137947908"
,"6668814191410691246849638388008228444294"
,"4952122070212780440963814752538149378639"
,"9827737761436134120332969866554332504400"
,"3412406588339828249986707470540386748886"
,"7521506848088506994554600408372456405830"
,"1916926179183007872881163173153907665999"
,"6636166791472761992310264951474925339024"
,"6679667717747231380196787943691121008076"
,"3218993234115685151069259138068533004433"
,"4920152552986426962081492913852060211795"
,"0365186235986445521382132973036266396894"
,"3205351414936828189305188614651974318855"
,"3144278971529524658788277656125598825426"
,"5525287537572356662391582052968411726245"
,"2130137226726919525622574701068062252930"
,"2369996694245544770519574837226971226841"
,"6806769058165410189286521891570936341547"
,"0448109211631660241710734664066810078242"
,"4622919135804954122810530631429501069659"
,"0235247446548732490429856705369583140671"
,"2193399741215975228987754171460722199304"
,"1203037020703833716225328076959743850915"
,"5419885193880826109484912489603262199432"};
			int expected__            = 7366;

			std::clock_t start__      = std::clock();
			int received__            = WallGameDiv1().play(vector <string>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string costs[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = WallGameDiv1().play(vector <string>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string costs[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = WallGameDiv1().play(vector <string>(costs, costs + (sizeof costs / sizeof costs[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string costs[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = WallGameDiv1().play(vector <string>(costs, costs + (sizeof costs / sizeof costs[0])));
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
