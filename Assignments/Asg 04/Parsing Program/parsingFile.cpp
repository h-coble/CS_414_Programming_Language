#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <fstream>

std::ofstream fileOut;
enum action //used for easy tracking of index of 2D array
{
    I=0, plus, star, leftParen, rightParen, dollar, E, T, F
};

//Create rows for parse table
const std::vector<std::string> state0 = { "S5","","","S4","","","S1","S2","S3" };
const std::vector<std::string> state1 = { "","S6","","","","accept","","","" };
const std::vector<std::string> state2 = { "","R2","S7","","R2","R2","","","" };
const std::vector<std::string> state3 = { "","R4","R4","","R4","R4","","","" };
const std::vector<std::string> state4 = { "S5","","","S4","","","S8","S2","S3" };
const std::vector<std::string> state5 = { "","R6","R6","","R6","R6","","","" };
const std::vector<std::string> state6 = { "S5","","","S4","","","","S9","S3"};
const std::vector<std::string> state7 = { "S5","","","S4","","","","","S10"};
const std::vector<std::string> state8 = {"","S6","","","S11","","","",""};
const std::vector<std::string> state9 = { "","R1","S7","","R1","R1","","",""};
const std::vector<std::string> state10 = { "","R3","R3","","R3","R3","","","" };
const std::vector<std::string> state11 = { "","R5","R5","","R5","R5","","","" };

const std::string RULE_1 = "E -> E + T";
const std::string RULE_2 = "E -> T";
const std::string RULE_3 = "T -> T * F";
const std::string RULE_4 = "T -> F";
const std::string RULE_5 = "F -> (E)";
const std::string RULE_6 = "F -> I";


//Create the parse table
const std::vector<std::vector<std::string>> parseTable = 
{
        state0,state1,state2,state3,state4,state5,
        state6,state7,state8,state9,state10,state11
};

std::stack<char> stringToStack(std::string expression)
{
    std::stack<char> expStack;
    int i=expression.length()-1;
    while(i>=0)
    {
        if(expression[i] !=' ')
        {
            switch (expression[i])
            {
                //if char is one of these tokens
                case '$':
                case '+':
                case '*':
                case '(':
                case ')':
                    expStack.push(expression[i]);
                    break;
                //else: char is some ID
                default:
                    expStack.push('I');
            }
        }
        i--;
    }

    return expStack;
}
void printStateStack(std::stack<int> state)
{
    std::stack<int> reload;
    for (int i = 0; i<= state.size();i++)
    {
        reload.push(state.top());
        state.pop();
    }
    for (int i = 0; i<=reload.size();i++)
    {
        fileOut<<"S"<<reload.top();
        state.push(reload.top());
        reload.pop();
    }
    fileOut << ",";
}

void printRemainingInput(std::stack<char> expression)
{
    std::string expStr ="";
    while(!expression.empty())
    {
        expStr += expression.top();
        expression.pop();
    }
    fileOut << expStr << ",";

    expression = stringToStack(expStr);
}

bool parseExpression(std::stack<char> expression,std::stack<int> state)
{
    //state must be initialized to only contain 0
    printStateStack(state);
    printRemainingInput(expression);
    
    int actionIndex = 0;
    //"Translate" from char to enum/index
   switch (expression.top())
    {
        case 'I':
            actionIndex = I;
            break;
        case '+':
            actionIndex = plus;
            break;
        case '*':
            actionIndex = star;
            break;
        case '(':
            actionIndex = leftParen;
            break;
        case ')':
            actionIndex = rightParen;
            break;
        case '$':
            actionIndex = dollar;
            break;
        default:
            std::cerr <<"Invalid char in expression stack\n";
            return false;
    }
    
    std::string foundAction = parseTable[state.top()][actionIndex];
    //END FUNCTION RETURN STR

    //START NEW FUNCTION RETURN BOOL
    std::string tempStr;
    if(foundAction =="")
        return false;
    else if(foundAction == "accept")
        {
            fileOut << foundAction << std::endl;
            return true;
        }
    else
    {
        switch(foundAction[0])
        {
            case 'S':
                //Remove char S from string
                
                //string to int conversion for push
                fileOut<<foundAction<<": Shift " <<foundAction<<" onto stack and continue with next input.\n";
                foundAction.erase(0,1);
                state.push( std::stoi(foundAction) ) ;
                
                //Pop off expression
                expression.pop();

                //Recur
                return parseExpression(expression,state);

            case 'R':
                //Call rule function
                fileOut<<"Reduce by "<<foundAction<<": ";
                
                
                switch(foundAction[1])
                {
                    case '1':
                        fileOut << RULE_1;
                        fileOut << "\tPop 3 from state stack and go to ";
                        //repeat x number of times
                        state.pop();
                        state.pop();
                        state.pop();

                        //[][go to]
                        tempStr = parseTable[state.top()][E];
                        fileOut << tempStr << ". Input remains.\n";
                        break;

                    case '2':
                        fileOut << RULE_2;
                        fileOut << "\tPop 1 from state stack and go to ";
                        //repeat x number of times
                        state.pop();

                        //[][go to]
                        tempStr = parseTable[state.top()][E];
                        fileOut << tempStr << ". Input remains.\n";
                        break;

                    case '3':
                        fileOut << RULE_3;
                        fileOut << "\tPop 3 from state stack and go to ";
                        //repeat x number of times
                        state.pop();
                        state.pop();
                        state.pop();

                        //[][go to]
                        tempStr = parseTable[state.top()][T];
                        fileOut << tempStr << ". Input remains.\n";
                        break;

                        case '4':
                        fileOut << RULE_4;
                        fileOut << "\tPop 1 from state stack and go to ";
                        //repeat x number of times
                        state.pop();

                        //[][go to]
                        tempStr = parseTable[state.top()][T];
                        fileOut << tempStr << ". Input remains.\n";
                        break;

                        case '5':
                        fileOut << RULE_5;
                        fileOut << "\tPop 3 from state stack and go to ";
                        //repeat x number of times
                        state.pop();
                        state.pop();
                        state.pop();

                        //[][go to]
                        tempStr = parseTable[state.top()][F];
                        fileOut << tempStr << ". Input remains.\n";
                        break;

                        case '6':
                        fileOut << RULE_6;
                        fileOut << "\tPop 1 from state stack and go to ";
                        //repeat x number of times
                        state.pop();

                        //[][go to]
                        tempStr = parseTable[state.top()][F];
                        fileOut << tempStr << ". Input remains.\n";
                        break;
                        
                    default:
                        std::cerr << "Rule with that number doesn't exist within original parse table\n";
                        return false;
                }
                
                tempStr.erase(0,1);
                state.push(std::stoi(tempStr));

                return parseExpression(expression,state);

            default:
                std::cerr << "Invalid action in parse table\n";
                return false;
        }
    }
     
}

int main()
{
    std::stack<char> a = stringToStack("A+B*C$");
    std::stack<int> b;
    b.push(0);

    fileOut.open("../Expression1.csv");
    if(!fileOut.is_open())
        return 9;
    if (parseExpression(a,b))
        std::cout << "\nHOT DAMN\n";
    fileOut.close();
    return 0;
} 


