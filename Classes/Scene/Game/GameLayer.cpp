//
//  GameLayer.cpp
//  Gekiyokekun
//
//  Created by 小松亮太 on 2017/04/20.
//

#include "GameLayer.hpp"
#include "Tools.h"
#include "GameUtils.hpp"
#include "SceneLoader.hpp"
#include "GameScene.hpp"
USING_NS_CC;
using namespace Lib;

namespace User
{
    GameLayer::GameLayer():
    filePath("texture/wilderness.png"),
    gameState( GameState::READY ),
    player( nullptr ),
    point( 0 ),
    second( 60.0f ),
    secondLabel( nullptr ),
    scoreLabel( nullptr ),
    bar( nullptr )
    {
        score = 0;
        highScore = 0;
    }
    
    GameLayer::~GameLayer()
    {
        CC_SAFE_RELEASE_NULL( secondLabel );
    }
    
    bool GameLayer::init()
    {
        if( !Sprite::init( ) ){ return false; }

        this->setContentSize( Size( WindowSize::WIDTH, WindowSize::HEIGHT ) );

        createBackground();
        createGameBar();
        //createTimeLabel();
        createScoreLabel();
        
        addPlayer();
        
        auto layerColor = LayerColor::create( Color4B( 255, 0, 0, 128 ), player->getCollisionBorder().width, player->getCollisionBorder().height );
        player->addChild( layerColor );
        log( "Player ContentSize x=%f y=%f", player->getContentSize().width, player->getContentSize().height );
        
        this->scheduleUpdate();
        return true;
    }
    
    void GameLayer::onEnterTransitionDidFinish()
    {
        createStartLabel();
    }
    
    void GameLayer::update(float delta)
    {
        if( gameState == GameState::PLAYING )
        {
            //ランダムで敵を生成する
            int random = rand() % 100; //TODO: 値を増やすと出現するスピードが遅くなる
            if( random == 0 )
            {
                addEnemy();
            }
            
            for( auto enemy : enemys )
            {
                //範囲外に落ちたら削除する
                if( enemy->getPosition().y <= -this->getContentSize().height / 2 ){ removeEnemy( enemy ); }
                //敵に当たった時にゲームオーバーにする
                if( player && this->isHIt( enemy ) )
                {
                    onResult();
                    return;
                }
            }
        }
        
        // TODO: 制限時間モードを追加した時に使う
//        if( second > 0 )
//        {
//            //残り時間を減らす
//            second -= delta;
//            int _second = static_cast<int>( second );
//            secondLabel->setString( StringUtils::toString( _second ) );
//        }
//        else
//        {
//            gameState = GameState::RESULT;
//            onResult();
//        }
        
    }
    
    bool GameLayer::isHIt(Enemy* _enemy)
    {
        return _enemy->getBoundingBox().intersectsRect( player->getBoundingBox() );
    }
    
    bool GameLayer::removeEnemy( Enemy* _enemy )
    {
        //enemysの配列に_enemyが含まれているかどうかを確認する
        if( enemys.contains( _enemy ) )
        {
            point += 1;
            auto score = dynamic_cast<Label*>( this->getScoreLabel()->getScore() );
            score->setString( StringUtils::toString( point ) );
            
            //親ノードから
            _enemy->removeFromParent();
            enemys.eraseObject( _enemy );
            return true;
        }
        return false;
    }
    
    //ゲームが終了した時の処理
    void GameLayer::onResult()
    {
        createGameOverLabel();
        gameOver();
    }
    
    void GameLayer::gameOver()
    {
        //TODO: プレイヤーがやられた時の処理を書く↓
        gameState = GameState::RESULT;
        createGameOverLabel();
        this->removeChildByName("Player");
    }
    
    void GameLayer::addPlayer()
    {
        auto p = Player::create();
        p->setContentSize( Size( 32, 32 ) );
        p->setScale( 5.f );
        this->setPLayer( p );
        p->setAnchorPoint( Vec2( 0.5f, 0 ) );
        p->setPosition( Vec2( this->getContentSize().width / 2, bar->getContentSize().height ));
        p->setName( "Player" );
        p->setAnimSpeed(0.1f);
        p->setTag( LayerType::OBJECT );
        this->addChild( p );
    }

    void GameLayer::addEnemy()
    {
        auto ene = Enemy::create();
        ene->setContentSize( Size(128,128) );
        ene->setScale( 1.3f );
        Vec2 pos = Vec2(  generateRndom( 0, WindowSize::WIDTH ),
                          generateRndom( WindowSize::HEIGHT, WindowSize::HEIGHT + WindowSize::HEIGHT / 2 )  );
        
        ene->setPosition( pos.x, pos.y );
        
        //当たり判定（円形）を用意
        auto circle = PhysicsBody::createCircle( ene->getContentSize().width / 3 );
        circle->setDynamic( true );
        circle->setRotationEnable( false );
        ene->setPhysicsBody( circle );
        
        this->addChild( ene, LayerType::OBJECT );
        enemys.pushBack( ene );
    }
    
    //制限時間の表示
    void GameLayer::createTimeLabel()
    {
        int time = static_cast<int>( second );
        auto timeLabel = Label::createWithSystemFont( StringUtils::toString( time ), "Arial", 50 );
        this->setSecondLabel( timeLabel );
        secondLabel->enableShadow( Color4B::BLACK, Size( 1.0f, 1.0f ), 5 );
        secondLabel->enableOutline( Color4B::BLACK, 2.5f );
        secondLabel->setPosition( Vec2( this->getContentSize().width/2, this->getContentSize().height * 0.4f ) );
        this->addChild( secondLabel );
        
        auto timeLabelFont = Label::createWithSystemFont( "Time", "arial", 50 );
        timeLabelFont->enableShadow( Color4B::BLACK, Size( 1.0f, 1.0f ), 5 );
        timeLabelFont->enableOutline( Color4B::BLACK, 2.5f );
        timeLabelFont->setPosition( Vec2( 0, this->getContentSize().height * 0.45f ) );
        this->addChild( timeLabelFont );
    }
    
