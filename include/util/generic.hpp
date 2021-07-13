#ifndef _generic_hpp_
#define _generic_hpp_

template <typename Iter, typename Pr>
void find_all(Iter& src, Iter& dest, Pr pred) {
	typename Iter::iterator begin = src.begin();
	typename Iter::iterator end = src.end();
	for (auto iter = std::find_if(begin, end, pred); iter != end; iter = std::find_if(++iter, end, pred)) {
		dest.push_back(*iter);
	}
}


#endif // !_generic_hpp_
