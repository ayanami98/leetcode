/******************************************************************************
 * Copyright (c)  2017, TigerGraph Inc.                                    *
 * All rights reserved                                                        *
 * Unauthorized copying of this file, via any medium is strictly prohibited   *
 * Proprietary and confidential                                               *
 ******************************************************************************
* File Name : 736_Parse_Lisp_Expression.cpp
*
* Created on : 2017-11-25
* Author : tufeng
*
* Last Modified : Sat 25 Nov 2017 08:07:50 PM PST
******************************************************************************/

#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;


class Solution {
public:
    int evaluate(string expression) {
        unordered_map<string, int> env;
        int s = 0;
        if (expression.back() == ')') {
            s = 1;
        } else {
            s = 0;
        }
        return eval(expression, s, env);
    }
    
private:
    int eval(const string& exp, int& s, unordered_map<string, int> env) {
        string op = token(exp, s);
        cout << "op = " << op << endl;
        ++s;
        if (op == "let") {
            string var;
            while (s < exp.size()) {
                string t1 = token(exp, s);
                if (exp[s] == '(') {
                  ++s;
                  int r = eval(exp, s, env);
                  ++s;
                  return r;
                }
                if (exp[s] == ')') { // reach the end
                  ++s;
                  return env.count(t1) > 0 ? env[t1] : stoi(t1);
                }
                ++s; // skip space
                if (exp[s] == '(') {
                    ++s;
                    env[t1] = eval(exp, s, env);
                } else {
                    auto t2 = token(exp, s);
                    if (env.count(t2) > 0) {
                      env[t1] = env[t2];
                    } else {
                      env[t1] = stoi(t2);
                    }
                    ++s;
                }
            }
        } else if (op  == "add") {
            int left = 0;
            int right = 0;
            if (exp[s] == '(') {
                ++s;
                left = eval(exp, s, env);
            } else {
                auto t1 = token(exp, s);
                if (env.count(t1) > 0) {
                    left = env[t1];
                } else {
                    left = stoi(t1);
                }
            }
            ++s; // skip space
            if (exp[s] == '(') {
                ++s;
                right = eval(exp, s, env);
            } else {
                auto t2 = token(exp, s);
                if (env.count(t2) > 0) {
                    right = env[t2];
                } else {
                    right = stoi(t2);
                }
            }
            ++s;
            return left + right;
        } else if (op == "mult") {
            int left = 0;
            int right = 0;
            if (exp[s] == '(') {
                ++s;
                left = eval(exp, s, env);
            } else {
                auto t1 = token(exp, s);
                if (env.count(t1) > 0) {
                    left = env[t1];
                } else {
                    left = stoi(t1);
                }
            }
            ++s; // skip space
            if (exp[s] == '(') {
                ++s;
                right = eval(exp, s, env);
            } else {
                auto t2 = token(exp, s);
                if (env.count(t2) > 0) {
                    right = env[t2];
                } else {
                    right = stoi(t2);
                }
            }
            ++s;
            return left * right;
        } else {
            ++s;
            return env[op];
        }
        
    }
    
    string token(const string& exp, int& s) {
        while (exp[s] == ' ') {
            ++s;
        }
        int p1 = s;
        auto pos = exp.find_first_of(" )(", s);
        if (pos == string::npos) {
            s = exp.size();
            return exp.substr(p1);
        } else {
            s = pos;
            return exp.substr(p1, pos - p1);
        }
    }
};

int main() {
  cout << Solution().evaluate("(let x 7 -12)") << endl;
  return 0;
}
