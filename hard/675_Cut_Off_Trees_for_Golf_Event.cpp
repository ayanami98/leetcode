/******************************************************************************
 * You are asked to cut off trees in a forest for a golf event. The forest is
 * represented as a non-negative 2D map, in this map:
 * 0 represents the obstacle can't be reached.
 * 1 represents the ground can be walked through.
 * The place with number bigger than 1 represents a tree can be walked through,
 * and this positive number represents the tree's height.
 * You are asked to cut off all the trees in this forest in the order of tree's
 * height - always cut off the tree with lowest height first. And after cutting,
 * the original place has the tree will become a grass (value 1).
 *
 * You will start from the point (0, 0) and you should output the minimum steps
 * you need to walk to cut off all the trees. If you can't cut off all the trees,
 * output -1 in that situation.
 *
 * You are guaranteed that no two trees have the same height and there is at least
 * one tree needs to be cut off.
 *
 * Example 1:
 * Input: 
 * [
 *  [1,2,3],
 *  [0,0,4],
 *  [7,6,5]
 * ]
 * Output: 6
 * Example 2:
 * Input: 
 * [
 *  [1,2,3],
 *  [0,0,0],
 *  [7,6,5]
 * ]
 * Output: -1
 * Example 3:
 * Input: 
 * [
 *  [2,3,4],
 *  [0,0,5],
 *  [8,7,6]
 * ]
 * Output: 6
 * Explanation: You started from the point (0,0) and you can cut off the tree in
 * (0,0) directly without walking.
 * Hint: size of the given matrix will not exceed 50x50.
******************************************************************************/

struct hasher {
  int operator()(const pair<int, int>& target) const {
      return (target.first << 10) + target.second;
  }  
};

class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        for (int i = 0; i < forest.size(); ++i) {
            for (int j = 0; j < forest[i].size(); ++j) {
                if (forest[i][j] > 1) {
                    maps.emplace_back(i, j, forest[i][j]);
                }
            }
        }
        if (forest[0][0] == 0) {
            return maps.size() == 0 ? 0 : -1;
        }
        sort(maps.begin(), maps.end(), 
            [](const tuple<int, int, int>& lhs, const tuple<int, int, int>& rhs) {
               return get<2>(lhs) < get<2>(rhs); 
            });
        
        int step = 0;
        int x = 0;
        int y = 0;
        for (auto& pos : maps) {
            int s = move(forest, x, y, get<0>(pos), get<1>(pos));
            if (s < 0) {
                return -1;
            }
            step += s;
            x = get<0>(pos);
            y = get<1>(pos);
        }
        return step;
    }

private:
    int move(vector<vector<int>>& forest, int s_x, int s_y, int t_x, int t_y) {
        unordered_set<pair<int, int>, hasher> visited;
        visited.insert(make_pair(s_x, s_y));
        int height = 0;
        queue<pair<int, int> > q;
        q.push(make_pair(s_x, s_y));
        int level_size = 1;
        int next_level_size = 0;
        bool has_reach = false;
        while (!q.empty()) {
           auto cur = q.front();
           q.pop();
            if (cur.first == t_x && cur.second == t_y) { // reach the target
                return height;
            }
            --level_size;

           // move upward
            if (cur.first > 0) {
                auto new_pos = make_pair(cur.first - 1, cur.second);
                auto res = visited.insert(new_pos);
                if (res.second && forest[new_pos.first][new_pos.second] > 0) {
                    q.push(new_pos);
                    ++next_level_size;
                }
            }           
            
           // move downward
            if (cur.first < forest.size() - 1) {
                auto new_pos = make_pair(cur.first + 1, cur.second);
                auto res = visited.insert(new_pos);
                if (res.second && forest[new_pos.first][new_pos.second] > 0) {
                    q.push(new_pos);
                    ++next_level_size;
                }
            }
            
           // move left
            if (cur.second > 0) {
                auto new_pos = make_pair(cur.first, cur.second - 1);
                auto res = visited.insert(new_pos);
                if (res.second && forest[new_pos.first][new_pos.second] > 0) {
                    q.push(new_pos);
                    ++next_level_size;
                }
            }
            
           // move right
            if (cur.second < forest[0].size() - 1) {
                auto new_pos = make_pair(cur.first, cur.second + 1);
                auto res = visited.insert(new_pos);
                if (res.second && forest[new_pos.first][new_pos.second] > 0) {
                    q.push(new_pos);
                    ++next_level_size;
                }
            }
            
            if (0 == level_size) {
                level_size = next_level_size;
                next_level_size = 0;
                ++height;
            }
        }
        return -1;
    }
    
private:
    // <x, y, height>
    vector<tuple<int, int, int> > maps;
};

