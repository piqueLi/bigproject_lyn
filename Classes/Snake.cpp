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
    //���������ж� ���� 1.��ͷ 2.���� 
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

