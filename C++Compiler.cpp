#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// intermediate instruction structure:
struct IntermediateCode {
  std::string opcode;
  std::string temporary1;
  std::string temporary2;
  std::string result;
};
//-------------------------------------

// intermediate code generator class:
class IntermediateCodeGenerator {
private:
  std::vector<IntermediateCode> code;

public:
  // constructor:
  IntermediateCodeGenerator() {}

  // generate intermediate code (three-address code (TAC)) for all operators:

  // add:
  void genAdd(std::string result, std::string temporary1,
              std::string temporary2) {
    code.push_back({"Add", temporary1, temporary2, result});
  }

  // sub:
  void genSub(std::string result, std::string temporary1,
              std::string temporary2) {
    code.push_back({"Sub", temporary1, temporary2, result});
  }

  // mul:
  void genMul(std::string result, std::string temporary1,
              std::string temporary2) {
    code.push_back({"Mul", temporary1, temporary2, result});
  }

  // div:
  void genDiv(std::string result, std::string temporary1,
              std::string temporary2) {
    code.push_back({"Div", temporary1, temporary2, result});
  }

  // print intermmediate code:
  void printIntermediateCode() {
    std::cout << "\n\nIntermediate Code: " << std::endl;
    for (const auto &instruction : code) {
      std::cout << instruction.opcode << " " << instruction.temporary1 << "  "
                << instruction.temporary2 << "  " << instruction.result
                << std::endl;
    }
  }

}; // end of intermediate code generator class
//-------------------------------------------------------------------------------

// token types:
enum TokenType {
  // numeric value:
  token_num = 0,
  // token for addition
  token_add = 1,
  // token for subtraction
  token_sub = 2,
  // token for multiplication
  token_mul = 3,
  // token for division
  token_div = 4,
  // token for invalid
  token_invalid = 5,
  // token for end of input
  token_end = 6
};
//----------------------------------------

// token struct:
struct Token {
  // type of token:
  TokenType type;
  // value of token:
  std::string value;
};
//----------------------------------------

// Lexical Analyzer Class:
class LexicalAnalyzer {
private:
  const std::string &input;
  size_t position;

public:
  // constructor:
  LexicalAnalyzer(const std::string &input) : input(input), position(0){};

  // get next token:
  Token getNextToken() {
    // loop until end of input:
    while (position < input.size()) {
      char currentChar = input[position];
      // skip whitespaces
      if (isspace(currentChar)) {
        ++position;
        // skip spaces
        continue;
      }

      // switch case
      switch (currentChar) {
      case '*':
        ++position;
        printf("Next token is: %d, Next lexeme is %c\n", token_mul,
               currentChar);
        return Token{token_mul, "*"};
        break;

      // if current char is division:
      case '/':
        ++position;
        printf("Next token is: %d, Next lexeme is %c\n", token_div,
               currentChar);
        return Token{token_div, "/"};
        break;

      // if current char is addition:
      case '+':
        ++position;
        printf("Next token is: %d, Next lexeme is %c\n", token_add,
               currentChar);
        return Token{token_add, "+"};
        break;

      // if current char is subtraction:
      case '-':
        ++position;
        printf("Next token is: %d, Next lexeme is %c\n", token_sub,
               currentChar);
        return Token{token_sub, "-"};
        break;

      default:
        if (isdigit(currentChar)) {
          // Handle the case for numeric values
          return handleNumber();
        } else {
          throw std::runtime_error("Invalid character!");
        }
        break;

      } // end of switch case
    }   // end of while

    std::cout << "Next token is: " << token_end << ", Next lexeme: end of input"
              << std::endl;
    return Token{token_end};

  } // end of getNextToken()
  //--------------------------------------------------------------------

private:
  // Handle numeric values
  Token handleNumber() {
    std::string numValue;
    while (position < input.size() && isdigit(input[position])) {
      numValue += input[position++];
      std::cout << "Next token is: " << token_num << ", Next lexeme is "
                << numValue << std::endl;
    }
    return Token{token_num, numValue};
  }

}; // end of LexicalAnalyzer class
//-------------------------------------------------------------

// node types for AST(abstract syntax tree)
enum NodeType {
  // node type for number
  node_num,
  // node type for addition
  node_add,
  // node type for subtraction
  node_sub,
  // node type for multiplication
  node_mul,
  // node type for division
  node_div
};
//----------------------------------------

// AST node struct
struct ASTNode {
  // type of node:
  NodeType type;
  // value of node:
  std::string value;
  // left child of node:
  ASTNode *left;
  // right child of node:
  ASTNode *right;
};
//----------------------------------------

// Parser Class:
class Parser {
private:
  LexicalAnalyzer &lexer;
  IntermediateCodeGenerator &codeGen;

public:
  // constructor:
  Parser(LexicalAnalyzer &lexer, IntermediateCodeGenerator &codeGen)
      : lexer(lexer), codeGen(codeGen){};

