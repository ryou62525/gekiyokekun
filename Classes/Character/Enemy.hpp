//
//  Enemy.hpp
//  Gekiyokekun
//
//  Created by 小松亮太 on 2017/04/21.
//
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include <cocos2d.h>

namespace User
{
    class Enemy : public cocos2d::Sprite
    {
    public:
        
        CREATE_FUNC( Enemy );
        
        bool init();
        bool isActive();
        
    private:
        
        std::string setFilePath();
        
    };
}
#endif /* Enemy_hpp */
