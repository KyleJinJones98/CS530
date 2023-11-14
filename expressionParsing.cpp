/**
 * CS 530, Fall 2023
 * Joseph Vue, RED ID: 820231744
 */

#include "expressionParsing.h"

//A Token can be either a value or a function(+-*/) in RPN
struct Token {
    //stores the string representation of the token
    //used when the token is an operand
    std::string tokenString;
    //is true when the token is an operand and not a function(+-*/)
    bool isOperand;
};

//performs relevant operation and checks for invalid state
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
                throw AssemblyException();
            }
            result.value=op1.value*op2.value;
            result.isAbsolute=0;
            return result;
        case '/':
            //we cannot have a relative value in div
            if(op1.isAbsolute!=0 || op2.isAbsolute!=0){
                std::cout<<"Division of relative values is not allowed."<<std::endl;
                throw AssemblyException();
            }
            if(op2.value==0){
                std::cerr << "Division by zero is not allowed." << std::endl;
                throw AssemblyException();
            }
            result.value=op1.value/op2.value;
            result.isAbsolute=0;
            return result;
        default:
            std::cerr << "Invalid operator: " << function << std::endl;
            throw AssemblyException();
    }
}


//used in shunting yard to determine order of operations
int getPrecedence(char function){
    if(function == '+'||function =='-'){
        return 1;
    }
    else if(function=='*'||function == '/'){
        return 2;
    }
    else{
        std::cout<<"Unkown function detected "<<function<<std::endl;
        throw AssemblyException();
    }
}

//create an rpn style queue of tokens using shunting yard algorithm
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

Operand parseExpressionRecursive(std::string expression, SymbolTable symtab, int depth) {
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
            Operand operand = Operand();
            std::string tokenString = currentToken.tokenString;
            if(symtab.isSymbol(tokenString)){
                //get already defined symbol value or recurse to define it
                if(symtab.isDefined(tokenString)){
                    operand.value=symtab.getSymbolValueInt(tokenString);
                    if(symtab.isAbsolute(tokenString)){
                        operand.isAbsolute=0;
                    }
                    else{
                        operand.isAbsolute=1;
                    }
                }
                //otherwise we call parseExpression again on the expression defining the symbol
                //and define its value
                else{
                    operand = parseExpressionRecursive(symtab.getSymbolValue(tokenString), symtab, depth+1);
                    symtab.defineSymbol(tokenString, operand.value, operand.getAbsoluteFlag());
                }
            }
            //if the operand is not a symbol it is an integer string we can convert
            else{
                try{
                    operand.isAbsolute=0;
                    operand.value=std::stoi(tokenString);
                }
                //if we are unable to convert to an integer we error out of the program
                catch(std::invalid_argument e){
                    std::cout<<"Unkown Operand Detected "<<currentToken.tokenString<<" in expression"<<expression<<std::endl;
                    throw AssemblyException();
                }
            }

            //add operand to the operand stack
            operands.push(operand);
        }

        //if the token is a function then we need to perform an operation
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
        throw AssemblyException();
    }

    if (operands.top().isAbsolute!=0 && operands.top().isAbsolute!=1) {
        std::cerr << "Invalid matching of relative and Absolute values in expression: " << expression<<std::endl;
        throw AssemblyException();
    }

    return operands.top();
}


//Called to begin the parsing of an expression
Operand parseExpression(std::string expression, SymbolTable symtab)
{
    return parseExpressionRecursive(expression, symtab, 1);
}




