#include "BuggeredFormatException.h"
#include <iostream>

using namespace std;

/* The constructor, accepts an error message (a string) as an argument.
*/
BuggeredFormatException::BuggeredFormatException(const string &err)
{
  message = err;
}

/* Returns the error message.
*/
string BuggeredFormatException::GetError()
{
  return message;
}
