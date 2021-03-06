
########################################################################################################################
#                                                                                                                      #
#   created by: MPZinke                                                                                                #
#   on 2021.07.21                                                                                                      #
#                                                                                                                      #
#   DESCRIPTION:                                                                                                       #
#   BUGS:                                                                                                              #
#   FUTURE:                                                                                                            #
#                                                                                                                      #
########################################################################################################################


CXX=clang

HEADER_PATH=./Headers/
SOURCE_FILES=./Source/*.c


lexer:
	$(CXX) -I $(HEADER_PATH) $(SOURCE_FILES) -std=c11 -o Lex
