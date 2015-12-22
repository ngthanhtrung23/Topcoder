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
int a[MN], na, nb;
pair<int,ll> b[MN];
ll has[MN];

bool check(ll bound) {
	FOR(i,1,nb) has[i] = b[i].second;

	int j = 1;
	FOR(i,1,na) {
		ll my = bound;
		while (a[i] >= b[j].first) {
			ll can = min(my, has[j]);
			if (!can) break;

			my -= can;
			has[j] -= can;
			if (has[j] == 0) ++j;
			if (j > nb) return true;
		}
	}
	return false;
}

class SpaceWarDiv1 {
public:
    long long minimalFatigue( vector <int> magicalGirlStrength, vector <int> enemyStrength, vector<long long> enemyCount ) {
		na = SZ(magicalGirlStrength);
		REP(i,na) a[i+1] = magicalGirlStrength[i];

		nb = SZ(enemyCount);
		REP(i,nb) b[i+1] = make_pair(enemyStrength[i], enemyCount[i]);

		sort(a+1, a+na+1);
		sort(b+1, b+nb+1);

		ll l = 0, r = 1e16, res = -1;
		while (l <= r) {
			ll mid = (l + r) / 2;
			if (check(mid)) {
				res = mid;
				r = mid - 1;
			}
			else l = mid + 1;
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
			int magicalGirlStrength[] = {2, 3, 5};
			int enemyStrength[]       = {1, 3, 4};
			long long enemyCount[]    = {2, 9, 4};
			long long expected__      = 7;

			std::clock_t start__      = std::clock();
			long long received__      = SpaceWarDiv1().minimalFatigue(vector <int>(magicalGirlStrength, magicalGirlStrength + (sizeof magicalGirlStrength / sizeof magicalGirlStrength[0])), vector <int>(enemyStrength, enemyStrength + (sizeof enemyStrength / sizeof enemyStrength[0])), vector<long long>(enemyCount, enemyCount + (sizeof enemyCount / sizeof enemyCount[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int magicalGirlStrength[] = {2, 3, 5};
			int enemyStrength[]       = {1, 1, 2};
			long long enemyCount[]    = {2, 9, 4};
			long long expected__      = 5;

			std::clock_t start__      = std::clock();
			long long received__      = SpaceWarDiv1().minimalFatigue(vector <int>(magicalGirlStrength, magicalGirlStrength + (sizeof magicalGirlStrength / sizeof magicalGirlStrength[0])), vector <int>(enemyStrength, enemyStrength + (sizeof enemyStrength / sizeof enemyStrength[0])), vector<long long>(enemyCount, enemyCount + (sizeof enemyCount / sizeof enemyCount[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int magicalGirlStrength[] = {14, 6, 22};
			int enemyStrength[]       = {8, 33};
			long long enemyCount[]    = {9, 1};
			long long expected__      = -1;

			std::clock_t start__      = std::clock();
			long long received__      = SpaceWarDiv1().minimalFatigue(vector <int>(magicalGirlStrength, magicalGirlStrength + (sizeof magicalGirlStrength / sizeof magicalGirlStrength[0])), vector <int>(enemyStrength, enemyStrength + (sizeof enemyStrength / sizeof enemyStrength[0])), vector<long long>(enemyCount, enemyCount + (sizeof enemyCount / sizeof enemyCount[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int magicalGirlStrength[] = {869, 249, 599, 144, 929, 748, 665, 37, 313, 99, 33, 437, 308, 137, 665, 834, 955, 958, 613, 417};
			int enemyStrength[]       = {789, 57, 684, 741, 128, 794, 542, 367, 937, 739, 568, 872, 127, 261, 103, 763, 864, 360, 618, 307};
			long long enemyCount[]    = {20626770196420LL, 45538527263992LL, 52807114957507LL, 17931716090785LL, 65032910980630LL, 88711853198687LL, 26353250637092LL, 61272534748707LL, 89294362230771LL, 52058590967576LL, 60568594469453LL, 23772707032338LL, 43019142889727LL, 39566072849912LL, 78870845257173LL, 68135668032761LL, 36844201017584LL, 10133804676521LL, 6275847412927LL, 37492167783296LL};
			long long expected__      = 75030497287405LL;

			std::clock_t start__      = std::clock();
			long long received__      = SpaceWarDiv1().minimalFatigue(vector <int>(magicalGirlStrength, magicalGirlStrength + (sizeof magicalGirlStrength / sizeof magicalGirlStrength[0])), vector <int>(enemyStrength, enemyStrength + (sizeof enemyStrength / sizeof enemyStrength[0])), vector<long long>(enemyCount, enemyCount + (sizeof enemyCount / sizeof enemyCount[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int magicalGirlStrength[] = ;
			int enemyStrength[]       = ;
			long long enemyCount[]    = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = SpaceWarDiv1().minimalFatigue(vector <int>(magicalGirlStrength, magicalGirlStrength + (sizeof magicalGirlStrength / sizeof magicalGirlStrength[0])), vector <int>(enemyStrength, enemyStrength + (sizeof enemyStrength / sizeof enemyStrength[0])), vector<long long>(enemyCount, enemyCount + (sizeof enemyCount / sizeof enemyCount[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int magicalGirlStrength[] = ;
			int enemyStrength[]       = ;
			long long enemyCount[]    = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = SpaceWarDiv1().minimalFatigue(vector <int>(magicalGirlStrength, magicalGirlStrength + (sizeof magicalGirlStrength / sizeof magicalGirlStrength[0])), vector <int>(enemyStrength, enemyStrength + (sizeof enemyStrength / sizeof enemyStrength[0])), vector<long long>(enemyCount, enemyCount + (sizeof enemyCount / sizeof enemyCount[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int magicalGirlStrength[] = ;
			int enemyStrength[]       = ;
			long long enemyCount[]    = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = SpaceWarDiv1().minimalFatigue(vector <int>(magicalGirlStrength, magicalGirlStrength + (sizeof magicalGirlStrength / sizeof magicalGirlStrength[0])), vector <int>(enemyStrength, enemyStrength + (sizeof enemyStrength / sizeof enemyStrength[0])), vector<long long>(enemyCount, enemyCount + (sizeof enemyCount / sizeof enemyCount[0])));
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
