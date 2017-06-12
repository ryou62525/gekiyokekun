//
//  GameUtils.cpp
//  Gekiyokekun
//
//  Created by 小松亮太 on 2017/04/17.
//
//

#include "GameUtils.hpp"
USING_NS_CC;

namespace Lib
{
    float fitWidth( Node* _node, float _tagetSize )
    {
        return  _tagetSize / _node->getContentSize().width;
    }
    
    float fitHeight( Node* _node, float _tagetSize )
    {
        return  _tagetSize / _node->getContentSize().height;
    }
    
    float generateRndom(float _min, float _max)
    {
        std::mt19937 rand;
        std::random_device randDev;
        rand.seed( randDev() );
        std::uniform_real_distribution<float> range( _min, _max );
        return  range( rand );
    }
}
