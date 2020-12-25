#include "Fixture.h"

using namespace EmbeddedCUnitTest;

namespace EmbeddedC {

void serial_read(uint8_t* data, uint8_t* serial_avail)
{
	return TestFixture::_serial->serial_read(data, serial_avail);
}

void serial_write(uint8_t value)
{
	return TestFixture::_serial->serial_write(value);
}

}
