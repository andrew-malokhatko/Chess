#include "GameBody/Board.h"
#include "cocos2d.h"

class InterfaceBoard
{
private:
    const int cellSize = 100;
    Board board;

    const cocos2d::Size winSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::DrawNode* boardNode = nullptr;

public:
    InterfaceBoard(cocos2d::Node* parentNode);
    void drawBoard();
};