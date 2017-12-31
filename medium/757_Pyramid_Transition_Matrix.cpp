/******************************************************************************
 * We are stacking blocks to form a pyramid. Each block has a color which is a
 * one letter string, like `'Z'`.
 *
 * For every block of color `C` we place not in the bottom row, we are placing
 * it on top of a left block of color `A` and right block of color `B`. We are
 * allowed to place the block there only if `(A, B, C)` is an allowed triple.
 * 
 * We start with a bottom row of bottom, represented as a single string. We also
 * start with a list of allowed triples allowed. Each allowed triple is represented
 * as a string of length 3.
 *
 * Return true if we can build the pyramid all the way to the top, otherwise false.
 *
 * Example 1:
 * Input: bottom = "XYZ", allowed = ["XYD", "YZE", "DEA", "FFF"]
 * Output: true
 * Explanation:
 * We can stack the pyramid like this:
 *     A
 *    / \
 *   D   E
 *  / \ / \
 * X   Y   Z
 *
 * This works because ('X', 'Y', 'D'), ('Y', 'Z', 'E'), and ('D', 'E', 'A') are
 * allowed triples.
 * Example 1:
 * Input: bottom = "XXYX", allowed = ["XXX", "XXY", "XYX", "XYY", "YXZ"]
 * Output: false
 * Explanation:
 * We can't stack the pyramid to the top.
 * Note that there could be allowed triples (A, B, C) and (A, B, D) with C != D.
 * Note:
 * bottom will be a string with length in range [2, 100].
 * allowed will have length in range [0, 350].
 * Letters in all strings will be chosen from the set {'A', 'B', 'C', 'D', 'E', 'F', 'G'}.
******************************************************************************/

class Solution {
public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        for (auto&& a : allowed) {
            int key = a[0] - 'A';
            key <<= 8;
            key |= (a[1] - 'A');
            rules[key].push_back(a[2] - 'A');
        }
        if (rules.empty()) {
            return false;
        }
        int size = bottom.size();
        // dp[i][j][6] indicates if the target chars are valid at the top for range [i - j] 
        vector<vector<vector<bool> > > dp(size, vector<vector<bool> >(size, vector<bool>(7, false)));
        for (int i = 0; i < size; ++i) {
            dp[i][i][bottom[i] - 'A'] = true;
        }
        for (int l = 2; l < size; ++l) {
            for (int i = 0; i < size - l + 1; ++i) {
                int j = i + l - 1;
                auto& l_set = dp[i][j - 1];
                auto& r_set = dp[i + 1][j];
                bool has_upper = false;
                for (int m = 0; m < 7; ++m) {
                    for (int n = 0; n < 7; ++n) {
                        if (!l_set[m] || !r_set[n]) {
                            continue;
                        }
                        int key = m;
                        key <<= 8;
                        key |= n;
                        auto it = rules.find(key);
                        if (it != rules.end()) {
                            for (auto b : it->second) {
                                dp[i][j][b] = true;
                                has_upper = true;
                            }
                        }
                    }
                }
                if (!has_upper) {
                    return false;
                }
            }
        }
        return true;
    }

private:
    unordered_map<int, vector<char> > rules;
};
