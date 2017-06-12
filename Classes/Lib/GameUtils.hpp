//
//  GameUtils.hpp
//  Gekiyokekun
//
//  Created by 小松亮太 on 2017/04/17.
//
//

#ifndef GameUtils_hpp
#define GameUtils_hpp

#include <cocos2d.h>

namespace Lib
{
    float fitWidth( cocos2d::Node* _node, float _tagetSize );
    float fitHeight( cocos2d::Node* _node, float _tagetSize );
    float generateRndom(float _min, float _max);
}

#endif /* GameUtils_hpp */
