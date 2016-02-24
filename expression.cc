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
   case '/':
      return 2;

   case '*':
      return 2;

   case '+':
      return 1;

   case '-':
      return 1;

   default:
      return 0;
   }
}


string Expression::convertToPostfix(string infix) const throw (SyntaxError)
{
   int length = infix.length();

   stack<char> s;
   string      postfix;
   int         i = 0;
   int         k = 0;
   char        x;

   while (i < length)
   {
      x = infix[i];
      int precedence = getPrecedence(x);
      if (precedence == 0)
      {
         postfix = postfix + x;
         k++;
      }

      else if (precedence > 0)
      {
         if (s.empty())
         {
            s.push(x);
         }
         else
         {
            while (!s.empty() && s.top() != '(' && precedence <= getPrecedence(s.top()))
            {
               postfix = postfix + s.top();
               s.pop();
               k++;
            }
            s.push(x);
         }
      }
      else if (x == '(')
      {
         s.push(x);
         i++;
      }

      else if (x == ')')
      {
         while (!s.empty() && s.top() != '(')
         {
            postfix = postfix + s.top();
            s.pop();
            k++;
         }
      }
      i++;
   }

   while (!s.empty())
   {
      postfix = postfix + s.top();
      s.pop();
      k++;
   }

//cout<<"post:"<<postfix<<endl;
//cout<< "input:"<< infix << endl;
   return postfix;
}  // Students: replace return code and remove this comment


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
int convertAsciiToInt(int x) {
  return (x - '0');
}

//Given two numbers and a ASCII code for a operator calculates a number

//INPUT number to be operated on and the ASCII code for a operator
//OUTPU int
int operate(int leftvalue, int rightvalue, int theop) {
  //Multiply
  if (theop == 42) {
    return (leftvalue * rightvalue);
  }
  //Add
  else if (theop == 43) {
    return (leftvalue + rightvalue);
  }
  //Subtract
  else if (theop == 45) {
    return (leftvalue - rightvalue);
  }
  //Divide
  else if (theop == 47) {
      return (leftvalue / rightvalue);
  }
}


int Expression::evaluate(string postfix) const throw (DivideByZeroError)
{
   stack<char> Cstack;
   stack<int> NumberStack;
   int finalvalue;

   //loop through the in reverse adding to the current stack
   for (int i = postfix.length() - 1; i > -1; i--)
   {
      char currentvalue = postfix[i];
      cout << currentvalue << endl;
      Cstack.push(currentvalue);
   }

   while (Cstack.size() != 0)
   {
     int workValueInt = Cstack.top();
     if (checkoperator(workValueInt)) {

       //Create the right Value
       int rightvalue = NumberStack.top();
       NumberStack.pop();

       //Create the left value
       int leftvalue = NumberStack.top();
       NumberStack.pop();

       //Check to see if this is the final operation
       if (Cstack.size() == 1 ) {
         //Set the final value
         finalvalue = operate(leftvalue,rightvalue,workValueInt);
       }

       //Add the operation back to the number stack
       NumberStack.push(operate(leftvalue,rightvalue,workValueInt));
     }
     else {
       //Push a number to the number stack
       NumberStack.push(convertAsciiToInt(workValueInt));
     }

     //Remove a item from the input stack
     Cstack.pop();
   }

   //The final return value
   return finalvalue;
}                       // Students: replace return code and remove this comment


string Expression::convertToPrefix(string postfix) const
{
   return string("");
}                       // Students: replace return code and remove this comment
