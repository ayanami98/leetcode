/******************************************************************************
 * There is a garden with N slots. In each slot, there is a flower. The N flowers
 * will bloom one by one in N days. In each day, there will be exactly one flower
 * blooming and it will be in the status of blooming since then.
 *
 * Given a array flowers consists of number from 1 to N. Each number in the array
 * represents the place where the flower will open in that day.
 *
 * For example, flowers[i] = x means that the unique flower that blooms at day i
 * will be at position x, where i and x will be in the range from 1 to N.
 *
 * Also given an integer k, you need to output in which day there exists two
 * flowers in the status of blooming, and also the number of flowers between them
 * is k and these flowers are not blooming.
 *
 * If there isn't such day, output -1.
 *
 * Example 1:
 * Input: 
 * flowers: [1,3,2]
 * k: 1
 * Output: 2
 * Explanation: In the second day, the first and the third flower have become blooming.
 * Example 2:
 * Input: 
 * flowers: [1,2,3]
 * k: 1
 * Output: -1
 * Note:
 * The given array will be in the range [1, 20000]. 
 ******************************************************************************/

ass Solution {
public:
    int kEmptySlots(vector<int>& flowers, int k) {
        multiset<int> windows;
        vector<int> f(flowers.size());
        for (int i = 0; i < flowers.size(); ++i) {
            f[flowers[i] - 1] = i + 1;
        }
        int window_size = k + 2;
        if (window_size > f.size()) {
            return -1;
        }
        // init window
        int max_day2 = INT_MAX;
        int s = 1;
        for (int i = 0; i < k; ++i) {
            windows.insert(f[s + i]);
        }
        int max_day = max(f[0], f[k + 1]);
        if (windows.empty() || max_day < *windows.begin()) {
            if (max_day < max_day2) {
                max_day2 = max_day;
            }
        }
        for (int e = k + 2; e < f.size(); ++e) {
            int s = e - k - 1;
            windows.insert(f[e - 1]);
            windows.erase(f[s]);
            int max_day = max(f[e], f[s]);
            if (windows.empty() || max_day < *windows.begin()) {
                if (max_day < max_day2) {
                    max_day2 = max_day;
                }
            }
        }
        return max_day2 == INT_MAX ? -1 : max_day2;
    }
};
