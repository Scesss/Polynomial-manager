// ладно, теперь в самый низ

//
// Created by Иванов Кирилл on 03.04.2024.
//
#include "polynomial.h"

vector<bool> polynomial::variable() {
    return variables;
}

long long fast(long long a, long long n, long long m) {
    if (n == 0) return 1;
    if (n == 1) return a;
    if (n % 2 == 0) {
        long long g = fast(a, n / 2, m);
        return g * g % m;
    } else return fast(a, --n, m) * a % m;
}

long long polynomial::size() const {
    return sz;
}

long long polynomial::value(vector<int> &a) {
    //size always 26, a[i] value -- (i + 'a') variable value
    long long ans = 0;
    for (auto *p = head; p != nullptr; p = p->next) {
        long long tmp = p->fact;
        for (int i = 0; i < 26; ++i) {
            long long pow = fast(a[i], p->var[i], 1e9);
            tmp *= pow;
        }
        ans += tmp;
    }
    return ans;
}

std::ostream &operator<<(std::ostream &out, const polynomial& p) {
    for (auto *tmp = p.head; tmp != nullptr; tmp = tmp->next) {
        if (tmp->next != nullptr) {
            if (tmp->fact) out << *tmp;
            continue;
        }
        out << *tmp;
    }
    return out;
}


polynomial::polynomial(vector<monomial *> &a) {
    variables.resize(26, false);
    sz = 0;
    head = tail = nullptr;
    for (auto &el: a) insert(el);
}

polynomial::polynomial() {
    variables.resize(26, false);
    head = nullptr;
    tail = nullptr;
    sz = 0;
}

polynomial::~polynomial() {
    for (auto &p = head; p != nullptr; p = p->next) {
        auto *&tmp = p;
        delete tmp;
    }
    //std::cout << "вызван деструктор" << '\n';
}

bool polynomial::is_empty() const {
    return (sz == 0);
}

void polynomial::insert(monomial *a) {
    //    cout << "ZAhel";
    if (is_empty()) {
        head = a;
        tail = a;
        head->prev = tail->next = nullptr;
    } else {
        tail->next = a;
        tail->next->prev = tail;
        tail = tail->next;
        tail->next = nullptr;
    }
    for (int i = 0; i < 26; ++i) {
        if (a->var[i]) variables[i] = true;
    }
    ++sz;
    //    normalize();
}

int polynomial_check(string &a) {
    if (a.empty()) throw static_cast <int> (10);
    try {
        int cond = 0;
        for (auto &el: a) {
            if (el >= 'a' && el <= 'z' && !cond) {
                cond = 1;
                continue;
            } else if (isdigit(el) && !cond) {
                cond = 2;
                continue;
            } else if (el == '^' && !cond) {
                cond = 3;
                continue;
            } else if ((el == '+' || el == '-') && !cond) {
                cond = 4;
                continue;
            } else if (!cond) {
                throw static_cast <int> (11);
            } else if (cond == 1) {
                if (el >= '0' && el <= '9') {
                    throw static_cast <int> (7);
                } else if (el == '+' || el == '-') {
                    cond = 4;
                } else if (el == '^') {
                    cond = 3;
                } else if (el >= 'a' || el <= 'z') {
                    continue;
                } else if (el < 'a' || el > 'z') {
                    throw static_cast <int> (1);
                } else {
                    throw static_cast <int> (11);
                }
            } else if (cond == 2) {
                if (el == '^') {
                    throw static_cast <int> (2);
                } else if (el == '-' || el == '+') {
                    cond = 4;
                } else if (el >= 'a' && el <= 'z') {
                    cond = 1;
                } else if (isdigit(el)) {
                    continue;
                } else {
                    throw static_cast <int> (11);
                }
            } else if (cond == 3) {
                if (!isdigit(el)) {
                    throw static_cast <int> (3);
                }
                cond = 5;
            } else if (cond == 4) {
                if (el >= 'a' && el <= 'z') {
                    cond = 1;
                } else if (isdigit(el)) {
                    cond = 2;
                } else {
                    throw static_cast <int> (4);
                }
            } else if (cond == 5) {
                if (el == '-' || el == '+') {
                    cond = 4;
                } else if (el >= 'a' && el <= 'z') {
                    cond = 1;
                } else if (!isdigit(el)) {
                    throw static_cast <int> (3);
                } else {
                    throw static_cast <int> (11);
                }
            }
        }
        if (cond == 3) {
            throw static_cast <int> (3);
        }
        if (cond == 4) {
             throw static_cast <int> (4);
        }


    } catch (int a) {
        // if (a == 0) {
        //     cout << "Expected variable found integer (ты вообще тепленький)";
        // } else if (a == 1) {
        //     cout << "Expected variable found ???";
        // } else if (a == 2) {
        //     cout << "Expected integer found ^";
        // } else if (a == 3) {
        //     cout << "Expected integer found ???";
        // } else if (a == 4 || a == 5) {
        //     cout << "Expected monomial found not monomial";
        // } else if (a == 10) {
        //     cout << "Empty string";
        // }
        return a;
    }
    return 0;
}


