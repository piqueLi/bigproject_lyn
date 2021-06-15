#ifndef __Level1_H__
#define __Level1_H__
#include "cocos2d.h"
using namespace cocos2d;
class Level1 :public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Level1);
	void Level1::logic(float t);
	void popScene(Ref* pSender);
	bool Level1::Death();
	void Level1::Eat();
	void Level1::Border();
	bool Level1::repeat(int x, int y);
};

#endif