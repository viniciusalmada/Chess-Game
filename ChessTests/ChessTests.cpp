#include <string>
#include "pch.h"
#include "CppUnitTest.h"
#include "../src/numeric_utils.cpp"
#include "../src/image_loader.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ChessTests
{
	TEST_CLASS(NumericUtilsTests)
	{
  public:

    TEST_METHOD(Return4ColorsConverted)
    {
      unsigned int colorInput = 0xFFE8E6E4; // 255, 232, 230, 228

      auto out = NumericUtils::hexTo4Dec(colorInput);

      bool assertion = 232 == out[0] && 230 == out[1] && 228 == out[2] && 255 == out[3];

      Assert::AreEqual(true, assertion);
    }
    
    TEST_METHOD(Return3ColorsConverted)
    {
      int colorInput = 0xE8E6E4; // 232, 230, 228

      auto out = NumericUtils::hexTo3Dec(colorInput);

      bool assertion = 232 == out[0] && 230 == out[1] && 228 == out[2];

      Assert::AreEqual(true, assertion);
    }
    
    TEST_METHOD(ReturnMaximumColor)
    {
      int colorInput = 0xFFFFFFF; // bigger than 0xFFFFFF

      auto out = NumericUtils::hexTo3Dec(colorInput);

      bool assertion = 
        0xFF == out[0] &&
        0xFF == out[1] && 
        0xFF == out[2];

      Assert::AreEqual(true, assertion);
    }

    TEST_METHOD(ReturnMinimumColor)
    {
      int colorInput = -0xFF; // less than 0x00

      auto out = NumericUtils::hexTo3Dec(colorInput);

      bool assertion = 
        0x00 == out[0] &&
        0x00 == out[1] && 
        0x00 == out[2];

      Assert::AreEqual(true, assertion);
    }
  };

  TEST_CLASS(ImageLoaderTests)
  {
    TEST_METHOD(LoadImageToMemory)
    {
      std::string path = R"(N:\Projects\ChessWithIUP\images\testing.png)";

      ImageLoader::load(path);

      Assert::IsTrue(true);
    }
  };
}
