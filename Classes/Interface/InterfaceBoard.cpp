#include "Interface/InterfaceBoard.h"

InterfaceBoard::InterfaceBoard(cocos2d::Node* parentNode)
{
    boardNode = cocos2d::DrawNode::create();
    int offsetX = (winSize.width - 8 * cellSize) / 2;
    int offsetY = (winSize.height - 8 * cellSize) / 2;
    boardNode->setPosition(offsetX, offsetY);
    parentNode->addChild(boardNode);
}

void InterfaceBoard::drawBoard()
{
    for (int file = 0; file < 8; file++)
    {
        for (int rank = 0; rank < 8; rank++)
        {
            bool isLightSquare = (file + rank) % 2;
            cocos2d::Color4F color = isLightSquare ? cocos2d::Color4F::WHITE : cocos2d::Color4F::BLACK;

            boardNode->drawRect(cocos2d::Vec2(file * cellSize, rank * cellSize), cocos2d::Vec2(file * cellSize + cellSize, rank * cellSize + cellSize), color);
        }
    }
}