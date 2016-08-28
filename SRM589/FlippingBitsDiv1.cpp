// Div1 - 900
// Algo:
// - The given condition is equivalent to:
//   S[i] = S[i+M]
// - Max |S| = 300
// - If M <= 17 --> brute force the first M character, then DP
// - If N/M <= 17 --> at most 17 group, brute force the flip k*M operations,
//   then solve using greedy

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

int N, M;

int f[2][311];
string s;
int solve1() {
	int nGroup = N / M;
	if (N % M) ++nGroup;

	int res = N;
	REP(mask,TWO(M)) {
		int cur = 0;
		REP(i,M) if (s[i] == '1') cur |= TWO(i);
		f[0][0] = __builtin_popcount(cur ^ mask);
		f[1][0] = 1 + f[0][0];

		FOR(g,1,nGroup-1) {
			int nBit = M;
			if (g == nGroup-1 && N % M) nBit = N % M;

			int curMask = 0;
			REP(i,nBit) {
				int pos = g * M + i;
				if (s[pos] == '1')
					curMask |= TWO(i);
			}
			int diff0 = 0;
			REP(i,nBit) {
				int x = (mask >> i) & 1;
				int y = (curMask >> i) & 1;
				if (x != y) ++diff0;
			}
			int diff1 = nBit - diff0;

			f[0][g] = min(f[0][g-1] + diff0, f[1][g-1] + 1 + diff1);
			f[1][g] = min(f[1][g-1] + diff1, f[0][g-1] + 1 + diff0);

		}
		res = min(res, min(f[0][nGroup-1], f[1][nGroup-1]));

//		if (cur == mask) {
//			DEBUG(mask);
//			PR0(f[0], nGroup);
//			PR0(f[1], nGroup);
//		}
	}
	return res;
}

int flip[311], cnt[2][311];
int solve2() {
	int nGroup = N / M;
	if (N % M) ++nGroup;

	int res = N;
	REP(mask,TWO(nGroup)) {
		memset(flip, 0, sizeof flip);
		memset(cnt, 0, sizeof cnt);

		REP(i,nGroup) if (CONTAIN(mask,i)) {
			REP(j,i+1) flip[j] ^= 1;
		}
		FOR(i,0,N-1) {
			int x = s[i] - '0';
			if (flip[i / M]) x ^= 1;

			cnt[x][i % M]++;
		}

		int sum = __builtin_popcount(mask);
		REP(i,M) sum += min(cnt[0][i], cnt[1][i]);
		res = min(res, sum);
	}
	return res;
}

class FlippingBitsDiv1 {
public:
    int getmin( vector <string> S, int M ) {
		s = accumulate(S.begin(), S.end(), string());
		N = SZ(s);
		::M = M;

		if (M <= 17) return solve1();
		else return solve2();
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
			string S[]                = {"00111000"};
			int M                     = 1;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string S[]                = {"101100001101"};
			int M                     = 3;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string S[]                = {"11111111"};
			int M                     = 4;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string S[]                = {"1101001000"};
			int M                     = 8;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string S[]                = {"1","10","11","100","101","110"};
			int M                     = 5;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string S[]                = {"1001011000101010001111111110111011011100110001001"};
			int M                     = 2;
			int expected__            = 16;

			std::clock_t start__      = std::clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string S[]                = ;
			int M                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string S[]                = ;
			int M                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string S[]                = ;
			int M                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
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
