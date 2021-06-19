#include"Level2.h"
#include"HelloWorldScene.h"
#include"Snake.h"
#include"food.h"
#include"gameover.h"
#include"barrier.h"
#include"win.h"
#define GameRange 10
bool keyPressedFirst2 = false;

Scene* Level2::createScene()
{
	auto scene = Scene::create();
	auto layer = Level2::create();
	scene->addChild(layer);
	return scene;
}
void Level2::popScene(Ref* pSpender)
{
	Director::getInstance()->popScene();
}

Snake snake2;
food Food2;
barrier MyBarrier2;
bool Level2::Death()
{
	for (int i = 2; i < snake2.snakeBodyNum - 1; i++)
	{
		if (snake2.x[0] == snake2.x[i + 1] && snake2.y[0] == snake2.y[i + 1])
		{
			return false;
		}
	}
	for (int i = 0; i < MyBarrier2.barrierNum; i++)
	{
		if (abs(snake2.x[0] - MyBarrier2.x[i]) <= 3 && abs(snake2.y[0] - MyBarrier2.y[i]) <= 3)
		{
			return false;
		}
	}
	return true;
}
void Level2::Eat()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	for (int i = 0; i < 20; i++)
	{
		if (snake2.x[0] - Food2.x[i] <= 5 && snake2.y[0] - Food2.y[i] <= 5 && snake2.x[0] - Food2.x[i] >= -5 && snake2.y[0] - Food2.y[i] >= -5)
		{
			Food2.Foodnum -= 1;
			Food2.x[i] = origin.x - 100;
			Food2.y[i] = origin.y - 100;
			this->removeChild(Food2.Food[i]);
			snake2.body[snake2.snakeBodyNum] = snake2.create(2);
			snake2.snakeBodyNum++;
			snake2.x[snake2.snakeBodyNum] = snake2.x[snake2.snakeBodyNum - 1];
			snake2.y[snake2.snakeBodyNum] = snake2.y[snake2.snakeBodyNum - 1] - (snake2.y[snake2.snakeBodyNum - 2] - snake2.y[snake2.snakeBodyNum - 1]);
			snake2.body[snake2.snakeBodyNum - 1]->setPosition(Vec2((float)snake2.x[snake2.snakeBodyNum], (float)snake2.y[snake2.snakeBodyNum]));
			this->addChild(snake2.body[snake2.snakeBodyNum - 1]);
			break;
		}
	}

}
void Level2::Border()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	for (int i = 0; i < snake2.snakeBodyNum + 1; i++)
	{
		if (snake2.x[i] - ((int)visibleSize.width + origin.x) > 3)
		{
			snake2.x[i] = (int)origin.x;
			if (i == 0)
				snake2.head->runAction(MoveTo::create(0.0f, Vec2((float)snake2.x[i], (float)snake2.y[i])));
			else
				snake2.body[i - 1]->runAction(MoveTo::create(0.0f, Vec2((float)snake2.x[i], (float)snake2.y[i])));
		}
		if (snake2.x[i] - origin.x < -2)
		{
			snake2.x[i] = (int)visibleSize.width + (int)origin.x;
			if (i == 0)
				snake2.head->runAction(MoveTo::create(0.0f, Vec2((float)snake2.x[i], (float)snake2.y[i])));
			else
				snake2.body[i - 1]->runAction(MoveTo::create(0.0f, Vec2((float)snake2.x[i], (float)snake2.y[i])));
		}
		if (snake2.y[i] - ((int)visibleSize.height + origin.y) > 0)
		{
			snake2.y[i] = (int)origin.y;
			if (i == 0)
				snake2.head->runAction(MoveTo::create(0.0f, Vec2((float)snake2.x[i], (float)snake2.y[i])));
			else
				snake2.body[i - 1]->runAction(MoveTo::create(0.0f, Vec2((float)snake2.x[i], (float)snake2.y[i])));
		}
		if (snake2.y[i] - origin.y < 0)
		{
			snake2.y[i] = (int)visibleSize.height + (int)origin.y;
			if (i == 0)
			{
				snake2.head->runAction(MoveTo::create(0.0f, Vec2((float)snake2.x[i], (float)snake2.y[i])));
			}
			else
				snake2.body[i - 1]->runAction(MoveTo::create(0.0f, Vec2((float)snake2.x[i], (float)snake2.y[i])));
		}
	}
}
bool Level2::repeat(int x, int y)
{
	if (Food2.Foodnum > 0)
	{
		for (int i = 0; i < Food2.Foodnum; i++)
		{
			if (Food2.x[i] == x && Food2.y[i] == y)
				return true;
		}
	}
	for (int i = 0; i < snake2.snakeBodyNum + 1; i++)
	{
		if (snake2.x[i] == x && snake2.y[i] == y)
			return true;
	}
	if (MyBarrier2.barrierNum > 0)
	{
		for (int i = 0; i < MyBarrier2.barrierNum; i++)
		{
			if (MyBarrier2.x[i] == x && MyBarrier2.y[i] == y)
				return true;
		}
	}
	return false;
}
void Level2::logic(float t)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	int ySecond[50] = {};
	int xSecond[50] = {};
	for (int i = 0; i < snake2.snakeBodyNum; i++)
	{
		ySecond[i] = snake2.y[i];//原来的坐标
		xSecond[i] = snake2.x[i];
	}
	//move head
	switch (snake2.direction)
	{
		case UP:
			snake2.y[0] += 3;
			break;
		case DOWN:
			snake2.y[0] -= 3;
			break;
		case LEFT:
			snake2.x[0] -= 3;
			break;
		case RIGHT:
			snake2.x[0] += 3;
			break;
	}
	for (int i = 0; i < snake2.snakeBodyNum; i++)
	{
		snake2.y[i + 1] = ySecond[i];
		snake2.x[i + 1] = xSecond[i];
	}
	for (int i = 0; i < snake2.snakeBodyNum + 1; i++)
	{
		auto moveTo = MoveTo::create(0.1f, Vec2((float)snake2.x[i], (float)snake2.y[i]));
		auto sequence = Sequence::create(moveTo, nullptr);
		if (i == 0)
			snake2.head->runAction((sequence));
		else
			snake2.body[i - 1]->runAction((sequence));
	}
	Level2::Eat();
	Level2::Border();
	if (Level2::Death() == false)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(Level2::logic));
		Director::getInstance()->replaceScene(TransitionFadeUp::create(0.0f, gameover::createScene()));

	}
	if (Food2.Foodnum == 0)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(Level2::logic));
		Director::getInstance()->replaceScene(TransitionFadeUp::create(0.0f, win::createScene()));
	}
}
bool Level2::init()
{
	//srand((int)time(0));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Label* label = Label::createWithSystemFont("Level2", "Arial", 20);
	label->setPosition(Vec2(origin.x + visibleSize.height / 10, origin.y + visibleSize.height / 21));
	this->addChild(label);
	//初始蛇身及蛇头的创建以及初始位置的设定
	snake2.head = snake2.create(1);
	snake2.body[0] = snake2.create(2);
	snake2.x[0] = rand() % (int)visibleSize.width + (int)origin.x;
	snake2.y[0] = rand() % (int)visibleSize.height + (int)origin.y;
	snake2.x[1] = snake2.x[0];
	snake2.y[1] = snake2.y[0] - 3;
	snake2.head->setPosition(Vec2((float)snake2.x[0], (float)snake2.y[0]));
	snake2.body[0]->setPosition(Vec2((float)snake2.x[1], (float)snake2.y[1]));
	//初始化蛇头的方向
	snake2.head->direction = UP;
	//食物的初始化以及位置设定
	for (int i = 0; i < 20; i++)
	{
		Food2.Food[i] = Food2.create();
		Food2.x[i] = rand() % (int)visibleSize.width + origin.x;
		Food2.y[i] = rand() % (int)visibleSize.height + origin.y;
		while (repeat(Food2.x[i], Food2.y[i]))
		{
			Food2.x[i] = rand() % (int)visibleSize.width + origin.x;
			Food2.y[i] = rand() % (int)visibleSize.height + origin.y;
		}
		Food2.Food[i]->setPosition(Vec2((float)Food2.x[i], (float)Food2.y[i]));
		Food2.Foodnum++;
		this->addChild(Food2.Food[i]);
	}
	for (int i = 0; i <20; i++)
	{

		MyBarrier2.Barrier[i] = MyBarrier2.create();
		MyBarrier2.x[i] = rand() % (int)visibleSize.width + origin.x;
		MyBarrier2.y[i] = rand() % (int)visibleSize.height + origin.y;
		while (repeat(MyBarrier2.x[i], MyBarrier2.y[i]))
		{
			MyBarrier2.x[i] = rand() % (int)visibleSize.width + origin.x;
			MyBarrier2.y[i] = rand() % (int)visibleSize.height + origin.y;
		}
		MyBarrier2.Barrier[i]->setPosition(Vec2((float)MyBarrier2.x[i], (float)MyBarrier2.y[i]));
		MyBarrier2.barrierNum++;
		MyBarrier2.Barrier[i]->setColor(Color3B::RED);
		this->addChild(MyBarrier2.Barrier[i]);
	}
	this->addChild(snake2.head);
	this->addChild(snake2.body[0]);

	auto listener = EventListenerKeyboard::create();

	snake2.head->scheduleUpdate();

	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (!keyPressedFirst2 && (keyCode == EventKeyboard::KeyCode::KEY_W
			|| keyCode == EventKeyboard::KeyCode::KEY_S
			|| keyCode == EventKeyboard::KeyCode::KEY_A
			|| keyCode == EventKeyboard::KeyCode::KEY_D))
		{
			schedule(CC_SCHEDULE_SELECTOR(Level2::logic), 0.05f);
			keyPressedFirst2 = true;
		}
		switch (keyCode)
		{
			case EventKeyboard::KeyCode::KEY_W:
			{
				if (snake2.direction != DOWN)
				{
					auto rotateTo = RotateTo::create(0.1f, 0);
					auto sequence = Sequence::create(rotateTo, nullptr);
					snake2.direction = UP;
					snake2.head->runAction((sequence));
				}
				break;
			}
			case EventKeyboard::KeyCode::KEY_S:
			{
				if (snake2.direction != UP)
				{
					auto rotateTo = RotateTo::create(0.1f, 180.0f);
					snake2.head->runAction(Sequence::create(rotateTo, nullptr));
					snake2.direction = DOWN;
				}
				break;
			}
			case EventKeyboard::KeyCode::KEY_A:
			{
				if (snake2.direction != RIGHT)
				{
					auto rotateTo = RotateTo::create(0.1f, -90.0f);
					snake2.head->runAction(Sequence::create(rotateTo, nullptr));
					snake2.direction = LEFT;
				}
				break;
			}
			case EventKeyboard::KeyCode::KEY_D:
			{
				if (snake2.direction != LEFT)
				{
					auto rotateTo = RotateTo::create(0.1f, 90.0f);
					snake2.head->runAction(Sequence::create(rotateTo, nullptr));
					snake2.direction = RIGHT;
				}
				break;
			}
			default:
				break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, snake2.head);
	return true;
}
