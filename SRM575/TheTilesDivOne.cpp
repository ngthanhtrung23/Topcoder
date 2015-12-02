// Div1 - 1000
// Algo: MaxFlow
// - (Wrong) 1st attempt:
//     - Color board with black & white
//     - Build flow
//     - Return max flow
//     --> Fail, because flow to black = 2, flow out of white = 1
//     --> black nodes can be split
// - Correct:
//     - Color board with 3 colors: black, blue, red (white --> blue + red)
//     - Build flow:
//     - s --> reds --> black (in nodes) --> black (out nodes) --> blue --> t
//     --> return max flow

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

const int INF = 1000000000;
 
struct Edge {
    int a, b, cap, flow;
};

struct MaxFlow {
    int n, s, t;
    vector<int> d, ptr, q;
    vector< Edge > e;
    vector< vector<int> > g;

    MaxFlow(int n) : n(n), d(n), ptr(n), q(n), g(n) {
        e.clear();
        REP(i,n) {
            g[i].clear();
            ptr[i] = 0;
        }
    }

    void addEdge(int a, int b, int cap) {
        Edge e1 = { a, b, cap, 0 };
        Edge e2 = { b, a, 0, 0 };
        g[a].push_back( (int) e.size() );
        e.push_back(e1);
        g[b].push_back( (int) e.size() );
        e.push_back(e2);
    }
    int getMaxFlow(int _s, int _t) {
        s = _s; t = _t;
        int flow = 0;
        for (;;) {
            if (!bfs()) break;
            REP(i,n) ptr[i] = 0;
            while (int pushed = dfs(s, INF))
                flow += pushed;
        }
        return flow;
    }

private:
    bool bfs() {
        int qh = 0, qt = 0;
        q[qt++] = s;
        REP(i,n) d[i] = -1;
        d[s] = 0;

        while (qh < qt && d[t] == -1) {
            int v = q[qh++];
            REP(i,g[v].size()) {
                int id = g[v][i], to = e[id].b;
                if (d[to] == -1 && e[id].flow < e[id].cap) {
                    q[qt++] = to;
                    d[to] = d[v] + 1;
                }
            }
        }
        return d[t] != -1;
    }

    int dfs (int v, int flow) {
        if (!flow) return 0;
        if (v == t) return flow;
        for (; ptr[v] < (int)g[v].size(); ++ptr[v]) {
            int id = g[v][ptr[v]],
                to = e[id].b;
            if (d[to] != d[v] + 1) continue;
            int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
            if (pushed) {
                e[id].flow += pushed;
                e[id^1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
};

const int BLACK = 0;
const int RED = 1;
const int BLUE = 2;

int color(int i, int j) {
    if ((i + j) % 2 == 0) return BLACK;
    if (i % 2 == 0) return RED;
    return BLUE;
}

int blue[55][55], red[55][55], blackIn[55][55], blackOut[55][55];
int m, n;

#define left left___
#define right right___

vector<string> a;
int up(int i, int j) {
    return i > 0 && a[i-1][j] == '.';
}

int left(int i, int j) {
    return j > 0 && a[i][j-1] == '.';
}

int down(int i, int j) {
    return i+1 < m && a[i+1][j] == '.';
}

int right(int i, int j) {
    return j+1 < n && a[i][j+1] == '.';
}

void connect(int x, int y, int i, int j, int u, int v, MaxFlow& flow) {
    if (color(x, y) == RED) {
        flow.addEdge(red[x][y], blackIn[u][v], 1);
        flow.addEdge(blackOut[u][v], blue[i][j], 1);
    }
    else {
        flow.addEdge(red[i][j], blackIn[u][v], 1);
        flow.addEdge(blackOut[u][v], blue[x][y], 1);
    }
}

class TheTilesDivOne {
public:
    int find(vector<string> board) {
        a = board;
        m = board.size();
        n = board[0].size();
        int cur = 0;

        // initialize vertex IDs
        REP(i,m) REP(j,n) {
            if (board[i][j] == '.') {
                int c = color(i, j);

                if (c == RED) {
                    red[i][j] = ++cur;
                }
                else if (c == BLUE) {
                    blue[i][j] = ++cur;
                }
                else {
                    blackIn[i][j] = ++cur;
                    blackOut[i][j] = ++cur;
                }
            }
        }
        // Build flow
        MaxFlow flow(cur + 2);
        int s = 0, t = cur + 1;
        REP(i,m) REP(j,n) {
            if (board[i][j] == '.') {
                int c = color(i, j);
                if (c == RED) {
                    flow.addEdge(s, red[i][j], 1);
                }
                else if (c == BLUE) {
                    flow.addEdge(blue[i][j], t, 1);
                }
                else {
                    flow.addEdge(blackIn[i][j], blackOut[i][j], 1);
                    if (  up(i, j) &&  left(i, j)) connect(i-1, j, i, j-1, i, j, flow);
                    if (  up(i, j) && right(i, j)) connect(i-1, j, i, j+1, i, j, flow);
                    if (down(i, j) && right(i, j)) connect(i+1, j, i, j+1, i, j, flow);
                    if (down(i, j) &&  left(i, j)) connect(i+1, j, i, j-1, i, j, flow);
                }
            }
        }
        return flow.getMaxFlow(s, t);
    }
};

TheTilesDivOne sol;

int main() {
    assert(sol.find({"X.X",
                    "...",
                    "X.X"}) == 1);
    assert(sol.find({"...",
                 "...",
                  "..."}) == 2);
    assert(sol.find({"......X.X.XXX.X.XX."}
                ) == 0);
    assert(sol.find({"X.....XXX.XX..XXXXXXXXX...X.XX.XX....X",
                 ".XXXX..X..XXXXXXXX....XX.X.X.X.....XXX",
                  "....XX....X.XX..X.X...XX.X..XXXXXXX..X",
                   "XX.XXXXX.X.X..X..XX.XXX..XX...XXX.X..."}) == 13);
}

