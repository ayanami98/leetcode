/******************************************************************************
 * Given a string which contains only lowercase letters, remove duplicate letters
 * so that every letter appear once and only once. You must make sure your result
 * is the smallest in lexicographical order among all possible results.
 * 
 * Example:
 * Given "bcabc"
 * Return "abc"
 * 
 * Given "cbacdcbc"
 * Return "acdb" 
 ******************************************************************************/

ass Solution {
public:
    string removeDuplicateLetters(string s) {
        int counters[26] = {0};
        int total_number = 0;
        for (char ch : s) {
            int& counter = counters[ch - 'a'];
            if (0 == counter) {
                ++total_number;
            }
            ++counter;
        }
        map<char, int> candidates;
        string result;
        int i = 0;
        vector<bool> selected_chars(26, false);
        int candidates_start = 0;
        int length = s.length();
        while (total_number-- > 0) {
            for (; i < length; ++i) {
                char ch = s[i];
                int& counter = counters[ch - 'a'];
                if (1 == counter) {
                    break;
                }
                if (counter > 0) {
                    --counter;
                    ++candidates[ch];
                }
            }
            if (!candidates.empty()) {
                auto it = candidates.begin();
                char ch = it->first;
                if (s[i] < ch) {
                    // the current charactor is ahead of all the candidates
                    result.append(1, s[i]);
                    selected_chars[s[i] - 'a'] = true;
                    counters[s[i] - 'a'] = 0;
                    candidates.clear();
                    ++i;
                    candidates_start = i;
                } else {
                    result.append(1, ch);
                    selected_chars[ch - 'a'] = true;
                    candidates.erase(it);
                    counters[ch - 'a'] = 0;  // remove this charactor
                    for (; candidates_start < i; ++candidates_start) {
                        // remove all the charactors before the selected one
                        char ch2 = s[candidates_start];
                        if (ch2 == ch) {
                            break;
                        }
                        if (!selected_chars[ch2 - 'a']) {
                            int& counter2 = candidates[ch2];
                            --counter2;
                            if (counter2 == 0) {
                                candidates.erase(ch2);
                            }
                        }
                    }
                }
            } else {
                result.append(1, s[i]);
                counters[s[i] - 'a'] = 0;
                selected_chars[s[i] - 'a'] = true;
                ++i;
            }
        }
        return result;
    }
};
