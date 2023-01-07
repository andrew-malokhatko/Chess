#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "Interface/InterfaceBoard.h"
#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
private:
    InterfaceBoard gameBoard = InterfaceBoard(this); 
    cocos2d::EventListenerMouse* mouseListener = nullptr;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void onMouseDown(cocos2d::Event* event);
    CREATE_FUNC(HelloWorld);
};

#endif
