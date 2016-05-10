/*
 * expression.cc - Implementation of a class representing simple arithmetic
 *                 expressions, as declared in expression.h.  Part of CPS222
 *                 Project 2.
 *
 * Skeleton copyright (c) 2001, 2013 - Russell C. Bjork
 *
 */

#include "expression.h"

/* The following methods are to be written by students, and constitute
 * CPS222 Project 2.
 */
int getPrecedence(char x)
{
        switch (x)
        {

        case '(':
                return 1;

        case ')':
                return 1;

        case '/':
                return 3;

        case '*':
                return 3;

        case '+':
                return 2;

        case '-':
                return 2;

        default:
                return 0;
        }
}


string Expression::convertToPostfix(string infix) const throw (SyntaxError)
{
        //Set Variables

        int length = infix.length();
        bool operandExpected = true;
        bool extraCharacter;
        stack<char> s;
        string postfix;
        int i = 0;
        char x;
        string numbers = "1234567890+/*-()";

        //go through the string character by character
        while (i < length)
        {
                x = infix[i];
                int precedence = getPrecedence(x);
                extraCharacter = numbers.find(x) == std::string::npos;


                //if the char is a extra character then throw the error check
                if(extraCharacter) {
                        throw SyntaxError(i, "Not valid character");
                }
                else{


                        //get the precedence of the character
                        if (precedence == 0 )
                        {
                                //if last char is a operator
                                if(operandExpected == true) {

                                        postfix = postfix + x;
                                        operandExpected = false;

                                }
                                //throw a error if it was a operand
                                else {
                                        throw SyntaxError(i, "operator expected");
                                }

                        }

                        //if the current char is a opertaor
                        else if (precedence > 1)
                        {
                                // check to make sure last char was a operand
                                if(operandExpected == false) {

                                        //if there sis a stack, add operators pushes with higher precedence to the
                                        //postfix string
                                        while (!s.empty() && getPrecedence(s.top()) >= precedence)
                                        {
                                                postfix = postfix + s.top();
                                                s.pop();
                                        }
                                        //push character
                                        s.push(x);
                                        operandExpected = true;
                                }
                                //if last char was a operator throw a error
                                else{
                                        throw SyntaxError(i, "Operand expected");
                                }
                        }
                        else if (x == '(')
                        {
                                s.push(x);
                        }

                        else if (x == ')')
                        {
                                //check if the matching  '(' is in the infix
                                if (s.empty()) {
                                        throw SyntaxError(0, "'(' expected");
                                }

                                while (s.top() != '(' )
                                {
                                        //check if the matching  '(' is in the infix
                                        if (s.empty()) {
                                                throw SyntaxError(0, "'(' expected");
                                        }

                                        postfix = postfix + s.top();
                                        s.pop();
                                }
                                s.pop();
                        }

                        i++;
                }
        }


        // if it ends with a operator throw a error
        if(operandExpected == true){
                throw SyntaxError(i, "Operand expected");
        }
        else{
                while (!s.empty())
                {
                        //throw error if there is not a matching ')' at the end
                        if(s.top() == '(') {
                                throw SyntaxError(infix.length(), "Missing ')' ");
                        }
                        postfix = postfix + s.top();
                        s.pop();
                }
        }

        return postfix;

}

// Given the ASCII code item checks if it is supported operator

//INPUT ASCII code
//OUTPUT True or False
bool checkoperator(int x)
{
        //ASCII codes for + - / *
        if ((x == 42) || (x == 43) || (x == 45) || (x == 47))
        {
                return true;
        }
        else
        {
                return false;
        }
}


//Given a ASCII code for a number converts it to a int

//INPUT ASCII code
//OUTPUT int
int convertAsciiToInt(int x)
{
        return(x - '0');
}


//Given two numbers and a ASCII code for a operator calculates a number

//INPUT number to be operated on and the ASCII code for a operator
//OUTPU int
int operate(int leftvalue, int rightvalue, int theop)
{
        //Multiply
        if (theop == 42)
        {
                return(leftvalue * rightvalue);
        }
        //Add
        else if (theop == 43)
        {
                return(leftvalue + rightvalue);
        }
        //Subtract
        else if (theop == 45)
        {
                return(leftvalue - rightvalue);
        }
        //Divide
        else if (theop == 47)
        {
                return(leftvalue / rightvalue);
        }
}


