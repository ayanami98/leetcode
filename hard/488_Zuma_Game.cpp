/******************************************************************************
 * Think about Zuma Game. You have a row of balls on the table, colored red(R),
 * yellow(Y), blue(B), green(G), and white(W). You also have several balls in
 * your hand.
 * 
 * Each time, you may choose a ball in your hand, and insert it into the row
 * (including the leftmost place and rightmost place). Then, if there is a group
 * of 3 or more balls in the same color touching, remove these balls. Keep doing
 * this until no more balls can be removed.
 *
 * Find the minimal balls you have to insert to remove all the balls on the table.
 * If you cannot remove all the balls, output -1.
 *
 * Examples:
 * Input: "WRRBBW", "RB"
 * Output: -1
 * Explanation: WRRBBW -> WRR[R]BBW -> WBBW -> WBB[B]W -> WW
 *
 * Input: "WWRRBBWW", "WRBRW"
 * Output: 2
 * Explanation: WWRRBBWW -> WWRR[R]BBWW -> WWBBWW -> WWBB[B]WW -> WWWW -> empty
 *
 * Input:"G", "GGGGG"
 * Output: 2
 * Explanation: G -> G[G] -> GG[G] -> empty 
 *
 * Input: "RBYYBBRRB", "YRBGB"
 * Output: 3
 * Explanation: RBYYBBRRB -> RBYY[Y]BBRRB -> RBBBRRB -> RRRB -> B -> B[B] -> BB[B]
 * -> empty 
 *
 * Note:
 * You may assume that the initial row of balls on the table won’t have any 3 or
 * more consecutive balls with the same color. The number of balls on the table won't
 * exceed 20, and the string represents these balls is called "board" in the input.
 * The number of balls in your hand won't exceed 5, and the string represents these
 * balls is called "hand" in the input.
 * Both input strings will be non-empty and only contain characters 'R','Y','B','G','W'.  
 ******************************************************************************/

#include <vector>
#include <string>
#include <iostream>

using namespace std;
#define INT_MAX 0x7fffffff

class Solution {
public:
    int findMinStep(string board, string hand) {
        hand_balls.resize(128);
        for (auto ch : hand) {
            ++hand_balls[ch];
        }
        return dfs(board);
    }

private:
    int dfs(const string& board) {
        int min_balls = INT_MAX;
        int idx = 0;
        while (idx < board.size()) {
            if (idx == board.size() - 1 || board[idx] != board[idx + 1]) {
                // remove one ball
                char ball = board[idx];
                if (hand_balls[ball] >= 2) {
                    auto&& new_board = check(board, idx, idx);
                    if (new_board.empty()) {
                        // all the balls on board have been removed
                        min_balls = min(2, min_balls);
                    } else {
                        hand_balls[ball] -= 2;
                        int balls = dfs(new_board);
                        if (balls > 0) {
                            min_balls = min(min_balls, 2 + balls);
                        }
                        hand_balls[ball] += 2;
                    }
                }
                ++idx;
            } else {
                // remove two consecutive balls
                char ball = board[idx];
                if (hand_balls[ball] >= 1) {
                    auto&& new_board = check(board, idx, idx + 1);
                    if (new_board.empty()) {
                        // all the balls on board have been removed
                        min_balls = min(1, min_balls);
                        break;
                    } else {
                        --hand_balls[ball];
                        int balls = dfs(new_board);
                        if (balls > 0) {
                            min_balls = min(min_balls, 1 + balls);
                        }
                        ++hand_balls[ball];
                    }
                }
                idx += 2;
            }
        }
        return min_balls == INT_MAX ? -1 : min_balls;
    }
    
    string check(const string& board, int c1, int c2) {
        //cout << board << ", " << c1 << ", " << c2 << endl;
        string new_board;
        for (int j = 0; j < c1; ++j) {
            new_board += board[j];
        }
        //cout << new_board << endl;
        char last_remove_ch = 'I';
        for (int j = c2 + 1; j < board.size(); ++j) {
            if (board[j] == last_remove_ch) {
                continue;
            }
            if (board[j] != new_board.back() || 
                new_board.size() < 2 ||
                new_board[new_board.size() - 2] != board[j]) {
                new_board += board[j];
                last_remove_ch = 'I';
            } else {
                new_board.pop_back();
                new_board.pop_back();
                last_remove_ch = board[j];
            }
            //cout << new_board << endl;
        }
        return new_board;
    }
    
private:
    vector<int> hand_balls;
};

int main () {
  cout <<  Solution().findMinStep("WWRRBBWW", "WRBRW") << endl;
  return 0;
}
