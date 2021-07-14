#include "lex/lexer.hpp"
#include "c.hpp"


Lexer::Lexer(const char* buf, int size) :_cur{ 0 }, _size{ size }, _buf{ buf }{
}


LexToken
Lexer::GetLexerToken() {
	if (_cur >= _size) {
		return nullptr;
	}
	Tok tok{ Tok::Unknown };
	char Char = _buf[_cur];

	switch (Char) {
	case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
		return lexNumber();
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':
		return lexIdentifier();
	case '(':
		tok = Tok::LeftBrace;
		break;
	case ')':
		tok = Tok::RightBrace;
		break;
	case ' ':
		tok = Tok::WhiteSpace;
		break;
	}
	_cur++;
	LexToken token = new LexTokenData{ tok };
	return token;
}

LexToken
Lexer::lexIdentifier() {
	int start = _cur;
	int count = 0;
	for (; _cur < _size; _cur++) {
		char c = _buf[_cur];
		if (c >= 'a' && c <= 'z') {
			count++;
		}
		else {
			break;
		}
	}

	char* p = new char[count + 1];
	strncpy(p, _buf + start, count);
	p[count] = '\0';

	LexToken token = new LexTokenData{ Tok::Identifier, yih::String{ p } };

	delete[] p;

	return token;
}

LexToken
Lexer::lexNumber() {
	int start = _cur;
	int count = 0;
	for (; _cur < _size; _cur++) {
		char c = _buf[_cur];
		if (c >= '0' && c <= '9') {
			count++;
		}
		else {
			break;
		}
	}

	char* p = new char[count+1];
	strncpy(p, _buf + start, count);
	p[count] = '\0';
	LexToken token = new LexTokenData{ Tok::Number, yih::String{ p } };

	delete[] p;
	return token;
}
