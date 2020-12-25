//#include "stdafx.h"

#include "Fixture.h"

namespace EmbeddedCUnitTest {

// Services
std::unique_ptr<SerialService> TestFixture::_serial;

// Modules mocks
std::unique_ptr<BaseModuleMock> TestFixture::_modulesMocks;

}
