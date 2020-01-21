/*
 * debugUtils.h
 *
 *  Created on: Feb 13, 2011
 *      Author: hariharanb
 */

#include "debug.h"

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
  cout << stream.str();
}

void Debug::clearStream()
{
  stream.str("");
}


void Debug::printDebugStreamToFile()
{
  // TODO 
}

void Debug::add(const char* data)
{
  if (newLine)
     startNewLine();
  stream << data;
}

void Debug::add(Uint8 data)
{
  if (newLine)
     startNewLine();
  stream << (Uint16)data;
}

void Debug::add(Uint16 data)
{
  if (newLine)
     startNewLine();
  stream << data;
}

void Debug::add(Uint32 data)
{
  if (newLine)
     startNewLine();
  stream << data;
}

void Debug::add(Uint64 data)
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
  Uint8 i;
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
