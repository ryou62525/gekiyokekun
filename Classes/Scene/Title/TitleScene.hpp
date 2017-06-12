//
//  TitleScene.hpp
//  Gekiyokekun
//
//  Created by 小松亮太 on 2017/05/11.
//
//

#ifndef TitleScene_hpp
#define TitleScene_hpp

#include "Player.hpp"
#include <cocos2d.h>

namespace User
{
    class TitleScene : public cocos2d::Layer
    {
    private:
        
        enum
        {
            TITLE,
            INFO
        };
        
    public:
        
        TitleScene();
        virtual ~TitleScene();
        CREATE_FUNC( TitleScene );
        
        bool init();
        static cocos2d::Scene* createScene();
        
        void createStaging();
        void createTitleLabel();
        
    private:
  
        cocos2d::Vector<cocos2d::Label*> titleLabel;
        
        float fallLength;
        float intervalTime;
        int fontSize;
        
        bool canInput;
        bool isCompDraw;
        
        void createDebugButton();
        void createTouchInfoUI();
        void createPlayer();
    
        void titleAction();
        void characterAction( cocos2d::FiniteTimeAction* _action_1, cocos2d::FiniteTimeAction* _action_2 );
        void pressedAfter();
        
        void fallObjects( cocos2d::Node* _node, float _length, float _delayTime );
        
        CC_SYNTHESIZE( Player*, player, Player);
        
        
        void update(float delta);
    };
}

#endif /* TitleScene_hpp */
