#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <iomanip>

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
    std::string tempStr="";
    while(!state.empty())
    {
        reload.push(state.top());
        state.pop();
    }
    while(!reload.empty())
    {
        tempStr+= "S";
        if(reload.top() < 10)
            tempStr+= reload.top() + '0';
        else if( reload.top() == 10)
            tempStr+= "10";
        else if(reload.top() == 11)
            tempStr+= 11;
        state.push(reload.top());
        reload.pop();
    }
    std::cout << std::setw(25) <<std::left << tempStr;
}

void printRemainingInput(std::stack<char> expression)
{
    std::string expStr ="";
    while(!expression.empty())
    {
        expStr += expression.top();
        //expStr+=" ";
        expression.pop();
    }
    std::cout << std::setw(25) << std::left << expStr;

    expression = stringToStack(expStr);
}

bool parseExpression(std::stack<char> expression,std::stack<int> state)
{
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
         {
        std::cout << " Undefined action; expression failed because it isn't supported.\n";
        return false;
        }  
    else if(foundAction == "accept")
        {
            std::cout << foundAction << std::endl;
            return true;
        }
    else
    {
        
        switch(foundAction[0])
        {
            case 'S':
                //Remove char S from string
                
                //string to int conversion for push
                std::cout<<foundAction <<": Shift " <<foundAction<<" onto stack, and continue with next input.\n";
                foundAction.erase(0,1);
                state.push( std::stoi(foundAction) ) ;
                
                //Pop off expression
                expression.pop();

                //Recur
                return parseExpression(expression,state);

            case 'R':
                //Call rule function
                std::cout<<"Reduce by "<<foundAction<<": ";
                
                
                switch(foundAction[1])
                {
                    case '1':
                        std::cout << RULE_1;
                        std::cout << " Pop 3 from state stack, go to ";
                        //repeat x number of times
                        state.pop();
                        state.pop();
                        state.pop();

                        //[][go to]
                        tempStr = parseTable[state.top()][E];
                        std::cout << tempStr << ". Input remains.\n";
                        break;

                    case '2':
                        std::cout << RULE_2;
                        std::cout << " Pop 1 from state stack, go to ";
                        //repeat x number of times
                        state.pop();

                        //[][go to]
                        tempStr = parseTable[state.top()][E];
                        std::cout << tempStr << ". Input remains.\n";
                        break;

                    case '3':
                        std::cout << RULE_3;
                        std::cout << " Pop 3 from state stack, go to ";
                        //repeat x number of times
                        state.pop();
                        state.pop();
                        state.pop();

                        //[][go to]
                        tempStr = parseTable[state.top()][T];
                        std::cout << tempStr << ". Input remains.\n";
                        break;

                        case '4':
                        std::cout << RULE_4;
                        std::cout << " Pop 1 from state stack, go to ";
                        //repeat x number of times
                        state.pop();

                        //[][go to]
                        tempStr = parseTable[state.top()][T];
                        std::cout << tempStr << ". Input remains.\n";
                        break;

                        case '5':
                        std::cout << RULE_5;
                        std::cout << " Pop 3 from state stack, go to ";
                        //repeat x number of times
                        state.pop();
                        state.pop();
                        state.pop();

                        //[][go to]
                        tempStr = parseTable[state.top()][F];
                        std::cout << tempStr << ". Input remains.\n";
                        break;

                        case '6':
                        std::cout << RULE_6;
                        std::cout << " Pop 1 from state stack, go to ";
                        //repeat x number of times
                        state.pop();

                        //[][go to]
                        tempStr = parseTable[state.top()][F];
                        std::cout << tempStr << ". Input remains.\n";
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

int main(){
    std::string expression;
    std::stack<char> expStack = stringToStack("A+B*C$");
    std::stack<int> stateStack;

    while(true)
    {
        std::cout << "\n\nEnter your expression, ending with \'$\'\n"
                  << "Please note that every character will be represented as I for \"id\"\n"
                  << "Type \"Exit\" to exit.\n\n>";
        std::getline(std::cin, expression);

        if(expression == "Exit" || expression == "exit")
            return 0;
        else if (expression[expression.length()-1] != '$')
        {
            std::cerr << "\nExpression must end with $; re-enter expression with $.\n\n";
            continue;
        }
        else
            {
                expStack = stringToStack(expression);
                while(!stateStack.empty())
                    stateStack.pop();

                stateStack.push(0);
                std::cout <<  std::setw(25)<<std::left <<"State Stack" << std::setw(25) <<std::left<< "Input" << "Action\n";
                if (parseExpression(expStack,stateStack))
                    std::cout << "\n\nExpression is supported by the rules given by the table.\n";
                else
                    std::cout << "\n\nExpression is not supported.\n";
            }
    }
    std::cerr << "Loop broken.\n";
    return -1;
} 

