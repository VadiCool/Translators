#include <iostream>
#include <fstream>
#include <string>
#include "antlr4-runtime.h"
#include "myGrammarLexer.h"
#include "myGrammarParser.h"
#include "EvalVisitor.cpp"

using namespace antlr4;


int main(int argc, const char *argv[]) {
    std::string input;
    std::cout << "Введите выражение: ";
    std::getline(std::cin, input);

    ANTLRInputStream inputStream(input);
    myGrammarLexer lexer(&inputStream);
    CommonTokenStream tokens(&lexer);
    myGrammarParser parser(&tokens);

    // Parse the input
    tree::ParseTree *tree = parser.types();

    // Print tokens (for debugging)
    for (antlr4::Token* token : tokens.getTokens()) {
        std::cout << "Token: " << token->getText()
                  << ", Type: " << token->getType()
                  << std::endl;
    }

    // Create and use the visitor
    EvalVisitor visitor;
    visitor.visit(tree);
    visitor.printVariables();
    

    return 0;
}
