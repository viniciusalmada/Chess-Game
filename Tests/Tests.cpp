#include "pch.h"
#include "CppUnitTest.h"
#include "numeric_utils.h"
#include "im/im.h"
#include "im/im_image.h"
#include "image_loader.h"
#include <string>
#include <filesystem>
#include "piece.h"
#include <algorithm>
#include <iterator>

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

  TEST_CLASS(PiecesTests)
  {
    TEST_METHOD(RookMovements)
    {
      RookPiece hook(Player::WHITE, { File::F_D, Rank::R_4 });

      auto movement = hook.possibleMovements();

      bool resD1 = movement.find({ File::F_D, Rank::R_1 }) != movement.end();
      bool resD2 = movement.find({ File::F_D, Rank::R_2 }) != movement.end();
      bool resD3 = movement.find({ File::F_D, Rank::R_3 }) != movement.end();
      bool resD5 = movement.find({ File::F_D, Rank::R_5 }) != movement.end();
      bool resD6 = movement.find({ File::F_D, Rank::R_6 }) != movement.end();
      bool resD7 = movement.find({ File::F_D, Rank::R_7 }) != movement.end();
      bool resD8 = movement.find({ File::F_D, Rank::R_8 }) != movement.end();
      bool resA4 = movement.find({ File::F_A, Rank::R_4 }) != movement.end();
      bool resB4 = movement.find({ File::F_B, Rank::R_4 }) != movement.end();
      bool resC4 = movement.find({ File::F_C, Rank::R_4 }) != movement.end();
      bool resE4 = movement.find({ File::F_E, Rank::R_4 }) != movement.end();
      bool resF4 = movement.find({ File::F_F, Rank::R_4 }) != movement.end();
      bool resG4 = movement.find({ File::F_G, Rank::R_4 }) != movement.end();
      bool resH4 = movement.find({ File::F_H, Rank::R_4 }) != movement.end();

      Assert::IsTrue(
        resD1 && resD2 && resD3 && resD5 && resD6 && resD7 && resD8 &&
        resA4 && resB4 && resC4 && resE4 && resF4 && resG4 && resH4);
    }
    
    
  };
}
