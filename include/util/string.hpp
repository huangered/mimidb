#ifndef _ustring_hpp_
#define _ustring_hpp_

namespace yih {
	class String {
	private:
		char* _data;
		int _len;
	public:
		String();
		String(const char* data);
		String(const String& str);
		~String();

	public:
		// common methods
		String& Append(const char* data);
	};
}
#endif // !_ustring_hpp_
