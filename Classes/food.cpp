#include"food.h"
food* food::create()
{
	food* ret = new food();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool food::init()
{
	if (!Node::init()) {
		return false;
	}
	Sprite* s;
	s = Sprite::create("food.png");
	this->addChild(s);

	return true;
}

