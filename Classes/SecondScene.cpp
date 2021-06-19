#include"SecondScene.h"
#include"Snake.h"
#include"food.h"
#include"gameover.h"
#include"barrier.h"
#include<time.h>
#include<iostream>
#include<fstream>
#define GameRange 10
using namespace std;
bool keyPressedFirst = false;              //判断开始游戏后有没有按下键盘，从而判断小蛇是否开始移动
struct tm* tt;                             //计时用
Scene* SecondScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SecondScene::create();
	scene->addChild(layer);
	return scene;
}
void SecondScene::popScene(Ref* pSpender)
{
	Director::getInstance()->popScene();
}

Snake snake;          //蛇类
food Food;            //食物
barrier MyBarrier;    //障碍物
bool SecondScene::Death()        //判断蛇是否死亡
{
	for (int i = 2; i < snake.snakeBodyNum - 1; i++)
	{
		if (snake.x[0] == snake.x[i + 1] && snake.y[0] == snake.y[i + 1])    //蛇头与身体相撞
		{
			return false;
		}
	}
	for (int i = 0; i < MyBarrier.barrierNum; i++)                         //蛇头撞到障碍
	{
		if (abs(snake.x[0] - MyBarrier.x[i]) <= 3 && abs(snake.y[0] - MyBarrier.y[i]) <= 3)
		{
			return false;
		}
	}
	return true;       //死亡返回false，未死亡返回true
}
void SecondScene::Eat()      //蛇吃食物
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	for (int i = 0; i < 20; i++)
	{
		if (snake.x[0] - Food.x[i] <= 5 && snake.y[0] - Food.y[i] <= 5 && snake.x[0] - Food.x[i] >= -5 && snake.y[0] - Food.y[i] >= -5)
		{
			score += 10;
			snake.body[snake.snakeBodyNum] = snake.create(2);              //吃食后身体变长
			Food.x[i] = rand() % (int)visibleSize.width + (int)origin.x;           //原来的食物消失，新的随即地点产生食物
			Food.y[i] = rand() % (int)visibleSize.height + (int)origin.y;
			Food.Food[i]->setPosition(Vec2((float)Food.x[i], (float)Food.y[i]));
			snake.snakeBodyNum++;
			snake.x[snake.snakeBodyNum] = snake.x[snake.snakeBodyNum - 1];
			snake.y[snake.snakeBodyNum] = snake.y[snake.snakeBodyNum - 1] - (snake.y[snake.snakeBodyNum - 2] - snake.y[snake.snakeBodyNum - 1]);//增加的蛇身位置
			snake.body[snake.snakeBodyNum - 1]->setPosition(Vec2((float)snake.x[snake.snakeBodyNum], (float)snake.y[snake.snakeBodyNum]));
			this->addChild(snake.body[snake.snakeBodyNum - 1]);
			break;
		}
	}
}
void SecondScene::Border()            //穿过边界
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	for (int i = 0; i < snake.snakeBodyNum + 1; i++)
	{
		if (snake.x[i] - ((int)visibleSize.width + origin.x) > 3)     //右边界到左边界
		{
			snake.x[i] = (int)origin.x;
			if (i == 0)
				snake.head->runAction(MoveTo::create(0.0f, Vec2((float)snake.x[i], (float)snake.y[i])));
			else
				snake.body[i - 1]->runAction(MoveTo::create(0.0f, Vec2((float)snake.x[i], (float)snake.y[i])));
		}
		if (snake.x[i] - origin.x < -2)                   //左边界到右边界
		{
			snake.x[i] = (int)visibleSize.width + (int)origin.x;
			if (i == 0)
				snake.head->runAction(MoveTo::create(0.0f, Vec2((float)snake.x[i], (float)snake.y[i])));
			else
				snake.body[i - 1]->runAction(MoveTo::create(0.0f, Vec2((float)snake.x[i], (float)snake.y[i])));
		}
		if (snake.y[i] - ((int)visibleSize.height + origin.y) > 0)
		{
			snake.y[i] = (int)origin.y;
			if (i == 0)
				snake.head->runAction(MoveTo::create(0.0f, Vec2((float)snake.x[i], (float)snake.y[i])));
			else
				snake.body[i - 1]->runAction(MoveTo::create(0.0f, Vec2((float)snake.x[i], (float)snake.y[i])));
		}
		if (snake.y[i] - origin.y < 0)
		{
			snake.y[i] = (int)visibleSize.height + (int)origin.y;
			if (i == 0)
			{
				snake.head->runAction(MoveTo::create(0.0f, Vec2((float)snake.x[i], (float)snake.y[i])));
			}
			else
				snake.body[i - 1]->runAction(MoveTo::create(0.0f, Vec2((float)snake.x[i], (float)snake.y[i])));
		}
	}
}
bool SecondScene::repeat(int x, int y)        //用于在随机生成坐标时判断是否重复
{
	if (Food.Foodnum > 0)
	{
		for (int i = 0; i < Food.Foodnum; i++)
		{
			if (Food.x[i] == x && Food.y[i] == y)
				return true;
		}
	}
	for (int i = 0; i < snake.snakeBodyNum + 1; i++)
	{
		if (snake.x[i] == x && snake.y[i] == y)
			return true;
	}
	if (MyBarrier.barrierNum > 0)
	{
		for (int i = 0; i < MyBarrier.barrierNum; i++)
		{
			if (MyBarrier.x[i] == x && MyBarrier.y[i] == y)
				return true;
		}
	}
	return false;
}
void  SecondScene::tj_time_output(const time_t input_time)  //得到系统时间的函数
{
	tt = localtime(&input_time);	//localtime为系统函数
}
void SecondScene::file(int score) //生成排行榜
{
	ofstream ofs;
	ifstream ifs;
	ofs.open("D:\\List.txt", ios::app);
	int t = (int)time(0);
	int rank[200] = {0}, score_second[200] = { 0 }, year[200] = { 0 }, mon[200] = { 0 }, day[200] = { 0 }, hour[200] = { 0 }, min[200] = { 0 }, sec[200] = { 0 }, i = 0;
	char c;
	tj_time_output(t);//直接得到系统时间，进而判断入库时间
	ofs << "1  " << score << "    ";
	ofs << tt->tm_year + 1900 << "." << tt->tm_mon + 1 << "." << tt->tm_mday << "  " << tt->tm_hour << ":" << tt->tm_min << ":" << tt->tm_sec<<endl;
	ofs.close();
	ifs.open("D:\\List.txt", ios::in);
	if (!ifs)
	{
		ifs.close();
	}
	else
	{
		while (ifs >> rank[i])
		{
			ifs >> score_second[i];
			ifs >> year[i] >> c >> mon[i] >> c >> day[i];
			ifs >> hour[i] >> c >> min[i] >> c >> sec[i];
			i++;
		}
		ofs.close();
		for (int i1 = 0; i1 < i; i1++)
		{
			//每一轮比较前n-1-i个，即已排序好的最后i个不用比较
			for (int j = 0; j < i - 1 - i1; j++)
			{
				if (score_second[j] < score_second[j + 1])
				{
					int temp0 = score_second[j], temp1 = year[j], temp2 = mon[j], temp3 = day[j], temp4 = hour[j], temp5 = min[j], temp6 = sec[j];
					score_second[j] = score_second[j + 1];
					year[j] = year[j + 1];
					mon[j] = mon[j + 1];
					day[j] = day[j + 1];
					hour[j] = hour[j + 1];
					min[j] = min[j + 1];
					sec[j] = sec[j + 1];
					score_second[j + 1] = temp0;
					year[j + 1] = temp1;
					mon[j + 1] = temp2;
					day[j + 1] = temp3;
					hour[j + 1] = temp4;
					min[j + 1] = temp5;
					sec[j + 1] = temp6;
				}
			}
		}
	}

	remove("D:\\List.txt");
	ofstream ofs1;
	ofs.open("D:\\List.txt", ios::out);
	for (int i2 = 0; i2 < i; i2++)
	{
		ofs<< i2 + 1<<"   ";
		ofs << score_second[i2] << "  " << year[i2] << "." << mon[i2] << "." << day[i2]<<"  " << hour[i2] <<":"<< min[i2] <<":"<< sec[i2] << endl;
	}
	ofs1.close();
}
void SecondScene::logic(float t)      //一段时间调用一次
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	int ySecond[500] = {};
	int xSecond[500] = {};
	for (int i = 0; i < snake.snakeBodyNum; i++)
	{
		ySecond[i] = snake.y[i];//原来的坐标
		xSecond[i] = snake.x[i];
	}
	//move head
	switch (snake.direction)    //判断蛇头方向
	{
		case UP:
			snake.y[0] += 3;
			break;
		case DOWN:
			snake.y[0] -= 3;
			break;
		case LEFT:
			snake.x[0] -= 3;
			break;
		case RIGHT:
			snake.x[0] += 3;
			break;
	}
	for (int i = 0; i < snake.snakeBodyNum; i++)      //蛇身坐标改变
	{
		snake.y[i + 1] = ySecond[i];
		snake.x[i + 1] = xSecond[i];
	}
	for (int i = 0; i < snake.snakeBodyNum + 1; i++)
	{
		auto moveTo = MoveTo::create(0.1f, Vec2((float)snake.x[i], (float)snake.y[i]));   //蛇身移动
		auto sequence = Sequence::create(moveTo, nullptr);
		if (i == 0)
			snake.head->runAction((sequence));
		else
			snake.body[i - 1]->runAction((sequence));
	}
	SecondScene::Eat();                                 //判断是否吃食物
	SecondScene::Border();                              //判断是否穿过地图边界
	bool clo[5] = { false };                            //在加速时，每到一个时间段内只改变一次
	if (score < 10 && clo[0] == false && keyPressedFirst == true)           //随时间增加，蛇的速度变快
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(SecondScene::logic));
		schedule(CC_SCHEDULE_SELECTOR(SecondScene::logic), 0.15f);
		clo[0] = true;
	}
	else if (score >= 10 && score < 50 && clo[1] == false)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(SecondScene::logic));
		schedule(CC_SCHEDULE_SELECTOR(SecondScene::logic), 0.12f);
		clo[1] = true;
	}
	else if (score >= 50 && score < 150 && clo[2] == false)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(SecondScene::logic));
		schedule(CC_SCHEDULE_SELECTOR(SecondScene::logic), 0.08f);
		clo[2] = true;
	}
	else if (score >= 150 && clo[3] == false)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(SecondScene::logic));
		schedule(CC_SCHEDULE_SELECTOR(SecondScene::logic), 0.05f);
		clo[3] = true;
	}

	if (SecondScene::Death() == false)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(SecondScene::logic));
		Director::getInstance()->replaceScene(TransitionFadeUp::create(0.0f, gameover::createScene()));
		SecondScene::file(score);
	}

}
bool SecondScene::init()
{
	srand((int)time(0));            //随机种子
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//初始蛇身及蛇头的创建以及初始位置的设定
	snake.head = snake.create(1);
	snake.body[0] = snake.create(2);
	snake.x[0] = rand() % (int)visibleSize.width + (int)origin.x;
	snake.y[0] = rand() % (int)visibleSize.height + (int)origin.y;
	snake.x[1] = snake.x[0];
	snake.y[1] = snake.y[0] - 3;
	snake.head->setPosition(Vec2((float)snake.x[0], (float)snake.y[0]));
	snake.body[0]->setPosition(Vec2((float)snake.x[1], (float)snake.y[1]));
	//初始化蛇头的方向
	snake.head->direction = UP;
	//食物的初始化以及位置设定
	for (int i = 0; i < 20; i++)
	{
		Food.Food[i] = Food.create();
		Food.x[i] = rand() % (int)visibleSize.width + origin.x;
		Food.y[i] = rand() % (int)visibleSize.height + origin.y;
		while (repeat(Food.x[i], Food.y[i]))
		{
			Food.x[i] = rand() % (int)visibleSize.width + origin.x;
			Food.y[i] = rand() % (int)visibleSize.height + origin.y;
		}
		Food.Food[i]->setPosition(Vec2((float)Food.x[i], (float)Food.y[i]));
		Food.Foodnum++;
		this->addChild(Food.Food[i]);
	}
	//障碍物创建
	for (int i = 0; i < 10; i++)
	{

		MyBarrier.Barrier[i] = MyBarrier.create();
		MyBarrier.x[i] = rand() % (int)visibleSize.width + origin.x;
		MyBarrier.y[i] = rand() % (int)visibleSize.height + origin.y;
		while (repeat(MyBarrier.x[i], MyBarrier.y[i]))
		{
			MyBarrier.x[i] = rand() % (int)visibleSize.width + origin.x;
			MyBarrier.y[i] = rand() % (int)visibleSize.height + origin.y;
		}
		MyBarrier.Barrier[i]->setPosition(Vec2((float)MyBarrier.x[i], (float)MyBarrier.y[i]));
		MyBarrier.barrierNum++;
		MyBarrier.Barrier[i]->setColor(Color3B::RED);
		this->addChild(MyBarrier.Barrier[i]);
	}
	this->addChild(snake.head);
	this->addChild(snake.body[0]);
	//监听器初始化
	auto listener = EventListenerKeyboard::create();
	//snake.head->scheduleUpdate();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (!keyPressedFirst && (keyCode == EventKeyboard::KeyCode::KEY_W
			|| keyCode == EventKeyboard::KeyCode::KEY_S
			|| keyCode == EventKeyboard::KeyCode::KEY_A
			|| keyCode == EventKeyboard::KeyCode::KEY_D))
		{
			schedule(CC_SCHEDULE_SELECTOR(SecondScene::logic), 0.1f);       //第一次按下键盘，小蛇开始移动
			keyPressedFirst = true;
		}
		switch (keyCode)
		{
			case EventKeyboard::KeyCode::KEY_W:
			{
				if (snake.direction != DOWN)                //不可以向前进方向反方向走
				{
					auto rotateTo = RotateTo::create(0.1f, 0);         //蛇头旋转
					snake.head->runAction(Sequence::create(rotateTo, nullptr));
					snake.direction = UP;
				}
				break;
			}
			case EventKeyboard::KeyCode::KEY_S:
			{
				if (snake.direction != UP)
				{
					auto rotateTo = RotateTo::create(0.1f, 180.0f);
					snake.head->runAction(Sequence::create(rotateTo, nullptr));
					snake.direction = DOWN;
				}
				break;
			}
			case EventKeyboard::KeyCode::KEY_A:
			{
				if (snake.direction != RIGHT)
				{
					auto rotateTo = RotateTo::create(0.1f, -90.0f);
					snake.head->runAction(Sequence::create(rotateTo, nullptr));
					snake.direction = LEFT;
				}
				break;
			}
			case EventKeyboard::KeyCode::KEY_D:
			{
				if (snake.direction != LEFT)
				{
					auto rotateTo = RotateTo::create(0.1f, 90.0f);
					snake.head->runAction(Sequence::create(rotateTo, nullptr));
					snake.direction = RIGHT;
				}
				break;
			}
			default:
				break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, snake.head);
	return true;
}
