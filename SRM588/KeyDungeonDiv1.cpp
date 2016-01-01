// Div1 - 450
// Algo: BFS
// - Observations:
//     - we can "color" the white keys as soon as we get them.
//     - For a set of opened doors, we can get the total number of keys that we
//       currently have
// - BFS with state (opened doors, number of red keys). From these two, we can
//   get the number of green keys
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

int sum[TWO(12)];
bool visited[TWO(12)][150];

class KeyDungeonDiv1 {
public:
    int maxKeys( vector <int> doorR, vector <int> doorG, vector <int> roomR, vector <int> roomG, vector <int> roomW, vector <int> keys ) {
		int n = SZ(doorR);

		REP(mask,TWO(n)) {
			sum[mask] = keys[0] + keys[1] + keys[2];

			REP(i,n) if (CONTAIN(mask,i)) {
				sum[mask] -= doorR[i] + doorG[i];
				sum[mask] += roomR[i] + roomG[i] + roomW[i];
			}
		}
		memset(visited, 0, sizeof visited);
		queue<int> qs;
		queue<int> qr;
		FOR(addR,0,keys[2]) {
			int red = keys[0] + addR;
			visited[0][red] = true;
			qs.push(0);
			qr.push(red);
		}
		int res = 0;
		while (!qs.empty()) {
			int s = qs.front(); qs.pop();
			int r = qr.front(); qr.pop();
			int g = sum[s] - r;

			res = max(res, sum[s]);

			REP(i,n) if (!CONTAIN(s,i) && r >= doorR[i] && g >= doorG[i]) {
				int rr = r - doorR[i] + roomR[i];
				int gg = g - doorG[i] + roomG[i];
				int ss = s + TWO(i);

				FOR(addR,0,roomW[i]) {
					rr += addR;

					if (!visited[ss][rr]) {
						visited[ss][rr] = true;
						qs.push(ss);
						qr.push(rr);
					}

					rr -= addR;
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
			int doorR[]               = {1, 2, 3};
			int doorG[]               = {0, 4, 9};
			int roomR[]               = {0, 0, 10};
			int roomG[]               = {0, 8, 9};
			int roomW[]               = {1, 0, 8};
			int keys[]                = {3, 1, 2};
			int expected__            = 8;

			std::clock_t start__      = std::clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int doorR[]               = {1, 1, 1, 2};
			int doorG[]               = {0, 2, 3, 1};
			int roomR[]               = {2, 1, 0, 4};
			int roomG[]               = {1, 3, 3, 1};
			int roomW[]               = {1, 0, 2, 1};
			int keys[]                = {0, 4, 0};
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int doorR[]               = {2, 0, 4};
			int doorG[]               = {3, 0, 4};
			int roomR[]               = {0, 0, 9};
			int roomG[]               = {0, 0, 9};
			int roomW[]               = {8, 5, 9};
			int keys[]                = {0, 0, 0};
			int expected__            = 27;

			std::clock_t start__      = std::clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int doorR[]               = {5, 3, 0, 0};
			int doorG[]               = {0, 1, 2, 1};
			int roomR[]               = {0, 9, 2, 4};
			int roomG[]               = {2, 9, 2, 0};
			int roomW[]               = {0, 9, 1, 1};
			int keys[]                = {1, 1, 0};
			int expected__            = 32;

			std::clock_t start__      = std::clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int doorR[]               = {9,5,10,8,4,3,0,8,4,1,3,9};
			int doorG[]               = {9,10,0,8,9,4,3,8,1,8,10,4};
			int roomR[]               = {1,2,0,2,3,3,5,3,1,3,0,5};
			int roomG[]               = {5,2,5,0,5,2,3,4,0,0,5,2};
			int roomW[]               = {1,5,1,2,0,4,4,0,3,3,1,3};
			int keys[]                = {5,0,1};
			int expected__            = 16;

			std::clock_t start__      = std::clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int doorR[]               = ;
			int doorG[]               = ;
			int roomR[]               = ;
			int roomG[]               = ;
			int roomW[]               = ;
			int keys[]                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int doorR[]               = ;
			int doorG[]               = ;
			int roomR[]               = ;
			int roomG[]               = ;
			int roomW[]               = ;
			int keys[]                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int doorR[]               = ;
			int doorG[]               = ;
			int roomR[]               = ;
			int roomG[]               = ;
			int roomW[]               = ;
			int keys[]                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = KeyDungeonDiv1().maxKeys(vector <int>(doorR, doorR + (sizeof doorR / sizeof doorR[0])), vector <int>(doorG, doorG + (sizeof doorG / sizeof doorG[0])), vector <int>(roomR, roomR + (sizeof roomR / sizeof roomR[0])), vector <int>(roomG, roomG + (sizeof roomG / sizeof roomG[0])), vector <int>(roomW, roomW + (sizeof roomW / sizeof roomW[0])), vector <int>(keys, keys + (sizeof keys / sizeof keys[0])));
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
