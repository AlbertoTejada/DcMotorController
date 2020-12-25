/*
  serial.c - Low level functions for sending and recieving bytes via the serial port
  Part of Grbl

  Copyright (c) 2009-2011 Simen Svale Skogsrud
  Copyright (c) 2011-2012 Sungeun K. Jeon

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

/* This code was initially inspired by the wiring_serial module by David A. Mellis which
   used to be a part of the Arduino project. */ 

#ifndef serial_h
#define serial_h

#if defined(__cplusplus)
//extern "C" {
namespace EmbeddedC {
#endif


//#include "nuts_bolts.h"
#include <stdint.h>

#ifndef RX_BUFFER_SIZE
  #define RX_BUFFER_SIZE 128
#endif
#ifndef TX_BUFFER_SIZE
  #define TX_BUFFER_SIZE 64
#endif
#ifndef BAUD_RATE
 #define BAUD_RATE 115200
#endif

#define SERIAL_NO_DATA 0xff // Return value when there is no serial data
#define SERIAL_NOT_AVAIL 0  // Flag value when there is no serial data
#define SERIAL_AVAIL 1 // Flag value when thre is serial data

#ifdef ENABLE_XONXOFF
  #define RX_BUFFER_FULL 96 // XOFF high watermark
  #define RX_BUFFER_LOW 64 // XON low watermark
  #define SEND_XOFF 1
  #define SEND_XON 2
  #define XOFF_SENT 3
  #define XON_SENT 4
  #define XOFF_CHAR 0x13
  #define XON_CHAR 0x11
#endif

void serial_init();

void serial_write(uint8_t data);

void serial_read(uint8_t* data, uint8_t* serial_avail);

// Reset and empty data in read buffer. Used by e-stop and reset.
void serial_reset_read_buffer();



#if defined(__cplusplus)
} //closing the embeddedC namespace

//} // closing brace for extern "C"
#endif

#endif