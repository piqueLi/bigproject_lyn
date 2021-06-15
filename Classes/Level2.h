#ifndef __Level2_H__
#define __Level2_H__
#include "cocos2d.h"
using namespace cocos2d;
class Level2 :public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Level2);
	void Level2::logic(float t);
	void popScene(Ref* pSender);
	bool Level2::Death();
	void Level2::Eat();
	void Level2::Border();
	bool Level2::repeat(int x, int y);
};

#endif