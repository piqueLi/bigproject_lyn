#include"Level1.h"
#include"Snake.h"
#include"food.h"
#include"gameover.h"
#include"barrier.h"
#include"Level2.h"
#define GameRange 10
bool keyPressedFirst1 = false;

Scene* Level1::createScene()
{
	auto scene = Scene::create();
	auto layer = Level1::create();
	scene->addChild(layer);
	return scene;
}
void Level1::popScene(Ref* pSpender)
{
	Director::getInstance()->popScene();
}

Snake snake1;
food Food1;
barrier MyBarrier1;
bool Level1::Death()
{
	for (int i = 2; i < snake1.snakeBodyNum - 1; i++)
	{
		if (snake1.x[0] == snake1.x[i + 1] && snake1.y[0] == snake1.y[i + 1])
		{
			return false;
		}
	}
	for (int i = 0; i < MyBarrier1.barrierNum; i++)
	{
		if (abs(snake1.x[0] - MyBarrier1.x[i]) <= 3 && abs(snake1.y[0] - MyBarrier1.y[i]) <= 3)
		{
			return false;
		}
	}
	return true;
}
void Level1::Eat()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	for (int i = 0; i < 20; i++)
	{
		if (snake1.x[0] - Food1.x[i] <= 5&& snake1.y[0] - Food1.y[i] <= 5 && snake1.x[0] - Food1.x[i] >= -5 && snake1.y[0] - Food1.y[i] >= -5)
		{
			Food1.Foodnum-=1;
			Food1.x[i] = origin.x - 100;
			Food1.y[i] = origin.y - 100;
			this->removeChild( Food1.Food[i]);
			snake1.body[snake1.snakeBodyNum] = snake1.create(2);
			snake1.snakeBodyNum++;
			snake1.x[snake1.snakeBodyNum] = snake1.x[snake1.snakeBodyNum - 1];
			snake1.y[snake1.snakeBodyNum] = snake1.y[snake1.snakeBodyNum - 1] - (snake1.y[snake1.snakeBodyNum - 2] - snake1.y[snake1.snakeBodyNum - 1]);
			snake1.body[snake1.snakeBodyNum - 1]->setPosition(Vec2((float)snake1.x[snake1.snakeBodyNum], (float)snake1.y[snake1.snakeBodyNum]));
			this->addChild(snake1.body[snake1.snakeBodyNum - 1]);
			break;
		}
	}
	
}
void Level1::Border()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	for (int i = 0; i < snake1.snakeBodyNum + 1; i++)
	{
		if (snake1.x[i] - ((int)visibleSize.width + origin.x) > 3)
		{
			snake1.x[i] = (int)origin.x;
			if (i == 0)
				snake1.head->runAction(MoveTo::create(0.0f, Vec2((float)snake1.x[i], (float)snake1.y[i])));
			else
				snake1.body[i - 1]->runAction(MoveTo::create(0.0f, Vec2((float)snake1.x[i], (float)snake1.y[i])));
		}
		if (snake1.x[i] - origin.x < -2)
		{
			snake1.x[i] = (int)visibleSize.width + (int)origin.x;
			if (i == 0)
				snake1.head->runAction(MoveTo::create(0.0f, Vec2((float)snake1.x[i], (float)snake1.y[i])));
			else
				snake1.body[i - 1]->runAction(MoveTo::create(0.0f, Vec2((float)snake1.x[i], (float)snake1.y[i])));
		}
		if (snake1.y[i] - ((int)visibleSize.height + origin.y) > 0)
		{
			snake1.y[i] = (int)origin.y;
			if (i == 0)
				snake1.head->runAction(MoveTo::create(0.0f, Vec2((float)snake1.x[i], (float)snake1.y[i])));
			else
				snake1.body[i - 1]->runAction(MoveTo::create(0.0f, Vec2((float)snake1.x[i], (float)snake1.y[i])));
		}
		if (snake1.y[i] - origin.y < 0)
		{
			snake1.y[i] = (int)visibleSize.height + (int)origin.y;
			if (i == 0)
			{
				snake1.head->runAction(MoveTo::create(0.0f, Vec2((float)snake1.x[i], (float)snake1.y[i])));
			}
			else
				snake1.body[i - 1]->runAction(MoveTo::create(0.0f, Vec2((float)snake1.x[i], (float)snake1.y[i])));
		}
	}
}
bool Level1::repeat(int x, int y)
{
	if (Food1.Foodnum > 0)
	{
		for (int i = 0; i < Food1.Foodnum; i++)
		{
			if (Food1.x[i] == x && Food1.y[i] == y)
				return true;
		}
	}
	for (int i = 0; i < snake1.snakeBodyNum + 1; i++)
	{
		if (snake1.x[i] == x && snake1.y[i] == y)
			return true;
	}
	if (MyBarrier1.barrierNum > 0)
	{
		for (int i = 0; i < MyBarrier1.barrierNum; i++)
		{
			if (MyBarrier1.x[i] == x && MyBarrier1.y[i] == y)
				return true;
		}
	}
	return false;
}
void Level1::logic(float t)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	int ySecond[50] = {};
	int xSecond[50] = {};
	for (int i = 0; i < snake1.snakeBodyNum; i++)
	{
		ySecond[i] = snake1.y[i];//原来的坐标
		xSecond[i] = snake1.x[i];
	}
	//move head
	switch (snake1.direction)
	{
		case UP:
			snake1.y[0] += 3;
			break;
		case DOWN:
			snake1.y[0] -= 3;
			break;
		case LEFT:
			snake1.x[0] -= 3;
			break;
		case RIGHT:
			snake1.x[0] += 3;
			break;
	}
	for (int i = 0; i < snake1.snakeBodyNum; i++)
	{
		snake1.y[i + 1] = ySecond[i];
		snake1.x[i + 1] = xSecond[i];
	}
	for (int i = 0; i < snake1.snakeBodyNum + 1; i++)
	{
		auto moveTo = MoveTo::create(0.1f, Vec2((float)snake1.x[i], (float)snake1.y[i]));
		auto sequence = Sequence::create(moveTo, nullptr);
		if (i == 0)
			snake1.head->runAction((sequence));
		else
			snake1.body[i - 1]->runAction((sequence));
	}
	Level1::Eat();
	Level1::Border();
	if (Level1::Death() == false)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(Level1::logic));
		Director::getInstance()->replaceScene(TransitionFadeUp::create(0.0f, gameover::createScene()));

	}
	if (Food1.Foodnum == 0)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(Level1::logic));
		Director::getInstance()->replaceScene(TransitionFadeUp::create(0.0f, Level2::createScene()));
	}
}
bool Level1::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Label* label = Label::createWithSystemFont("Level1", "Arial", 20);
	label->setPosition(Vec2(origin.x + visibleSize.height/10, origin.y + visibleSize.height/21));
	this->addChild(label);
	//初始蛇身及蛇头的创建以及初始位置的设定
	snake1.head = snake1.create(1);
	snake1.body[0] = snake1.create(2);
	snake1.x[0] = rand() % (int)visibleSize.width + (int)origin.x;
	snake1.y[0] = rand() % (int)visibleSize.height + (int)origin.y;
	snake1.x[1] = snake1.x[0];
	snake1.y[1] = snake1.y[0] - 3;
	snake1.head->setPosition(Vec2((float)snake1.x[0], (float)snake1.y[0]));
	snake1.body[0]->setPosition(Vec2((float)snake1.x[1], (float)snake1.y[1]));
	//初始化蛇头的方向
	snake1.head->direction = UP;
	//食物的初始化以及位置设定
	for (int i = 0; i < 20; i++)
	{
		Food1.Food[i] = Food1.create();
		Food1.x[i] = rand() % (int)visibleSize.width + origin.x;
		Food1.y[i] = rand() % (int)visibleSize.height + origin.y;
		while (repeat(Food1.x[i], Food1.y[i]))
		{
			Food1.x[i] = rand() % (int)visibleSize.width + origin.x;
			Food1.y[i] = rand() % (int)visibleSize.height + origin.y;
		}
		Food1.Food[i]->setPosition(Vec2((float)Food1.x[i], (float)Food1.y[i]));
		Food1.Foodnum++;
		this->addChild(Food1.Food[i]);
	}
	for (int i = 0; i < 10; i++)
	{

		MyBarrier1.Barrier[i] = MyBarrier1.create();
		MyBarrier1.x[i] = rand() % (int)visibleSize.width + origin.x;
		MyBarrier1.y[i] = rand() % (int)visibleSize.height + origin.y;
		while (repeat(MyBarrier1.x[i], MyBarrier1.y[i]))
		{
			MyBarrier1.x[i] = rand() % (int)visibleSize.width + origin.x;
			MyBarrier1.y[i] = rand() % (int)visibleSize.height + origin.y;
		}
		MyBarrier1.Barrier[i]->setPosition(Vec2((float)MyBarrier1.x[i], (float)MyBarrier1.y[i]));
		MyBarrier1.barrierNum++;
		MyBarrier1.Barrier[i]->setColor(Color3B::RED);
		this->addChild(MyBarrier1.Barrier[i]);
	}
	this->addChild(snake1.head);
	this->addChild(snake1.body[0]);

	auto listener = EventListenerKeyboard::create();

	snake1.head->scheduleUpdate();

	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (!keyPressedFirst1 && (keyCode == EventKeyboard::KeyCode::KEY_W
			|| keyCode == EventKeyboard::KeyCode::KEY_S
			|| keyCode == EventKeyboard::KeyCode::KEY_A
			|| keyCode == EventKeyboard::KeyCode::KEY_D))
		{
			schedule(CC_SCHEDULE_SELECTOR(Level1::logic), 0.05f);
			keyPressedFirst1 = true;
		}
		switch (keyCode)
		{
			case EventKeyboard::KeyCode::KEY_W:
			{
				if (snake1.direction != DOWN)
				{
					auto rotateTo = RotateTo::create(0.1f, 0);
					auto sequence = Sequence::create(rotateTo, nullptr);
					snake1.direction = UP;
					snake1.head->runAction((sequence));
				}
				break;
			}
			case EventKeyboard::KeyCode::KEY_S:
			{
				if (snake1.direction != UP)
				{
					auto rotateTo = RotateTo::create(0.1f, 180.0f);
					snake1.head->runAction(Sequence::create(rotateTo, nullptr));
					snake1.direction = DOWN;
				}
				break;
			}
			case EventKeyboard::KeyCode::KEY_A:
			{
				if (snake1.direction != RIGHT)
				{
					auto rotateTo = RotateTo::create(0.1f, -90.0f);
					snake1.head->runAction(Sequence::create(rotateTo, nullptr));
					snake1.direction = LEFT;
				}
				break;
			}
			case EventKeyboard::KeyCode::KEY_D:
			{
				if (snake1.direction != LEFT)
				{
					auto rotateTo = RotateTo::create(0.1f, 90.0f);
					snake1.head->runAction(Sequence::create(rotateTo, nullptr));
					snake1.direction = RIGHT;
				}
				break;
			}
			default:
				break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, snake1.head);
	return true;
}
