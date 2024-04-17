#include "dataBase.h"
#include "cell.h"
#include "polynomial.h"

dataBase::dataBase() {
    size = 0;
    head = tail = nullptr;
}

bool dataBase::is_empty() const {
    return (size == 0);
}

void dataBase::insert(polynomial &a, int n) {
    auto c = new cell(a, n);
    if (is_empty()) {
        head = c;
        tail = c;
        head->prev = tail->next = nullptr;
    } else {
        tail->next = c;
        tail->next->prev = tail;
        tail = tail->next;
        tail->next = nullptr;
    }
    ++size;
}

void balance(cell *c) {
    for (; c != nullptr; c = c->next) {
        c->num = c->num -1;
    }
}

void dataBase::delete_cell(int n) {
    cell *c = head;
    int i = 0;
    while (c->num != n || i++ != size) {
        c = c->next;
    }
    if (i == size) {
        return;
    }
    c->next->prev = c->prev;
    c->prev->next = c->next;
    balance(c);
    delete c;
}
