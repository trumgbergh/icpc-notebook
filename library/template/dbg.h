#include <bits/stdc++.h>

std::string _repr(std::string s) { return '"' + s + '"'; }
std::string _repr(char* s) { return _repr((std::string)s); }
std::string _repr(int s) { return std::to_string(s); }
std::string _repr(int64_t s) { return std::to_string(s); }
std::string _repr(bool b) { return b ? "True" : "False"; }

template <typename A, typename B>
std::string _repr(std::pair<A, B> p);

template <typename T>
std::string _repr(T v) {
    bool f = true;
    std::string res = "{";
    for (auto& x : v) {
        if (!f) res += ", ";
        f = false;
        res += _repr(x);
    }
    return res + "}";
}

template <typename A, typename B>
std::string _repr(std::pair<A, B> p) {
    return "(" + _repr(p.first) + ", " + _repr(p.second) + ")";
}

void debug_out() { std::cerr << std::endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    std::cerr << " " << _repr(H);
    debug_out(T...);
}

#define dbg(...) \
    std::cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);
