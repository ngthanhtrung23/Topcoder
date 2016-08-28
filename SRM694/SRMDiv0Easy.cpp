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

#define MAXM 666 // leave one extra 
#define MAXN 666 // leave one extra 
#define EPS 1e-9 
#define INF 1e100
double A[MAXM][MAXN]; 
int basis[MAXM], out[MAXN]; 
double C[MAXN][MAXN];
double X[MAXN];
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
double simplex(int m, int n) {
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

const int MN = 211;
vector<int> a[MN];

int nVar, nEqu;

class SRMDiv0Easy {
public:
    int get( int N, vector <int> L, vector <int> R, vector <int> LX, vector <int> Y ) {
        REP(j,N) a[j].clear();

        int Q = SZ(L);
        REP(i,Q) {
            FOR(j,L[i],R[i]) a[j].push_back(i);
        }

        if (a[0].empty()) {
            // 1st element is not changed
            for(int x : LX) {
                if (x > 0) return -1;
            }
            return 0;
        }

        nVar = Q;
        nEqu = 0;
        memset(C, 0, sizeof C);
        memset(X, 0, sizeof X);
        // objective
        for(int x : a[0]) {
            C[0][x] = 1.0;
        }
        // inequalities
        REP(i,Q) {
            // V[i] <= Y[i]
            ++nEqu;
            C[nEqu][i] = 1.0;
            C[nEqu][nVar] = Y[i];

            // -V[i] <= -X[i]
            ++nEqu;
            C[nEqu][i] = -1.0;
            C[nEqu][nVar] = -LX[i];
        }
        // all j are equal
        REP(j,N) {
            ++nEqu;
            for(int i : a[j]) C[nEqu][i] += 1.0;
            for(int i : a[(j+1) % N]) C[nEqu][i] -= 1.0;
        }
        double x = simplex(nEqu, nVar);
        if (x < -1e98 || x > 1e98) return -1;
        return (int) (round(x) + 1e-6);
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
			int N                     = 2;
			int L[]                   = {0,1};
			int R[]                   = {0,1};
			int X[]                   = {1,2};
			int Y[]                   = {2,3};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = SRMDiv0Easy().get(N, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 2;
			int L[]                   = {0,1};
			int R[]                   = {0,1};
			int X[]                   = {1,3};
			int Y[]                   = {2,4};
			int expected__            = -1;

			std::clock_t start__      = std::clock();
			int received__            = SRMDiv0Easy().get(N, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 3;
			int L[]                   = {0,1,0,0,2};
			int R[]                   = {2,2,1,0,2};
			int X[]                   = {1,3,1,4,2};
			int Y[]                   = {11,13,19,15,17};
			int expected__            = 41;

			std::clock_t start__      = std::clock();
			int received__            = SRMDiv0Easy().get(N, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 12;
			int L[]                   = {0,0,1,4,9,7,0};
			int R[]                   = {6,11,11,4,10,11,0};
			int X[]                   = {1,73,334,1,1,5,362};
			int Y[]                   = {546,342,645,249,999,535,458};
			int expected__            = -1;

			std::clock_t start__      = std::clock();
			int received__            = SRMDiv0Easy().get(N, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 200;
			int L[]                   = {0,49,0,97,0,65,0,55,0,24,0,86,0,139,0,34,0,11,0,62,0,172,0,59,0,97,0,47,0,156,0,24,0,103,0,184,0,130,0,154,0,26,0,121,0,72,0,183,0,5};
			int R[]                   = {48,199,96,199,64,199,54,199,23,199,85,199,138,199,33,199,10,199,61,199,171,199,58,199,96,199,46,199,155,199,23,199,102,199,183,199,129,199,153,199,25,199,120,199,71,199,182,199,4,199};
			int X[]                   = {1,1,1,1,2,1,2,2,2,2,1,1,1,1,2,1,1,1,1,1,2,2,2,1,2,1,1,2,2,1,1,1,2,2,1,1,2,1,1,1,1,1,2,2,2,2,2,2,2,1};
			int Y[]                   = {964,962,952,993,983,973,971,954,978,980,958,999,991,978,977,991,971,976,977,998,968,992,951,955,987,981,986,958,968,966,992,957,975,995,958,995,983,985,956,974,966,986,985,999,959,989,980,998,971,973};
			int expected__            = 24202;

			std::clock_t start__      = std::clock();
			int received__            = SRMDiv0Easy().get(N, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int N                     = 5;
			int L[]                   = {};
			int R[]                   = {};
			int X[]                   = {};
			int Y[]                   = {};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = SRMDiv0Easy().get(N, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int N                     = ;
			int L[]                   = ;
			int R[]                   = ;
			int X[]                   = ;
			int Y[]                   = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = SRMDiv0Easy().get(N, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int N                     = ;
			int L[]                   = ;
			int R[]                   = ;
			int X[]                   = ;
			int Y[]                   = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = SRMDiv0Easy().get(N, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int N                     = ;
			int L[]                   = ;
			int R[]                   = ;
			int X[]                   = ;
			int Y[]                   = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = SRMDiv0Easy().get(N, vector <int>(L, L + (sizeof L / sizeof L[0])), vector <int>(R, R + (sizeof R / sizeof R[0])), vector <int>(X, X + (sizeof X / sizeof X[0])), vector <int>(Y, Y + (sizeof Y / sizeof Y[0])));
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
