#include "util/string.hpp"
#include <cstring>
using namespace yih;

String::String() {
	_data = new char[1];
	_data[0] = '\0';
	_len = 0;
}

String::String(const char* data) {
	_len = strlen(data);
	_data = new char[_len + 1];
	strcpy(_data, data);
}

String::String(const String& str) {
	_len = str._len;
	_data = new char[_len + 1];
	strcpy(_data, str._data);
}

String::~String() {
	if (_data != nullptr) {
		delete[] _data;
	}
}

const char*
String::Data() {
	return _data;
}

int
String::Len() const {
	return _len;
}

String&
String::Append(const char* data) {
	size_t sz = strlen(data);
	if (sz == 0) {
		return *this;
	}
	size_t nlen = _len + sz;
	char* buf = new char[nlen + 1];
	strcpy(buf, _data);
	strcpy(buf + _len, data);
	_len = nlen;
	delete _data;
	_data = buf;
	return *this;
}