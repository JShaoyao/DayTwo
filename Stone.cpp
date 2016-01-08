//
//  Stone.cpp
//  Run
//
//  Created by neworigin on 15-11-27.
//
//

#include "Stone.h"
#include "cocos2d.h"
Stone*Stone::create()
{
    Stone*stone=new Stone();
    int i=arc4random()%3;
    __String*stoneStr=__String::createWithFormat("stone%d.png",i+1);
    bool init=stone->initWithFile(stoneStr->getCString());
    //    stoneStr->release();
    if(stone&&init)
    {
        stone->autorelease();//石头放入自动释放池，不需要手动删除
        return stone;
    }
    CC_SAFE_DELETE(stone);
    return NULL;
}
void Stone::launch()
{
    JumpBy*launch=JumpBy::create(8, Point(2000,200-arc4random()%10*40),30,1);//jumpby是以当前位置为参考(从当前位置移2000)(时间,位置,高度,跳跃次数)
    CallFunc*launchFinish=CallFunc::create(CC_CALLBACK_0(Stone::removeStone, this));
    auto t=RotateBy::create(0.5, 300);//转动
    this->runAction(RepeatForever::create(t));
    Sequence*seq=Sequence::create(launch,launchFinish,NULL);//发射和移除
    this->runAction(seq);
}
void Stone::removeStone()
{
    this->setPosition(Vec2::ZERO);
    this->removeFromParent();
}