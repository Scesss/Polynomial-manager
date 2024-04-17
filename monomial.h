//
// Created by Иванов Кирилл on 01.04.2024.
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


using namespace std;
//#define int long long;

class polynomial;

class monomial {
private:
    vector <long long> var;
    long long fact;
    monomial *prev, *next;
public:
    monomial();

    //    ~monomial();

    explicit monomial(string& a);

    //    explicit monomial(string a);

    explicit monomial(monomial* other);

    friend bool comp(monomial *a, monomial *b);

    friend bool similarity(monomial *a, monomial *b);

    friend std::ostream& operator<<(std::ostream& out, monomial &mon);

    friend vector <monomial*> to_normal(vector <monomial*> &a);

    friend class polynomial;

    friend std::ostream& operator<<(std::ostream& out, const polynomial &p);

    bool operator==(monomial &a);

    bool operator!=(monomial &a);

    friend void sort(vector <monomial*> &a);

    friend void mergeSort(monomial*& l, long long n);

    friend monomial* merge(monomial* l, monomial* r);

    monomial operator*(monomial &a);

    monomial operator-();

    monomial derivative(char x);

    monomial operator/(monomial &a);

    [[nodiscard]] int v_size() const;

    long long pow();

     string to_string();
};