int Expression::evaluate(string postfix) const throw (DivideByZeroError)
{
        //local vairables
        stack<char> Cstack;
        stack<int> NumberStack;
        int finalvalue;

        //loop through the in reverse adding to the current stack
        for (int i = postfix.length() - 1; i > -1; i--)
        {
                char currentvalue = postfix[i];
                Cstack.push(currentvalue);
        }

        if(postfix.length() == 1) {
                finalvalue = convertAsciiToInt(postfix[0]);
        }
        else{

                while (Cstack.size() != 0)
                {
                        int workValueInt = Cstack.top();
                        if (checkoperator(workValueInt))
                        {
                                //Create the right Value
                                int rightvalue = NumberStack.top();
                                NumberStack.pop();

                                //Create the left value
                                int leftvalue = NumberStack.top();
                                NumberStack.pop();
                                int result;

                                //Check to ensure we don't divide by zero
                                //If we do we through a error
                                if ((rightvalue == 0) && (workValueInt == 47))
                                {
                                        throw DivideByZeroError(Cstack.size());
                                }
                                else
                                {
                                        result = operate(leftvalue, rightvalue, workValueInt);
                                }

                                //Check to see if this is the final operation
                                if (Cstack.size() == 1)
                                {
                                        //Set the final value
                                        finalvalue = result;
                                }

                                //Add the operation back to the number stack
                                NumberStack.push(result);
                        }
                        else
                        {
                                //Push a number to the number stack
                                NumberStack.push(convertAsciiToInt(workValueInt));
                        }

                        //Remove a item from the input stack
                        Cstack.pop();
                }
        }
        //The final return value
        return finalvalue;
}

//Given a ASCII int value checks to see if it is a
//High priority operator if so we return true
bool checkforhighpriorityoperator(int x)
{
        if ((x == 42) || (x == 47))
        {
                return true;
        }
        else
        {
                return false;
        }
}


string Expression::convertToPrefix(string postfix) const
{
        //Declar initial variables
        stack<char> Cstack;
        stack<char> Cnumbers;
        string output;

        // Add the input to a stack
        for (int i = postfix.length() - 1; i > -1; i--)
        {
                char currentvalue = postfix[i];

                Cstack.push(currentvalue);
        }

        //While there is still items in our stack to process
        //we keep going
        while (Cstack.size() != 0)
        {
                //Set the working value for this cycle
                char workValue = Cstack.top();

                //Check to see if the current working value is
                //A high priority operator
                if (checkforhighpriorityoperator(workValue))
                {
                        //Variables

                        //Set a suboutput to rearrange the numbers
                        //So the stack does not swap the numbers
                        string suboutput;

                        //momentary value we add to the suboutput
                        char valuetoadd;

                        //Add the high priority operator to the ouput
                        //Then remove that from the current stack
                        valuetoadd = Cstack.top();
                        output = output + valuetoadd;
                        Cstack.pop();

                        //Add the 1st value for the high priority operator
                        //Then remove that from the current stack
                        if (Cnumbers.size() != 0)
                        {
                                valuetoadd = Cnumbers.top();
                                suboutput = valuetoadd + suboutput;

                                Cnumbers.pop();
                        }

                        //Add the 2nd value for the high priority operator
                        //Then remove that from the current stack
                        if (Cnumbers.size() != 0)
                        {
                                valuetoadd = Cnumbers.top();
                                suboutput = valuetoadd + suboutput;
                                Cnumbers.pop();
                        }

                        //Add the numbers in the correct order behind the priority operator
                        output = output + suboutput;

                        //Flush the stack of all objects before the high priority operator
                        string suboutputflush;
                        while (Cnumbers.size() != 0)
                        {
                                valuetoadd = Cnumbers.top();

                                //Check for operators
                                if (checkoperator(valuetoadd))
                                {
                                        suboutputflush = suboutputflush + valuetoadd;
                                        Cnumbers.pop();
                                }
                                else
                                {
                                        output = valuetoadd + output;
                                        Cnumbers.pop();
                                }
                        }
                        //Add operators to the front of the output
                        output = suboutputflush + output;
                }
                else
                {
                        Cnumbers.push(workValue);
                        Cstack.pop();
                }

                //Print out the rest of the numbers

                //If there are no more items to process through
                //Then we assume there are no more high priortiy
                //operators so we process all the other items in the Cnumber stack
                if (Cstack.size() == 0)
                {
                        //Variable

                        //A string to keep our numbers from getting swaped around due to the stack
                        string suboutputop;

                        //While there are still items in our Cnumbers stack then we keep going
                        while (Cnumbers.size() != 0)
                        {
                                //Variables

                                //momentary variable to add to the output
                                char valuetoadd;
                                valuetoadd = Cnumbers.top();

                                //Check to see if the valuetoadd is a operator

                                //True: we add that value to the suboutput
                                //False: we add that value to the back of the output
                                if (checkoperator(valuetoadd))
                                {
                                        suboutputop = suboutputop + valuetoadd;
                                        Cnumbers.pop();
                                }
                                else
                                {
                                        output = output + valuetoadd;
                                        Cnumbers.pop();
                                }
                        }

                        //Add the suboutput to the front of the output thus completing prefix
                        output = suboutputop + output;
                }
        }


        // int size = postfix.length();-1;
        // string output = "";
        // int OperandsNeeded = 1;
        // int length = postfix.length();
        //
        //
        //
        // while(size > 0) {
        //         size--;
        //         if (OperandsNeeded != 0) {
        //                 if (getPrecedence(postfix[length-size]) == 0) {
        //                         OperandsNeeded--;
        //                 }
        //                 else{
        //                         OperandsNeeded++;
        //                 }
        //         }
        // }
        // output += postfix[postfix.length() - 1];
        // output += convertToPrefix(postfix.substr(0, size));
        // output += convertToPrefix(postfix.substr(size, (postfix.length()-1)-(size)));



//return the completed output
        return output;
}
