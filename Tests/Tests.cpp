#include "pch.h"
#include "CppUnitTest.h"
#include "numeric_utils.h"
#include "im/im.h"
#include "im/im_image.h"
#include "image_loader.h"
#include <string>
#include <filesystem>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
  TEST_CLASS(NumericUtilsTest)
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
      auto cp = std::filesystem::current_path()
        .parent_path()
        .parent_path()
        .append("images")
        .append("img_king_black.png");
      std::string path = cp.generic_string();

      auto img = ImageLoader::load(path);

      Assert::IsTrue(img != nullptr);
    }
  };
}
