#ifndef _lexer_hpp_
#define _lexer_hpp_

#include "util/string.hpp"

enum Tok :int
{
	Select = 1,
	WhiteSpace,
	From,
	Insert,
	Into,
	Values,
	Create,
	Table,
	View,

	Plus,

	Comma,
	Semicolon,

	LeftBrace,
	RightBrace,

	Number,
	Identifier,

	Money,

	Unknown,
};

struct LexTokenData {
	Tok tok;
	yih::String str;

	int compare(const LexTokenData& token) {
		return tok - token.tok;
	}
};

typedef LexTokenData* LexToken;

struct LexerOption {
	bool skipWhiteSpace;
};

class Lexer {
private:
	int _cur;
	int _size;
	const char* _buf;

public:
	Lexer(const char* buf, int size);

	LexToken getLexerToken();
private:
	LexToken LexNumber();
	LexToken LexIdentifier();
};

#endif // !_lexer_hpp_
