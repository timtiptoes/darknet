/*
  slavefuncs.h - slavefuncs library for Wiring - description
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// ensure this library description is only included once
#ifndef slavefuncs_h
#define slavefuncs_h

// include types & constants of Wiring core API
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
// library interface description
class slavefuncs
{
  // user-accessible "public" interface
  public:
    slavefuncs(int);
    void doSomething(void);

  // library-accessible "private" interface
  private:
    int value;
    void doSomethingSecret(void);
};

#endif

