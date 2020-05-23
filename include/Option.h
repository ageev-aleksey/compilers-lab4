//
// Created by nrx on 06.05.2020.
//

#ifndef OPTION_H
#define OPTION_H
template<typename T>
class Option {
public:
    Option(T value) {
        v = value;
        ok = true;
    }
    Option(T value, bool isOk) {
        v = value;
        ok = isOk;
    }
    Option() {
        ok = false;
    }
    bool isError() {
        return !ok;
    }
    operator bool() {
        return ok;
    }
    T get() {
        return v;
    }
private:
    T v;
    bool ok;
};

#endif