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

String&
String::operator=(const String& str) {
	_len = str._len;
	_data = new char[_len + 1];
	strcpy(_data, str._data);
	return *this;
}


String::~String() {
	if (_data != nullptr) {
		delete[] _data;
	}
}

char*
String::Data() const {
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

int
String::compare(const String& other) {
	if (this == &other) {
		return 0;
	}
	int i;
	if ((i = (_len - other._len)) != 0) {
		return i;
	}

	for (int j = 0; j < _len; j++) {
		if ((i = _data[j] - other._data[j]) != 0) {
			return i;
		}
	}

	return 0;
}
