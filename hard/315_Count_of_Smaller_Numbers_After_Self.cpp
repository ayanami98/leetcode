/*********************************************************************
 * You are given an integer array nums and you have to return a new counts
 * array. The counts array has the property where counts[i] is the number
 * of smaller elements to the right of nums[i].
 *
 * Example:
 * Given nums = [5, 2, 6, 1]
 *
 * To the right of 5 there are 2 smaller elements (2 and 1).
 * To the right of 2 there is only 1 smaller element (1).
 * To the right of 6 there is 1 smaller element (1).
 * To the right of 1 there is 0 smaller element.
 * Return the array [2, 1, 1, 0].
 *********************************************************************/

class BIT {
public:
    BIT(long long int max) : max_num(max) {
    }
    
    void insert(long long int x) {
        while (x <= max_num) {
            ++counters[x];
            x += lowbit(x);
        }
    }

    int sum(long long int x) {
        int sum = 0;
        while (x > 0) {
            sum += counters[x];
            x = x - lowbit(x);
        }
        return sum;
    }

private:
    long long int lowbit(long long int x) const {
        return (x & -x);
    }

private:
    long long int max_num = 0;
    unordered_map<long long int, int> counters; // hash_map<number, count>
};

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> result;
        long long int max_num = INT_MIN;
        long long int min_num = INT_MAX;
        for (long long int num : nums) {
            if (max_num < num) {
                max_num = num;
            }
            if (min_num > num) {
                min_num = num;
            }
        }
        BIT bitree(max_num - min_num + 1);
        for (int i = nums.size() - 1; i >= 0; --i) {
            long long int num = nums[i] - min_num + 1;
            bitree.insert(num);
            result.push_back(bitree.sum(num - 1));
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
