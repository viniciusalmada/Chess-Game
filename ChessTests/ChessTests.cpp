#include "pch.h"
#include "CppUnitTest.h"
#include "../src/numeric_utils.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessTests
{
	TEST_CLASS(NumericUtilsTests)
	{
  public:

    TEST_METHOD(ReturnColorsConverted)
    {
      int colorInput = 0xE8E6E4; // 232, 230, 228

      auto out = NumericUtils::hexToDecColors(colorInput);

      bool assertion = 232 == out[0] && 230 == out[1] && 228 == out[2];

      Assert::AreEqual(true, assertion);
    }
    
    TEST_METHOD(ReturnMaximumColor)
    {
      int colorInput = 0xFFFFFFF; // bigger than 0xFFFFFF

      auto out = NumericUtils::hexToDecColors(colorInput);

      bool assertion = 
        0xFF == out[0] &&
        0xFF == out[1] && 
        0xFF == out[2];

      Assert::AreEqual(true, assertion);
    }

    TEST_METHOD(ReturnMinimumColor)
    {
      int colorInput = -0xFF; // less than 0x00

      auto out = NumericUtils::hexToDecColors(colorInput);

      bool assertion = 
        0x00 == out[0] &&
        0x00 == out[1] && 
        0x00 == out[2];

      Assert::AreEqual(true, assertion);
    }
  };
}
