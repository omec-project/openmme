/*
 * Copyright (c) 2019, Infosys Ltd.
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

#include <debug.h>

using namespace cmn::utils;

Debug::Debug()
{
  indent = 0;
  newLine = true;
}

Debug::~Debug()
{
  //TODO
}

void Debug::printDebugStream()
{
  fprintf(stderr, "%s" , stream.str().c_str());
}

void Debug::clearStream()
{
  stream.str("");
}

void Debug::printDebugStreamToFile()
{
  // TODO 
}

void Debug::add(char* data)
{
  if (newLine)
     startNewLine();
  stream << data;
}

void Debug::add(uint8_t data)
{
  if (newLine)
     startNewLine();
  stream << (uint16_t)data;
}

void Debug::add(uint16_t data)
{
  if (newLine)
     startNewLine();
  stream << data;
}

void Debug::add(uint32_t data)
{
  if (newLine)
     startNewLine();
  stream << data;
}

void Debug::add(uint64_t data)
{
  if (newLine)
     startNewLine();
  stream << data;
}


void Debug::endOfLine()
{
  stream <<"\n";
  newLine = true;
}

void Debug::startNewLine()
{
  uint8_t i;
  for (i = 0; i<= indent; i++)
  {
    stream <<"  ";
  }
  newLine = false;
}

void Debug::incrIndent()
{
  indent++;
}

void Debug::decrIndent()
{
  if (indent > 0)
    indent --;
}

void Debug::setHexOutput()
{
  stream.setf(ios::hex, ios::basefield);
}

void Debug::unsetHexOutput()
{
  stream.unsetf(ios::hex);
}

