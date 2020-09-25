CXX=clang

all:
	$(CXX) ZNK.c -o ZNK

run:
	$(CXX) ZNK.c -o ZNK && ./ZNK test.znk