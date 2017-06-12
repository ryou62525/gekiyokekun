//
//  GameScene.cpp
//  Gekiyokekun
//
//  Created by 小松亮太 on 2017/04/18.
//
//

#include "GameScene.hpp"
#include "GameUtils.hpp"
#include "Tools.h"
#include "SceneLoader.hpp"


USING_NS_CC;
using namespace Lib;

namespace User
{
    GameScene::GameScene():
        gameLayer( nullptr )
    {
        winSize = Director::getInstance()->getWinSize();
    }

    GameScene::~GameScene()
    {

    }
    
    Scene* GameScene::createScene()
    {
        auto scene = Scene::createWithPhysics();
        
        scene->getPhysicsWorld()->setGravity( Vec2( 0, -5 ) );
        scene->getPhysicsWorld()->setSpeed( 6.0f );
        scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
        
        auto layer = GameScene::create();
        scene->addChild( layer );
        return scene;
    }
    
    bool GameScene::init()
    {
        if( !Layer::init() ){ return false; }
        
        addStage();
        touchOperation();
        outZoneSize = Vec2( gameLayer->getPosition().x - gameLayer->getContentSize().width / 2 , winSize.height);
        createOutZone();
        
        debugButton();
        
        return true;
    }
    
    void GameScene::addStage()
    {
        auto layer = GameLayer::create();
        layer->setScale( fitHeight( layer, winSize.height ) );
        layer->setPosition( winSize / 2 );
        layer->setName( "Stage" );
        this->setGameLayer( layer );
        this->addChild( layer );
    }
    
    //16:9の比率ではない場合黒帯を生成
    void GameScene::createOutZone()
    {
        if( !isFitWindowSize() )
        {
            for(int i = 0; i < 2; i++)
            {
                auto layer = Layer::create();
                layer->setPosition( Vec2( ( winSize.width - outZoneSize.x ) * i, 0 ) );
                layer->setContentSize( Size( outZoneSize.x, outZoneSize.y ) );
                layer->addChild( LayerColor::create(Color4B::BLACK,
                                                    layer->getContentSize().width,
                                                    layer->getContentSize().height ) );
                
                auto label = Label::createWithSystemFont("げ\nき\nよ\nけ\nく\nん", "Arial", 50);
                label->setPosition( Vec2( layer->getContentSize().width * 0.5f, layer->getContentSize().height * 0.6f ) );
                layer->addChild( label );
                
                this->addChild( layer );
            }
        }
    }
    
    //16:9のサイズと画面が一致しているかどうか
    bool GameScene::isFitWindowSize()
    {
        if( outZoneSize.x >= 0 )
        {
            return false;
        }
        return true;
    }
    
    //関数で定義したタッチイベントを登録します
    void GameScene::touchOperation()
    {
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2( GameScene::onTouchBegan, this );
        listener->onTouchMoved = CC_CALLBACK_2( GameScene::onTouchMoved, this );
        listener->onTouchEnded = CC_CALLBACK_2( GameScene::onTouchEnded, this );
        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    }
    
    //タッチした瞬間の処理
    bool GameScene::onTouchBegan( cocos2d::Touch* _touch, cocos2d::Event* _event )
    {
        log("タッチされました");
        return true;
    }
    
    //スワイプしている時の処理
    void GameScene::onTouchMoved( cocos2d::Touch* _touch, cocos2d::Event* _event )
    {
        if( auto player = dynamic_cast<Player*>( this->getChildByName( "Stage" )->getChildByName( "Player" ) ) )
        player->move( _touch );
    }
    
    //離した瞬間の処理
    void GameScene::onTouchEnded( cocos2d::Touch* _touch, cocos2d::Event* _event )
    {
        log("離しました");
    }
    
    void GameScene::debugButton()
    {
        auto button = ui::Button::create("CloseNormal.png");
        button->setPosition( Vec2(this->getContentSize().width * 0.5f, this->getContentSize().height * 0.95f ) );
        button->setScale(2);
        this->addChild( button );
        
        button->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType type){
            if(type == ui::Widget::TouchEventType::ENDED)
            {
                User::SceneLoader::createTitle();
            }
        });
    }
}
