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

    //std::cout << std::string("int").compare(input);

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

/*
int main(int argc, const char *argv[])
{
    std::string input;
    std::cout << "Введите выражение: ";
    std::getline(std::cin, input);

    ANTLRInputStream inputStream(input);
    myGrammarLexer lexer(&inputStream);
    CommonTokenStream tokens(&lexer);
    myGrammarParser parser(&tokens);

    for (antlr4::Token* token : tokens.getTokens()) {
        std::cout << "Token: " << token->getText() 
                  << ", Type: " << token->getType() 
                  << std::endl;
    }

//tree::ParseTree *tree = parser.typeList();
    tree::ParseTree *tree = parser.types();
    EvalVisitor visitor;

   // visitor.setVariable("c", 5);
   // visitor.setVariable("b", 10);

    try
    {
        int result = std::any_cast<int>(visitor.visit(tree));
        std::cout << "Результат: " << result << std::endl;
    }
    catch (const std::bad_any_cast &e)
    {
        std::cerr << "Ошибка: некорректный тип выражения." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}

*/
