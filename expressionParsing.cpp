#include "expressionParsing.h"

int parseExpression(std::string expression, SymbolTable symtab)
{
    return parseExpression(expression, symtab, 1);
}


#include <iostream>
#include <stack>
#include <string>
#include <queue>

//A Token can be either a value or a function(+-*/) in RPN
struct Token {
    //stores the string representation of the token
    //used when the token is an operand
    std::string tokenString;
    //is true when the token is an operand and not a function(+-*/)
    bool isOperand;
};

struct Operand{
    int value;
    //absolute is indicated by 0
    //relative is indicated by 1
    //expression is invalid if relatives do not cancel back to 0 or 1
    int isAbsolute =0;
}; 

Operand performOperation(Operand op1, Operand op2, char function) {
    Operand result = Operand();
    switch (function) {
        case '+':
            result.value= op1.value+op2.value;
            //we can add relative values as long as another relative value is subtracted later
            result.isAbsolute= op1.isAbsolute+op2.isAbsolute;
            return result;

        case '-':
            result.value= op1.value-op2.value;
            //we can subtract relative value from absolute as long as we add a relative value later
            result.isAbsolute= op1.isAbsolute-op2.isAbsolute;
            return result;
        case '*':
            //we cannot have a relative value in mul
            if(op1.isAbsolute!=0 || op2.isAbsolute!=0){
                std::cout<<"Multiplication of relative values is not allowed."<<std::endl;
                exit(3);
            }
            result.value=op1.value*op2.value;
            result.isAbsolute=0;
            return result;
        case '/':
            //we cannot have a relative value in div
            if(op1.isAbsolute!=0 || op2.isAbsolute!=0){
                std::cout<<"Division of relative values is not allowed."<<std::endl;
                exit(3);
            }
            if(op2.value==0){
                std::cerr << "Division by zero is not allowed." << std::endl;
                exit(1);
            }
            result.value=op1.value/op2.value;
            result.isAbsolute=0;
            return result;
        default:
            std::cerr << "Invalid operator: " << function << std::endl;
            exit(1);
    }
}

Operand getValue(std::string tokenString){
    Operand operand = Operand();
    operand.isAbsolute=0;
    operand.value=std::stoi(tokenString);
    return operand;
}

int getPrecedence(char function){
    if(function == '+'||function =='-'){
        return 1;
    }
    else if(function=='*'||function == '/'){
        return 2;
    }
    else{
        std::cout<<"Unkown function detected "<<function<<" in expression"<<std::endl;
        exit(3);
    }
}

//create an rpn style queue of tokens
void createTokenQueue(std::string expression, std::queue<Token> &tokens){
    //operator stack
    std::stack<char> functions;

    std::string currentToken = "";
    for (unsigned int i = 0; i < expression.size(); i++) { 
        char c= expression[i];
        //if c is alphanumeric it is either a symbol or an integer
        if(isalnum(c)){
            currentToken+=c;
        }
        else{
            //when we hit an operand that means the end of our current operand
            Token newOperandToken = Token();
            newOperandToken.isOperand=true;
            newOperandToken.tokenString=currentToken;
            tokens.push(newOperandToken);

            //reset our current token string
            currentToken="";

            while(!functions.empty() && getPrecedence(c)<=getPrecedence(functions.top())){
                char poppedFunction = functions.top();
                functions.pop();
                Token newFunctionToken = Token();
                newFunctionToken.isOperand=false;
                newFunctionToken.tokenString=poppedFunction;
                tokens.push(newFunctionToken);
            }
            functions.push(c);
        }  
    }

    //add the last operand in the expression
    //we cannot ever end an expression with a function so our last value will always be an operand that we need to add
    Token newOperandToken = Token();
    newOperandToken.isOperand=true;
    newOperandToken.tokenString=currentToken;
    tokens.push(newOperandToken);

    //add all remaining operators
    while(!functions.empty()){
        char poppedFunction = functions.top();
        functions.pop();
        Token newFunctionToken = Token();
        newFunctionToken.isOperand=false;
        newFunctionToken.tokenString=poppedFunction;
        tokens.push(newFunctionToken);
    }
}

int parseExpression(std::string expression, SymbolTable symtab, int depth) {
    std::queue<Token> tokens;
    createTokenQueue(expression,tokens);
    std::stack<Operand> operands;

    Token currentToken;
    while (!tokens.empty())
    {
        //get our next token from the queue
        currentToken= tokens.front();
        tokens.pop();

        //the next token is either an operand or function
        if(currentToken.isOperand){

            operands.push(getValue(currentToken.tokenString));
        }
        else{
            if(operands.size()<2){
                std::cout<<"Insufficient operands for function: "<<currentToken.tokenString<< " in expression: "<<expression<<std::endl;
            }
            Operand operand2 = operands.top();
            operands.pop();
            Operand operand1 = operands.top();
            operands.pop();
            Operand result = performOperation(operand1,operand2,currentToken.tokenString[0]);
            operands.push(result);
        }
    }
    
    if (operands.size() != 1) {
        std::cerr << "Invalid expression." << std::endl;
        exit(1);
    }

    return operands.top().value;
}

int main() {
    std::string testExpression = "35+100/5*8";
    //int result = parseExpression(testExpression);

    //std::cout << "Expression: " << testExpression << std::endl;
    //std::cout << "Result: " << result << std::endl;

    return 0;
}



