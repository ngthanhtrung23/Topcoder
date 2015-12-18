// SRM676 - 1000
// Algo:
// - Notice m <= 50 --> not so many paths..
// - Fix upper bound of path length
// - For 
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

#define MAXM 20000 // leave one extra 
#define MAXN 55 // leave one extra 
#define EPS 1e-9 
#define INF 1.0/0.0 
double A[MAXM][MAXN]; 
int basis[MAXM], out[MAXN]; 
void pivot(int m, int n, int a, int b) { 
    int i,j; 
    for (i=0;i<=m;i++) 
        if (i!=a) 
            for (j=0;j<=n;j++)
                if (j!=b) 
                    A[i][j] -= A[a][j] * A[i][b] / A[a][b]; 
    for (j=0;j<=n;j++) 
        if (j!=b) A[a][j] /= A[a][b]; 
    for (i=0;i<=m;i++) 
        if (i!=a) A[i][b] = -A[i][b]/A[a][b]; 
            A[a][b] = 1/A[a][b]; 
    swap(basis[a], out[b]);
} 
double simplex(int m, int n, double C[][MAXN], double X[]) { 
    int i,j,ii,jj; // i,ii are row indexes; j,jj are column indexes 
    for (i=1;i<=m;i++) 
        for (j=0;j<=n;j++) 
            A[i][j] = C[i][j]; 
    for (j=0;j<=n;j++) A[0][j] = -C[0][j]; 
    for (i=0;i<=m;i++) basis[i] = -i; 
    for (j=0;j<=n;j++) out[j] = j; 
    for(;;) { 
        for (i=ii=1;i<=m;i++) 
            if (A[i][n]<A[ii][n] || (A[i][n]==A[ii][n] && basis[i]<basis[ii])) 
                ii=i; 
        if (A[ii][n] >= -EPS) break; 
        for (j=jj=0;j<n;j++) 
            if (A[ii][j]<A[ii][jj]-EPS || (A[ii][j]<A[ii][jj]-EPS && out[i]<out[j])) 
                jj=j;
        if (A[ii][jj] >= -EPS) return -INF; 
        pivot(m,n,ii,jj); 
    } 
    for(;;) { 
        for (j=jj=0;j<n;j++) 
            if (A[0][j]<A[0][jj] || (A[0][j]==A[0][jj] && out[j]<out[jj])) 
                jj=j; 
        if (A[0][jj] > -EPS) break; 
        for (i=1,ii=0;i<=m;i++) 
            if ((A[i][jj]>EPS) && 
                    (!ii || (A[i][n]/A[i][jj] < A[ii][n]/A[ii][jj]-EPS) || 
                ((A[i][n]/A[i][jj] < A[ii][n]/A[ii][jj]+EPS) && (basis[i] < basis[ii])))) 
            ii=i; 
        if (A[ii][jj] <= EPS) return INF; 
        pivot(m,n,ii,jj); 
    } 
    for (j=0;j<n;j++)
        X[j] = 0; 
    for (i=1;i<=m;i++) 
        if (basis[i] >= 0) 
            X[basis[i]] = A[i][n]; 
    return A[0][n]; 
} 

vector<int> ke[55];
int n;

vector< vector<int> > paths;
vector<int> cur;

void dfs(int u) {
	if (u == n) {
		paths.push_back(cur);
		return ;
	}
	cur.push_back(u);
	for(int v : ke[u]) {
		dfs(v);
	}
	cur.pop_back();
}

