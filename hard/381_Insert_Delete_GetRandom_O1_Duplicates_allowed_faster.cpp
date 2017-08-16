ass RandomizedCollection {
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        //srand(time(0));   
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        auto res = lists.insert(make_pair(val, nums.size()));
        if (!res.second) {
            // already exist
            nums.emplace_back(val, res.first->second);
            res.first->second = nums.size() - 1;
        } else {
            nums.emplace_back(val, -1);
        }
        return res.second;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        auto it = lists.find(val);
        if (lists.end() == it) {
            return false;
        } else {
            int offset = it->second;
            auto& erased_slot = nums[offset];
            if (-1 == erased_slot.second) {
                lists.erase(it);
            } else {
                it->second = erased_slot.second;
            }       
            // swap the end slot and erased slot if neccessary
            if (offset < nums.size() - 1) {
                auto slot = &nums.back();
                erased_slot.first = slot->first;
                if (-1 == slot->second) {
                    lists[slot->first] = offset;
                    erased_slot.second = -1;
                } else {
                    while (slot->second != -1 && slot->second > offset) {
                        slot = &nums[slot->second];
                    }
                    if (-1 == slot->second) {
                        // all the slots after erased slot
                        erased_slot.second = -1;
                        slot->second = offset;
                    } else {
                        // find a slot of this list before erased slot
                        erased_slot.second = slot->second;
                        slot->second = offset;
                    }
                    lists[slot->first] = nums.back().second;
                }
            }
            nums.pop_back();
            return true;
        }
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        return nums[rand() % nums.size()].first;
    }

private:
    // pair<val, offset>
    vector<pair<int, int>> nums;
    unordered_map<int, int> lists;
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
