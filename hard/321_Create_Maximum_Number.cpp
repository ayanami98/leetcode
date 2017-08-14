#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int size1 = nums1.size();
        int size2 = nums2.size();
        deque<int> digit_pos1;
        deque<int> digit_pos2;
        for (int i = 0; i < min(k, size1); ++i) {
            insertOneDigit(nums1, digit_pos1);
        }
        vector<int> result(k, 0);
        for (int i = min((int)nums1.size() - k, 0); i < 0; ++i) {
            insertOneDigit(nums2, digit_pos2);
        }
        for (int i = 0; i <= k; ++i) {
            merge(nums1, nums2, digit_pos1, digit_pos2, result);
            cout << "num1 = ";
            for (auto pos : digit_pos1) {
                cout << nums1[pos] << " ";
            }
            cout << endl;
            cout << "num2 = ";
            for (auto pos : digit_pos2) {
                cout << nums2[pos] << " ";
            }
            cout << endl;
            cout << "result = ";
            for (auto num : result) {
                cout << num << " ";
            }
            cout << endl;
            if (digit_pos1.empty() || digit_pos2.size() == size2) {
                break;
            } 
            removeOneDigit(nums1, digit_pos1);
            insertOneDigit(nums2, digit_pos2);
        }
        return result;
    }
    
private:
    void merge(const vector<int>& nums1, const vector<int>& nums2, 
        const deque<int>& pos1, const deque<int>& pos2, vector<int>& max_num) {
        int start1 = 0;
        int end1 = pos1.size();
        int start2 = 0;
        int end2 = pos2.size();
        int idx = 0;
        bool exceed = false;
        while (idx < max_num.size()) {
            int new_digit = -1;
            if (start1 == end1) { // num1 reach the end
                new_digit = nums2[pos2[start2++]];
            } else if (start2 == end2) { // num2 reach the end
                new_digit = nums1[pos1[start1++]];
            } else {
                int n1 = nums1[pos1[start1]];
                int n2 = nums2[pos2[start2]];
                if (n1 > n2) { 
                    new_digit = n1;
                    ++start1;
                } else if (n1 < n2) {
                    new_digit = n2;
                    ++start2;
                } else {
                    bool choose_num1 = true;
                    int count = min(end1 - start1, end2 - start2);
                    int i = 1;
                    for (; i < count; ++i) {
                        int n1 = nums1[pos1[start1 + i]];
                        int n2 = nums2[pos2[start2 + i]];
                        if (n1 < n2) {
                            choose_num1 = false;
                            break;
                        } else if (n1 > n2) {
                            break;
                        }
                    }
                    if (start1 + i == end1) { // num1 maybe the shorter one
                        choose_num1 = false;
                    }
                    if (choose_num1) { // num1 is our candidate
                        for (int j = 0; j < i; ++j) {
                            int n = nums1[pos1[start1]];
                            if (n != n1) {
                              break;
                            }
                            if (exceed || n > max_num[idx]) {
                                exceed = true;
                                max_num[idx] = n;
                            } else if (n < max_num[idx]) {
                                return;
                            }
                            ++idx;
                            ++start1;
                        }
                    } else {
                        for (int j = 0; j < i; ++j) {
                            int n = nums2[pos2[start2]];
                            if (n != n2) {
                                break;
                            }
                            if (exceed || n > max_num[idx]) {
                                exceed = true;
                                max_num[idx] = n;
                            } else if (n < max_num[idx]) {
                                return;
                            }
                            ++idx;
                            ++start2;
                        }
                    }
                    continue;
                }
            }
            if (exceed || new_digit > max_num[idx]) {
                exceed = true;
                max_num[idx] = new_digit;
            } else if (new_digit < max_num[idx]) {
                break;
            }
            ++idx;
        }
    } 
    
    void removeOneDigit(const vector<int>& nums, deque<int>& pos) {
        int size = pos.size();
        if (size == 0) {
            return;
        } else if (size == 1) {
            pos.pop_back();
            return;
        }
        int last_pos = 0;
        int last_num = nums[pos[0]];
        for (auto it = pos.begin() + 1; it != pos.end(); ++it) {
            int num = nums[*it];
            if (last_num < num) {
                pos.erase(--it);
                return;
            }
            last_num = num;
        }
        pos.pop_back(); // pop the laste element if the pos is in descending order
    }
    
    void insertOneDigit(const vector<int>& nums, deque<int>& pos) {
        int total_num = nums.size();
        int current_num = pos.size();
        int insert_pos = -1;
        int start = -1; // starting spot for searching
        int end = -1;   // ending spot for searching
        if (current_num == 0) { // init case
            start = 0;
            end = total_num;
            insert_pos = 0;
        } else {
            int remain_num = total_num - pos.back() - 1;
            if (remain_num > 0) {
                start = pos.back() + 1;
                end = total_num;
                insert_pos = current_num; // append to the end
            } else if (current_num == 1) {
                start = 0;
                end = pos.front();
                insert_pos = 0;
            } else {
                // try to find a "hole" in the existing position from the end
                int i = current_num - 2;
                int last_pos = pos.back();
                for (; i >= 0; --i) {
                    int cur_pos = pos[i];
                    if (last_pos - cur_pos != 1) {
                        insert_pos = i + 1;
                        start = pos[i] + 1;
                        end = last_pos;
                        break;
                    }
                    last_pos = cur_pos;
                }
                if (i < 0) {
                    start = 0;
                    end = pos.front();
                    insert_pos = 0;
                }
            }
        }
        int num = nums[start];
        int chosen_pos = start;
        for (int i = start + 1; i < end; ++i) {
            if (nums[i] > num) {
                num = nums[i];
                chosen_pos = i;
            }
        }
        pos.insert(pos.begin() + insert_pos, chosen_pos);
    }
};

int main() {
  vector<int> nums1({5,0,2,1,0,1,0,3,9,1,2,8,0,9,8,1,4,7,3});
  vector<int> nums2({7,6,7,1,0,1,0,5,6,0,5,0});
  auto r = Solution().maxNumber(nums1, nums2, 31);
  for (auto num : r) {
    cout << num << endl;
  }
  return 0;
}
