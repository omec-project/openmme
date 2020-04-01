 /*
Copyright 2019-present Infosys Limited  
   
SPDX-License-Identifier: Apache-2.0  
  
*/ 


#include "../../../gtpV2Codec/ieClasses/dataTypeCodecUtils.h"
#include "../../../gtpV2Codec/ieClasses/manual/gtpV2DataTypes_Manual.h"

bool
DataTypeCodecUtils::encodeDigitRegister (MsgBuffer & buffer,
                                     DigitRegister const & data)
{
  Uint8 i;
  for (i = 0; i< data.length; i+= 2)
  {
    Uint8 digit1 = data.digits[i];
    Uint8 digit2 = data.digits[i+1];
   
    if (digit1 >9 || (digit2 > 9 && digit2 != 0x0F))
    {
      errorStream.add((char *)"Data validation failure: Non BCD digit encountered in DigitRegister\n");
      return false;
    }
    else
    {
      buffer.writeBits(digit2, 4);
      buffer.writeBits(digit1, 4);
    }
  }
  return true;
}

bool
DataTypeCodecUtils::decodeDigitRegister (MsgBuffer & buffer,
                                     DigitRegister & data, 
                                     Uint16 length)
{
  Uint8 i;
  Uint8 digitLength = 0;
  if (length > 8)
  { 
    errorStream.add((char *)"Data validation failure:DigitRegister.Length\n");
    return false;
  }
  for (i = 0; i < length; i ++)
  {
     Uint8 digit1;
     Uint8 digit2;
     digit2 = buffer.readBits(4);
     digit1 = buffer.readBits(4);
     if (digit1 >9 || (digit2 > 9 && digit2 != 0x0F))
     {
       errorStream.add((char *)"Data validation failure: Non BCD Digit in DigitRegister\n");
       return false;
     }
     else
     {
       data.digits[i*2] = digit1;
       data.digits[i*2+1] = digit2;
     }
     digitLength += 2;
     if (digit2 == 0x0F)
     { 
       // Reached the last digit stop here
       digitLength--;
       break;
     }
  }
  data.length = digitLength;
  return true;

}

void
DataTypeCodecUtils::displayDigitRegister_v (DigitRegister const & data,
                                            Debug & stream)
{
  stream.incrIndent();
  stream.add((char *)"DigitRegister:");
  stream.endOfLine();
  stream.incrIndent();
  stream.add((char *)"Length:");
  stream.add(data.length);
  stream.endOfLine();
  Uint8 i;
  for (i = 0; i < data.length; i++)
  {
    stream.add(data.digits[i]);
    stream.add((char *)"  ");
  }
  stream.endOfLine();
  stream.decrIndent();
  stream.decrIndent();
}


