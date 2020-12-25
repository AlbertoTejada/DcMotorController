/*
  protocol.h - the serial protocol master control unit
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

#ifndef protocol_h
#define protocol_h

#ifdef __cplusplus
//extern "C" {
namespace EmbeddedC {
#endif

//#include <avr/sleep.h>
#include "nuts_bolts.h"
#include <stdint.h>

// Line buffer size from the serial input stream to be executed.
// NOTE: Not a problem except for extreme cases, but the line buffer size can be too small
// and g-code blocks can get truncated. Officially, the g-code standards support up to 256
// characters. In future versions, this will be increased, when we know how much extra
// memory space we can invest into here or we re-write the g-code parser not to have his 
// buffer.
#ifndef LINE_BUFFER_SIZE
  #define LINE_BUFFER_SIZE 50
#endif

// Define protocol bit map. Used internally by protocol to get the command code and
// the length of a new message.
// #define MSG_LEN 0b00001111
// #define MSG_CMD 0b11110000
// #define GET_MSG_CMD(x) (((x) & MSG_CMD) >> 4)

// Define the maximun nomber of read cycles, to avoid inifinite loops:
#define MAX_CYCLIC_READ LINE_BUFFER_SIZE


// Define the end of line character:
#define EOL '\0' 

// Initialize the serial protocol
void protocol_init();

// Read frames from the serial port and execute them as they
// come in. Blocks until the serial buffer is emptied. 
void protocol_read();

// Executes one line of input according to protocol
uint8_t protocol_execute_line(char *line);

// Checks and executes a runtime command at various stop points in main program
void protocol_execute_runtime();

//// Execute the startup script lines stored in EEPROM upon initialization
//void protocol_execute_startup();

//#ifndef __cplusplus
// Write frames to the serial port.
void protocol_write(char* frame, uint8_t len);
//#endif

#ifdef __cplusplus
} // closing brace for the EmbeddedC namespace

//} // closing brace for extern "C"
#endif

#endif