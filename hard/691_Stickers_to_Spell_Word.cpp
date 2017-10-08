/******************************************************************************
 * Copyright (c)  2017, TigerGraph Inc.                                    *
 * All rights reserved                                                        *
 * Unauthorized copying of this file, via any medium is strictly prohibited   *
 * Proprietary and confidential                                               *
 ******************************************************************************
* File Name : 691_Stickers_to_Spell_Word.cpp
*
* Created on : 2017-10-07
* Author : tufeng
*
* Last Modified : Sat 07 Oct 2017 06:30:22 PM PST
******************************************************************************/

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        vector<vector<int> > letters(stickers.size(), vector<int>(26, 0));
        for (int i = 0; i < stickers.size(); ++i) {
            auto& sticker = stickers[i];
            auto& letter = letters[i];
            for (auto ch : sticker) {
                ++letter[ch - 'a'];
                maps[ch - 'a'].insert(i);
            }
        }
        for (auto ch : target) {
            if (maps[ch - 'a'].empty()) {
                return -1;
            }
        }
        vector<int> choice(26, 0);
        dfs(letters, choice, target, 0, 0);
        return min_path == INT_MAX ? -1 : min_path;
    }

private:
    void dfs(const vector<vector<int>>& letters, vector<int>& choice, const string& target, int idx, int path_size) {
        if (idx == target.length()) {
            min_path = min(path_size, min_path);
            return;
        }
        if (path_size >= min_path) {
            return;
        }
        int ch = target[idx] - 'a';
        --choice[ch];
        if (choice[ch] >= 0) {
            dfs(letters, choice, target, idx + 1, path_size);
            ++choice[ch];
            return;
        }
        auto& map = maps[ch];
        for (auto s : map) {
            auto& letter = letters[s];
            for (int j = 0; j < 26; ++j) {
                choice[j] += letter[j];
            }
            dfs(letters, choice, target, idx + 1, path_size + 1);
            for (int j = 0; j < 26; ++j) {
                choice[j] -= letter[j];
            }
        }
        ++choice[ch];
    }
    
private:
    unordered_set<int> maps[26];
    int min_path = INT_MAX;
};

int main() {
  vector<string> data({"city","would","feel","effect","cell","paint"});
  cout << Solution().minStickers(data, "putcat") << endl;
  return 0;
}

