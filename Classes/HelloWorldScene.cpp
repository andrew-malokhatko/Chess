#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    mouseListener = cocos2d::EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    gameBoard.loadPosFromFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    //gameBoard.loadPosFromFen("8/8/8/8/4Kk/8/8/8");
    gameBoard.drawBoard();
    gameBoard.loadPieceSprites();

    return true;
}

void HelloWorld::onMouseDown(cocos2d::Event* event)
{
    cocos2d::EventMouse* mouseEvent = static_cast<cocos2d::EventMouse*>(event);
    gameBoard.onMouseDown(mouseEvent);
}