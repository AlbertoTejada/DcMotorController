/*
  protocol.c - the serial protocol master control unit
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

#include "protocol.h"
#include "serial.h"
#include "nuts_bolts.h"
#include "database.h"
#include "sysenv.h"

static char line[LINE_BUFFER_SIZE] = {'\0'} ; // Line to be executed. Zero-terminated.
static uint8_t char_counter; // Last character counter in line variable.
static uint8_t msglen; //Incoming menssage length

#if defined(__cplusplus)
namespace EmbeddedC {
#endif

void protocol_init() 
{
  char_counter = 0; // Reset line input
  msglen = 0;  // Reset the incoming message length to 0 (no message incoming)
}

//Read one frame of incoming serial data.
void protocol_read()
{
  uint8_t cyclic_cnt = 0;
  uint8_t data;
  uint8_t serial_avail;
  uint8_t canid;  //Command code for new message
  bool end_loop = false;

  /*
  Read byte acceptance conditions:
  (msglen == 0) && (c != SERIAL_NO_DATA) -> New message, first byte.
  (msglen != 0) -> Incoming message.
  */

  while ((!end_loop) && (cyclic_cnt < MAX_CYCLIC_READ))
  {
    cyclic_cnt++;
    serial_read(&data, &serial_avail); //Read byte from the serial buffer

    // The serial bus is not empty:
    if (serial_avail == SERIAL_AVAIL)
    {
      // New message received:
      if (msglen == 0) 
      {
        canid = data;
        // Get the message length associated to the message ID:
        switch(canid)
        {
          case TESTER_PRESENT_ID:
            msglen = TESTER_PRESENT_LEN;
            SysEnv_Wr_protocol_Cmd(canid);
            break;
          case MASTER_01_ID:
            msglen = MASTER_01_LEN;
            SysEnv_Wr_protocol_Cmd(canid);            
            break;
          default:
            // TODO: raise an error -> Undefined CANID
            end_loop = true;
            cyclic_cnt = 0;
            break;
        } 

        char_counter = 0; // Reset char_counter for caution
      }
      // Message reception in process:
      else {
        // Last byte check:
        if (char_counter >= (msglen - 1))
        {
          if (data == EOL)
          {
            get_msg(line);
          }
          else
          {
            // TODO: raise an error -> Incorrect message end      
          }
          end_loop = true;
          cyclic_cnt = 0;
          msglen = 0;
          char_counter = 0;
        }
        // Incoming byte:
        else {
          line[char_counter++] = data;
        }
    }
    }
    // There is no serial data available, reset the parameters and end the loop
    else
    {
      end_loop = true;
      cyclic_cnt = 0;
    }
  }
} 

//Write one frame of outcoming serial data
void protocol_write(char* frame, uint8_t len)
{
  char c;
  uint8_t idx = 0;
  for (idx = 0; idx < len; idx++)
   {
     c = *(frame + idx);
     serial_write((uint8_t)c);
   }
   serial_write((uint8_t)EOL);
}

#if defined(__cplusplus)
}
#endif