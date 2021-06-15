#ifndef __barrier_H__
#define __barrier_H__
#include "cocos2d.h"
using namespace cocos2d;
class barrier : public Node
{
public:
    static barrier* create();
    bool init();
    int x[50]; //横坐标
    int y[50]; //纵坐标
    int barrierNum = 0;//障碍的数目
    barrier* Barrier[50];
};
#endif