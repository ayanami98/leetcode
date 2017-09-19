/******************************************************************************
 * You have 4 cards each containing a number from 1 to 9. You need to judge
 * whether they could operated through *, /, +, -, (, ) to get the value of 24.
 *
 * Example 1:
 * Input: [4, 1, 8, 7]
 * Output: True
 * Explanation: (8-4) * (7-1) = 24
 *
 * Example 2:
 * Input: [1, 2, 1, 2]
 * Output: False
 *
 * Note:
 * The division operator / represents real division, not integer division. For
 * example, 4 / (1 - 2/3) = 12. Every operation done is between two numbers. In
 * particular, we cannot use - as a unary operator. For example, with [1, 1, 1, 1]
 * as input, the expression -1 - 1 - 1 - 1 is not allowed. You cannot concatenate
 * numbers together. For example, if the input is [1, 2, 1, 2], we cannot write
 * this as 12 + 12. 
******************************************************************************/

class Solution {
public:
    bool judgePoint24(vector<int>& nums) {
        vector<pair<int, int> > data;
        for (auto num : nums) {
            data.emplace_back(num, 1);
        }
        return judge(data);
    }
    
private:
    bool judge(vector<pair<int, int>>& nums) {
        //cout << "---------------" << endl;
        //for (auto p : nums) {
        //    cout << '[' << p.first << ", " << p.second << "]  ";
        //}
        //cout << "\n===============" << endl;
        int size = nums.size();
        if (size == 1) {
            return nums[0].first == 24 && nums[0].second == 1;
        }
        vector<pair<int, int> > new_data;
        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                new_data.clear();
                for (int k = 0; k < size; ++k) {
                    if (k != i && k != j) {
                        new_data.push_back(nums[k]);
                    }
                }
                auto left = nums[i];
                auto right = nums[j];
                // sum
                pair<int, int> new_num = make_pair(left.first * right.second + left.second * right.first,
                                               right.second * left.second);
                int gcd = get_gcd(new_num.first, new_num.second);
                new_num.first /= gcd;
                new_num.second /= gcd;
                new_data.push_back(new_num);
                if (judge(new_data)) {
                    return true;
                }
                // sub1
                new_num.first = left.first * right.second - left.second * right.first;
                new_num.second = right.second * left.second;
                gcd = get_gcd(new_num.first, new_num.second);
                new_num.first /= gcd;
                new_num.second /= gcd;
                new_data.back() = new_num;
                if (judge(new_data)) {
                    return true;
                }
                // sub2
                new_num.first = -new_num.first;
                new_data.back() = new_num;
                if (judge(new_data)) {
                    return true;
                }
                // product
                new_num.first = left.first * right.first;
                new_num.second = left.second * right.second;
                gcd = get_gcd(new_num.first, new_num.second);
                new_num.first /= gcd;
                new_num.second /= gcd;
                new_data.back() = new_num;
                if (judge(new_data)) {
                    return true;
                }
                // div
                if (right.first == 0 || left.first == 0) {
                    new_num.first = 0;
                    new_num.second = 1;
                    new_data.back() = new_num;
                    if (judge(new_data)) {
                        return true;
                    }
                } else {
                    // div1
                    new_num.first = left.first * right.second;
                    new_num.second = left.second * right.first;
                    gcd = get_gcd(new_num.first, new_num.second);
                    new_num.first /= gcd;
                    new_num.second /= gcd;
                    new_data.back() = new_num;
                    if (judge(new_data)) {
                        return true;
                    }
                    // div2 
                    int tmp = new_num.first;
                    new_num.first = new_num.second;
                    new_num.second = tmp;
                    new_data.back() = new_num;
                    if (judge(new_data)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    int get_gcd(int a, int b) {
        if (a < b) {
            int tmp = b;
            b = a;
            a = tmp;
        }
        if (b == 0) {
            return a;
        }
        while (true) {
            int c = a % b;
            if (c == 0) {
                return b;
            }
            a = b;
            b = c;
        }
        return b;
    }
};
