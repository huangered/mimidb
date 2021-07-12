#ifndef _directory_hpp_
#define _directory_hpp_

#include <map>

template<class p1, class p2, class p3>
class Dictionary {
};

template<class p1, class p2, class p3>
class Dictionary<p1, p2, p3*> {
public:
	//template<class a1, class b1>
	struct Entry {
		p1 param1;
		p2 param2;

		Entry(p1 a, p2 b) {
			param1 = a;
			param2 = b;
		}

		bool operator<(const Entry& right) const {
			int i = param1 - right.param1;
			if (i != 0) {
				return i < 0 ? true : false;
			}
			else {
				return param2 < right.param2;
			}
		}
	};

	std::map<Entry, p3*> data;

public:
	Dictionary() {}
	~Dictionary() {
		for (auto g = data.begin(); g != data.end(); g++) {
			delete g->second;
		}
	}
	void put(p1 a, p2 b, p3* c) {
		Entry entry{ a,b };
		std::pair<Entry, p3*> p = std::make_pair(entry, c);
		data.insert(p);
	}

	std::pair<bool, p3*> get(p1 a, p2 b) {
		Entry entry{ a,b };
		auto r = data.find(entry);
		if (r != data.end()) {
			return std::make_pair(true, r->second);
		}

		return std::make_pair(false, nullptr);
	}
};


#endif // !_directory_hpp_
