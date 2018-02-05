/****
Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
****/

class Solution {
public:
int lengthOfLongestSubstring(string S) {
    vector<char> stats(128, 0);
    int s = 0;
    int e = 0;
    int count = 0;
    int max_len = 0;
    while (e < S.size()) {
        if (stats[S[e++]]++ > 0) {
            ++count;
        }
        while (count > 0) {
            if (stats[S[s++]]-- == 2) {
                --count;
            }
        }
        max_len = max(max_len, e - s);
    }
    return max_len;
}
};
