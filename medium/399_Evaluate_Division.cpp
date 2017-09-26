/******************************************************************************
 * Equations are given in the format A / B = k, where A and B are variables
 * represented as strings, and k is a real number (floating point number). Given
 * some queries, return the answers. If the answer does not exist, return -1.0.
 *
 * Example:
 * Given a / b = 2.0, b / c = 3.0. 
 * queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? . 
 * return [6.0, 0.5, -1.0, 1.0, -1.0 ].
 * 
 * The input is: vector<pair<string, string>> equations, vector<double>& values,
 * vector<pair<string, string>> queries , where equations.size() == values.size(),
 * and the values are positive. This represents the equations. Return vector<double>.
 *
 * According to the example above:
 *
 * equations = [ ["a", "b"], ["b", "c"] ],
 * values = [2.0, 3.0],
 * queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ]. 
 * The input is always valid. You may assume that evaluating the queries will
 * result in no division by zero and there is no contradiction. 
******************************************************************************/

class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        vector<double> r;
        int cur_id = 0;
        unordered_map<string, int> ids;
        unordered_map<int, unordered_map<int, double> > dict;
        int size = values.size();
        for (int i = 0; i < size; ++i) {
            auto& equation = equations[i];
            double value = values[i];
            int d1 = insert_id(ids, equation.first, ++cur_id);
            if (d1 != cur_id) {
                --cur_id;
            }
            int d2 = insert_id(ids, equation.second, ++cur_id);
            if (d2 != cur_id) {
                --cur_id;
            }
            dict[d1][d2] = value;
            if (value > 1e-6) {
                dict[d2][d1] = 1 / value;
            }
        }
        for (auto& p : queries) {
            int s = query_id(ids, p.first);
            int e = query_id(ids, p.second);
            if (s >= 0 && e >= 0) {
                double value = bfs(dict, s, e);
                r.push_back(value);
            } else {
                r.push_back(-1.0);
            }
        }
        return r;
    }
    
    int insert_id(unordered_map<string, int>& ids, const string& sid, int id) {
        auto res = ids.insert(make_pair(sid, id));
        if (res.second) {
            return id;
        }
        return res.first->second;
    }
    
    int query_id(const unordered_map<string, int>& ids, const string& sid) {
        auto it = ids.find(sid);
        return it == ids.end() ? -1 : it->second;
    }
    
    double bfs(unordered_map<int, unordered_map<int, double> >& dict, const int s, const int e) {
        queue<int> q;
        queue<double> v_q;
        unordered_set<int> visited;
        q.push(s);
        v_q.push(1.0);
        while (!q.empty()) {
            int cur = q.front();
            double value = v_q.front();
            if (e == cur) {
                return value;
            }
            q.pop();
            v_q.pop();
            auto& map = dict[cur];
            for (auto kv : map) {
                if (visited.count(kv.first) == 0) {
                    q.push(kv.first);
                    v_q.push(value * kv.second);
                    visited.insert(kv.first);
                }
            }
        }
        return -1.0;
    }
};
