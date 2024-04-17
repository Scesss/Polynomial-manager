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
#include "monomial.h"
#include "polynomial.h"
#include "cell.h"


using namespace std;
//#define int long long;


class dataBase {
private:
    int size;
    cell *head, *tail;
public:
    ~dataBase();

    dataBase();

    void insert(polynomial &a, int n);

    void delete_cell(int n);

    bool is_empty() const;


};
