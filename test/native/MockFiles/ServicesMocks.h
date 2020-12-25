#pragma once

#include <stdint.h>
#include "gmock/gmock.h"

namespace EmbeddedCUnitTest {

class SerialService
{
	public:
		virtual ~SerialService() {} // IMPORTANT: This is needed by std::unique_ptr

		MOCK_METHOD(void, serial_read, (uint8_t*, uint8_t*));
		MOCK_METHOD(void, serial_write, (uint8_t));
};


}
