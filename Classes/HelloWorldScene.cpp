#include "HelloWorldScene.h"
#include "SecondScene.h"
#include"Level1.h"

USING_NS_CC;

Scene* HelloWorld::createScene()              //创建HelloWorld场景
{
	return HelloWorld::create();
}

bool HelloWorld::init()
{
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();            //得到屏幕的size
	Vec2 origin = Director::getInstance()->getVisibleOrigin();               //得到初始点坐标（即显示框左下角）

	
	auto startgame1 = MenuItemImage::create(
		"startgame1.png",
		"startgame1.png",
		CC_CALLBACK_1(HelloWorld::menuScenefirst, this));                //无尽模式字样的按钮创建
	startgame1->setScaleX(visibleSize.width / 200);
	startgame1->setScaleY(visibleSize.height / 230);                     //调整按钮大小
	float x1 = origin.x + visibleSize.width / 3;
	float y1 = origin.y + visibleSize.height * 2 / 5;
	startgame1->setPosition(Vec2(x1, y1));                               //设置按钮位置
	auto startgame2 = MenuItemImage::create(
		"startgame2.png",
		"startgame2.png",
		CC_CALLBACK_1(HelloWorld::menuSceneSecond, this));               //关卡模式字样的按钮创建
	startgame2->setScaleX(visibleSize.width / 200);
	startgame2->setScaleY(visibleSize.height / 230);                     //调整按钮大小
	float x2 = origin.x + visibleSize.width * 2 / 3;
	float y2 = origin.y + visibleSize.height * 2 / 5;
	startgame2->setPosition(Vec2(x2, y2));                                //设置按钮位置
	auto startgame3 = MenuItemImage::create(
		"startgame3.png",
		"startgame3.png",
		CC_CALLBACK_1(HelloWorld::menuSceneThird, this));                  //结束游戏字样的按钮创建
	startgame3->setScaleX(visibleSize.width / 230);
	startgame3->setScaleY(visibleSize.height / 270);                       //调整按钮大小
	float x3 = origin.x + visibleSize.width /2;
	float y3 = origin.y + visibleSize.height * 2 / 7; 
	startgame3->setPosition(Vec2(x3, y3));                                //设置按钮位置
	auto menu = Menu::create(startgame1, startgame2, startgame3, NULL);   //菜单类创建
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	auto background = DrawNode::create();
	background->drawSolidRect(origin, visibleSize * 3 / 2, cocos2d::Color4F(1.0, 1.0, 1.0, 1.0));         //背景颜色设置
	this->addChild(background);
	auto sprite = Sprite::create("TITLE.png");
	sprite->setScaleX(visibleSize.width / 2 / sprite->getTextureRect().getMaxX());
	sprite->setScaleY(visibleSize.height / 4 / sprite->getTextureRect().getMaxY());//调整精灵大小
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 2 / 3 + origin.y));//放置于屏幕中央

	// add the sprite as a child to this layer
	this->addChild(sprite);
	return true;
}


void HelloWorld::menuScenefirst(Ref* pSender)                              //三个按钮按下后进入的场景
{
	Director::getInstance()->replaceScene(TransitionFadeUp::create(2.0f, SecondScene::createScene()));
}
void HelloWorld::menuSceneSecond(Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionFadeUp::create(2.0f, Level1::createScene()));
}
void HelloWorld::menuSceneThird(cocos2d::Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();
}

