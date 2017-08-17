/********************************************************************************
 * Start from integer 1, remove any integer that contains 9 such as 9, 19, 29...
 *
 * So now, you will have a new integer sequence: 1, 2, 3, 4, 5, 6, 7, 8, 10, 11, ...
 *
 * Given a positive integer n, you need to return the n-th integer after removing.
 * Note that 1 will be the first integer.
 *
 * Example 1:
 * Input: 9
 * Output: 10
 * Hint: n will not exceed 9 x 10^8.
 *********************************************************************************/

#include <iostream>

using namespace std;

class Solution {
public:
    int newInteger(int n) {
        long long int counters[11] = {0};
        counters[0] = 0;
        counters[1] = 8;
        counters[2] = 80; // 1 - 8, 10 - 18, 20 - 28, ....
        // counters[3] = 8 * (counters[2] + 1) + counters[2];  // 1 - 88, 100 - 188 
        for (int i = 3; i < 11; ++i) {
            counters[i] = 8 * (counters[i - 1] + 1)  + // add tailing 0 
                          counters[i - 1];  // add the heading 0
        }
        int base = 0;
        int i = 10;
        while (i > 0) {
            if (counters[i] < n) {
                int d = counters[i] + 1;
                base += n / d;
                n %= d;
            } 
            base *= 10;
            --i;
        }
        base += n;
        return base;
    }
};

int main() {
  cout << Solution().newInteger(44) << endl;
  return 0;
}
