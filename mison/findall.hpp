#ifndef _find_all_hpp_
#define _find_all_hpp_

#include <algorithm>
#include <vector>
#include <string>

template <typename Iter, typename Pr>
void
find_all(const Iter& src, Iter& dest, Pr pred) {
    typename Iter::const_iterator begin = src.cbegin();
    typename Iter::const_iterator end   = src.cend();
    for (auto iter = std::find_if(begin, end, pred); iter != end; iter = std::find_if(++iter, end, pred)) {
        dest.push_back(*iter);
    }
}

template <typename T>
std::string
format_string(const std::vector<T>& v) {
    if (v.size() == 0) {
        return "";
    }
    if (v.size() == 1) {
        return std::to_string(v[0]);
    }

    std::string a = std::to_string(v[0]);

    for (int i = 1; i != v.size(); i++) {
        a += ",";
        a += std::to_string(v[i]);
    }
    return a;
}

#endif // !_find_all_hpp_
