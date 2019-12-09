/*
* Copyright (c) 2019 Infosys Limited
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
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
