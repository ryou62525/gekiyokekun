//
//  GameScore.cpp
//  Gekiyokekun
//
//  Created by 小松亮太 on 2017/04/26.
//
//

#include "GameScore.hpp"
#include "../Lib/Tools.h"
USING_NS_CC;
using namespace Lib;

namespace User
{
    GameScore::GameScore():
        winSize( Director::getInstance()->getWinSize() ),
        point( 0 ),
        highScorePoint( 0 )
    {
        
    }

    GameScore::~GameScore()
    {
        
    }

    bool GameScore::init()
    {
        if( !Label::init() ){ return false; }

        createScoreLabel( "SCORE", "HIGHSCORE" );
        
        return true;
    }
    
    void GameScore::createScoreLabel( const std::string _scoreLabel, const std::string _highScoreLabel )
    {
        scoreFont = Label::createWithSystemFont("SCORE", "Arial", 50);
        scoreFont->enableShadow( Color4B::BLACK, Size(0.5,0.5), 1 );
        scoreFont->enableOutline( Color4B::BLACK, 1.5f );
        scoreFont->setPosition( Vec2( WindowSize::WIDTH * 0.2f , WindowSize::HEIGHT * 0.95f ) );
        this->addChild( scoreFont );
        
        score = Label::createWithSystemFont( StringUtils::toString( this->point ), "fonts/arial.ttf", 50 );
        score->setPosition( Vec2( WindowSize::WIDTH * 0.2f, WindowSize::HEIGHT * 0.9f ) );
        score->setColor(Color3B::BLACK);
        this->addChild( score );

        highScoreFont = Label::createWithSystemFont( "HIGHSCORE", "Arial", 50 );
        highScoreFont->enableShadow( Color4B::BLACK, Size (0.5f, 0.5f ), 1 );
        highScoreFont->enableOutline( Color4B::BLACK, 1.5f );
        highScoreFont->setPosition( Vec2( WindowSize::WIDTH * 0.8f, WindowSize::HEIGHT * 0.95f ) );
        this->addChild( highScoreFont );

        highScore = Label::createWithSystemFont( StringUtils::toString( this->highScorePoint ), "fonts/arial.ttf", 50 );
        highScore->setPosition( Vec2( WindowSize::WIDTH * 0.8f, WindowSize::HEIGHT * 0.9f ) );
        highScore->setColor(Color3B::BLACK);
        this->addChild( highScore );
    }
}
