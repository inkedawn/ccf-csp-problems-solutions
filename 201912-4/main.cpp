#include <bits/stdc++.h>
using namespace std;

using nodeid_t = int;
using chain_t = vector<nodeid_t>;
using broadcastMsg = pair<nodeid_t, chain_t>; // 发出节点ID，主链
vector<vector<nodeid_t> > rel; // 节点-邻接表{相连节点...}
vector<chain_t> chain;// 节点-主链{主链节点...}
unordered_map<int, vector<pair<nodeid_t, int>>> creation; // 时间- {{节点，块编号}...}
unordered_map<int, vector<broadcastMsg> > transmission; // 时间- {节点，链{接收链组成节点...｝}...}
set<int> timepoints;

int n;
int delay;

inline void gen(int node, int t, int id) {
    creation[t].push_back({node, id});
    timepoints.insert(t);
}

inline void broadcastNeighbor(int node, int tp) {
    transmission[tp + delay].push_back({node, chain[node]});
    timepoints.insert(tp + delay); // 不要忘记维护时间点表
}

inline void processAndQuery(int node, int t) {
    auto it = timepoints.begin();
    for (; it != timepoints.end() && *it <= t; ++it) {
        int tp = *it;
        // 先处理接收
        if (transmission.count(tp)) {
            for (const auto &msg: transmission[tp]) {
                const auto &fromid = msg.first;
                const auto &sentchain = msg.second;
                for (const auto &toid: rel[fromid]) {
                    if (chain[toid].size() < sentchain.size()
                        || (chain[toid].size() == sentchain.size() && chain[toid].back() > sentchain.back())
                            ) {
                        chain[toid] = sentchain; // 接受更新
                        broadcastNeighbor(toid, tp); // 向邻居广播自己的主链
                    }
                }
            }
        }
        transmission.erase(tp);
        // 处理创建
        if (creation.count(tp)) {
            for (const auto &p: creation[tp]) {
                const auto &nodeid = p.first;
                const auto &blockid = p.second;
                chain[nodeid].push_back(blockid); // 主链延长
                broadcastNeighbor(nodeid, tp); // 向邻居广播自己的主链
            }
        }
        creation.erase(tp);
    }
    timepoints.erase(timepoints.begin(), it); // 此处erase使用有坑，不能在循环中擦除当前key，否则当前迭代器失效无法自增至下一元素
    // 输出该时间点状态
    cout << chain[node].size();
    for (int b: chain[node]) {
        cout << " " << b;
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int m;
    cin >> n >> m;
    rel.resize(n + 1);
    chain.resize(n + 1, chain_t(1, 0));
    creation.reserve(2000);
    transmission.reserve(2000);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        rel[u].push_back(v);
        rel[v].push_back(u);
    }
    int k;
    cin >> delay >> k;
    for (int i = 1; i <= k; ++i) {
        int a, b, c;
        cin >> a >> b;
        if (cin.get() == '\n' || cin.eof()) {
            processAndQuery(a, b);
        } else {
            cin >> c;
            gen(a, b, c);
        }
    }
}