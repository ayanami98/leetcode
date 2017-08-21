/******************************************************************************
 * Given a string and a string dictionary, find the longest string in the dictionary
 * that can be formed by deleting some characters of the given string. If there
 * are more than one possible results, return the longest word with the smallest
 * lexicographical order. If there is no possible result, return the empty string.
 *
 * Example 1:
 * Input:
 * s = "abpcplea", d = ["ale","apple","monkey","plea"]
 *
 * Output: 
 * "apple"
 * Example 2:
 * Input:
 * s = "abpcplea", d = ["a","b","c"]
 *
 * Output: 
 * "a"
 * Note:
 * All the strings in the input will only contain lower-case letters.
 * The size of the dictionary won't exceed 1,000.
 * The length of all the strings in the input won't exceed 1,000.
 ******************************************************************************/

class Solution {
public:
    string findLongestWord(string s, vector<string>& d) {
        sort(d.begin(), d.end(), [](const string& lhs, const string& rhs) -> bool {
            return lhs.size() > rhs.size() || (lhs.size() == rhs.size() && lhs < rhs);
        });
        for (auto& s2 : d) {
            if (check(s, s2)) {
                return s2;
            }
        }
        return "";
    }

private:
    bool check(const string& s, const string& s2) {
        int pos = -1;
        for (auto ch : s2) {
            pos = s.find_first_of(ch, pos + 1);
            if (string::npos == pos) {
                return false;
            }
        }
        return true;
    }
};
