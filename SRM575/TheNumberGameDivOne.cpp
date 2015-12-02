// Div1 - 250
// Algo: brute force + observe pattern
// - Find winning states + losing states by brute force
//     - Win states: odd number, != 2^(2k+1)
// - Can prove by induction
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

#define WIN "John"
#define LOSE "Brus"

class TheNumberGameDivOne {
	public:
	string find(ll n) {
        if (n % 2 == 1) return LOSE;
        if (n % 2 == 0) {
            int cnt = 0;
            while (n % 2 == 0) {
                n /= 2;
                cnt++;
            }
            if (cnt % 2 == 1 && n == 1) return LOSE;
            return WIN;
        }
	}
};

TheNumberGameDivOne sol;

bool win[100111];
int main() {
    int n = 1000;
    FOR(i,1,n) {
        win[i] = 0;
        for(int j = 2; j < i; ++j)
            if (i % j == 0)
                if (win[i - j] == 0) {
                    win[i] = 1;
                    break;
                }
    }
    FOR(i,1,n) if (win[i] == 1) {
        assert(i % 2 == 0);
    }
    FOR(i,1,n) if (win[i] == 0) {
        if (i % 2 == 0) cout << i << ' ';
    }
    cout << endl;

    assert(sol.find(6) == "John");
    assert(sol.find(2) == "Brus");
    assert(sol.find(747) == "Brus");
    assert(sol.find(128) == "Brus");
}

