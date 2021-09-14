//
// Created by 13495 on 9/11/2021.
//

#ifndef C___TINY_CALCULATOR_H
#define C___TINY_CALCULATOR_H
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class calculator {
private:
    string expression_string;
    stack<char> bracket_stack;
    stack<string> formula_stack;
    static unordered_map<char,char> bracket_map;
    static unordered_set<char> mark_set;
    static unordered_set<char> bracket_set;
    static unordered_set<char> operator_set;
public:
    bool illegal_formula;
    double result;
    vector<string> expression_vector;
    vector<string> suffix_vector;
    bool check(string str);
    void convert_string_to_vector();
    void convert_to_suffix();
    double calculate_suffix_expression();
};


#endif //C___TINY_CALCULATOR_H
