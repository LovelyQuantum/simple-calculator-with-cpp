//
// Created by 13495 on 9/11/2021.
//

#include "calculator.h"
#include <algorithm>
#include <utility>
#include <iostream>

unordered_map<char, char> calculator::bracket_map = {{')', '('},
                                                     {']', '['},
                                                     {'}', '{'}};
unordered_set<char> calculator::mark_set = {'+', '-', '*', '/', '(', ')', '[', ']', '{', '}'};
unordered_set<char> calculator::bracket_set = {'(', '[', '{'};
unordered_set<char> calculator::operator_set = {'+', '-', '*', '/'};

bool calculator::check(string str) {
//    clean bracket_stack
    while (!bracket_stack.empty())
        bracket_stack.pop();

    expression_string = move(str);
//    remove spaces in expression
    auto iterator = remove_if(expression_string.begin(), expression_string.end(), ::isspace);
    expression_string.erase(iterator, expression_string.end());

    if (any_of(expression_string.begin(), expression_string.end(),
               [](char c) { return mark_set.find(c) == mark_set.end() && (c < 48 || c > 57); })) {
        illegal_formula = true;
        return false;
    }
    for (char item: expression_string) {
        if (item == '(' || item == '[' || item == '{') {
            bracket_stack.push(item);
        }
        if (item == ')' || item == ']' || item == '}') {
            if (bracket_stack.empty() || bracket_map[item] != bracket_stack.top()) {
                illegal_formula = true;
                return false;
            }
            bracket_stack.pop();
        }
    }
    if (bracket_stack.empty()) {
        illegal_formula = false;
        return true;
    }
    illegal_formula = true;
    return false;
}

void calculator::convert_string_to_vector() {
    expression_vector.clear();
    if (illegal_formula) {
        cout << "formula is wrong, check it plz!" << endl;
        return;
    }
    string operand, tmp;
    for (char item: expression_string) {
        if (item >= 48 && item <= 57) {
            operand += item;
        } else {
            if (!operand.empty()) {
                expression_vector.push_back(operand);
                operand = "";
            }
            tmp = item;
            expression_vector.push_back(tmp);
        }
    }
    if (!operand.empty())
        expression_vector.push_back(operand);
}

void calculator::convert_to_suffix() {
    suffix_vector.clear();
    while (!formula_stack.empty())
        formula_stack.pop();
    if (illegal_formula) {
        cout << "formula is wrong, check it plz!" << endl;
        return;
    }
    for (string item: expression_vector) {
        if (mark_set.find(item[0]) == mark_set.end())
            suffix_vector.push_back(item);
        if (bracket_set.find(item[0]) != bracket_set.end())
            formula_stack.push(item);
        if (bracket_map.find(item[0]) != bracket_map.end()) {
            while (formula_stack.top()[0] != bracket_map[item[0]]) {
                suffix_vector.push_back(formula_stack.top());
                formula_stack.pop();
            }
            formula_stack.pop();
        }
        if (operator_set.find(item[0]) != operator_set.end()) {
            if (item == "+" || item == "-") {
                while (!formula_stack.empty() && bracket_set.find(formula_stack.top()[0]) == bracket_set.end()) {
                    suffix_vector.push_back(formula_stack.top());
                    formula_stack.pop();
                }
            }
            if (item == "*" || item == "/") {
                while (!formula_stack.empty() &&
                       bracket_set.find(formula_stack.top()[0]) == bracket_set.end() &&
                       formula_stack.top() != "+" &&
                       formula_stack.top() != "-") {
                    suffix_vector.push_back(formula_stack.top());
                    formula_stack.pop();
                }
            }
            formula_stack.push(item);
        }
    }
    while (!formula_stack.empty()) {
        suffix_vector.push_back(formula_stack.top());
        formula_stack.pop();
    }
}

double calculator::calculate_suffix_expression() {
    while (!formula_stack.empty())
        formula_stack.pop();
    for (string item: suffix_vector) {
        if (operator_set.find(item[0]) == operator_set.end())
            formula_stack.push(item);
        else {
            double right_operand = stod(formula_stack.top());
            formula_stack.pop();
            double left_operand = stod(formula_stack.top());
            formula_stack.pop();
            switch (item[0]) {
                case '+':
                    formula_stack.push(to_string(left_operand + right_operand));
                    break;
                case '-':
                    formula_stack.push(to_string(left_operand - right_operand));
                    break;
                case '*':
                    formula_stack.push(to_string(left_operand * right_operand));
                    break;
                case '/':
                    if (abs(right_operand) < 0.00000001) {
                        cout << "Zero cannot be divisor!" << endl;
                        exit(-1);
                    }
                    formula_stack.push(to_string(left_operand / right_operand));
            }
        }
    }
    result = stod(formula_stack.top());
    return result;
}