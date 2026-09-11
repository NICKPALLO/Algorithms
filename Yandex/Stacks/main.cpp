#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

void processBuf(std::stack<int>& st, std::string& buf)
{
    if(buf.size() == 1)
    {
        switch(buf[0])
        {
            case '*':
            {
                if(st.size()<2)
                {
                    throw std::runtime_error("invalid input data");
                }
                int a = st.top();
                st.pop();
                int b = st.top();
                st.pop();
                st.push(a*b);
                break;
            }
            case '+':
            {   
                if(st.size()<2)
                {
                    throw std::runtime_error("invalid input data");
                }
                int a = st.top();
                st.pop();
                int b = st.top();
                st.pop();
                st.push(a+b);
                break;
            }
            case '-':
            {
                if(st.size()<2)
                {
                    throw std::runtime_error("invalid input data");
                }
                int a = st.top();
                st.pop();
                int b = st.top();
                st.pop();
                st.push(b-a);
                break;
            }
            default:
            {
                st.push(std::stoi(buf));
            }
        }
    }
    else
    {
        st.push(std::stoi(buf));
    }
    buf.clear();
}

int solveExpression(const std::string& expression)
{
    std::stack<int> st;
    std::string buf;
    
    try{
        for(size_t i = 0; i < expression.size(); ++i)
        {
            if(expression[i] != ' ')
            {
                buf.push_back(expression[i]);
            }
            if((expression[i] == ' ' || i+1 == expression.size()) && !buf.empty())
            {
                processBuf(st,buf);
            }
        }
        if(st.size() != 1)
        {
            throw std::runtime_error("invalid input data");
        }
        return st.top();
    }   
    catch(const std::exception& ex)
    {
        std::cout<<ex.what();
    }
}


//В выражении могут встречаться знаки сложения, вычитания, умножения, скобки и пробелы (пробелов внутри чисел быть не должно)
//1+(-2*2 - 3) = 2
//1+a+1 = WRONG
//1 1 + 2

//стек 
//1 -2 2 * 3 - +

/*
1+1
(1+1)*5
-1 + 2

+ - * - слева не может ничего не быть - либо число либо скобка

*/


int main()
{
    std::string expression;

    std::string expression_infix;    
    std::stack<char> st;

    std::unordered_map<char,int> priority;
    priority['-'] = 1;
    priority['+'] = 1;
    priority['*'] = 2;

    priority[')'] = 999;
    priority['('] = 999;

    std::string buf;
    bool wasOperand = false;

    for(size_t i = 0; i<expression.size(); ++i)
    {
        if(expression[i] == ' ')
        {
            continue;
        }
        if(expression[i] >= '1' && expression[i] <= '9')
        {
            //Должна быть защита от пробелов
            wasOperand = false;
            expression_infix.push_back(expression[i]);
        }
        else if(expression[i] == '+' || expression[i] == '-' || expression[i] == '*') 
        {
            //Мы тут если есть операнд!!!
            //Прошлым должно быть число
            //выталкиваем в ответ все операции большего и равного приоритета и сами кладемся в стек
            if(i == 0 || wasOperand)
            {
                std::cout<<"WRONG";
                return;
            }
            while(!st.empty())
            {
                if(priority[st.top()] >= priority[expression[i]])
                {
                    expression_infix.push_back(' ');
                    expression_infix.push_back(st.top());
                    st.pop();
                }  
                else
                {
                    break;
                }
            }
            st.push(expression[i]);
            wasOperand = true;
        }
        else if(expression[i] == '(')
        {
            if(i == 0 || wasOperand)
            {
                st.push('(');
            }
            else
            {
                std::cout<<"WRONG";
                return;
            }   
            wasOperand = true;
        }
        else if(expression[i] == ')')
        {
            //для ')' прошлым должно быть число
            if(i == 0 || wasOperand)
            {
                std::cout<<"WRONG";
                return;
            }
            while(true)
            {
                if(st.empty())
                {    
                    std::cout<<"WRONG";
                    return;
                }
                if(st.top() == '(')
                {
                    st.pop();
                    break;
                }
                else
                {
                    expression_infix.push_back(' ');
                    expression_infix.push_back(st.top());
                    st.pop();
                }
            }
        }
        else
        {
            std::cout<<"WRONG";
            return;
        }
    }

    return 0;
}