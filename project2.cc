/*
 * project2.cc - Main program for CPS222 project 2
 *
 * Repeatedly read infix expressions from standard input (one per line)
 * and echo each and print out various information.
 *
 * Copyright (c) 2001, 2003, 2013 - Russell C. Bjork
 *
 */
<<<<<<< HEAD
 
=======

>>>>>>> 03926b5f7dcc37a9f0d2f47f087d8407eaee7491
#include <iostream>
using namespace std;
#include "expression.h"

// Write out an expression with an extra space between characters
static void writeExpression(string expression)
{
    for (int i = 0; i < expression.length(); i ++)
    {
        if (i != 0) cout << " ";
        cout << expression[i];
    }
}

// Write out an error marker carat (^) at specified place
static void writeErrorMarker(int position)
{
    for (int i = 0; i < position; i ++)
        cout << "  ";
    cout << "^";
}

int main(int argc, char * argv [])
{
    string infix, postfix, prefix;
    getline(cin, infix);
    while (! cin.eof())
    {
        try
        {
            Expression theExpression(infix);
<<<<<<< HEAD
            
            cout << "Infix:   ";
            writeExpression(theExpression.getInfix());
            cout << endl;
        
=======

            cout << "Infix:   ";
            writeExpression(theExpression.getInfix());
            cout << endl;

>>>>>>> 03926b5f7dcc37a9f0d2f47f087d8407eaee7491
            postfix = theExpression.getPostfix();
            if (postfix.length() > 0)
            {
                cout << "Postfix: ";
                writeExpression(postfix);
                cout << endl;
<<<<<<< HEAD
            
=======

>>>>>>> 03926b5f7dcc37a9f0d2f47f087d8407eaee7491
                int value = theExpression.getValue();
                cout << "Value:   " << value << endl;

                prefix = theExpression.getPrefix();
                if (prefix.length() > 0)
                {
                    cout << "Prefix:  ";
                    writeExpression(prefix);
                    cout << endl;
                }
            }
        }
        catch(SyntaxError e)
        {
            cout << "         ";
            writeErrorMarker(e.getPosition());
            cout << e.getDescription() << endl;
        }
        catch(DivideByZeroError e)
        {
            cout << "         ";
            writeErrorMarker(e.getPosition());
            cout << "Division by Zero" << endl;
        }
<<<<<<< HEAD
                
        cout << endl;        
=======

        cout << endl;
>>>>>>> 03926b5f7dcc37a9f0d2f47f087d8407eaee7491

        getline(cin, infix);
    }
}
<<<<<<< HEAD
            
        
=======
>>>>>>> 03926b5f7dcc37a9f0d2f47f087d8407eaee7491
