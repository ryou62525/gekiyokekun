//
//  TitleScene.cpp
//  Gekiyokekun
//
//  Created by 小松亮太 on 2017/05/11.
//
//

#include "TitleScene.hpp"
#include "Tools.h"
#include "GameUtils.hpp"
#include "SceneLoader.hpp"
#include "../../../cocos2d/cocos/audio/AudioEngine.cpp"
#include "ui/CocosGUI.h"

using namespace experimental;
using namespace Lib;
USING_NS_CC;

namespace User
{
    TitleScene::TitleScene():
        fontSize( 80 ),
        intervalTime( 2 ),
        canInput(false),
        isCompDraw(false),
        player(nullptr)
    {
        this->setContentSize( Size( WindowSize::WIDTH, WindowSize::HEIGHT ) );
        fallLength = ( this->getContentSize().height + fontSize / 2) - this->getContentSize().height * 0.85f;
        log("fallLength %f", fallLength);
    }

    TitleScene::~TitleScene()
    {
        
    }
    
    Scene* TitleScene::createScene()
    {
        auto scene = Scene::createWithPhysics();
        scene->getPhysicsWorld()->setGravity( Vec2( 0, -5 ) );
        scene->getPhysicsWorld()->setSpeed( 6.0f );
        scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
        auto layer = TitleScene::create();
        scene->addChild( layer );
        return scene;
    }
    
    bool TitleScene::init()
    {
        if( !Layer::init() ){ return false; }
        
        createStaging();
        createTitleLabel();
        createPlayer();
        createDebugButton();
        
        this->runAction( Sequence::create( DelayTime::create( 1.5f ),
                                           CallFunc::create([this] { titleAction(); } ),
                                           DelayTime::create( 1.5f ),
                                           CallFunc::create( [this] {
 
            auto move = MoveTo::create( 1, Vec2( this->getContentSize().width / 2, player->getPosition().y ) );
            auto changeDir = CallFunc::create( [this]{ player->setAnim( "FRONT" ); } );
            characterAction( move, changeDir );
            
        } ),
                                           DelayTime::create(1),
                                           CallFunc::create( [this]{
        
            createTouchInfoUI();
            canInput = true;
        
        } ),
                                           nullptr ) );
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [this]( Touch* touch, Event* event )
        {
            if( canInput )
            {
                this->runAction( Sequence::create( CallFunc::create( CC_CALLBACK_0( TitleScene::pressedAfter, this ) ),
                                                   DelayTime::create( 1.f ),
                                                   CallFunc::create( [this]{ player->setAnim( "LEFT" ); } ),
                                                   DelayTime::create(0.1f),
                                                   CallFunc::create( [this] { player->runAction( MoveTo::create( 1, Vec2( -player->getContentSize().width * 2, player->getPosition().y ) ) ); } ),
                                                   DelayTime::create( intervalTime ),
                                                   CallFunc::create( [this]{ User::SceneLoader::craeteGame(); } ),
                                                   nullptr ) );
            }
            return true;
        };
        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority( listener, this );
        
        
        this->scheduleUpdate();
        return true;
    }
    
    void TitleScene::update(float delta)
    {
        log( "PlayerPosition x=%f y=%f", player->getPosition().x, player->getPosition().y );
    }
    
    void TitleScene::createStaging()
    {
        auto back = Sprite::create( "texture/title_img.png" );
        back->setPosition( this->getContentSize() / 2 );
        back->setScale( fitHeight( back, Director::getInstance()->getWinSize().height ) );
        this->addChild( back );
        
        auto rect = Rect( 0, 0, this->getContentSize().width, this->getContentSize().height * 0.2f );
        auto bar_ = Sprite::create();
        
        bar_->setAnchorPoint( Point( 0.5f, 0.0f ) );
        bar_->setTextureRect( rect );
        bar_->setPosition( Vec2( this->getContentSize().width / 2, 0) );
        bar_->setColor( Color3B::BLACK );
        bar_->setOpacity( 150 );
        this->addChild( bar_, LayerType::FOREGROUND );
    }
    
