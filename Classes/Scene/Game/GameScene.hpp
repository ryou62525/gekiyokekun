//
//  GameScene.hpp
//  Gekiyokekun
//
//  Created by 小松亮太 on 2017/04/18.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "GameLayer.hpp"

namespace User
{
    class GameScene : public cocos2d::Layer
    {
    public:
 
        GameScene();
        virtual ~GameScene();
        bool init();
        CREATE_FUNC( GameScene );
    
        static cocos2d::Scene* createScene();
        
    private:
 
        CC_SYNTHESIZE( GameLayer*, gameLayer, GameLayer );
        CC_SYNTHESIZE_READONLY( cocos2d::Size, winSize, WinSize );

        cocos2d::Vec2 outZoneSize;
        
        void addStage();
        void touchOperation();
        void createOutZone();
        
        bool isFitWindowSize();
        bool onTouchBegan( cocos2d::Touch* _touch, cocos2d::Event* _event );
        void onTouchMoved( cocos2d::Touch* _touch, cocos2d::Event* _event );
        void onTouchEnded( cocos2d::Touch* _touch, cocos2d::Event* _event );
        
        void debugButton();
    };
}

#endif /* GameScene_hpp */
