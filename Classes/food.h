#ifndef __food_H__
#define __food_H__
#include "cocos2d.h"
using namespace cocos2d;

class food : public Node
{

public:
    static food* create();
    bool init();
    int y[20]; //������
    int x[20]; //������
    int Foodnum = 0;
    food* Food[20];
};
#endif