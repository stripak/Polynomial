#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Polynomial {
private:
    vector<T> data;

public:
    Polynomial(const vector<T>& a) {
        data = a;
        DeleteUselessZeros();
    }
    Polynomial(const T& a = T(0)) {
        data.push_back(a);
        DeleteUselessZeros();
    }
    template<typename I>
    Polynomial(I first, I last) {
        while (first != last) {
            data.push_back(*first);
            ++first;
        }
        DeleteUselessZeros();
    }
    void DeleteUselessZeros() {
        while (data.size() > 0 && data.back() == T(0)) {
            data.pop_back();
        }
    }
    Polynomial operator+ (const Polynomial<T>& a) const {
        vector<T> ans;
        ans.resize(max(data.size(), a.data.size()));
        size_t i = 0;
        while (i < data.size()) {
            ans[i] += data[i];
            ++i;
        }
        i = 0;
        while (i < a.data.size()) {
            ans[i] += a.data[i];
            ++i;
        }
        Polynomial<T> answer(ans);
        answer.DeleteUselessZeros();
        return answer;
    }
    Polynomial operator+ (const T& a) const {
        Polynomial<T> flag(a);
        Polynomial<T> answer = (flag + *this);
        answer.DeleteUselessZeros();
        return answer;
    }
    Polynomial operator- (const Polynomial<T>& a) const {
        vector<T> ans;
        ans.resize(max(data.size(), a.data.size()));
        size_t i = 0;
        while (i < data.size()) {
            ans[i] += data[i];
            ++i;
        }
        i = 0;
        while (i < a.data.size()) {
            ans[i] -= a.data[i];
            ++i;
        }
        Polynomial<T> answer(ans);
        answer.DeleteUselessZeros();
        return answer;
    }
    Polynomial operator- (const T& a) const {
        Polynomial<T> flag(a);
        Polynomial<T> answer = (*this - flag);
        answer.DeleteUselessZeros();
        return answer;
    }
    Polynomial& operator+= (const Polynomial<T>& a) {
        vector<T> ans;
        ans.resize(max(data.size(), a.data.size()));
        size_t i = 0;
        while (i < data.size()) {
            ans[i] += data[i];
            ++i;
        }
        i = 0;
        while (i < a.data.size()) {
            ans[i] += a.data[i];
            ++i;
        }
        data = ans;
        DeleteUselessZeros();
        return *this;
    }
    Polynomial& operator+= (const T& a) {
        Polynomial<T> flag(a);
        *this += flag;
        DeleteUselessZeros();
        return *this;
    }
    Polynomial& operator-= (const Polynomial<T>& a) {
        vector<T> ans;
        ans.resize(max(data.size(), a.data.size()));
        size_t i = 0;
        while (i < data.size()) {
            ans[i] += data[i];
            ++i;
        }
        i = 0;
        while (i < a.data.size()) {
            ans[i] -= a.data[i];
            ++i;
        }
        data = ans;
        DeleteUselessZeros();
        return *this;
    }
    Polynomial& operator-= (const T& a) {
        Polynomial<T> flag(a);
        *this -= flag;
        DeleteUselessZeros();
        return *this;
    }
    bool operator== (const Polynomial<T>& a) const {
        if (data.size() != a.data.size()) {
            return false;
        } else {
            size_t i = 0;
            while (i < data.size()) {
                if (data[i] != a.data[i]) {
                    return false;
                }
                ++i;
            }
            return true;
        }
    }
    bool operator!= (const Polynomial<T>& a) const {
        return !(*this == a);
    }
    typename vector <T>::const_iterator begin() const {
        return data.begin();
    }
    typename vector <T>::const_iterator end() const {
        return data.end();
    }
    int Degree() const {
        return data.size() - 1;
    }
    const T operator[] (size_t i) const {
        if (i >= data.size()) {
            return static_cast<T> (0);
        } else {
            return data[i];
        }
    }
    Polynomial operator* (const Polynomial<T>& a) const {
        vector<T> ans;
        ans.resize(Degree() + a.Degree() + 1);
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < a.data.size(); ++j) {
                ans[i + j] += data[i] * a.data[j];
            }
        }
        Polynomial<T> answer(ans);
        answer.DeleteUselessZeros();
        return answer;
    }
    Polynomial operator* (const int& a) const {
        Polynomial<T> flag(a);
        Polynomial<T> answer = (*this * flag);
        answer.DeleteUselessZeros();
        return answer;
    }
    Polynomial& operator*= (const Polynomial<T>& a) {
        vector<T> ans;
        ans.resize(Degree() + a.Degree() + 1);
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < a.data.size(); ++j) {
                ans[i + j] += data[i] * a.data[j];
            }
        }
        data = ans;
        DeleteUselessZeros();
        return *this;
    }
    Polynomial& operator*= (const T& a) {
        Polynomial<T> flag(a);
        *this *= flag;
        DeleteUselessZeros();
        return *this;
    }
    T operator() (const T& a) const {
        T sumar = static_cast<T>(0);
        T x = static_cast<T>(1);
        int i = 0;
        while (i <= Degree()) {
            sumar += data[i] * x;
            x *= static_cast<T>(a);
            ++i;
        }
        return sumar;
    }
    int size() const {
        return data.size();
    }
    T operator[] (size_t i) {
        if (i >= data.size()) {
            return static_cast<T> (0);
        } else {
            return data[i];
        }
    }
    Polynomial deg(const Polynomial<T> a, const int& k) const {
        Polynomial<T> answer = a;
        int i = 1;
        while (i < k) {
            answer *= a;
            ++i;
        }
        answer.DeleteUselessZeros();
        return answer;
    }
    Polynomial operator& (const Polynomial<T>& a) const {
        Polynomial<T> answer;
        for (int i  = 0; i <= Degree(); ++i) {
            if (i >= 1) {
                answer += data[i] * deg(a, i);
            } else {
                answer += data[i];
            }
        }
        answer.DeleteUselessZeros();
        return answer;
    }
    Polynomial& operator&= (const Polynomial<T>& a) {
        Polynomial<T> answer;
        for (int i  = 0; i <= Degree(); ++i) {
            if (i >= 1) {
                answer += data[i] * deg(a, i);
            } else {
                answer += data[i];
            }
        }
        *this = answer;
        DeleteUselessZeros();
        return *this;
    }
};

