#pragma once

#ifndef _SDT_TYPES_H_
#define _SDT_TYPES_H_

#include <stdint.h>

//This type can be used as standard API return type which is shared between the 
//RTE and the BSW modules
typedef uint8_t Std_ReturnType;

//This type shall be used to request the version of a BSW module using the
//<Module name>_GetVersionInfo() function
typedef struct {
	uint16_t vendorID;
	uint16_t moduleID;
	uint8_t sw_major_version;
	uint8_t sw_minor_version;
	uint8_t sw_patch_version;
}Std_VersionInfoType ;

#define E_OK		(0x00u)
#define E_NOT_OK	(0x01u)

#define STD_HIGH	(0x01u) /* Physical state 5V or 3.3V */ 
#define STD_LOW		(0x00u) /* Physical state 0V */ 

#define STD_ACTIVE	(0x01u) /* Logical state active */ 
#define STD_IDLE	(0x00u) /* Logical state idle */

#define STD_ON		(0x01u)
#define STD_OFF		(0x00u) 

#endif // _SDT_TYPES_H_
