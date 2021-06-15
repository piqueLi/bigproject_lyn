#include"win.h"
USING_NS_CC;

Scene* win::createScene()
{
	return win::create();
}


bool win::init()
{

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(win::menuCloseCallback, this));


	float x = origin.x + visibleSize.width * 3 / 5 - closeItem->getContentSize().width / 2;
	float y = origin.y + visibleSize.height * 2 / 5;
	closeItem->setPosition(Vec2(x, y));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	auto sprite = Sprite::create("win.png");
	sprite->setScaleX(visibleSize.width /1.5/ sprite->getTextureRect().getMaxX());
	sprite->setScaleY(visibleSize.height / 3 / sprite->getTextureRect().getMaxY());//调整精灵大小
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 2 / 3 + origin.y));//放置于屏幕中央

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	return true;
}


void win::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}
