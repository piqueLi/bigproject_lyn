#ifndef __barrier_H__
#define __barrier_H__
#include "cocos2d.h"
using namespace cocos2d;
class barrier : public Node
{
public:
    static barrier* create();
    bool init();
    int x[50]; //������
    int y[50]; //������
    int barrierNum = 0;//�ϰ�����Ŀ
    barrier* Barrier[50];
};
#endif