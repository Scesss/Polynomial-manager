//
// Created by Иванов Кирилл on 03.04.2024.
//

#include "monomial.h"

bool monomial::operator==(monomial &a) {
    return (this->fact == a.fact && this->var == a.var);
}

bool comp(monomial *a, monomial *b) {
    int fi = 0, se = 0;
    long long f_sum = 0, se_sum = 0;
    for (auto & el : a->var) if (el) ++fi, f_sum += el;
    for (auto & el :  b->var) if (el) ++se, se_sum += el;
    return (fi >= se && f_sum >= se_sum);
}

bool similarity(monomial *a, monomial *b) {
    return (a->var == b->var);
}

bool monomial::operator!=(monomial &a) {
    return !(*this == a);
}

std::ostream& operator<<(std::ostream& out, monomial &mon) {
    bool flag = false;
    for (auto & el : mon.var) {
        if (el) flag = true;
    }
    if (!flag) {
        out << (mon.fact >= 0 ? "+" : "") << mon.fact;
        return out;
    }
    if (abs(mon.fact) == 1) {
        if (mon.fact == 1) {
            out << '+';
        } else if (mon.fact == -1) {
            out << '-';
        }
    } else {
        out << (mon.fact >= 0 ? "+" : "") << mon.fact;
    }
    for (int i = 0; i < mon.var.size(); ++i) {
        if (mon.var[i] > 1) {
            out << (char)(i + 'a') << "^" << mon.var[i];
        } else if (mon.var[i] == 1) {
            out << (char)(i + 'a');
        }
    }
    return out;
}

vector <monomial*> to_normal(vector <monomial*> &a) {
    vector <monomial*> ans;
    vector <bool> b(a.size(), false);
    for (int i = 0; i < a.size(); ++i) {
        if (b[i]) continue;
        b[i] = true;
        long long val = a[i]->fact;
        for (int j = 0; j < a.size(); ++j) {
            if (similarity(a[i], a[j]) && !b[j]) {
                val += a[j]->fact;
                b[j] = true;
            }
        }
        if (val == 0) continue;
        monomial* c = a[i];
        c->fact = val;
        ans.push_back(c);
    }
    return ans;
}

monomial::monomial(std::string &a)  {
    var.resize(26, 0);
    prev = next = nullptr;
    string num;
    int i = 0;
    while ((a[i] < 'a' || a[i] > 'z') && i < a.size()) {
        num += a[i++];
    }
    fact = stol(num); // определили множитель одночлена
    if (i == a.size()) return;
    string tmp;
    vector <string> parse;
    bool flag = false;
    for (; i < a.size(); ++i) {
        if ((a[i] >= 'a' && a[i] <= 'z') && flag) {
            if (!isdigit(tmp.back())) tmp += "^1";
            parse.push_back(tmp);
            tmp = "";
            flag = false;
        }
        if ((a[i] >= 'a' && a[i] <= 'z') && !flag) {
            flag = true;
        }
        if (flag) tmp += a[i];
    }
    if (!isdigit(tmp.back())) tmp += "^1";
    parse.push_back(tmp); // массив где храняться строки вида x^N
    for (auto & el : parse) {
        var[el[0] - 'a'] += stol(el.substr(2, el.size() - 1));
    }
}

//monomial::monomial(std::string a) {
//    this = new monomial(a);
//}

monomial::monomial(monomial *other)  {
    var.resize(26, 0);
    fact = other->fact;
    var = other->var;
    prev = other->prev;
    next = other->next;
}

monomial::monomial() {
    prev = nullptr;
    next = nullptr;
    fact = 0;
    var.resize(26, 0);
}

void sort(vector <monomial*> &a) {
    sort(a.begin(), a.end(), comp);
}

monomial* merge(monomial* l, monomial* r) {
    if (l == nullptr) return r;
    if (r == nullptr) return l;
    monomial* cur;
    if (comp(l, r)) {
        cur = l;
        l = l->next;
    } else {
        cur = r;
        r = r->next;
    }
    monomial* beg = cur;
    while (l != nullptr && r != nullptr) {
        if (comp(l, r)) {
            cur->next = l;
            cur->next->prev = cur;
            cur = cur->next;
            l = l->next;
        } else {
            cur->next = r;
            cur->next->prev = cur;
            cur = cur->next;
            r = r->next;
        }
    }
    if (l != nullptr) {
        cur->next = l;
        cur->next->prev = cur;
    }
    if (r != nullptr) {
        cur->next = r;
        cur->next->prev = cur;
    }
    return beg;
}

void mergeSort(monomial*& l, long long n) {
    if (n <= 1) return;
    long long m = n / 2;
    monomial* cur = l;
    for (int i = 0; i < m; ++i) {
        cur = cur->next;
    }
    monomial* r = cur;
    cur->prev->next = nullptr;
    mergeSort(l, m);
    mergeSort(r, n - m);
    l = merge(l, r);
}

int monomial::v_size() const {
    return (int)var.size();
}

//monomial::~monomial() {
//    delete this;
//}

monomial monomial::operator*(monomial &a) {
    auto res = new monomial();
    res->fact = fact * a.fact;
    for (int i = 0; i < 26; ++i) {
        res->var[i] = var[i] + a.var[i];
    }
    return *res;
}

monomial monomial::operator/(monomial &a) {
    auto res = new monomial();
    res->fact = fact / a.fact;
    for (int i = 0; i < 26; ++i) {
        res->var[i] = var[i] - a.var[i];
    }
    return *res;
}

monomial monomial::operator-() {
    auto res = new monomial();
    res->fact = -fact;
    for (int i = 0; i < 26; ++i) {
        res->var[i] = var[i];
    }
    return *res;
}

long long monomial::pow() {
    long long ans = var[0];
    for (int i = 1; i < 26; ++i) {
        ans = max(ans, var[i]);
    }
    return ans;
}

monomial monomial::derivative(char x) {
    auto ans = new monomial();
    ans->fact = fact;
    for (int i = 0; i < 26; ++i) {
        if (i == x - 'a') {
            if (!var[i]) {
                ans->fact = 0;
                break;
            }
            ans->fact *= var[i];
            ans->var[i] = var[i] - 1;
            continue;
        }
        ans->var[i] = var[i];
    }
    return *ans;
}

string monomial::to_string() {
    string ans;
    //    ans += std::to_string(fact);
    bool flag = false;
    for (auto & el : var) {
        if (el) flag = true;
    }
    if (!flag) {
        ans += (fact >= 0 ? "+" : "") + std::to_string(fact);
        return ans;
    }
    if (abs(fact) == 1) {
        if (fact == 1) {
            ans += '+';
        } else if (fact == -1) {
            ans += '-';
        }
    } else {
        ans += (fact >= 0 ? "+" : "") + std::to_string(fact);
    }
    for (int i = 0; i < var.size(); ++i) {
        if (var[i] > 1) {
            char tmp = (char)(i + 'a');
            ans += tmp;
            ans += "^" + std::to_string(var[i]);
        } else if (var[i] == 1) {
            char tmp = (char)(i + 'a');
            ans += tmp;
        }
    }
    return ans;
}
