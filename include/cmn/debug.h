/*
 * Copyright 2019-present Open Networking Foundation
 * Copyright (c) 2019, Infosys Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <iostream>
#include <sstream>
#include <stdint.h>

using namespace std;

namespace cmn
{
namespace utils
{
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

  void add(char* data);
  void add(uint8_t data);
  void add(uint16_t data);
  void add(uint32_t data);
  void add(uint64_t data);
  
  void endOfLine();
  void startNewLine();
  void incrIndent();
  void decrIndent();

  void clearStream();
 
  void setHexOutput();
  void unsetHexOutput();

private:

  ostringstream stream;
  uint8_t indent;
  bool newLine;
};
};
};

#endif /* DEBUGUTILS_H_ */

