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

    TEST_METHOD(GetAllOnSWtoNEFromNW)
    {
      SquarePosition pos{ File::F_A, Rank::R_8 };
      auto allOnSWtoNE = pos.getAllOnSWtoNE();

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
      auto allOnSWtoNE = pos.getAllOnSWtoNE();

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

    TEST_METHOD(GetAllOnSWtoNEFromAny)
    {
      SquarePosition pos{ File::F_D, Rank::R_4 };
      auto allOnSWtoNE = pos.getAllOnSWtoNE();

      std::set<SquarePosition> allOnExpected = {
        {File::F_C, Rank::R_3},
        {File::F_B, Rank::R_2},
        {File::F_A, Rank::R_1},
        {File::F_E, Rank::R_5},
        {File::F_F, Rank::R_6},
        {File::F_G, Rank::R_7},
        {File::F_H, Rank::R_8},
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

    TEST_METHOD(GetAllOnNWtoSEFromNE)
    {
      SquarePosition pos{ File::F_H, Rank::R_8 };
      auto allOnNWtoSE = pos.getAllOnNWtoSE();

      std::set<SquarePosition> allOnExpected = {
        {File::F_H, Rank::R_8},
      };

      bool allIn = true;
      for (const auto& exp : allOnExpected)
      {
        if (allOnNWtoSE.find(exp) == allOnNWtoSE.end())
        {
          allIn = false;
          break;
        }
      }

      Assert::IsTrue(allIn);
    }

    TEST_METHOD(GetAllOnNWtoSEFromSW)
    {
      SquarePosition pos{ File::F_A, Rank::R_1 };
      auto allOnNWtoSE = pos.getAllOnSWtoNE();

      std::set<SquarePosition> allOnExpected = {
        {File::F_A, Rank::R_1},
      };

      bool allIn = true;
      for (const auto& exp : allOnExpected)
      {
        if (allOnNWtoSE.find(exp) == allOnNWtoSE.end())
        {
          allIn = false;
          break;
        }
      }

      Assert::IsTrue(allIn);
    }

    TEST_METHOD(GetAllOnNWtoSEFromAny)
    {
      SquarePosition pos{ File::F_D, Rank::R_4 };
      auto allOnNWtoSE = pos.getAllOnNWtoSE();

      std::set<SquarePosition> allOnExpected = {
        {File::F_C, Rank::R_5},
        {File::F_B, Rank::R_6},
        {File::F_A, Rank::R_7},
        {File::F_E, Rank::R_3},
        {File::F_F, Rank::R_2},
        {File::F_G, Rank::R_1},
      };

      bool allIn = true;
      for (const auto& exp : allOnExpected)
      {
        if (allOnNWtoSE.find(exp) == allOnNWtoSE.end())
        {
          allIn = false;
          break;
        }
      }

      Assert::IsTrue(allIn);
    }

    TEST_METHOD(GetFromRelativePathInvalid)
    {
      SquarePosition pos{ File::F_B, Rank::R_2 };
      int fileSteps = -3;
      int rankSteps = 0;

      auto posInvalid = pos.fromRelativePath(fileSteps, rankSteps);

      Assert::IsTrue(!posInvalid.isValid());
    }
    TEST_METHOD(GetFromRelativePathValid)
    {
      SquarePosition pos{ File::F_B, Rank::R_2 };
      int fileSteps = 3;
      int rankSteps = 2;

      auto posValid = pos.fromRelativePath(fileSteps, rankSteps);
      SquarePosition expected{ File::F_E, Rank::R_4 };

      Assert::IsTrue(posValid == expected);
    }
  };

  TEST_CLASS(PiecesTests)
  {

    bool checkExpectedInsideMovements(
      const std::set<SquarePosition>& calculatedMovements,
      const std::set<SquarePosition>& expectedMovements)
    {
      bool allIn = true;

      for (const auto& exp : expectedMovements)
      {
        if (calculatedMovements.find(exp) == calculatedMovements.end())
        {
          allIn = false;
          break;
        }
      }

      return allIn;
    }
    TEST_METHOD(RookMovements)
    {
      RookPiece rook(Player::WHITE, { File::F_D, Rank::R_4 });

      auto rookMovement = rook.possibleMovements();

      std::set<SquarePosition> expectedOut = {
        { File::F_D, Rank::R_1 },
        { File::F_D, Rank::R_2 },
        { File::F_D, Rank::R_3 },
        { File::F_D, Rank::R_5 },
        { File::F_D, Rank::R_6 },
        { File::F_D, Rank::R_7 },
        { File::F_D, Rank::R_8 },
        { File::F_A, Rank::R_4 },
        { File::F_B, Rank::R_4 },
        { File::F_C, Rank::R_4 },
        { File::F_E, Rank::R_4 },
        { File::F_F, Rank::R_4 },
        { File::F_G, Rank::R_4 },
        { File::F_H, Rank::R_4 },
      };

      Assert::IsTrue(checkExpectedInsideMovements(rookMovement, expectedOut));
    }

    TEST_METHOD(BishopMovements)
    {
      BishopPiece bishop(Player::WHITE, { File::F_D, Rank::R_4 });

      auto bishopMovement = bishop.possibleMovements();

      std::set<SquarePosition> expectedOut = {
        { File::F_C, Rank::R_3 },
        { File::F_B, Rank::R_2 },
        { File::F_A, Rank::R_1 },
        { File::F_E, Rank::R_5 },
        { File::F_F, Rank::R_6 },
        { File::F_G, Rank::R_7 },
        { File::F_H, Rank::R_8 },
        { File::F_E, Rank::R_3 },
        { File::F_F, Rank::R_2 },
        { File::F_G, Rank::R_1 },
        { File::F_C, Rank::R_5 },
        { File::F_B, Rank::R_6 },
        { File::F_A, Rank::R_7 },
      };

      Assert::IsTrue(checkExpectedInsideMovements(bishopMovement, expectedOut));
    }

    TEST_METHOD(KnightMovements)
    {
      KnightPiece knight(Player::WHITE, { File::F_D, Rank::R_5 });

      auto knightMovement = knight.possibleMovements();

      std::set<SquarePosition> expectedOut = {
        { File::F_E, Rank::R_7 },
        { File::F_F, Rank::R_6 },
        { File::F_F, Rank::R_4 },
        { File::F_E, Rank::R_3 },
        { File::F_C, Rank::R_3 },
        { File::F_B, Rank::R_4 },
        { File::F_B, Rank::R_6 },
        { File::F_C, Rank::R_7 },
      };

      Assert::IsTrue(checkExpectedInsideMovements(knightMovement, expectedOut));
    }

    TEST_METHOD(QueenMovements)
    {
      QueenPiece queen(Player::WHITE, { File::F_D, Rank::R_4 });

      auto queenMovement = queen.possibleMovements();

      std::set<SquarePosition> expectedOut = {
        { File::F_C, Rank::R_3 },
        { File::F_B, Rank::R_2 },
        { File::F_A, Rank::R_1 },
        { File::F_E, Rank::R_5 },
        { File::F_F, Rank::R_6 },
        { File::F_G, Rank::R_7 },
        { File::F_H, Rank::R_8 },
        { File::F_E, Rank::R_3 },
        { File::F_F, Rank::R_2 },
        { File::F_G, Rank::R_1 },
        { File::F_C, Rank::R_5 },
        { File::F_B, Rank::R_6 },
        { File::F_A, Rank::R_7 },
        { File::F_D, Rank::R_1 },
        { File::F_D, Rank::R_2 },
        { File::F_D, Rank::R_3 },
        { File::F_D, Rank::R_5 },
        { File::F_D, Rank::R_6 },
        { File::F_D, Rank::R_7 },
        { File::F_D, Rank::R_8 },
        { File::F_A, Rank::R_4 },
        { File::F_B, Rank::R_4 },
        { File::F_C, Rank::R_4 },
        { File::F_E, Rank::R_4 },
        { File::F_F, Rank::R_4 },
        { File::F_G, Rank::R_4 },
        { File::F_H, Rank::R_4 },
      };

      Assert::IsTrue(checkExpectedInsideMovements(queenMovement, expectedOut));
    }
    
    TEST_METHOD(KingMovementsFromInside)
    {
      KingPiece king(Player::WHITE, { File::F_F, Rank::R_5 });

      auto kingMovement = king.possibleMovements();

      std::set<SquarePosition> expectedOut = {
        { File::F_E, Rank::R_6 },
        { File::F_F, Rank::R_6 },
        { File::F_G, Rank::R_6 },
        { File::F_G, Rank::R_5 },
        { File::F_G, Rank::R_4 },
        { File::F_F, Rank::R_4 },
        { File::F_E, Rank::R_4 },
        { File::F_E, Rank::R_5 },
      };

      Assert::IsTrue(checkExpectedInsideMovements(kingMovement, expectedOut));
    }
    
    TEST_METHOD(KingMovementsFromCorner)
    {
      KingPiece king(Player::WHITE, { File::F_H, Rank::R_8 });

      auto kingMovement = king.possibleMovements();

      std::set<SquarePosition> expectedOut = {
        { File::F_G, Rank::R_8 },
        { File::F_G, Rank::R_7 },
        { File::F_H, Rank::R_7 },
      };

      Assert::IsTrue(checkExpectedInsideMovements(kingMovement, expectedOut));
    }

    TEST_METHOD(PawnMovements)
    {
      PawnPiece pawn(Player::WHITE, { File::F_C, Rank::R_4 });

      auto pawnMovement = pawn.possibleMovements();

      std::set<SquarePosition> expectedOut = {
        { File::F_C, Rank::R_5 },
      };

      Assert::IsTrue(checkExpectedInsideMovements(pawnMovement, expectedOut));
    }
  };
}
