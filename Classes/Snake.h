#ifndef __Snake_H__
#define __Snake_H__
#include "cocos2d.h"
using namespace cocos2d;
enum DIR
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};
class Snake : public Node
{

public:
    static Snake* create(int type);
    bool init(int type);
    int x[50]; //������
    int y[50]; //������
    int snakeBodyNum=1;//�������Ŀ
    int direction;//����
    int score=0;
   Snake* head;
   Snake* body[100];
};
#endif
