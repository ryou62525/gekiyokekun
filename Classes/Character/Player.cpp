//
//  Player.cpp
//  Gekiyokekun
//
//  Created by 小松亮太 on 2017/04/20.
//
//

#include "Player.hpp"
#include "../Lib/Tools.h"
USING_NS_CC;
using namespace Lib;

namespace User
{
    Player::Player():
        winSize( Director::getInstance()->getWinSize() ),
        filePath( "texture/player.png" ),
        sizeIndex( Vec2( 3, 4 ) ),
        dirState(Dir::FRONT),
        animSpeed(0.1f)
    {
    }
    
    Player::~Player()
    {
        
    }

    bool Player::init()
    {
        if( !Sprite::initWithFile( filePath ) ){ return false; }

        frameSize = Size( this->getContentSize().width / sizeIndex.x,
                         this->getContentSize().height / sizeIndex.y );
        
        creatAnimation();
        
        this->scheduleUpdate();
        return true;
    }
    
    void Player::update(float delta)
    {
 
    }

    void Player::creatAnimation()
    {
        std::vector<std::vector<int>> indexes;
        std::vector<int> index;

        Vector<SpriteFrame*> frames;
        SpriteFrame* frame;
        
        for (int y = 0; y < 3; y++)
        {
            for(int x = 0; x < 3; x++)
            {
                frame = SpriteFrame::create( filePath, Rect( frameSize.width  * x,
                                                             frameSize.height * y,
                                                             frameSize.width,
                                                             frameSize.height ) );
                frames.pushBack( frame );
            }
        }
        
        Vector<Animation*> anim;
        for (int i = 0; i < static_cast<int>(Dir::MAX_COUNT); i++)
        {
            anim.pushBack( Animation::create() );
        }
        
        for (int i = 0; i < 9; i++)
        {
            index.push_back(i);
        }

        //---indexesに描画順の配列を追加
        indexes.push_back( { index[0], index[1], index[2], index[1] } );
        indexes.push_back( { index[3], index[4], index[5], index[4] } );
        indexes.push_back( { index[6], index[7], index[8], index[7] } );
        
        //---アニメーションを各方向ごとに追加
        for(int i = 0; i < static_cast<int>( Dir::MAX_COUNT ); i++)
        {
            for (int k = 0; k < 4; k++)
            {
                anim.at( i )->addSpriteFrame( frames.at( indexes.at(i).at(k) ) );
                anim.at( i )->setDelayPerUnit(0.1f);
            }
        }

        //---各方向のアニメーションを名前をつけてキャッシュクラスに登録
        auto animCache = AnimationCache::getInstance();
        animCache->addAnimation( anim.at(0), "FRONT" );
        animCache->addAnimation( anim.at(1), "LEFT" );
        animCache->addAnimation( anim.at(2), "RIGHT" );
        
        //---キャッシュクラスから指定したアニメーションを取り出して実行
        this->runAction( RepeatForever::create( Animate::create( AnimationCache::getInstance()->animationByName("FRONT") ) ) );
    }

    void Player::move(Touch* _touch)
    {
        Vec2 delta = _touch->getDelta() * 2.0f;
        Vec2 pos = this->getPosition();
        
        Vec2 newPos = Vec2(pos.x + delta.x, pos.y + delta.y);
        newPos = newPos.getClampPoint( Vec2( ( WindowSize::WIDTH * 0.0f ) + this->getContentSize().width, pos.y ),
                                       Vec2( WindowSize::WIDTH - this->getContentSize().width , pos.y ) );
        
        if(delta.x != 0){
            if(pos.x < newPos.x){
                if( dirState != Dir::RIGHT ){
                    setAnim("RIGHT");
                    dirState = Dir::RIGHT;
                }
            }
            else{
                if(dirState != Dir::LEFT ){
                    setAnim("LEFT");
                    dirState = Dir::LEFT;
                }
            }
        }
        
        this->setPosition( newPos );
    }
   
    void Player::setAnim( const std::string animPath )
    {
        this->stopAllActions();
        this->runAction( RepeatForever::create( Animate::create( AnimationCache::getInstance()->animationByName( animPath ) ) ) );
    }
    
    void Player::dead()
    {
    }
    
    Size Player::getCollisionBorder()
    {
        auto size = Size( this->getContentSize().width, this->getContentSize().height );
        return size;
    }
    
}
