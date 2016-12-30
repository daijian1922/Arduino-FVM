/**
 * @file FVM/Blink.ino
 * @version 1.0
 *
 * @section License
 * Copyright (C) 2016, Mikael Patel
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
 * Classical blink sketch using the Forth Virtual Machine (FVM).
 *
 * @section Analysis
 * Bytes      Section
 * ------------------------------------------------
 *        1400 Baseline; Startup and Serial
 *  +474  1874 +Measurement
 *  +84   1958 +Blink sketch code and task
 *  +3314 5272 +Forth Virtual Machine
 *  +780  6052 +Kernel dictionary (112 words)
 *  +978  7030 +Trace mode
 * ------------------------------------------------
 * Arduino Uno/IDE 1.6.13
 */

#define MEASURE
#define BLINK_SKETCH
#define BLINK_TRACE
#define BLINK_RUN

// Enable/disable virtual machine code
#if defined(BLINK_SKETCH)
#include "FVM.h"

const int BLINK_FN = 0;
const char BLINK_PSTR[] PROGMEM = "blink";
// : blink ( ms pin -- )
//   1 over pinmode
//   begin
//     dup digitaltoggle
//     over delay
//   repeat
// ;
const FVM::code_t BLINK_CODE[] PROGMEM = {
  FVM_OP(ONE),
  FVM_OP(OVER),
  FVM_OP(PINMODE),
  FVM_OP(DUP),
  FVM_OP(DIGITALTOGGLE),
  FVM_OP(OVER),
  FVM_OP(DELAY),
  FVM_OP(BRANCH), -6,
  FVM_OP(EXIT)
};

const int SKETCH_FN = 1;
const char SKETCH_PSTR[] PROGMEM = "sketch";
// : sketch ( -- ) 500 13 blink ;
const FVM::code_t SKETCH_CODE[] PROGMEM = {
  FVM_LIT(500),
  FVM_CLIT(13),
  FVM_CALL(BLINK_FN),
  FVM_OP(HALT)
};

const FVM::code_P FVM::fntab[] PROGMEM = {
  BLINK_CODE,
  SKETCH_CODE
};

const str_P FVM::fnstr[] PROGMEM = {
  (str_P) BLINK_PSTR,
  (str_P) SKETCH_PSTR,
  0
};

FVM::task_t task(Serial, SKETCH_CODE);
FVM fvm;
#endif

void setup()
{
  Serial.begin(57600);
  while (!Serial);

  // Enable/disable trace
#if defined(BLINK_TRACE)
  task.trace(true);
#endif
}

void loop()
{
  // Enable/disable measurement
#if defined(MEASURE)
  uint32_t start = micros();
#endif

  // Enable/disable resume (base-line foot-print)
#if defined(BLINK_RUN)
  fvm.resume(task);
#endif

  // Enable/disable measurement
#if defined(MEASURE)
  uint32_t stop = micros();
  uint32_t us = stop-start;
  Serial.print(stop);
  Serial.print(':');
  Serial.println(us);
  Serial.flush();
  delay(100);
#endif
}
