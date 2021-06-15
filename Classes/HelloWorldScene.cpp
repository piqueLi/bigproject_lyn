#include "HelloWorldScene.h"
#include "SecondScene.h"
#include"Level1.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem1 = MenuItemImage::create(
		"startgame1.png",
		"startgame1.png",
		CC_CALLBACK_1(HelloWorld::menuScenefirst, this));
	closeItem1->setScaleX(visibleSize.width / 200);
	closeItem1->setScaleY(visibleSize.height / 230);//调整精灵大小
	float x1 = origin.x + visibleSize.width / 3;
	float y1 = origin.y + visibleSize.height * 2 / 5;
	closeItem1->setPosition(Vec2(x1, y1));
	auto closeItem2 = MenuItemImage::create(
		"startgame2.png",
		"startgame2.png",
		CC_CALLBACK_1(HelloWorld::menuSceneSecond, this));
	closeItem2->setScaleX(visibleSize.width / 200);
	closeItem2->setScaleY(visibleSize.height / 230);//调整精灵大小
	float x2 = origin.x + visibleSize.width * 2 / 3;
	float y2 = origin.y + visibleSize.height * 2 / 5;
	closeItem2->setPosition(Vec2(x2, y2));
	auto closeItem3 = MenuItemImage::create(
		"startgame3.png",
		"startgame3.png",
		CC_CALLBACK_1(HelloWorld::menuSceneSecond, this));
	closeItem3->setScaleX(visibleSize.width / 170);
	closeItem3->setScaleY(visibleSize.height / 250);//调整精灵大小
	float x3 = origin.x + visibleSize.width /2;
	float y3 = origin.y + visibleSize.height * 2 / 7;
	closeItem3->setPosition(Vec2(x3, y3));
	auto menu = Menu::create(closeItem1, closeItem2, closeItem3, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	auto background = DrawNode::create();
	background->drawSolidRect(origin, visibleSize * 3 / 2, cocos2d::Color4F(1.0, 1.0, 1.0, 1.0));
	this->addChild(background);
	auto sprite = Sprite::create("TITLE.png");
	sprite->setScaleX(visibleSize.width / 2 / sprite->getTextureRect().getMaxX());
	sprite->setScaleY(visibleSize.height / 4 / sprite->getTextureRect().getMaxY());//调整精灵大小
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 2 / 3 + origin.y));//放置于屏幕中央

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	return true;
}


void HelloWorld::menuScenefirst(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->replaceScene(TransitionFadeUp::create(2.0f, SecondScene::createScene()));
}
void HelloWorld::menuSceneSecond(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->replaceScene(TransitionFadeUp::create(2.0f, Level1::createScene()));
}
void HelloWorld::menuSceneThird(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->replaceScene(TransitionFadeUp::create(2.0f, list::createScene()));
}

