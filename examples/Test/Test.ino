/**
 * @file FVM/Test.ino
 * @version 1.0
 *
 * @section License
 * Copyright (C) 2016-2017, Mikael Patel
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 *
 * @section Description
 * Token compiler test sketch. Copy-paste forth source below and send
 * to the token compiler.
 */

#include "FVM.h"

/*
: test0 ." hello world" cr halt ;
: test1 0 begin dup 1+ dup 9 = if halt then again ;
: test2 0 begin dup 1+ dup 9 = until halt ;
: test3 0 begin dup 9 < while dup 1+ repeat halt ;
: test4 10 0 do i loop halt ;
: test5 10 0 do i 3 +loop halt ;
: test6 10 0 do i i 5 = if leave then loop halt ;
: test7 2 0 do 2 0 do i j loop loop halt ;
: test8 0 analogread ;
generate-code
*/

const char WORD0_PSTR[] PROGMEM = "test0";
const FVM::code_t WORD0_CODE[] PROGMEM = {
  117, 104, 101, 108, 108, 111, 32, 119, 111, 114, 108, 100, 0, 111, 20, 0
};
const char WORD1_PSTR[] PROGMEM = "test1";
const FVM::code_t WORD1_CODE[] PROGMEM = {
  60, 45, 74, 45, 3, 9, 99, 11, 2, 20, 10, -10, 0
};
const char WORD2_PSTR[] PROGMEM = "test2";
const FVM::code_t WORD2_CODE[] PROGMEM = {
  60, 45, 74, 45, 3, 9, 99, 11, -7, 20, 0
};
const char WORD3_PSTR[] PROGMEM = "test3";
const FVM::code_t WORD3_CODE[] PROGMEM = {
  60, 45, 3, 9, 98, 11, 5, 45, 74, 10, -9, 20, 0
};
const char WORD4_PSTR[] PROGMEM = "test4";
const FVM::code_t WORD4_CODE[] PROGMEM = {
  3, 10, 60, 12, 4, 13, 16, -2, 20, 0
};
const char WORD5_PSTR[] PROGMEM = "test5";
const FVM::code_t WORD5_CODE[] PROGMEM = {
  3, 10, 60, 12, 6, 13, 3, 3, 17, -4, 20, 0
};
const char WORD6_PSTR[] PROGMEM = "test6";
const FVM::code_t WORD6_CODE[] PROGMEM = {
  3, 10, 60, 12, 11, 13, 13, 3, 5, 99, 11, 2, 15, 16, -9, 20, 0
};
const char WORD7_PSTR[] PROGMEM = "test7";
const FVM::code_t WORD7_CODE[] PROGMEM = {
  62, 60, 12, 11, 62, 60, 12, 5, 13, 14, 16, -3, 16, -9, 20, 0
};
const char WORD8_PSTR[] PROGMEM = "test8";
const FVM::code_t WORD8_CODE[] PROGMEM = {
  60, 22, -128, 0
};
const FVM::code_P FVM::fntab[] PROGMEM = {
  (code_P) &WORD0_CODE,
  (code_P) &WORD1_CODE,
  (code_P) &WORD2_CODE,
  (code_P) &WORD3_CODE,
  (code_P) &WORD4_CODE,
  (code_P) &WORD5_CODE,
  (code_P) &WORD6_CODE,
  (code_P) &WORD7_CODE,
  (code_P) &WORD8_CODE
};
const str_P FVM::fnstr[] PROGMEM = {
  (str_P) WORD0_PSTR,
  (str_P) WORD1_PSTR,
  (str_P) WORD2_PSTR,
  (str_P) WORD3_PSTR,
  (str_P) WORD4_PSTR,
  (str_P) WORD5_PSTR,
  (str_P) WORD6_PSTR,
  (str_P) WORD7_PSTR,
  (str_P) WORD8_PSTR,
  0
};

FVM::Task<32,16> task(Serial);
FVM fvm;

void setup()
{
  Serial.begin(57600);
  while (!Serial);
  Serial.println(F("FVM/Test: started"));
}

void loop()
{
  fvm.interpret(task);
}
