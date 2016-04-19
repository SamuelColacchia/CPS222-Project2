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

 //could not figure out paranthseies in time
int getPrecedence(char x)
{
  switch (x)
  {
    case '(':
      return 3;

    case ')':
      return 3;

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

enum Character {OPERAND, OPERATOR};

string Expression::convertToPostfix(string infix) const throw (SyntaxError)
{
  //Set Variables
  Character chr = OPERATOR;
  int length = infix.length();

  stack<char> s;
  string postfix;
  int i = 0;
  int k = 0;
  char x;
  bool openParen = false;
  bool closedParen = false;

  while (i < length)
  {
    x = infix[i];
    int precedence = getPrecedence(x);
    if (precedence == 0)
    {

      if (chr == OPERAND){
        throw SyntaxError(i, "Operator expected");}
      else{
         chr = OPERAND;}

      postfix = postfix + x;
      k++;
    }

    else if (precedence > 0 )
    {
<<<<<<< Updated upstream
        while (!s.empty() && precedence <= getPrecedence(s.top()))
=======
<<<<<<< HEAD
      if (chr == OPERATOR && precedence != 3 ){
        throw SyntaxError(i, "OPERAND expected");}
      else if (precedence != 3){
         chr = OPERATOR;}
      else{
        chr = OPERAND;
      }

      if (s.empty())
      {
        s.push(x);
      }
      else
      {
        while (!s.empty() && s.top() != '(' && precedence <= getPrecedence(s.top()))
=======
        while (!s.empty() && precedence <= getPrecedence(s.top()))
>>>>>>> master
>>>>>>> Stashed changes
        {
          postfix = postfix + s.top();
          s.pop();
          k++;
        }
        s.push(x);
      }
<<<<<<< HEAD
      if (x == '(')
=======
    }
    else if (x == '(')
    {
      s.push(x);
      i++;
    }

    else if (x == ')')
    {
      while (s.top() != '(')
<<<<<<< Updated upstream
=======
>>>>>>> master
>>>>>>> Stashed changes
      {
        openParen = true;
        s.push(x);
        i++;
      }

      else if (x == ')')
      {
        bool closedParen = true;
        while (!s.empty() && s.top() != '(')
        {
          postfix = postfix + s.top();

          if (s.top() == '(')
            openParen = true;


          s.pop();
          k++;
        }
        //if (openParen == false){
        //  throw SyntaxError(i,"-( expected");}

    }

    }
    i++;
  }
  while (!s.empty())
  {

    postfix = postfix + s.top();

  //  if (s.top() == ')')
    //  closedParen = true;

    s.pop();
    k++;
  }
  //if (closedParen == false && openParen == true )
  //  throw SyntaxError(i, "-) expected");

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

//return the completed output
  return output;
}
