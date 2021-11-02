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

  TEST_CLASS(CoordinatesTests)
  {
    TEST_METHOD(GetAllOnFile)
    {
      SquarePosition pos{ File::F_D, Rank::R_4 };
      auto allOnFile = pos.getAllOnFile();

      std::set<SquarePosition> allOnFileExpected = {
        {File::F_D, Rank::R_1},
        {File::F_D, Rank::R_2},
        {File::F_D, Rank::R_3},
        {File::F_D, Rank::R_4},
        {File::F_D, Rank::R_5},
        {File::F_D, Rank::R_6},
        {File::F_D, Rank::R_7},
        {File::F_D, Rank::R_8},
      };

      bool allIn = true;
      for (const auto& exp : allOnFileExpected)
      {
        if (allOnFile.find(exp) == allOnFile.end())
        {
          allIn = false;
          break;
        }
      }

      Assert::IsTrue(allIn);
    }
    TEST_METHOD(GetAllOnRank)
    {
      SquarePosition pos{ File::F_D, Rank::R_4 };
      auto allOnRank = pos.getAllOnRank();

      std::set<SquarePosition> allOnRankExpected = {
        {File::F_A, Rank::R_4},
        {File::F_B, Rank::R_4},
        {File::F_C, Rank::R_4},
        {File::F_D, Rank::R_4},
        {File::F_E, Rank::R_4},
        {File::F_F, Rank::R_4},
        {File::F_G, Rank::R_4},
        {File::F_H, Rank::R_4},
      };

      bool allIn = true;
      for (const auto& exp : allOnRankExpected)
      {
        if (allOnRank.find(exp) == allOnRank.end())
        {
          allIn = false;
          break;
        }
      }

      Assert::IsTrue(allIn);
    }
    TEST_METHOD(GetEastOrSouthBorderSquareFromDiagonal)
    {
      SquarePosition sA1{ File::F_A, Rank::R_1 };
      SquarePosition sG7{ File::F_G, Rank::R_7 };

      auto fromA1 = sA1.getEastOrSouthBorderSquare();
      auto fromG7 = sA1.getEastOrSouthBorderSquare();
      SquarePosition expected(File::F_A, Rank::R_1);

      Assert::IsTrue(
        fromA1 == expected &&
        fromG7 == expected);
    }

    TEST_METHOD(GetEastOrSouthBorderSquareFromBottomRight)
    {
      SquarePosition sC2{ File::F_C, Rank::R_2 };

      auto fromC2 = sC2.getEastOrSouthBorderSquare();
      SquarePosition expected(File::F_B, Rank::R_1);

      Assert::IsTrue(fromC2 == expected);
    }

    TEST_METHOD(GetEastOrSouthBorderSquareFromUpperLeft)
    {
      SquarePosition sB3{ File::F_B, Rank::R_3 };

      auto fromB3 = sB3.getEastOrSouthBorderSquare();
      SquarePosition expected(File::F_A, Rank::R_2);

      Assert::IsTrue(fromB3 == expected);
    }
    TEST_METHOD(GetAllOnSWtoNEFromNW)
    {
      SquarePosition pos{ File::F_A, Rank::R_8 };
      auto allOnSWtoNE = pos.getAllInSWtoNE();

      std::set<SquarePosition> allOnExpected = {
        {File::F_A, Rank::R_8},
      };

      bool allIn = true;
      for (const auto& exp : allOnExpected)
      {
        if (allOnSWtoNE.find(exp) == allOnSWtoNE.end())
        {
          allIn = false;
          break;
        }
      }

      Assert::IsTrue(allIn);
    }
    TEST_METHOD(GetAllOnSWtoNEFromSE)
    {
      SquarePosition pos{ File::F_H, Rank::R_1 };
      auto allOnSWtoNE = pos.getAllInSWtoNE();

      std::set<SquarePosition> allOnExpected = {
        {File::F_H, Rank::R_1},
      };

      bool allIn = true;
      for (const auto& exp : allOnExpected)
      {
        if (allOnSWtoNE.find(exp) == allOnSWtoNE.end())
        {
          allIn = false;
          break;
        }
      }

      Assert::IsTrue(allIn);
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
