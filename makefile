CXX=clang

all:
	$(CXX) ZNK.c -o ZNK

run:
	$(CXX) ZNK.c -o ZNK && ./ZNK test.znk

lexer:
	$(CXX) Lexer.c Symbols.c LexerLengths.c LexerLiterals.c LexerMatching.c LexerRegexes.c -std=c11 -o Lex