    //スコア表示
    void GameLayer::createScoreLabel()
    {
        auto score = GameScore::create();
        this->setScoreLabel( score );
        this->addChild( score, LayerType::FOREGROUND );
    }
    
    //背景の設定
    void GameLayer::createBackground()
    {
        auto back = Sprite::create( filePath );
        back->setPosition( this->getContentSize()/2 );
        back->setScale( fitHeight( back, this->getContentSize().height ) );
        this->addChild( back );
    }
    
    //画面下部黒枠の設定
    void GameLayer::createGameBar()
    {
        auto rect = Rect( 0, 0, this->getContentSize().width, this->getContentSize().height * 0.2f );
        auto bar_ = Sprite::create();
        this->setBar(bar_);
        
        bar_->setAnchorPoint( Point( 0.5f, 0.0f ) );
        bar_->setTextureRect( rect );
        bar_->setPosition( Vec2( this->getContentSize().width / 2, 0) );
        bar_->setColor( Color3B::WHITE );
        bar_->setOpacity( 150 );
        this->addChild( bar, LayerType::FOREGROUND );
    }
    
    void GameLayer::createStartLabel()
    {
        auto startLabel = Label::createWithSystemFont("Ready", "Arial", 24);
        startLabel->enableShadow(Color4B::BLACK,Size(0.5,0.5),1);
        startLabel->enableOutline(Color4B::BLACK,1.5);
        startLabel->setScale( 0 );
        startLabel->setPosition( this->getContentSize() / 2 );
        this->addChild( startLabel );
        
        auto startFunc = CallFunc::create([=]()
                                          {
                                              //Readyの文字をスケーリングさせる
                                              startLabel->runAction( ScaleTo::create(0.5f, 5.0f) );
                                              startLabel->runAction( ScaleTo::create(0.1f, 0) );
                                              log("Processing of [startFunc] started");
                                          });
        
        auto delay = DelayTime::create( 2.0f );
        
        auto middleFunc = CallFunc::create([=]()
                                           {
                                               //Readyの文字を変更してStartの文字に変更。
                                               startLabel->setString( "Go!!" );
                                               log("Processing of [middleFunc] started");
                                           });
        
        auto endFunc = CallFunc::create([=]()
                                           {
                                               startLabel->runAction( ScaleTo::create(0.5f, 5.0f) );
                                               startLabel->runAction( ScaleTo::create(0.1f, 0) );
                                               
                                               this->removeChild(startLabel, true);
                                               gameState = GameState::PLAYING;
                                           });
        
        startLabel->runAction(Sequence::create( startFunc, delay, middleFunc, delay, endFunc, nullptr ));
    }
    
    //ゲームオーバーした時のリザルト画面の生成
    void GameLayer::createGameOverLabel()
    {
        auto layer = Layer::create();
        layer->setContentSize( Size( this->getContentSize().width, this->getContentSize().height * 0.3f ) );
        auto layerColor = LayerColor::create( Color4B( 0,0,0,128 ), layer->getContentSize().width, layer->getContentSize().height );
        layerColor->setPosition( Vec2( -layerColor->getContentSize().width / 2,
                                       -layerColor->getContentSize().height / 2) );
        
        layer->addChild( layerColor );
        layer->setPosition(  this->getContentSize() / 2 );
        this->addChild( layer );
        
        auto rep = Label::createWithSystemFont( "もう一回", "arial", 50 );
        auto replayButton = MenuItemLabel::create( rep, [this](Ref* _ref)
                                                  {
                                                      SceneLoader::craeteGame();
                                                  });
        
        auto back = Label::createWithSystemFont( "タイトルに戻る", "arial", 50 );
        auto backButton = MenuItemLabel::create( back, [this](Ref* _ref)
                                                {
                                                    SceneLoader::createTitle();
                                                });
        
        auto menu = Menu::create( replayButton, backButton, NULL );
        menu->alignItemsVerticallyWithPadding( 15 );
        menu->setPosition( Vec2(0, -layerColor->getContentSize().height * 0.2f ) );
        
        
        //TODO: 今回のスコアと今までに出したハイスコアより上回った時と
        //      そうでなかった時の表示を追加する↓
        //スコアの表示
        auto scoreLabel = Label::createWithSystemFont(StringUtils::toString(score), "Marker Felt", 15);
        scoreLabel->setPosition( layer->getContentSize().width * 0.5f, layer->getContentSize().height * 0.7f );
        scoreLabel->enableShadow(Color4B::RED,Size(0.5,0.5),1);
        scoreLabel->enableOutline(Color4B::RED, 3);
        layer->addChild( scoreLabel );
        //ハイスコアの更新
        
//        highScore = UserDefault::getInstance()->getIntegerForKey(HIGH_SCORE_KEY);
//        if(score > highScore)
//        {
//            highScoreLabel->setString(StringUtils::toString(score));
//            UserDefault::getInstance()->setIntegerForKey(HIGH_SCORE_KEY, score);
//            
//            auto scoreFont = Label::createWithSystemFont("ハイスコア!", "Arial", 15);
//            scoreFont->setPosition(pos.x / 2, 50);
//            this->addChild(scoreFont);
//        }
//        else if(score < highScore)
//        {
//            auto scoreFont = Label::createWithSystemFont("今回のスコア", "Arial", 15);
//            scoreFont->setPosition(pos.x / 2, 50);
//            layout->addChild(scoreFont);
//        }
        
        
        layer->addChild( menu );
    }
}
