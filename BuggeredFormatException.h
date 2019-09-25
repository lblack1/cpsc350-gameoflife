#ifndef BUGGERED_FORMAT_EXCEPTION
#define BUGGERED_FORMAT_EXCEPTION

#include <iostream>

using namespace std;

/* An exception class to be thrown when a game of life input file isn't properly formatted.
*/
class BuggeredFormatException {

  public:
    BuggeredFormatException(const string &err);
    string GetError();

  private:
    string message;

};

#endif
