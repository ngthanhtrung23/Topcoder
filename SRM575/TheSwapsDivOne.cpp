// Div1 - 500
// Algo: Probability + DP
// - Step 1: Find expected value of each position
//     - f(t) = probability that an element moves to same position after t turns
//     - g(t) = probability that an element moves to different position after t turns
//     --> Can find expected value of each position
// - Step 2: For each position, how many substring contains it
//	   - Expected value of all substring
//	   = sum(all substring) / C(n+1, 2)

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

const int MN = 1000111;
string a;
int n;
double f[MN], g[MN];
double x[MN];

class TheSwapDivOne {
public:
    double find(vector<string> sequence, int k) {
        a = "";
        for(auto x : sequence) a += x;
        n = a.length();
        ll nc2 = n * (n-1LL) / 2;
        ll n_1c2 = (n-1) * (n-2LL) / 2;

        f[0] = 1.0; g[0] = 0.0;
        FOR(i,1,k) {
            f[i] = (f[i-1] * n_1c2 + g[i-1]) / nc2;
            g[i] = (f[i-1] * (nc2 - n_1c2) + g[i-1] * (nc2 - 1)) / nc2;
        }

        int sum = 0;
        for(char c : a) sum += c - '0';

        REP(i,n) {
            int cur = a[i] - '0';
            x[i] = f[k] * cur + g[k] * (sum - cur) / (n-1);
        }
        double res = 0.0;
        ll can = n * (n+1) / 2;
        REP(i,n) {
            int left = i+1;
            int right = n - i;
            res += left * right * x[i] / can;
        }
        return res;
    }
};

TheSwapDivOne sol;

int main() {
    assert(fabs(sol.find({"4", "77"}, 1) - 10.0) < 1e-6);
    assert(fabs(sol.find({"4", "77"}, 47) - 10.0) < 1e-6);
    assert(fabs(sol.find({"1", "1", "1", "1", "1", "1", "1"}, 1000000) - 3.0) < 1e-6);
    assert(fabs(sol.find({"572685085149095989026478064633266980348504469", "19720257361", "9", "69"}
                    , 7) - 98.3238536775161) < 1e-6);
}

