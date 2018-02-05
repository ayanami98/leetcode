/******
There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
******/

class Solution {
public:
using iterator = std::vector<int>::iterator;
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int sz1 = nums1.size();
        int sz2 = nums2.size();
        if (sz1 == 0 && sz2 == 0) {
            return 0;
        } else if (sz1 == 0) {
            return (sz2 % 2 == 1) ? nums2[sz2 / 2] : (nums2[sz2 / 2 - 1] + nums2[sz2 / 2]) / 2.0;
        } else if (sz2 == 0) {
            return (sz1 % 2 == 1) ? nums1[sz1 / 2] : (nums1[sz1 / 2 - 1] + nums1[sz1 / 2]) / 2.0;
        }
        int total_size = sz1 + sz2; 
        if (total_size & 0x1) {
            return topK(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), total_size / 2 + 1);
        } else {
            return topK(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), total_size / 2) / 2 +
                   topK(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), total_size / 2 + 1) / 2;
        }
    }
    
private:
    double topK(iterator s1, iterator e1, iterator s2, iterator e2, int k) {
        // cout << *s1 << ", " << *e1 << " -- " << *s2 << ", " << *e2 << " --- " << k << endl;
        if (s1 == e1) {
            return *(s2 + k - 1);
        } else if (s2 == e2) {
            return *(s1 + k - 1);
        }
        int distance = std::distance(s1, e1);
        auto mid = s1 + distance / 2;
        auto it2 = upper_bound(s2, e2, *mid);
        int distance2 = std::distance(s2, it2);
        int total_num = distance / 2 + 1 + distance2;
        // cout << "mid = " << *mid << ":" << total_num << endl;
        if (total_num == k) {
            return *mid;
        } else if (total_num > k) {
            return topK(s1, mid, s2, it2, k);
        } else {
            return topK(mid + 1, e1, it2, e2, k - total_num);
        }
    }
};
