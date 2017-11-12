/******************************************************************************
 * Given a chemical formula (given as a string), return the count of each atom.
 *
 * An atomic element always starts with an uppercase character, then zero or more
 * lowercase letters, representing the name.
 *
 * 1 or more digits representing the count of that element may follow if the count
 * is greater than 1. If the count is 1, no digits will follow. For example, H2O and
 * H2O2 are possible, but H1O2 is impossible.
 *
 * Two formulas concatenated together produce another formula. For example, H2O2He3Mg4
 * is also a formula.
 *
 * A formula placed in parentheses, and a count (optionally added) is also a formula.
 * For example, (H2O2) and (H2O2)3 are formulas.
 *
 * Given a formula, output the count of all elements as a string in the following
 * form: the first name (in sorted order), followed by its count (if that count is
 * more than 1), followed by the second name (in sorted order), followed by its
 * count (if that count is more than 1), and so on.
 *
 * Example 1:
 * Input: 
 * formula = "H2O"
 * Output: "H2O"
 * Explanation: 
 * The count of elements are {'H': 2, 'O': 1}.
 * Example 2:
 * Input: 
 * formula = "Mg(OH)2"
 * Output: "H2MgO2"
 * Explanation: 
 * The count of elements are {'H': 2, 'Mg': 1, 'O': 2}.
 * Example 3:
 * Input: 
 * formula = "K4(ON(SO3)2)2"
 * Output: "K4N2O14S4"
 * Explanation: 
 * The count of elements are {'K': 4, 'N': 2, 'O': 14, 'S': 4}.
 * Note:
 *
 * All atom names consist of lowercase letters, except for the first character which
 * is uppercase. The length of formula will be in the range [1, 1000]. formula will
 * only consist of letters, digits, and round parentheses, and is a valid formula as
 * defined in the problem.
******************************************************************************/

class Solution {
public:
    string countOfAtoms(string formula) {
        map<string, int> counter;
        int s = 0;
        calc(formula, s, formula.length(), counter);
        stringstream ss;
        for (auto& kv : counter) {
            ss << kv.first;
            if (kv.second > 1) {
                ss << kv.second;
            }
        }
        return ss.str();
    }
    
private:
    void calc(string& f, int& s, int e, map<string, int>& c) {
        if (s == e) {
            return;
        }        
        while (s < e) {
            char ch = f[s];
            if (ch == '(') {
                map<string, int> c2;
                ++s;
                calc(f, s, e, c2);
                // get the number
                if (s == e || f[s] < '1' || f[s] > '9' ) {
                    // case 1
                    for (auto& kv : c2) {
                        c[kv.first] += kv.second;
                    }
                } else {
                    int base = 0;
                    while (s < e && (f[s] >= '0'&& f[s] <= '9')) {
                        base *= 10;
                        base += (f[s] - '0');
                        ++s;
                    }
                    for (auto& kv : c2) {
                        c[kv.first] += kv.second * base;
                    }
                }
            } else if (ch == ')') {
                ++s;
                return;
            } else {
                auto pos = f.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXZY123456789()", s + 1);
                if (pos == string::npos) {
                    auto name = f.substr(s);
                    c[name] += 1;
                    s = e;
                } else {
                    auto name = f.substr(s, pos - s);
                    s = pos;
                    int base = 0;
                    while (s < e && (f[s] >= '0' && f[s] <= '9')) {
                        base *= 10;
                        base += (f[s] - '0');
                        ++s;
                    }
                    c[name] += max(base, 1);
                }              
            }
        }
    }
    
};
