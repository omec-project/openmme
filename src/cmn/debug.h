/*
 * debugUtils.h
 *
 *  Created on: Feb 13, 2011
 *      Author: hariharanb
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <iostream>
#include <sstream>
#include "basicTypes.h"
using namespace std;

typedef enum{
              LEVEL_1,
              LEVEL_2,
              LEVEL_3,
              LEVEL_4
            }DebugLevel;


class Debug{
public:
  Debug();
  ~Debug();

  
  void printDebugStream();
  void printDebugStreamToFile();

  void add(const char* data);
  void add(Uint8 data);
  void add(Uint16 data);
  void add(Uint32 data);
  void add(Uint64 data);
  
  void endOfLine();
  void startNewLine();
  void incrIndent();
  void decrIndent();

  void clearStream();
 
  void setHexOutput();
  void unsetHexOutput();

private:

  ostringstream stream;
  Uint8 indent;
  bool newLine;
};

#endif /* DEBUGUTILS_H_ */
