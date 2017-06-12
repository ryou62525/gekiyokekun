//
//  Player.hpp
//  Gekiyokekun
//
//  Created by 小松亮太 on 2017/04/20.
//
//

#ifndef Player_hpp
#define Player_hpp

#include <cocos2d.h>

namespace User
{
    enum class Dir
    {
        FRONT = 0,
        LEFT,
        RIGHT,
        
        MAX_COUNT
    };
    
    class Player : public cocos2d::Sprite
    {
    private:
        
        
        
    public:
        
        Player();
        ~Player();
    
        CREATE_FUNC( Player );
        bool init();
    
        void setAnim( const std::string animPath );
        cocos2d::Size getCollisionBorder();
        
    private:
        
        CC_SYNTHESIZE( cocos2d::Vec2, sizeIndex, SizeIndex );
        CC_SYNTHESIZE( Dir, dirState, DirState );
        CC_SYNTHESIZE( float, animSpeed, AnimSpeed );
        
        const cocos2d::Size winSize;
        const std::string filePath;
        std::vector<std::string> nameTag;
        
        cocos2d::AnimationCache* animCache;
        cocos2d::Size frameSize;
        
        void creatAnimation();
        void move( cocos2d::Touch* _touch );
        void dead();
        void update( float delta );
    };
}
#endif /* Player_hpp */