double X[MAXN], C[MAXM][MAXN];
class Farmville {
public:
    int minTime( vector <string> s, vector <int> time, vector <int> cost, int budget ) {
		n = SZ(s);
		REP(i,n+1) ke[i].clear();

		REP(i,n) {
			ke[i].push_back(n);
			REP(j,n) if (s[i][j] == '1') {
				ke[j].push_back(i);
			}
		}
		REP(i,n) {
			random_shuffle(ke[i].begin(), ke[i].end());
		}
		paths.clear();
		cur.clear();
		REP(i,n) dfs(i);

		DEBUG(SZ(paths));

		double bound = budget;
		REP(i,n) bound -= time[i] * (double) cost[i];
		bound += EPS;

		// C[0]
		REP(i,n) C[0][i] = cost[i];
		
		// time constraint
		int cur = 1;
		REP(i,n) {
			C[cur][i] = 1.0;
			C[cur][n] = time[i];
			++cur;

			C[cur][i] = -1.0;
			C[cur][n] = 0.0;
			++cur;
		}

		int start = cur;
		for(auto path : paths) {
			for(auto x : path) {
				C[cur][x] = 1.0;
			}
			C[cur][n] = -1.0;
			++cur;
			if (cur > MAXM - 5) break;
		}

		int l = 0, r = 1500, res = 1500;
		while (l <= r) {
			int mid = (l + r) / 2;

			FOR(i,start,cur-1) C[i][n] = mid;
			double cost = simplex(cur-1, n, C, X);

			if (-cost <= bound) {
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
			string s[]                = {"000",
 "000",
 "000"};
			int time[]                = {25,15,10};
			int cost[]                = {1,2,3};
			int budget                = 50;
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = Farmville().minTime(vector <string>(s, s + (sizeof s / sizeof s[0])), vector <int>(time, time + (sizeof time / sizeof time[0])), vector <int>(cost, cost + (sizeof cost / sizeof cost[0])), budget);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string s[]                = {"0000",
 "1000",
 "0100",
 "0010"};
			int time[]                = {25,25,25,25};
			int cost[]                = {100,200,300,400};
			int budget                = 2800;
			int expected__            = 74;

			std::clock_t start__      = std::clock();
			int received__            = Farmville().minTime(vector <string>(s, s + (sizeof s / sizeof s[0])), vector <int>(time, time + (sizeof time / sizeof time[0])), vector <int>(cost, cost + (sizeof cost / sizeof cost[0])), budget);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string s[]                = {"01110",
 "00010",
 "00000",
 "00000",
 "10000"};
			int time[]                = {25,10,23,12,5};
			int cost[]                = {123,456,789,1011,1213};
			int budget                = 1000000000;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = Farmville().minTime(vector <string>(s, s + (sizeof s / sizeof s[0])), vector <int>(time, time + (sizeof time / sizeof time[0])), vector <int>(cost, cost + (sizeof cost / sizeof cost[0])), budget);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string s[]                = {"00",
 "00"};
			int time[]                = {25,25};
			int cost[]                = {1000000000,1000000000} ;
			int budget                = 1000000000;
			int expected__            = 25;

			std::clock_t start__      = std::clock();
			int received__            = Farmville().minTime(vector <string>(s, s + (sizeof s / sizeof s[0])), vector <int>(time, time + (sizeof time / sizeof time[0])), vector <int>(cost, cost + (sizeof cost / sizeof cost[0])), budget);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string s[]                = {"0000000000000000",
 "1000000000000000",
 "1000000000000000",
 "0100000000000000",
 "0110000000000000",
 "0010000000000000",
 "0001000000000000",
 "0001100000000000",
 "0000110000000000",
 "0000010000000000",
 "0000001100000000",
 "0000000110000000",
 "0000000011000000",
 "0000000000110000",
 "0000000000011000",
 "0000000000000110"};
			int time[]                = {24,25,23,25,23,24,25,24,23,22,25,24,23,25,23,25};
			int cost[]                = {82912,129482,235934,3294812,523942,460492,349281,592384, 109248,2305923,340945,2304934,582396,548935,767872,423981};
			int budget                = 87654321;
			int expected__            = 49;

			std::clock_t start__      = std::clock();
			int received__            = Farmville().minTime(vector <string>(s, s + (sizeof s / sizeof s[0])), vector <int>(time, time + (sizeof time / sizeof time[0])), vector <int>(cost, cost + (sizeof cost / sizeof cost[0])), budget);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string s[]                = {"000","100","110"};
			int time[]                = {3,18,1};
			int cost[]                = {242949,8471,54403957};
			int budget                = 53867;
			int expected__            = 16;

			std::clock_t start__      = std::clock();
			int received__            = Farmville().minTime(vector <string>(s, s + (sizeof s / sizeof s[0])), vector <int>(time, time + (sizeof time / sizeof time[0])), vector <int>(cost, cost + (sizeof cost / sizeof cost[0])), budget);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string s[]                = ;
			int time[]                = ;
			int cost[]                = ;
			int budget                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = Farmville().minTime(vector <string>(s, s + (sizeof s / sizeof s[0])), vector <int>(time, time + (sizeof time / sizeof time[0])), vector <int>(cost, cost + (sizeof cost / sizeof cost[0])), budget);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string s[]                = ;
			int time[]                = ;
			int cost[]                = ;
			int budget                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = Farmville().minTime(vector <string>(s, s + (sizeof s / sizeof s[0])), vector <int>(time, time + (sizeof time / sizeof time[0])), vector <int>(cost, cost + (sizeof cost / sizeof cost[0])), budget);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string s[]                = ;
			int time[]                = ;
			int cost[]                = ;
			int budget                = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = Farmville().minTime(vector <string>(s, s + (sizeof s / sizeof s[0])), vector <int>(time, time + (sizeof time / sizeof time[0])), vector <int>(cost, cost + (sizeof cost / sizeof cost[0])), budget);
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
