CXX=clang

all:
	$(CXX) ZNK.c -o ZNK

run:
	$(CXX) ZNK.c -o ZNK && ./ZNK test.znk

lexer:
	$(CXX) Lexer.c LexerLengths.c LexerLiterals.c LexerMatching.c LexerRegexes.c Symbols.c -std=c99 -o Lex