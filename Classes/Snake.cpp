#include"Snake.h"
Snake* Snake::create(int type)
{
    Snake* ret = new Snake();
    if (ret && ret->init(type))
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

bool Snake::init(int type)
{
    if (!Node::init()) {
        return false;
    }
    Sprite* s;
    //根据类型判断 产生 1.蛇头 2.身体 
    switch (type)
    {
        case 1:
            s = Sprite::create("snakehead.png");
            break;
        case 2:
        {
            snakeBodyNum++;
            s = Sprite::create("snakebody.png"); 
        }
        break;
        default:
            break;
    }
   
    this->addChild(s);

    return true;
}

