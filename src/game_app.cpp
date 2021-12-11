#include "game_app.h"
#include <algorithm>

std::array<Piece, 32> GameApp::piecesData{};
bool GameApp::gameChanged = true;

void GameApp::checkSelectedPiece(SquarePosition pos)
{
  if (currentSelectedPiece != nullptr)
    currentSelectedPiece->unselect();

  currentSelectedPiece = nullptr;
  for (Piece& piece : piecesData)
  {
    if (!piece.equalPosition(pos))
      continue;
    currentSelectedPiece = &piece;
    break;
  }
}

bool GameApp::checkPieceOfCurrentPlayer() const
{
  if (currentSelectedPiece == nullptr) return false;

  if (currentPlayer == Player::BLACK)
  {
    return currentSelectedPiece->isBlack();
  }
  else
  {
    return currentSelectedPiece->isWhite();
  }
}

void GameApp::confirmPieceSelected()
{
  currentSelectedPiece->select();
  setChanged(true);
}

GameApp::GameApp()
{
  piecesData =
  {
    Piece{ PieceName::ROOK, Player::BLACK, { File::F_A, Rank::R_8 } },
    Piece{ PieceName::KNIGHT, Player::BLACK, { File::F_B, Rank::R_8 } },
    Piece{ PieceName::BISHOP, Player::BLACK, { File::F_C, Rank::R_8 } },
    Piece{ PieceName::QUEEN, Player::BLACK, { File::F_D, Rank::R_8 } },
    Piece{ PieceName::KING, Player::BLACK, { File::F_E, Rank::R_8 } },
    Piece{ PieceName::BISHOP, Player::BLACK, { File::F_F, Rank::R_8 } },
    Piece{ PieceName::KNIGHT, Player::BLACK, { File::F_G, Rank::R_8 } },
    Piece{ PieceName::ROOK, Player::BLACK, { File::F_H, Rank::R_8 } },
    Piece{ PieceName::PAWN, Player::BLACK, { File::F_A, Rank::R_7 } },
    Piece{ PieceName::PAWN, Player::BLACK, { File::F_B, Rank::R_7 } },
    Piece{ PieceName::PAWN, Player::BLACK, { File::F_C, Rank::R_7 } },
    Piece{ PieceName::PAWN, Player::BLACK, { File::F_D, Rank::R_7 } },
    Piece{ PieceName::PAWN, Player::BLACK, { File::F_E, Rank::R_7 } },
    Piece{ PieceName::PAWN, Player::BLACK, { File::F_F, Rank::R_7 } },
    Piece{ PieceName::PAWN, Player::BLACK, { File::F_G, Rank::R_7 } },
    Piece{ PieceName::PAWN, Player::BLACK, { File::F_H, Rank::R_7 } },
    Piece{ PieceName::ROOK, Player::WHITE, { File::F_A, Rank::R_1 } },
    Piece{ PieceName::KNIGHT, Player::WHITE, { File::F_B, Rank::R_1 } },
    Piece{ PieceName::BISHOP, Player::WHITE, { File::F_C, Rank::R_1 } },
    Piece{ PieceName::QUEEN, Player::WHITE, { File::F_D, Rank::R_1 } },
    Piece{ PieceName::KING, Player::WHITE, { File::F_E, Rank::R_1 } },
    Piece{ PieceName::BISHOP, Player::WHITE, { File::F_F, Rank::R_1 } },
    Piece{ PieceName::KNIGHT, Player::WHITE, { File::F_G, Rank::R_1 } },
    Piece{ PieceName::ROOK, Player::WHITE, { File::F_H, Rank::R_1 } },
    Piece{ PieceName::PAWN, Player::WHITE, { File::F_A, Rank::R_2 } },
    Piece{ PieceName::PAWN, Player::WHITE, { File::F_B, Rank::R_2 } },
    Piece{ PieceName::PAWN, Player::WHITE, { File::F_C, Rank::R_2 } },
    Piece{ PieceName::PAWN, Player::WHITE, { File::F_D, Rank::R_2 } },
    Piece{ PieceName::PAWN, Player::WHITE, { File::F_E, Rank::R_2 } },
    Piece{ PieceName::PAWN, Player::WHITE, { File::F_F, Rank::R_2 } },
    Piece{ PieceName::PAWN, Player::WHITE, { File::F_G, Rank::R_2 } },
    Piece{ PieceName::PAWN, Player::WHITE, { File::F_H, Rank::R_2 } },
  };
}

void GameApp::forEachPiece(const std::function<void(const Piece&, const std::set<SquarePosition>&)>& fun)
{
  for (const auto& p : piecesData)
  {
    std::set<SquarePosition> options{};
    if (p.isSelected())
      options = getOptions(p);
    fun(p, options);
  }
}

void GameApp::forEachSquare(const std::function<void(const SquarePosition& p)>& fun)
{
  for (int fileId = (int)File::F_A; fileId < 8; fileId++)
  {
    for (int rankId = (int)Rank::R_1; rankId < 8; rankId++)
    {
      fun({ fileId, rankId });
    }
  }
}

bool GameApp::getChanged()
{
  return gameChanged;
}

void GameApp::setChanged(bool changed)
{
  gameChanged = changed;
}

std::set<SquarePosition> GameApp::getOptions(const Piece& piece)
{
  if (!piece.isSelected())
    return {};

  std::set<SquarePosition> movementOptionsFromPiece = piece.possibleMovements();
  std::set<SquarePosition> freeMovementOptions{};
  for (const SquarePosition& movementOp : movementOptionsFromPiece)
  {
    auto result = std::find_if(piecesData.cbegin(), piecesData.cend(), [movementOp](const Piece piece) 
      { 
        return piece.equalPosition(movementOp); 
      });

    if (result == piecesData.end())
      freeMovementOptions.insert(movementOp);
  }

  return freeMovementOptions;
}

bool GameApp::processAction(SquarePosition pos)
{
  checkSelectedPiece(pos);
  if (currentSelectedPiece == nullptr)
    return false;

  bool toContinue = checkPieceOfCurrentPlayer();
  if (!toContinue)
    return false;

  if (currentCommandType == CommandType::SHOW_OPTIONS)
    confirmPieceSelected();

  return true;
}
