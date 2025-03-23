#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "myGrammarBaseVisitor.h"

bool isNumber(const std::string& s) {
    if (s.empty()) return false;  // Empty string isn’t a number
    for (char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return false;  // Non-digit found
        }
    }
    return true;  // All characters are digits
}


class EvalVisitor : public myGrammarBaseVisitor
{
private:
    std::map<std::string, std::string> variables;

public:
    EvalVisitor() {}

    void printVariables() {
	for (auto [name, val] : variables) {
		std::cout << "Var name: " << name << " Val: " << val << std::endl;
	}
    }

antlrcpp::Any visitTypes(myGrammarParser::TypesContext *ctx) override {
	if (!(ctx->bool_var() || ctx->int_var())) {
		return std::any();
	}

	if (ctx->bool_var()) {
	    visit(ctx->bool_var());
    } else if (ctx->int_var()) {
	    visit(ctx->int_var());
    }
	  
    if (ctx->types()) {
	    visit(ctx->types());	
    }
	  
    return std::any();
  }

antlrcpp::Any visitVar_name(myGrammarParser::Var_nameContext *ctx) override {
	  return ctx->NAME();
  }

antlrcpp::Any visitBool_var(myGrammarParser::Bool_varContext *ctx) override {

	 auto vecNameOld = std::any_cast<std::vector<antlr4::tree::TerminalNode *>>(visit(ctx->var_name()));

         std::vector<std::string> vecName;
         for (auto x : vecNameOld) {
               vecName.push_back(x->getText());
               std::cout << x->getText() << std::endl;
         }

         std::string value = std::any_cast<std::string>(visit(ctx->bool_expr()));
         std::cout << value << std::endl;

         for (auto name : vecName) {
               variables[name] = value;
         }

	 return value;
}

antlrcpp::Any visitInt_var(myGrammarParser::Int_varContext *ctx) override { 
    auto vecNameOld = std::any_cast<std::vector<antlr4::tree::TerminalNode *>>(visit(ctx->var_name()));

    std::vector<std::string> vecName;
	for (auto x : vecNameOld) {
        vecName.push_back(x->getText());
		std::cout << x->getText() << std::endl;
	}
	  
    std::string value = std::any_cast<std::string>(visit(ctx->int_expr()));
    std::cout << value << std::endl;

    for (auto name : vecName) {
	    variables[name] = value;
    }
	
    return value;
}

antlrcpp::Any visitInt_expr(myGrammarParser::Int_exprContext *ctx) override {
	int result = std::stoi(ctx->NUM()->getText());

	if (ctx->int_expr_tail()) {
		antlrcpp::Any tempAny = visit(ctx->int_expr_tail());
		std::vector<std::string> temp = std::any_cast<std::vector<std::string>>(tempAny);

		for (auto x : temp) {
			std::cout << "New Val:" << x << std::endl;
		}

		for (int i = 0; i < temp.size(); i+=2) {
			if (isNumber(temp[i + 1])) {
				if (temp[i] == "+") result+=stoi(temp[i+1]);
				else if (temp[i] == "-") result-=stoi(temp[i+1]);
				else std::cout << "Error: Unknown operation" << std::endl;
			}
			else std::cout << "Error: Not a number" << std::endl;
		}
	}
    return std::to_string(result);
  }

antlrcpp::Any visitInt_expr_tail(myGrammarParser::Int_expr_tailContext *ctx) override {
    if (!ctx->int_oper()) return std::vector<std::string>();
	  
	std::vector<std::string> res;
	res.push_back((std::string)ctx->int_oper()->getText());
	res.push_back((std::string)ctx->NUM()->getText());

	std::vector<std::string> tempVec = std::any_cast<std::vector<std::string>>(visit(ctx->int_expr_tail()));

	res.insert(res.end(), tempVec.begin(), tempVec.end());

	return res;
  }

antlrcpp::Any visitInt_oper(myGrammarParser::Int_operContext *ctx) override {

    return visitChildren(ctx);
  }

antlrcpp::Any visitBool_expr(myGrammarParser::Bool_exprContext *ctx) override {
	bool result = (std::string(ctx->bool_val()->getText()).find("TRUE") != std::string::npos);

	antlrcpp::Any tempAny = visit(ctx->bool_expr_tail());
	// contains array || bool_val
	std::vector<std::string> temp = std::any_cast<std::vector<std::string>>(tempAny);

	for (int i = 0; i < temp.size(); i+=2) {
		if (temp[i] == "||") {
			if (temp[i+1] == "TRUE") result = result || true;
			else if (temp[i+1] == "FALSE") result = result || false;
			else std::cout << "Error: Unknown type" << std::endl;
		}
		else std::cout << "Error: Unknown operation" << std::endl;
    }
	  
	return result ? std::string("true") : std::string("false");
}

antlrcpp::Any visitBool_expr_tail(myGrammarParser::Bool_expr_tailContext *ctx) override {
	if (!ctx->bool_oper()) return std::vector<std::string>();
	
	std::vector<std::string> res;
	res.push_back((std::string)ctx->bool_oper()->getText());
	res.push_back((std::string)ctx->bool_val()->getText());

	std::vector<std::string> tempVec = std::any_cast<std::vector<std::string>>(visit(ctx->bool_expr_tail()));
	res.insert(res.end(), tempVec.begin(), tempVec.end());
	
	return res;
}

antlrcpp::Any visitBool_val(myGrammarParser::Bool_valContext *ctx) override {
    return visitChildren(ctx);
}

antlrcpp::Any visitBool_oper(myGrammarParser::Bool_operContext *ctx) override {
    return visitChildren(ctx);
}

};



