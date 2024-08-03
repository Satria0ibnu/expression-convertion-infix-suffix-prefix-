#include <iostream>
//#include <stack>
#include <string>

using namespace std;

class Stack { // parent class
protected:
    static const int size = 32;
    int top;

public:
    Stack() {
        top = -1;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == size - 1;
    }

};

class CharStack : public Stack {
private:
    char stackArray[size];

public:
    CharStack() {
    }

    void push(char element) {
        if (isFull()) {
            cout << "Stack overflow, cannot push element: " << element << endl;
            return;
        }
        stackArray[++top] = element;
    }

    char pop() {
        if (isEmpty()) {
            cout << "Stack is empty, cannot pop." << endl;
            return '\0'; //returning a null character 
        }
        return stackArray[top--];
    }

    char peek() {
        if (isEmpty()) {
            cout << "Stack is empty, cannot peek." << endl;
            return '\0'; //returning a null character
        }
        return stackArray[top];
    }
};

class StringStack : public Stack {
private:
    string stackArray[size];

public:
    StringStack() {
    }

    void push(const string& element) {
        if (isFull()) {
            cout << "Stack overflow, cannot push element: " << element << endl;
        }
        stackArray[++top] = element;
    }

    string pop() {
        if (isEmpty()) {
            cout << "Stack is empty, cannot pop." << endl;
            return "";
        }
        return stackArray[top--];
    }

    string peek() {
        if (isEmpty()) {
            cout << "Stack is empty, cannot peek." << endl;
            return "";
        }
        return stackArray[top];
    }
};


bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int comparePrior(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    }

    return 0;
}

string reverse(string str) {
    int n = str.length(); 
    string result = "";
    while(n--)
       result += str[n];
    
    return result;
}

string infix2suffix(const string& infix) { // only work with the input is string (no space)
    string suffix = "";
    CharStack operatorSt;

    for (char c : infix) { // scanning each char

        if (isalnum(c)) { // to make sure it is only alpha numeric
            suffix += c;

        } else if (c == '(') { // just fill the open para.. to stack
            operatorSt.push(c); 

        } else if (c == ')') {
            while (!operatorSt.isEmpty() && operatorSt.peek() != '(') // output pop if not (
            {
                suffix += operatorSt.peek();
                operatorSt.pop();
            }
            if (operatorSt.peek() == '(') { //pop delete (
                operatorSt.pop();
            }

        } else if (isOperator(c)){
            while (!operatorSt.isEmpty() && comparePrior(c)<=comparePrior(operatorSt.peek())) {
                suffix += operatorSt.peek();
                operatorSt.pop();
            }

            operatorSt.push(c);
        }
    }

    while (!operatorSt.isEmpty()) {
        suffix += operatorSt.peek();
        operatorSt.pop();
    }

    return suffix;
}



string infix2prefix(string str) {
    // reverse str then do infix suffix then reverse back
    return reverse(infix2suffix(reverse(str)));
}


string suffix2infix(const string& postfix) {
    StringStack expresSt;
    for (char c : postfix) {
        if (isalnum(c)) {
            string operand(1, c);
            expresSt.push(operand);
        } else if (isOperator(c)) {
            string operand2 = expresSt.peek();
            expresSt.pop();

            string operand1 = expresSt.peek();
            expresSt.pop();

            string subExpression = "(" + operand1 + c + operand2 + ")";
            expresSt.push(subExpression);
        }
    }

    if (!expresSt.isEmpty()) {
        return expresSt.peek();
    } else {
        return ""; // Return an empty string something unexpected happen
    }
}

string prefix2infix(const string& prefix) {
    StringStack expresSt2;

    int length = prefix.length();
    for (int i = length - 1; i >= 0; i--) { // scanning each char from the last
        char currentChar = prefix[i];

        if (isalnum(currentChar)) {
            string operand(1, currentChar); // char to string convert
            expresSt2.push(operand);

        } else if (isOperator(currentChar)) {
            string operand1, operand2;

            if (!expresSt2.isEmpty()) {
                operand1 = expresSt2.peek();
                expresSt2.pop();
            }

            if (!expresSt2.isEmpty()) {
                operand2 = expresSt2.peek();
                expresSt2.pop();
            }

            string subExpression = "(" + operand1 + currentChar + operand2 + ")";
            expresSt2.push(subExpression);
        }
    }

    if (!expresSt2.isEmpty()) {
        return expresSt2.peek();
    } else {
        return "";
    }
}



int main()
{
    int choice;
    string expression;

    while(true) {


        cout << endl;
        cout << "Choose the conversion option:" << endl;
        cout << "1. Infix to Suffix(Postfix)" << endl;
        cout << "2. Infix to Prefix" << endl;
        cout << "3. Suffix(Postfix) to Infix" << endl;
        cout << "4. Prefix to Infix" << endl;
        
        //example input A+B*C-D/E
        //cant read parantheses
        cout << "Enter your choice:  ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1:
                {
                    cout << "Enter the infix expression:  " << endl;
                    cin >> expression;
                    cout << "Suffix expression: " << infix2suffix(expression) << endl;
                    break;
                }
            case 2:
                {
                    cout << "Enter the infix expression:  " << endl;
                    cin >> expression;
                    cout << "Prefix expression: " << infix2prefix(expression) << endl;
                    break;
                }
            case 3:
                {
                    cout << "Enter the suffix(postfix) expression:  " << endl;
                    cin >> expression;
                    cout << "Infix expression: " << suffix2infix(expression) << endl;
                    break;
                }
            case 4:
                {
                    cout << "Enter the prefix expression:  " << endl;
                    cin >> expression;
                    cout << "Infix expression: " << prefix2infix(expression) << endl;
                    break;
                }
            default:
                cout << "Invalid choice. Please enter 1,2,3 or 4" << endl;
        }
        
        char conti;
        cout << endl;
        cout << "Do you want to retry (y/n)? ";
        cin >> conti;

        if (conti != 'y' && conti != 'Y') {
            break;
        }

    }


    return 0;
}







// make tree expression
//2 stack ( node stack & operator stack)
// if operand 
//     fill node stack

// if (
//     fill operator stack

// if )
//     loop if not (
//         assign top operator stack *right to most top node stack
//         pop top node stack
//         assign top operator stack *left to most top node stack
//         pop top node stack
//         fill top node stack with operator that already assigned
//         pop top operator stack

//     if (
//         pop top operator(delete)

// if operator
//     // compare

//     loop if  not empty && newoperator <= most top operator in stack
//         assign top operator stack *right to most top node stack
//         pop top node stack
//         assign top operator stack *left to most top node stack
//         pop top node stack
//         fill top node stack with operator that already assigned
//         pop top operator stack

//     fill operator stack

// loop if stack not empty   after scanning
//     assign top operator stack *right to most top node stack
//     pop top node stack
//     assign top operator stack *left to most top node stack
//     pop top node stack
//     fill top node stack with operator that already assigned
//     pop top operator stack

