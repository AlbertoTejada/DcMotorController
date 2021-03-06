#pragma once
#include <memory>

#include "gmock/gmock.h"
#include "ServicesMocks.h"
#include "ModuleMock.h"

namespace EmbeddedCUnitTest {

using namespace ::testing;

class TestFixture : public ::testing::Test
{
public:
	TestFixture(BaseModuleMock *mocks)
	{
		_serial.reset(new ::testing::NiceMock<SerialService>());
		_modulesMocks.reset(mocks);
	}

	~TestFixture()
	{
		_serial.reset();
		_modulesMocks.reset();
	}

	template<typename T>
	static T& GetMock()
	{
		auto ptr = dynamic_cast<T*>(_modulesMocks.get());
		if (ptr == nullptr)
		{
			auto errMsg = "The test does not provide mock of \"" + std::string(typeid(T).name()) + "\"";
			throw std::exception(errMsg.c_str());
		}
		return *ptr;
	}

	// Services
	static std::unique_ptr<SerialService> _serial;

	// Modules mocks
	static std::unique_ptr<BaseModuleMock> _modulesMocks;
};

}
