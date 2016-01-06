#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();

    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //退出按钮
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 , origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    //文本框
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    //背景图片
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
    
    
    
    //动画
    /*
     创建帧动画的步骤：
     1、将多张散图合成一张大图
     2、使用精灵帧缓存将大图中的小图读取到缓存中
     3、将多张精灵帧创建为动画帧
     4、将多张动画帧做成动作
     5、将动画转成动作
     6、让精灵来执行这个动作
     */
    
//    rabbit = Sprite::create("blue1.png") ;
//    rabbit->setPosition(Vec2(150, 150)) ;
//    this->addChild(rabbit) ;
    
    //将大图中的小图读取到缓存中，制作成精灵帧缓存对象
    auto spriteFrame = SpriteFrameCache::getInstance() ;  //单例
    spriteFrame->addSpriteFramesWithFile("Blue.plist", "Blue.png") ;  //将.plist文件和.png大图加入到精灵帧缓存中
    
    //将多张精灵帧创建为动画帧
    Vector<SpriteFrame*>vector ;  //创建一个容器来存放精灵帧
    auto tempDic = __Dictionary::createWithContentsOfFile("Blue.plist") ;  //读取.plist文件中的内容，用一个字典来接收
    
    auto dic = (__Dictionary*)tempDic->objectForKey("frames") ;  //得到字典中的frames，也是用一个字典来接收
    int num = dic->allKeys()->count() ;  //得到frames中键值对的数量
    
    for (int i = 1; i <= num; ++i) {
        SpriteFrame* frame = NULL ;
        __String* str = __String::createWithFormat("%d.png" , i) ;
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString()) ;  //通过名字得到小图片
        
        vector.pushBack(frame) ;  //将小图片放入到容器中
    }
    
    auto animation = Animation::createWithSpriteFrames(vector , 0.1 , 1) ;  //创建精灵帧动画（第二个参数表示每一帧的时间间隔，第三个参数表示动画执行的次数）
    
    //将动画帧做成动作
    auto animate = Animate::create(animation) ;
    
    auto rep = RepeatForever::create(animate) ;  //永久执行这个动作
    
    //利用精灵帧缓存中某一帧的图片名称来初始化精灵
    rabbit = Sprite::createWithSpriteFrameName("1.png") ;
    rabbit->setPosition(Vec2(150, 150)) ;
    this->addChild(rabbit) ;
    
    //让精灵来执行这个动作（必须要在精灵被初始化之后才能执行动作）
    rabbit->runAction(rep) ;
    
    
    //运动
    auto moveBy = MoveBy::create(4, Vec2(150, 0)) ;  //运动到相对位置
    
    auto jumpBy1 = JumpBy::create(2, Vec2(75, 150), 150, 1) ;  //跳跃到相对位置
    
    auto jumpBy2 = JumpBy::create(2, Vec2(75, -150), 150, 1) ;
    
    auto spawn = Spawn::create(moveBy , jumpBy1 , jumpBy2 , NULL) ;  //同步动作
    
    auto repeat = Repeat::create(spawn, 2) ;  //重复动作
    
    rabbit->runAction(repeat) ;
    
    
    
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
