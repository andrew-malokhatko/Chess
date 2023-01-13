#include "GameBody/Board.h"
#include <vector>
#include "cocos2d.h"

class InterfaceBoard
{
private:
    const int cellSize = 100;
    Board board;
    Cell selectedPiece = Cell{99};
    std::vector<Move> possibleMoves; 
    std::set<Cell> Threats;

    const cocos2d::Size winSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::DrawNode* boardNode = nullptr;
    cocos2d::DrawNode* highlightNode = nullptr;
    std::vector<cocos2d::Sprite*> pieceSprites;

public:
    InterfaceBoard(cocos2d::Node* parentNode);
    void drawBoard();
    void loadPieceSprites();
    bool loadPosFromFen(std::string fen);
    void highlightMovesForSelectedPiece();
    void highLightCells(uint64_t map);

    void onMouseDown(cocos2d::EventMouse* event);
    void movePiece(Move move);
    void setSpritePos(cocos2d::Sprite* sprite, Cell pos);
    void loadImage(Cell from);
};