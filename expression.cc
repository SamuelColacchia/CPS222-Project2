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


int Expression::evaluate(string postfix) const throw (DivideByZeroError)
{
   return 0;
}                       // Students: replace return code and remove this comment


string Expression::convertToPrefix(string postfix) const
{
   return string("");
}                       // Students: replace return code and remove this comment
