#include "util/string.hpp"
#include <cstring>
using namespace yih;

String::String() {
	_data = nullptr;
	_len = 0;
}

String::String(const char* data) {
	_len = strlen(data) + 1;
	_data = new char[_len];
	strcpy(_data, data);
}

String::String(const String& str) {
	_len = str._len;
	_data = new char[_len];
	strcpy(_data, str._data);
}

String::~String() {
	if (_data != nullptr) {
		delete[] _data;
	}
}