    //タイトルの描画
    void TitleScene::createTitleLabel()
    {
        titleLabel.pushBack( Label::createWithTTF("げきよけくん", "fonts/GenShinGothic-Bold.ttf", fontSize) );
        titleLabel.at( TITLE )->setPosition( this->getContentSize().width / 2, this->getContentSize().height + fontSize / 2 );
        titleLabel.at( TITLE )->setTextColor( Color4B( 255, 0, 0, 255 ) );
        this->addChild( titleLabel.at( TITLE ) );
    }
    
    void TitleScene::titleAction()
    {
        //１文字ずつスプライトに変換してActionを実行
        int labelLength = titleLabel.at( TITLE )->getStringLength();
        
        for (int i = 0; i < labelLength; i++)
        {
            auto sp = titleLabel.at( TITLE )->getLetter( i );
            if( sp )
            {
                fallObjects( sp, -fallLength, static_cast<float>( i * 0.1f ) );
            }
        }
    }
    
    void TitleScene::pressedAfter()
    {
        int labelLength = titleLabel.at( TITLE )->getStringLength();
        for (int i = 0; i < labelLength; i++ )
        {
            auto sp = titleLabel.at( TITLE )->getLetter( 5 - i );
            float length = ( titleLabel.at( TITLE )->getPosition().y - fallLength ) -
            ( this->getContentSize().height * 0.2f + sp->getContentSize().height / 2 );

            if( sp ){ fallObjects( sp, -length, i * 0.1f ); }
        }
        this->canInput = false;
        
        auto blink = Blink::create( 0.5f, 5 );
        titleLabel.at( INFO )->stopAllActions();
        titleLabel.at( INFO )->runAction( RepeatForever::create( blink ) );
    }
    
    void TitleScene::fallObjects( cocos2d::Node* _node, float _length, float _delayTime )
    {
        auto move = MoveBy::create( 1.5f, Vec2( 0, _length ) );
        auto delay = DelayTime::create( _delayTime );
        auto eaaseAction = EaseOut::create( move, 0.1f );
        auto addSE = CallFunc::create([this]{
            AudioEngine::play2d("sound/SE/se_maoudamashii_se_fall02.wav");
        });
        //アクションの実行。最後の文字まで行ったらゲーム開始できるようにする
        _node->runAction( Sequence::create( delay, eaaseAction, addSE, nullptr) );
    }
    

    //キャラクターの挙動
    void TitleScene::characterAction( FiniteTimeAction* _action_1, FiniteTimeAction* _action_2 )
    {
        player->runAction( Sequence::create( _action_1, _action_2, NULL ) );
    }
    
    void TitleScene::createTouchInfoUI()
    {
        titleLabel.pushBack( Label::createWithTTF( "TAP TO START", "fonts/GenShinGothic-Regular.ttf", 32 ) );
        titleLabel.at( INFO )->setPosition( this->getContentSize().width * 0.5f, this->getContentSize().height * 0.65f );
        titleLabel.at( INFO )->setTextColor( Color4B( 255, 0, 0, 255 ) );
        titleLabel.at( INFO )->setOpacity( 255 );
        this->addChild( titleLabel.at( INFO ) );
        
        auto labelStaging = Sequence::create(FadeTo::create(0.5, 64),
                                      FadeTo::create(0.5, 255),
                                      NULL);
        
        auto action_2 = RepeatForever::create( labelStaging );
        titleLabel.at( INFO )->runAction( action_2 );
    }

    void TitleScene::createPlayer()
    {
        auto pra = Player::create();
        pra->setScale( 5.f );
        this->setPlayer( pra );
        pra->setAnchorPoint( Vec2( 0.5f, 0 ) );
        pra->setPosition( Vec2( this->getContentSize().width + pra->getContentSize().width, this->getContentSize().height * 0.2f ) );
        pra->setName( "Player" );
        pra->setAnim("LEFT");
        pra->setTag( LayerType::OBJECT );
        this->addChild( pra );
    }
    
    //デバッグ用ボタン TODO: 完成したら削除する--->
    void TitleScene::createDebugButton()
    {
        auto button = cocos2d::ui::Button::create("CloseNormal.png");
        button->setPosition( Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.15f ) );
        button->setScale(2);
        this->addChild( button );
        
        button->addTouchEventListener([this](Ref* ref, cocos2d::ui::Widget::TouchEventType type){
            if(type == cocos2d::ui::Widget::TouchEventType::ENDED)
            {
                User::SceneLoader::createDebugTitle();
            }
        });
    }
    
}
