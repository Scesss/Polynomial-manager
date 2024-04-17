#include "cell.h"

cell::cell() {
    next = prev = nullptr;
    data = nullptr;
    num = -1e9;
}

cell::cell(polynomial &a, int n) {
    *data = a;
    prev = next = nullptr;
    num = n;
}
