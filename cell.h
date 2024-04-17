#include "polynomial.h"
// #include "dataBase.h"

#pragma once
class cell {
public:
// private:
    int num;
    polynomial *data;
    cell *next, *prev;



    cell();

    cell(polynomial &a, int n);

    friend class dataBase;
};


