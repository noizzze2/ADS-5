// Copyright 2025 NNTU-CS
#include <string>
#include "tstack.h"

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> st;
    std::string result = "";

    size_t i = 0;
    while (i < inf.length()) {
        char c = inf[i];

        if (c == ' ') {
            ++i;
            continue;
        }

        if (isDigit(c)) {
            while (i < inf.length() && isDigit(inf[i])) {
                result += inf[i];
                ++i;
            }
            result += ' ';
            continue;
        }

        if (c == '(') {
            st.push(c);
            ++i;
            continue;
        }

        if (c == ')') {
            while (!st.isEmpty() && st.top() != '(') {
                result += st.pop();
                result += ' ';
            }
            if (!st.isEmpty() && st.top() == '(') {
                st.pop();
            }
            ++i;
            continue;
        }

        if (isOperator(c)) {
            while (!st.isEmpty() && st.top() != '(' &&
                   precedence(st.top()) >= precedence(c)) {
                result += st.pop();
                result += ' ';
            }
            st.push(c);
            ++i;
            continue;
        }

        ++i;
    }

    while (!st.isEmpty()) {
        result += st.pop();
        result += ' ';
    }

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> st;

    size_t i = 0;
    while (i < post.length()) {
        char c = post[i];

        if (c == ' ') {
            ++i;
            continue;
        }

        if (isDigit(c)) {
            int num = 0;
            while (i < post.length() && isDigit(post[i])) {
                num = num * 10 + (post[i] - '0');
                ++i;
            }
            st.push(num);
            continue;
        }

        if (isOperator(c)) {
            int b = st.pop();
            int a = st.pop();
            int res = 0;

            switch (c) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
            }
            st.push(res);
            ++i;
            continue;
        }

        ++i;
    }

    if (st.isEmpty()) {
        return 0;
    }
    return st.pop();
}
