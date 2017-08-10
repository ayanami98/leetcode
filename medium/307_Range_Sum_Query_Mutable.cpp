#include <iostream>
#include <vector>

using namespace std;

class BITree {
public:
    BITree(const vector<int>& nums)
    : max_num(nums.size() + 1), btree(max_num, 0) {
        for (int i = 1; i < max_num; ++i) {
            update(i, nums[i - 1]);
        }
    }
    
    void update(int idx, long long int delta_val) {
        while (idx < max_num) {
            btree[idx] += delta_val;
            idx = next(idx);
        }
    }
    
    long long int sum(int idx) {
        int sum = 0;
        if (idx < max_num) {
            while (idx > 0) {
                sum += btree[idx];
                idx = parent(idx);
            }
        }
        return sum;
    }

private:
    int parent(int idx) {
        return idx - (idx & -idx);
    }
    
    int next(int idx) {
        return idx + (idx & -idx);
    }
    
private:
    int max_num = 0;
    vector<long long int> btree;
};

class NumArray {
public:
    NumArray(vector<int> nums) : btree(nums), ns(nums) {
    }
    
    void update(int i, int val) {
        btree.update(i + 1, val - ns[i]);
        ns[i] = val;
    }
    
    long long int sumRange(int i, int j) {
        return btree.sum(j + 1) - btree.sum(i);
    }

private:
    BITree btree;
    vector<int> ns;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */

int main() {
  vector<int> nums({7, 2, 7, 2, 0});
  NumArray array(nums);
  array.update(4, 6);
  array.update(0, 2);
  cout << array.sumRange(0, 2) << endl;
  return 0;
}
