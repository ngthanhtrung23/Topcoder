// Div1 - 500
// Algo: Greedy
// - For each friend with segment [s, t], there are 2 cases:
// 1. A friend [u, v] with u <= s <= t <= v repost --> optimal(i) = optimal(j) + 1
// 2. In the other case, it can be view as expanding [s, t] to the left and
//    to the right, by having friend repost

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

#define left left___
#define right right___

string combine(const vector<string>& s) {
	string res = "";
	for(auto p : s) res += p;
	return res;
}

struct Seg {
	int s, t, id;
} a[5011];

bool cmpLeft(const Seg& a, const Seg& b) {
	if (a.s != b.s) return a.s < b.s;
	return a.t > b.t;
}
bool cmpRight(const Seg& a, const Seg& b) {
	if (a.t != b.t) return a.t > b.t;
	return a.s < b.s;
}

int left[5011], right[5011], f[5011];

int d(char c) {
	return c - '0';
}

const int INF = 1000111000;
class ShoutterDiv1 {
public:
    int count( vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1 ) {
		string S1000 = combine(s1000);
		string S100  = combine(s100);
		string S10   = combine(s10);
		string S1    = combine(s1);

		string T1000 = combine(t1000);
		string T100  = combine(t100);
		string T10   = combine(t10);
		string T1    = combine(t1);

		int n = SZ(S1);
		REP(i,n) {
			a[i+1].id = i + 1;
			a[i+1].s = d(S1000[i]) * 1000 + d(S100[i]) * 100 + d(S10[i]) * 10 + d(S1[i]);
			a[i+1].t = d(T1000[i]) * 1000 + d(T100[i]) * 100 + d(T10[i]) * 10 + d(T1[i]);
		}
		sort(a+1, a+n+1, cmpLeft);
//		FOR(i,1,n) {
//			cout << a[i].id << "   " << a[i].s << ' ' << a[i].t << endl;
//		}

		FOR(i,1,n) {
			int u = a[i].id;
			int res = 0, covered = a[i].t;
			int maxNext = a[i].t;

			FOR(j,i+1,n) {
				if (a[j].s > covered) {
					if (maxNext < a[j].s) {
						res = INF;
						break;
					}
					else {
						++res;
						covered = maxNext;
						maxNext = max(maxNext, a[j].t);
					}
				}
				else {
					maxNext = max(maxNext, a[j].t);
				}
			}

			left[u] = res;
		}
//		PR(left, n);

		sort(a+1, a+n+1, cmpRight);
//		FOR(i,1,n) {
//			cout << a[i].id << "   " << a[i].s << ' ' << a[i].t << endl;
//		}
		FOR(i,1,n) {
			int u = a[i].id;
			int res = 0, covered = a[i].s;
			int minNext = a[i].s;
			FOR(j,i+1,n) {
				if (a[j].t < covered) {
					if (minNext > a[j].t) {
						res = INF;
						break;
					}
					else {
						covered = minNext;
						minNext = min(minNext, a[j].s);
						++res;
					}
				}
				else {
					minNext = min(minNext, a[j].s);
				}
			}
			right[u] = res;
		}
//		PR(right, n);
		
		sort(a+1, a+n+1, cmpLeft);
		int total = 0;
		FOR(i,1,n) {
			int u = a[i].id;
			f[u] = left[u] + right[u];
			FOR(j,1,i-1)
				if (a[j].s <= a[i].s && a[i].t <= a[j].t)
					f[u] = min(f[u], f[a[j].id] + 1);
			total += f[u];
			if (total >= INF) break;
		}
		if (total >= INF) total = -1;
		return total;
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
			string s1000[]            = {"22", "2"};
			string s100[]             = {"00", "0"};
			string s10[]              = {"11", "1"};
			string s1[]               = {"21", "4"};
			string t1000[]            = {"22", "2"};
			string t100[]             = {"00", "0"};
			string t10[]              = {"11", "1"};
			string t1[]               = {"43", "6"};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string s1000[]            = {"00"};
			string s100[]             = {"00"};
			string s10[]              = {"00"};
			string s1[]               = {"13"};
			string t1000[]            = {"00"};
			string t100[]             = {"00"};
			string t10[]              = {"00"};
			string t1[]               = {"24"};
			int expected__            = -1;

			std::clock_t start__      = std::clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string s1000[]            = {"0000"};
			string s100[]             = {"0000"};
			string s10[]              = {"0000"};
			string s1[]               = {"1234"};
			string t1000[]            = {"0000"};
			string t100[]             = {"0000"};
			string t10[]              = {"0000"};
			string t1[]               = {"2345"};
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string s1000[]            = {"0000000000"};
			string s100[]             = {"0000000000"};
			string s10[]              = {"0000000000"};
			string s1[]               = {"7626463146"};
			string t1000[]            = {"0000000000"};
			string t100[]             = {"0000000000"};
			string t10[]              = {"0000000000"};
			string t1[]               = {"9927686479"};
			int expected__            = 18;

			std::clock_t start__      = std::clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string s1000[]            = {"00000000000000000000000000000000000000000000000000"};
			string s100[]             = {"00000000000000000000000000000000000000000000000000"};
			string s10[]              = {"50353624751857130208544645495168271486083954769538"};
			string s1[]               = {"85748487990028258641117783760944852941545064635928"};
			string t1000[]            = {"00000000000000000000000000000000000000000000000000"};
			string t100[]             = {"00000000000000000000000000000000000000000000000000"};
			string t10[]              = {"61465744851859252308555855596388482696094965779649"};
			string t1[]               = {"37620749792666153778227385275518278477865684777411"};
			int expected__            = 333;

			std::clock_t start__      = std::clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string s1000[]            = ;
			string s100[]             = ;
			string s10[]              = ;
			string s1[]               = ;
			string t1000[]            = ;
			string t100[]             = ;
			string t10[]              = ;
			string t1[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string s1000[]            = ;
			string s100[]             = ;
			string s10[]              = ;
			string s1[]               = ;
			string t1000[]            = ;
			string t100[]             = ;
			string t10[]              = ;
			string t1[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string s1000[]            = ;
			string s100[]             = ;
			string s10[]              = ;
			string s1[]               = ;
			string t1000[]            = ;
			string t100[]             = ;
			string t10[]              = ;
			string t1[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
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
