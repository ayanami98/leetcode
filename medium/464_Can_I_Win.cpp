/******************************************************************************
 * In the "100 game," two players take turns adding, to a running total, any
 * integer from 1..10. The player who first causes the running total to reach or
 * exceed 100 wins.
 *
 * What if we change the game so that players cannot re-use integers?
 *
 * For example, two players might take turns drawing from a common pool of numbers
 * of 1..15 without replacement until they reach a total >= 100.
 * 
 * Given an integer maxChoosableInteger and another integer desiredTotal, determine
 * if the first player to move can force a win, assuming both players play optimally.
 * 
 * You can always assume that maxChoosableInteger will not be larger than 20 and
 * desiredTotal will not be larger than 300.
 * 
 * Example
 * 
 * Input:
 * maxChoosableInteger = 10
 * desiredTotal = 11
 * 
 * Output:
 * false
 *
 * Explanation:
 * No matter which integer the first player choose, the first player will lose.
 * The first player can choose an integer from 1 up to 10.
 * If the first player choose 1, the second player can only choose integers from 2
 * up to 10. The second player will win by choosing 10 and get a total = 11, which
 * is >= desiredTotal. Same with other integers chosen by the first player, the
 * second player will always win. 
******************************************************************************/

// minimax
class Solution {
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if (desiredTotal <= maxChoosableInteger) {
            return true;
        }
        if (desiredTotal > ((1 + maxChoosableInteger) * maxChoosableInteger >> 1)) {
            return false;
        }
        int bitmap = 0;
        dp.resize(1 << maxChoosableInteger, -1);
        return canIWinImpl(bitmap, true, maxChoosableInteger, desiredTotal);
    }
    
private:
    bool canIWinImpl(int bitmap, bool is_max, int max_num, int sum) {
        if (dp[bitmap] > -1) {
            return dp[bitmap] > 0 ? true : false;
        }
        if (sum <= 0) {
            return is_max ? false : true;
        }
        int r = -1;
        if (is_max) {
            // maximizer can force a win if one path is okay
            r = 0;
            for (int i = 1; i <= max_num; ++i) {
                int num = 1 << (i - 1);
                if ((bitmap & num) == 0) { // not used
                    if (canIWinImpl(bitmap | num, false, max_num, sum - i)) {
                        r = 1;
                        break;
                    }
                }
            }
        } else {
            // minimizer can prevent maximizer from a force-win if one path is not okay.
            r = 1;
            for (int i = 1; i <= max_num; ++i) {
                int num = 1 << (i - 1);
                if ((bitmap & num) == 0) {
                    if (!canIWinImpl(bitmap | num, true, max_num, sum - i)) {
                        r = 0;
                        break;
                    }
                }
            }
        }
        dp[bitmap] = r;
        return r > 0 ? true : false;
    }

private:
    vector<int> dp;
};
