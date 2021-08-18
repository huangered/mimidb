#ifndef _find_all_hpp_
#define _find_all_hpp_

#include <algorithm>

template <typename Iter, typename Pr>
void
find_all(const Iter& src, Iter& dest, Pr pred) {
    typename Iter::const_iterator begin = src.cbegin();
    typename Iter::const_iterator end   = src.cend();
    for (auto iter = std::find_if(begin, end, pred); iter != end; iter = std::find_if(++iter, end, pred)) {
        dest.push_back(*iter);
    }
}

#endif // !_find_all_hpp_
