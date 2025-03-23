export CPLUS_INCLUDE_PATH := /usr/local/include/antlr4-runtime:$(CPLUS_INCLUDE_PATH)
export LIBRARY_PATH := /usr/local/lib:$(LIBRARY_PATH)
export LD_LIBRARY_PATH := /usr/local/lib:$(LD_LIBRARY_PATH)
export CLASSPATH := .:/home/sollan/antlr4/runtime/Cpp/build/antlr-4.13.1-complete.jar:$(CLASSPATH)

all:
	java -jar /home/sollan/antlr4/runtime/Cpp/build/antlr-4.13.1-complete.jar -Dlanguage=Cpp ./myGrammar.g4 -visitor
	g++ main.cpp -o main -lantlr4-runtime myGrammarLexer.cpp myGrammarParser.cpp
