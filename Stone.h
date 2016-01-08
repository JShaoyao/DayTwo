//
//  Stone.h
//  Run
//
//  Created by neworigin on 15-11-27.
//
//

#ifndef __Run__Stone__
#define __Run__Stone__

#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
using namespace cocos2d;
class Stone:public Sprite
{
public:
    static Stone*create();//构造函数
    void launch();
    void removeStone();
};
#endif /* defined(__Run__Stone__) */
