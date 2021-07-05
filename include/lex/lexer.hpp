#ifndef _lexer_hpp_
#define _lexer_hpp_

enum tok {
	unknown,
	identifier,
	number,
};

class Token {

};

class Lexer {
public:
	bool lexInternal(Token& token);
};

#endif