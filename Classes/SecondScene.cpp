#include"SecondScene.h"
#include"Snake.h"
#include"food.h"
#include"gameover.h"
#include"barrier.h"
#define GameRange 10

bool keyPressedFirst = false;

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

Snake snake;
food Food;
barrier MyBarrier;
bool SecondScene::Death()
{
	for (int i = 2; i < snake.snakeBodyNum - 1; i++)
	{
		if (snake.x[0] == snake.x[i + 1] && snake.y[0] == snake.y[i + 1])
		{
			return false;
		}
	}
	for (int i = 0; i < MyBarrier.barrierNum; i++)
	{
		if (abs(snake.x[0] -MyBarrier.x[i])<=3 && abs(snake.y[0] -MyBarrier.y[i])<=3)
		{
			return false;
		}
	}
	return true;
}
void SecondScene::Eat()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	for (int i = 0; i < 20; i++)
	{
		if (snake.x[0] - Food.x[i] <= 5 && snake.y[0] - Food.y[i] <= 5 && snake.x[0] - Food.x[i] >= -5 && snake.y[0] - Food.y[i] >= -5)
		{
			score+=10;
			snake.body[snake.snakeBodyNum] = snake.create(2);
			Food.x[i] = rand() % (int)visibleSize.width + (int)origin.x;
			Food.y[i] = rand() % (int)visibleSize.height + (int)origin.y;
			Food.Food[i]->setPosition(Vec2((float)Food.x[i], (float)Food.y[i]));
			snake.snakeBodyNum++;
			snake.x[snake.snakeBodyNum] = snake.x[snake.snakeBodyNum - 1];
			snake.y[snake.snakeBodyNum] = snake.y[snake.snakeBodyNum - 1] - (snake.y[snake.snakeBodyNum - 2] - snake.y[snake.snakeBodyNum - 1]);
			snake.body[snake.snakeBodyNum - 1]->setPosition(Vec2((float)snake.x[snake.snakeBodyNum], (float)snake.y[snake.snakeBodyNum]));
			this->addChild(snake.body[snake.snakeBodyNum - 1]);
			break;
		}
	}
}
void SecondScene::Border()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	for (int i = 0; i < snake.snakeBodyNum + 1; i++)
	{
		if (snake.x[i] - ((int)visibleSize.width + origin.x) > 3)
		{
			snake.x[i] = (int)origin.x;
			if (i == 0)
				snake.head->runAction(MoveTo::create(0.0f, Vec2((float)snake.x[i], (float)snake.y[i])));
			else
				snake.body[i - 1]->runAction(MoveTo::create(0.0f, Vec2((float)snake.x[i], (float)snake.y[i])));
		}
		if (snake.x[i] - origin.x < -2)
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
bool SecondScene::repeat(int x, int y)
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
void SecondScene::logic(float t)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	int ySecond[50] = {};
	int xSecond[50] = {};
	for (int i = 0; i < snake.snakeBodyNum; i++)
	{
		ySecond[i] = snake.y[i];//原来的坐标
		xSecond[i] = snake.x[i];
	}
	//move head
	switch (snake.direction)
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
	for (int i = 0; i < snake.snakeBodyNum; i++)
	{
		snake.y[i + 1] = ySecond[i];
		snake.x[i + 1] = xSecond[i];
	}
	for (int i = 0; i < snake.snakeBodyNum + 1; i++)
	{
		auto moveTo = MoveTo::create(0.1f, Vec2((float)snake.x[i], (float)snake.y[i]));
		auto sequence = Sequence::create(moveTo, nullptr);
		if (i == 0)
			snake.head->runAction((sequence));
		else
			snake.body[i - 1]->runAction((sequence));
	}
	SecondScene::Eat();
	SecondScene::Border();
	bool clo[5] = { false };
	if (clock() / 1000 < 5 && clo[0] == false && keyPressedFirst == true)           //随时间增加，蛇的速度变快
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(SecondScene::logic));
		schedule(CC_SCHEDULE_SELECTOR(SecondScene::logic), 0.15f);
		clo[0] = true;
	}
	else if (clock() / 1000 >= 5 && clock() / 1000 < 10 && clo[1] == false)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(SecondScene::logic));
		schedule(CC_SCHEDULE_SELECTOR(SecondScene::logic), 0.12f);
		clo[1] = true;
	}
	else if (clock() / 1000 >= 10 && clock() / 1000 < 20 && clo[2] == false)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(SecondScene::logic));
		schedule(CC_SCHEDULE_SELECTOR(SecondScene::logic), 0.08f);
		clo[2] = true;
	}
	else if (clock() / 1000 >= 20 && clock() / 1000 < 30 && clo[3] == false)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(SecondScene::logic));
		schedule(CC_SCHEDULE_SELECTOR(SecondScene::logic), 0.05f);
		clo[3] = true;
	}

	if (SecondScene::Death() == false)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(SecondScene::logic));
		Director::getInstance()->replaceScene(TransitionFadeUp::create(0.0f, gameover::createScene()));
		FILE* fp = fopen("D:\\Test.txt", "a");
		fprintf(fp,"%d\n",score );
		fclose(fp);
	}
	
}
bool SecondScene::init()
{

	srand((int)time(0));

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

	auto listener = EventListenerKeyboard::create();

	


	snake.head->scheduleUpdate();

	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (!keyPressedFirst && (keyCode == EventKeyboard::KeyCode::KEY_W
			|| keyCode == EventKeyboard::KeyCode::KEY_S
			|| keyCode == EventKeyboard::KeyCode::KEY_A
			|| keyCode == EventKeyboard::KeyCode::KEY_D))
		{
			schedule(CC_SCHEDULE_SELECTOR(SecondScene::logic), 0.1f);
			keyPressedFirst = true;
		}
		switch (keyCode)
		{
			case EventKeyboard::KeyCode::KEY_W:
			{
				if (snake.direction != DOWN)
				{
					auto rotateTo = RotateTo::create(0.1f, 0);
					auto sequence = Sequence::create(rotateTo, nullptr);
					snake.direction = UP;
					snake.head->runAction((sequence));
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