template<typename T>
Polynomial<T> operator- (const T& a, const Polynomial<T>& other) {
    Polynomial<T> flag(a);
    Polynomial<T> answer = (flag - other);
    answer.DeleteUselessZeros();
    return answer;
}

template<typename T>
Polynomial<T> operator+ (const T& a, const Polynomial<T>& other) {
    Polynomial<T> flag(a);
    Polynomial<T> answer = (flag + other);
    answer.DeleteUselessZeros();
    return answer;
}

template<typename T>
Polynomial<T> operator* (const T& a, const Polynomial<T>& other) {
    Polynomial<T> flag(a);
    Polynomial<T> answer = (flag * other);
    answer.DeleteUselessZeros();
    return answer;
}

template<typename T>
ostream& operator<< (ostream& out, const Polynomial<T> a) {
    if (a.size() == 0) {
        out << '0';
    } else {
        auto key = a.Degree();
        for (auto i = 0; i < a.size(); ++i) {
            if (a[key - i] != static_cast<T>(0)) {
                if (key - i == a.Degree() && (key - i != 1) && (key - i != 0)) {
                    if (a[key - i] == static_cast<T>(1)) {
                        out << "x^" << key - i;
                    } else if (a[key - i] == static_cast<T>(-1)) {
                        out << "-x^" << key - i;
                    } else {
                        out << a[key - i] << "*x^" << key - i;
                    }
                } else if (key - i == 1) {
                    if (key - i == a.Degree()) {
                        if (a[key - i] == static_cast<T>(1)) {
                            out << 'x';
                        } else if (a[key - i] == static_cast<T>(-1)) {
                            out << "-x";
                        } else {
                            out << a[key - i] << "*x";
                        }
                    } else {
                        if (a[key - i] == static_cast<T>(1)) {
                            out << "+x";
                        } else if (a[key - i] == static_cast<T>(-1)) {
                            out << "-x";
                        } else if (a[key - i] > static_cast<T>(0)) {
                            out << '+' << a[key - i] << "*x";
                        } else {
                            out << a[key - i] << "*x";
                        }
                    }
                } else if (key - i == static_cast<T>(0)) {
                    if (key - i == a.Degree()) {
                        out << a[key - i];
                    } else {
                        if (a[key - i] > static_cast<T>(0)) {
                            out << '+' << a[key - i];
                        } else {
                            out << a[key - i];
                        }
                    }
                } else {
                    if (a[key - i] == static_cast<T>(1)) {
                        out << "+x^" << key - i;
                    } else if (a[key - i] == static_cast<T>(-1)) {
                        out << "-x^" << key - i;
                    } else if (a[key - i] > static_cast<T>(0)) {
                        out << '+' << a[key - i] << "*x^" << key - i;
                    } else {
                        out << a[key - i] << "*x^" << key - i;
                    }
                }
            }
        }
    }
    return out;
}
