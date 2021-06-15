#ifndef __Gameover_H__
#define __Gameover_H__

#include "cocos2d.h"

class gameover : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(gameover);
};

#endif 