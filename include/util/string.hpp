#ifndef _ustring_hpp_
#define _ustring_hpp_

#include <ostream>

namespace yih {
	class String {
		friend std::ostream& operator<<(std::ostream& os, const String& dt);
	private:
		char* _data;
		int _len;
	public:
		String();
		String(const char* data);
		String(const String& str);
		String& operator=(const String& str);
		~String();
		char* Data() const;
		int Len() const;
	public:
		// common methods
		String& Append(const char* data);

		int compare(const String& other);


	};

	static std::ostream&
		operator<<(std::ostream& os, const String& dt) {
		os << dt.Data();
		return os;
	}
}


#endif // !_ustring_hpp_
