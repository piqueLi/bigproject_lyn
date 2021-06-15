#ifndef __SecondScene_H__
#define __SecondScene_H__
#include "cocos2d.h"
using namespace cocos2d;
class SecondScene :public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SecondScene);
	void SecondScene::logic(float t);
	void popScene(Ref* pSender);
	bool SecondScene::Death();
	void SecondScene::Eat();
	void SecondScene::Border();
	bool SecondScene::repeat(int x,int y);
	int score=0;
};

#endif