vector<string> parse(string a) {
    vector<string> b;
    string tmp;
    bool flag = false;
    if (a[0] != '-' && isdigit(a[0])) {
        a = '+' + a;
    } else if (a[0] != '-' && !isdigit(a[0])) {
        a = "+1" + a;
    } else if (a[0] == '-' && !isdigit(a[1])) {
        std::string tmp2 = "";
        tmp2 = a[0];
        tmp2 += "1" + a.substr(1, a.size() - 1);
        a = tmp2;

    }
    for (auto &el: a) {
        if ((el == '+' || el == '-') && flag) {
            if (!isdigit(tmp[1])) {
                std::string tmp2 = "";
                tmp2 += tmp[0];
                tmp2 += "1" + tmp.substr(1, tmp.size() - 1);
                tmp = tmp2;
            }
            b.push_back(tmp);
            tmp = "";
            flag = false;
        }
        if ((el == '+' || el == '-') && !flag) {
            flag = true;
        }
        if (flag) tmp += el;
    }
    if (!isdigit(tmp[1])) {
        std::string tmp2 = "";
        tmp2 += tmp[0];
        tmp2 += "1" + tmp.substr(1, tmp.size() - 1);
        tmp = tmp2;
    }
    b.push_back(tmp);
    return b;
}
//23xx-5x^2+3x^2-56xy-50+56xy+xy

polynomial::polynomial(string &a) {
    if (a == "0") {
        insert(new monomial(a));
        return;
    }
    polynomial_check(a);
    variables.resize(26, false);
    head = tail = nullptr;
    sz = 0;
    vector<string> parsed = parse(a);
    vector<monomial*> normalize;
    normalize.reserve((int)parsed.size());
    for (auto &el: parsed) {
        normalize.push_back(new monomial(el));
    }
    normalize = to_normal(normalize);

    for (auto &el: normalize) {
        insert(el);
    }
    poly_sort();
}

bool polynomial::operator==(polynomial &a) {
    if (sz != a.sz) return false;
    for (auto f = this->head, s = a.head; f != nullptr && s != nullptr; f = f->next, s = s->next) {
        //cout << f << " " << s;
        if (*f != *s) return false;
    }
    return true;
}

bool polynomial::operator!=(polynomial &a) {
    return !(*this == a);
}

void polynomial::poly_sort() {
    mergeSort(head, sz);
}

polynomial polynomial::operator+(polynomial& a) {
    auto copy = new polynomial();
    for (auto tmp = a.head; tmp != nullptr; tmp = tmp->next) {
        copy->insert(new monomial(tmp));
        //        cout << "(" << *tmp << ")";
    }
    for (auto tmp = head; tmp != nullptr; tmp = tmp->next) {
        copy->insert(new monomial(tmp));
        //        cout << "(" << *tmp << ")";
    }
    copy->normalize();
    if (copy->is_empty()) {
        string null = "0";
        copy->insert(new monomial(null));

    }
    return *copy;
}

polynomial polynomial::operator-(polynomial &a) {
    auto copy = new polynomial();
    for (auto tmp = a.head; tmp != nullptr; tmp = tmp->next) {
        copy->insert(new monomial(-*tmp));
        //        cout << "(" << *tmp << ")";
    }
    for (auto tmp = head; tmp != nullptr; tmp = tmp->next) {
        copy->insert(new monomial(*tmp));
        //        cout << "(" << *tmp << ")";
    }
    copy->normalize();
    if (copy->is_empty()) {
        string null = "0";
        copy->insert(new monomial(null));

    }
    return *copy;
}

polynomial polynomial::operator*(polynomial &a) {
    string null = "0";
    auto copy = new polynomial();
    for (auto *first = this->head; first != nullptr; first = first->next) {
        for (auto *second = a.head; second != nullptr; second = second->next) {
            copy->insert(new monomial(*first * *second));
        }
    }
    copy->normalize();
    if (copy->is_empty()) copy->insert(new monomial(null));
    return *copy;
}

