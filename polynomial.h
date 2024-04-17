//
// Created by Иванов Кирилл on 21.03.2024.
//

#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include "algorithm"
#include "deque"
#include "stack"
#include "climits"
#include "queue"
#include "fstream"
#include "random"
#include "monomial.h"


using namespace std;
//#define int long long;

int polynomial_check(string &a);

class polynomial {

private:
    monomial *head, *tail;
    long long sz;
    vector <bool> variables;
public:
    polynomial();

    polynomial(string& a);

    explicit polynomial(vector <monomial*> &a);

    polynomial(const polynomial &a);

    ~polynomial();

    vector <long long> roots();

    [[nodiscard]] bool is_empty() const;

    void insert(monomial *a);

    long long value(vector <int> &a);

    friend std::ostream& operator<<(std::ostream& out, const polynomial& p);

    bool operator==(polynomial &a);

    bool operator!=(polynomial &a);

    [[nodiscard]] long long size() const;

    vector <bool> variable();

    void poly_sort();

    polynomial operator+(polynomial& a);

    polynomial operator-(polynomial& a);

    polynomial operator*(polynomial &a);

    pair <polynomial, polynomial> operator/(polynomial &a);

    void operator+=(polynomial& a);

    void normalize();

    polynomial derivative(char x);

    polynomial derivative(int n, char x);

    [[nodiscard]] monomial* p_head() const;

    [[nodiscard]] monomial* p_tail() const;

    vector <bool> variabless();

    string to_string();
};

