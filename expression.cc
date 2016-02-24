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
  string postfix;
  int i = 0;
  int k = 0;
  char x;

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

  //The final return value
  return finalvalue;
}                       // Students: replace return code and remove this comment


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
  stack<char> Cstack;
  stack<char> Cnumbers;
  string output;

  for (int i = postfix.length() - 1; i > -1; i--)
  {
    char currentvalue = postfix[i];

    Cstack.push(currentvalue);
  }
  while (Cstack.size() != 0)
  {
    char workValue = Cstack.top();
    if (checkforhighpriorityoperator(workValue))
    {
      string suboutput;
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
    if (Cstack.size() == 0)
    {
      string suboutputop;
      while (Cnumbers.size() != 0)
      {
        char valuetoadd;
        valuetoadd = Cnumbers.top();
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
      output = suboutputop + output;
    }
  }

//Mat
// string subString2;
// string subString1;
// string prefix;
// string part1;
// string part2;
// int size = 1;
// int OperandsNeeded = 1;
// int length = postfix.length();
//
//
// while(size<length){
//   if (OperandsNeeded != 0){
//     if (getPrecedence(postfix[length-size]) == 0){
//       OperandsNeeded--;
//     }
//     else{
//       OperandsNeeded++;
//       prefix += postfix[length];
//     }
//   }
//   else{
//     subString1 = postfix.substr(0, size);
//     subString2 =  postfix.substr(size, length);
//     part1 += convertToPrefix(subString1);
//     part2 += convertToPrefix(subString2);
//   }
//   size++;
// }
//  prefix = part1 + part2;
//  cout<<prefix<<endl;
//  return prefix;
//   return "";
  return output;
}


// Students: replace return code and remove this comment
