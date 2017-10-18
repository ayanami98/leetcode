#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> fallingSquares(vector<pair<int, int>>& positions) {
        vector<int> result;
        int size = positions.size();
        if (size == 0) {
            return result;
        }
        // s_position -> (e_position, height)
        map<int, pair<int, int> > tab;
        auto& pos = positions[0];
        tab[pos.first] = make_pair(pos.first + pos.second, pos.second);
        int highest = pos.second;
        result.push_back(highest);
        for (int i = 1; i < size; ++i) {
            auto& pos = positions[i];
            int s = pos.first;
            int e = pos.first + pos.second;
            int height = pos.second;
            auto e_it = tab.lower_bound(e);
            if (e_it == tab.begin()) {
                tab[pos.first] = make_pair(e, height);
                highest = max(highest, height);
            } else {
                auto s_it = tab.lower_bound(s);
                if (s_it != tab.begin() && prev(s_it)->second.first > s) {
                    advance(s_it, -1);
                }
                int height2 = 0;
                for (auto it = s_it; it != e_it; ++it) {
                     height2 = max(height2, it->second.second + height);
                }
                if (height2 == 0) {
                    tab[pos.first] = make_pair(e, height);
                    highest = max(highest, height);
                } else {
                    highest = max(height2, highest);
                    auto prev_e_it = prev(e_it);
                    bool need_split = false;
                    int old_height = 0;
                    int old_end = 0;
                    if (prev_e_it->second.first > e) {
			need_split = true;
                        old_height = prev_e_it->second.second;
                        old_end = prev_e_it->second.first;
                    }
                    if (s_it->first < s && s_it->second.first > s) {
                        s_it->second.first = s;
                        advance(s_it, 1);
                    }
                    tab.erase(s_it, e_it);
                    tab[s] = make_pair(e, height2);
                    if (need_split) {
                      tab[e] = make_pair(old_end, old_height);
                    }
                }
            }
            result.push_back(highest);
        }
        return result;
    }
};

int main() {
   vector<pair<int, int> > data;
   data.emplace_back(33, 34);
   data.emplace_back(47, 62);
   data.emplace_back(70, 16);
   data.emplace_back(90, 79);
   data.emplace_back(73, 86);
   data.emplace_back(55, 6);
   data.emplace_back(74, 2);
   data.emplace_back(40, 95);
   data.emplace_back(52, 16);
   data.emplace_back(50, 33);
   auto res = Solution().fallingSquares(data);
   for (int num : res) {
     cout << num << ", ";
   }
   cout << endl;
   return 0;
}

