/******************************************************************************
 * Given a string array words, find the maximum value of length(word[i]) * length(word[j])
 * where the two words do not share common letters. You may assume that each word will
 * contain only lower case letters. If no such two words exist, return 0.
 *
 * Example 1:
 * Given ["abcw", "baz", "foo", "bar", "xtfn", "abcdef"]
 * Return 16
 * The two words can be "abcw", "xtfn".
 *
 * Example 2:
 * Given ["a", "ab", "abc", "d", "cd", "bcd", "abcd"]
 * Return 4
 * The two words can be "ab", "cd".
 *
 * Example 3:
 * Given ["a", "aa", "aaa", "aaaa"]
 * Return 0
 * No such pair of words. 
******************************************************************************/

// you can map a word to a 26-bit-size bitmap and save it to hashtable
class Solution {
public:
    int maxProduct(vector<string>& words) {
        vector<int> masks;
        masks.reserve(words.size());
        for (auto& word : words) {
            int mask = 0;
            for (char ch : word) {
                mask |= (1 << (ch - 'a'));
            }
            masks.push_back(mask);
        }
        size_t result = 0;
        size_t size = words.size();
        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                if ((masks[i] & masks[j]) == 0) {
                    result = max(result, words[i].size() * words[j].size());
                }
            }
        }

        return result;
    }
};
