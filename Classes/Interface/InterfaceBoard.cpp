#include <map>
#include "Interface/InterfaceBoard.h"
#include "GameBody/Piece.h"

InterfaceBoard::InterfaceBoard(cocos2d::Node* parentNode)
{
    boardNode = cocos2d::DrawNode::create();
    highlightNode = cocos2d::DrawNode::create();
    int offsetX = (winSize.width - 8 * cellSize) / 2;
    int offsetY = (winSize.height - 8 * cellSize) / 2;
    boardNode->setPosition(offsetX, offsetY);
    parentNode->addChild(boardNode);
    boardNode->addChild(highlightNode);
}

void InterfaceBoard::drawBoard()
{
    for (int file = 0; file < 8; file++)
    {
        for (int rank = 0; rank < 8; rank++)
        {
            bool isLightSquare = (file + rank) % 2;
            cocos2d::Color4F color = isLightSquare ? cocos2d::Color4F::WHITE : cocos2d::Color4F(153.0f/255, 184.0f/255, 152.0f/255, 1);

            cocos2d::Vec2 rectangle[4];

            rectangle[0] = cocos2d::Vec2(file * cellSize, rank * cellSize);
            rectangle[1] = cocos2d::Vec2(file * cellSize + cellSize, rank * cellSize);
            rectangle[2] = cocos2d::Vec2(file * cellSize + cellSize, rank * cellSize + cellSize);
            rectangle[3] = cocos2d::Vec2(file * cellSize, rank * cellSize + cellSize);
            boardNode->drawPolygon(rectangle, 4, color, 0, color);
        }
    }
}

void InterfaceBoard::loadPieceSprites()
{
    pieceSprites.resize(64, nullptr);

    for (int rank = 0; rank < 8; rank++)
    {
        for (int file = 0; file < 8; file++)
        {
            Piece piece = board.getPiece(Cell(file, rank));
            if (piece != Piece::None)
            {
                cocos2d::Sprite* sprite = cocos2d::Sprite::create();
                sprite->setTexture(std::string{getPieceName(piece)} + ".png");
                setSpritePos(sprite, Cell{file, rank});
                sprite->setScale(0.5);
                boardNode->addChild(sprite);
                pieceSprites[Cell(file, rank)] = sprite;
            }
        }
    }
}

bool InterfaceBoard::loadPosFromFen(std::string fen)
{
    return board.loadposFromFen(fen);
}

void InterfaceBoard::highlightMovesForSelectedPiece()
{
    cocos2d::Color4F red = cocos2d::Color4F( 1.0f, .2f, .2f, .6f);
    for (const Move move : possibleMoves)
    {
        highlightNode->drawDot(cocos2d::Vec2((move.to % 8) * cellSize + cellSize / 2, (move.to / 8) * cellSize + cellSize / 2), 20.0f, red);
    }
}

void InterfaceBoard::highLightCells(uint64_t map)
{
    cocos2d::Color4F red = cocos2d::Color4F( 0.0f, 0.2f, 1.0f, .6f);
    std::vector<Cell> cells;
    for (int i = 0; i < 64; i++)
    {
        if (map & 1)
        {
            cells.push_back(Cell{i});
        }
        map  = map >> 1;
    }

    for (const Cell cell : cells)
    {
        highlightNode->drawDot(cocos2d::Vec2((cell % 8) * cellSize + cellSize / 2, (cell / 8) * cellSize + cellSize / 2), 20.0f, red);
    }
}

void InterfaceBoard::onMouseDown(cocos2d::EventMouse* event)
{
    if (!board.WhiteToMove())
    {
        Move move = board.AIMovePiece();
        movePiece(move);
    }

    highlightNode->clear();

    int onBoardX = (event->getCursorX() - boardNode->getPositionX()) / cellSize;
    int onBoardY = (event->getCursorY() - boardNode->getPositionY()) / cellSize;

    Cell cell = Cell{onBoardX, onBoardY};
    highLightCells(board.getThreatMap(!board.WhiteToMove()));
    
    if (selectedPiece.isValid() == false)
    {
        // Make it selected
        selectedPiece = cell;
        possibleMoves = board.getLegalMoves(board.getMoves(selectedPiece));
        highlightMovesForSelectedPiece();

        return;
    }

    bool wasMoved = false;
    for (Move move : possibleMoves)
    {
        if (Cell{move.to} == cell)
        {
            movePiece(move);
            wasMoved = true;
            break;
        }
    }

    if (wasMoved == true)
    {
        possibleMoves.clear();
        selectedPiece = Cell{99};
    }
    else
    {
        selectedPiece = cell;
        possibleMoves = board.getLegalMoves(board.getMoves(selectedPiece));

        highlightMovesForSelectedPiece();
    }
}

void InterfaceBoard::movePiece(Move move)
{
    if (pieceSprites[move.to] != nullptr)
    {
        pieceSprites[move.to]->removeFromParent();
    }

    board.movePiece(move);
    
    pieceSprites[move.to] = std::exchange(pieceSprites[move.from], nullptr);
    setSpritePos(pieceSprites[move.to], Cell{move.to});

    switch (move.specailMove)
    {
        case Move::SpecialMoves::None:
            break;

        case Move::SpecialMoves::PromoteToBishop:
        case Move::SpecialMoves::PromoteToKnight:
        case Move::SpecialMoves::PromoteToQueen:
        case Move::SpecialMoves::PromoteToRook:
            loadImage(Cell{move.to});
            break;
    }

    possibleMoves.clear();
}

void InterfaceBoard::setSpritePos(cocos2d::Sprite* sprite, Cell pos)
{
    sprite->setPosition(pos.x() * cellSize + 50, pos.y() * cellSize + 50);
}

void InterfaceBoard::loadImage(Cell from)
{
    if (pieceSprites[from] != nullptr)
    {
        pieceSprites[from]->setTexture(std::string{getPieceName(board.getPiece(from))} + ".png");
    }
}