  // parse the input to construct AST:
  ASTNode *parse() { return parseExpression(); }

private:
  // recursive descent parsing function:
  ASTNode *parseExpression() {
    // parse the left child:
    ASTNode *left = parseTerm();
    Token token = lexer.getNextToken();

    // lowest precedence:
    while (token.type == token_add || token.type == token_sub) {
      ASTNode *newNode = new ASTNode();
      newNode->type = (token.type == token_add) ? node_add : node_sub;
      newNode->value = token.value;
      newNode->left = left;
      newNode->right = parseTerm();
      left = newNode;
      token = lexer.getNextToken();
    }
    return left;
  } // end of parseExpression()

  ASTNode *parseTerm() {
    // parse the left child:
    ASTNode *left = parseFactor();
    Token token = lexer.getNextToken();
    // higher precedence:
    while (token.type == token_mul || token.type == token_div) {
      ASTNode *newNode = new ASTNode();
      newNode->type = (token.type == token_mul) ? node_mul : node_div;
      newNode->value = token.value;
      newNode->left = left;
      newNode->right = parseFactor();
      left = newNode;
      token = lexer.getNextToken();

      // intermediate code for mul/div:
      if (token.type == token_mul) {
        codeGen.genMul(newNode->value, left->left->value, left->right->value);
      }

      else {
        codeGen.genDiv(newNode->value, left->left->value, left->right->value);
      }
    }

    // handle addition/subtraction operation
    if (token.type == token_add || token.type == token_sub) {
      ASTNode *newNode = new ASTNode();
      newNode->type = (token.type == token_add) ? node_add : node_sub;
      newNode->value = token.value;
      newNode->left = left;
      newNode->right = parseTerm();
      left = newNode;

      // intermediate code for add/sub:
      if (token.type == token_add) {
        codeGen.genAdd(newNode->value, left->left->value, left->right->value);
      }

      else {
        codeGen.genSub(newNode->value, left->left->value, left->right->value);
      }
    }

    return left;
  } // end of parseTerm()

  ASTNode *parseFactor() {
    Token token = lexer.getNextToken();

    if (token.type == token_num) {
      ASTNode *newNode = new ASTNode();
      newNode->type = node_num;
      newNode->value = token.value;
      // empty pointer
      newNode->left = nullptr;
      newNode->right = nullptr;
      return newNode;
    }

    else {
      throw std::runtime_error("Invalid token");
    }
  } // end of parseFactor()
  //-----------------------------------------------------------

public:
  // function to evaluate the AST
  double evaluateAST(ASTNode *node) {
    if (node == nullptr) {
      throw std::runtime_error("Empty node");
    }

    switch (node->type) {
    case node_num:
      return std::stod(node->value);

    case node_add:
      return evaluateAST(node->left) + evaluateAST(node->right);

    case node_sub:
      return evaluateAST(node->left) - evaluateAST(node->right);

    case node_mul:
      return evaluateAST(node->left) * evaluateAST(node->right);

    case node_div: {
      double rightValue = evaluateAST(node->right);

      if (rightValue == 0) {
        throw std::runtime_error(
            "\nYou cannot divide by zero. Please try again :)");
      }
      return evaluateAST(node->left) / rightValue;
    }

    default:
      throw std::runtime_error("\nInvalid node type");
    }
  } // end of evaluateAST()

  // print AST function
  void printAST(ASTNode *node, int indent = 0) {
    // if empty, nothing
    if (node == nullptr) {
      return;
    }

    for (int i = 0; i < indent; ++i) {
      std::cout << " ";
    }

    switch (node->type) {
    case node_num:
      std::cout << "Number: " << node->value << std::endl;
      break;

    case node_mul:
      std::cout << "Multiplication: ' " << node->value << " '" << std::endl;
      break;

    case node_div:
      std::cout << "Division: ' " << node->value << " '" << std::endl;
      break;

    case node_add:
      std::cout << "Addition: ' + '" << std::endl;
      break;

    case node_sub:
      std::cout << "Subtraction: ' - '" << std::endl;
      break;

    default:
      std::cout << "\nInvalid node type" << std::endl;
      break;

    } // end of switch case

    // printing left child
    if (node->left != nullptr) {
      std::cout << "\nLeft:" << std::endl;
      printAST(node->left, indent + 2);
    }
    // printing right child
    if (node->right != nullptr) {
      std::cout << "\nRight:" << std::endl;
      printAST(node->right, indent + 2);
    }

  } // end of printAST()

}; // end of Parser class
//------------------------------------------------------------------------------

// main function:
int main() {
  std::string userin;
  std::cout << "Please enter an expression: ";
  std::getline(std::cin, userin);

  // instances:
  LexicalAnalyzer lexer(userin);
  IntermediateCodeGenerator codeGen;
  Parser parser(lexer, codeGen);

  try {
    // parse the input and construct AST:
    ASTNode *root = parser.parse();

    // print the AST:
    std::cout << "\nAbstract Syntax Tree:\n" << std::endl;
    parser.printAST(root);

    // print intermediate code:
    codeGen.printIntermediateCode();

    // evaluate the AST:
    double result = parser.evaluateAST(root);
    std::cout << "\nResult: " << result << std::endl;

    return 0;
  }

  catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}