pair <polynomial, polynomial> polynomial::operator/(polynomial &a) {
    if (a.head == nullptr || a.head->fact == 0) {
        throw static_cast <int> (228);
    }
    string h = "0";
    auto integer = new polynomial(), remainder = new polynomial();
    auto variable = new polynomial(*this);

    while (!variable->is_empty() && variable->head->pow() >= a.head->pow()) {
        auto tmp = (*variable->head / *a.head);
        auto multiplier = new polynomial();
        integer->insert(new monomial(tmp));
        multiplier->insert(&tmp);
        auto subtrahend = (*multiplier * a);
        if (variable->head->fact % a.head->fact) {
            variable = new polynomial(*variable - subtrahend);
            variable->normalize();
            if (variable->sz == 1) {
                remainder->insert(new monomial(variable->head));
                delete variable;
                variable = new polynomial();
                break;
            }
            variable->head = variable->head->next;
            remainder->insert(new monomial(variable->head->prev));
            delete variable->head->prev;
        } else {
            if (*variable == subtrahend) {
                remainder->insert(new monomial(h));
                variable = new polynomial(h);
                break;
            }
            variable = new polynomial(*variable - subtrahend);
        }
        variable->normalize();
    }
    for (auto tmp = variable->head ; tmp != nullptr; tmp = tmp->next) {
        remainder->insert(new monomial(tmp));
    }
    if (remainder->is_empty()) remainder->insert(new monomial(h));
    if (integer->is_empty()) {
        integer->insert(new monomial(h));
        return make_pair(*integer, *this);
    }
    return make_pair(*integer, *remainder);
}

void polynomial::operator+=(polynomial& a) {
    *this = *this + a;
}

void polynomial::normalize() {
    vector<monomial*> tmp;
    for (auto *p = head; p != nullptr; p = p->next) {
        tmp.push_back(p);
    }
    tmp = to_normal(tmp);
    auto *t = new polynomial(tmp);
    t->poly_sort();
    //    delete this;
    *this = *t;
}

polynomial::polynomial(const polynomial &a) {
    variables.resize(26, false);
    sz = 0;
    for (auto tmp = a.head; tmp != nullptr; tmp = tmp->next) {
        insert(new monomial(tmp));
    }
    head->prev = a.head->prev;
    tail->next = a.tail->next;
}

monomial* polynomial::p_head() const {
    return head;
}

monomial* polynomial::p_tail() const {
    return tail; // ты вообще тепленкий нахуй, очень классно придумал такой код писать
    // это как ты придумал так
}

void rec(vector <pair<int, int> > &fact, const string cur, vector <string> &ans, int id = 0) {
    if (id == fact.size()) {
        ans.push_back(cur);
        return;
    }
    for (int i = 0; i <= fact[id].second; ++i) {
        rec(fact, cur + to_string(i), ans, id + 1);
    }
}

vector <long long> polynomial::roots() {

    vector <long long> ans;
    vector <int> disc(26, 0);
    int variable;
    bool zero = false;
    for (auto & el : tail->var) {
        if (el) zero = true;
    }
    if (zero) ans.push_back(0); // zero is a root if last monomial has variable value

    for (int i = 0; i < 26; ++i) {
        if (head->var[i]) variable = i;
    }

    //factorizing last factor to {value, degree of inclusion} pairs:
    long long n = abs(tail->fact);
    vector <pair <int, int> > fact;
    for (int i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            if (fact.empty() || fact.back().first != i) fact.emplace_back(i, 1);
            else fact.back().second++;
            n /= i;
        }
    }
    if (n != 1) {
        if (fact.empty() || fact.back().first != n) fact.emplace_back(n, 1);
        else fact.back().second++;
    }

    vector <string> comb;
    rec(fact, "", comb, 0); //returns all combinations of degrees of occurrence
    //    for (auto & el : comb) cout << el << " ";
    //divider constructor:
    vector <long long> del;
    for (auto & el : comb) {
        long long tmp = 1;
        for (int j = 0; j < fact.size(); ++j) {
            tmp *= fast(fact[j].first, el[j] - '0', 1e9 + 7);
        }
        del.push_back(tmp);
        del.push_back(-tmp);
    }

    //root search
    for (auto & el : del) {
        disc[variable] = (int)el;
        if (value(disc) == 0) {
            ans.push_back(el);
        }
    }
    return ans;
}

string null = "0";

polynomial polynomial::derivative(int n, char x) {
    auto ans = new polynomial(*this);
    auto nulls = new polynomial();
    nulls->insert(new monomial(null));
    for (int i = 0; i < n; ++i) {
        if (*ans == *nulls) {
            return *ans;
        }
        ans = new polynomial(ans->derivative(x));
        //        cout << *ans;
    }
    return *ans;
}


polynomial polynomial::derivative(char x) {
    auto ans = new polynomial();
    for  (auto m = head; m != nullptr; m = m->next) {
        ans->insert(new monomial(m->derivative(x)));
    }
    ans->normalize();
    if (ans->is_empty()) {
        ans->insert(new monomial(null));
    }
    return *ans;
}

string polynomial::to_string() {
    string ans;
    for (auto tmp = head; tmp != nullptr; tmp = tmp->next) {
        ans += tmp->to_string();
    }
    return ans;
}

vector <bool> polynomial::variabless() {
    return variables;
}
