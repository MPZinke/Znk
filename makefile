CXX=clang

all:
	$(CXX) ZNK.c -o ZNK

run:
	$(CXX) ZNK.c -o ZNK && ./ZNK test.znk

lexer:
	$(CXX) Lexer.c LexerLengthMatching.c LinkedList.c Symbol.c Token.c -std=c11 -o Lex