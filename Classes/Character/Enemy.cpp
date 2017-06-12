//
//  Enemy.cpp
//  Gekiyokekun
//
//  Created by 小松亮太 on 2017/04/21.
//
//

#include "Enemy.hpp"
#include "../Lib/Tools.h"
#include "../Lib/GameUtils.hpp"
USING_NS_CC;
using namespace Lib;
namespace User
{

    bool Enemy::init()
    {
        if( !Sprite::initWithFile( setFilePath() ) ){ return false; }
        
        this->setScale( 0.25f );
        
        return true;
    }
    
    std::string Enemy::setFilePath()
    {
        int enemyType = Lib::generateRndom( 0, static_cast<int>( EnemyType::MAX ) );
        auto fileName = StringUtils::format( "texture/Enemy_%d.png", enemyType );
        this->setTag( enemyType );
        
        return fileName;
    }
    
    bool Enemy::isActive()
    {
        if(this->getPosition().y <= 50)
        {
            return true;
        }
        return false;
    }
}
