#include"barrier.h"
barrier* barrier::create()
{
	barrier* ret = new barrier();
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
bool barrier::init()
{
	if (!Node::init()) {
		return false;
	}
	Sprite* s;
	barrierNum++;
	s = Sprite::create("barrier.png");
	this->addChild(s);

	return true;
}
