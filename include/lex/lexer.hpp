#ifndef _lexer_hpp_
#define _lexer_hpp_

#include "util/string.hpp"

enum Tok
{
	Select,
	WhiteSpace,
	From,
	Insert,
	Into,
	Values,
	Create,
	Table,
	View,

	Comma,
	Semicolon,

	LeftBrace,
	RightBrace,

	Number,
	Identifier,

	Unknown,
};

struct LexToken {
	Tok tok;
	yih::String str;
};

struct LexerOption {
	int i;
};

class Lexer {
private:
	int _cur;
	int _size;
	const char* _buf;

public:
	Lexer(const char* buf, int size);

	LexToken* getLexerToken();
private:
	LexToken* LexNumber();
	LexToken* LexIdentifier();
};

#endif // !_lexer_hpp_
