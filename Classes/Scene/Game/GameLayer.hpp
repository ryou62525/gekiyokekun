//
//  GameLayer.hpp
//  Gekiyokekun
//
//  Created by 小松亮太 on 2017/04/20.
//
//

#ifndef GameLayer_hpp
#define GameLayer_hpp

#include "Player.hpp"
#include "Enemy.hpp"
#include "GameScore.hpp"
#include "Tools.h"
#include "../../ui/CocosGUI.h"

namespace User
{
    class GameLayer : public cocos2d::Sprite
    {
    private:
        
        std::string filePath;
        CC_SYNTHESIZE( cocos2d::Vector<Enemy*>, enemys, Enemys );
        CC_SYNTHESIZE( Player*, player, PLayer );
        CC_SYNTHESIZE( Lib::GameState, gameState, GameState );
        CC_SYNTHESIZE( float, second, Second );
        CC_SYNTHESIZE( int , point, Point );
        CC_SYNTHESIZE( GameScore*, scoreLabel, ScoreLabel );
        CC_SYNTHESIZE( cocos2d::Sprite*, bar, Bar );
        
        CC_SYNTHESIZE( int, score, Score );
        CC_SYNTHESIZE( int, highScore, HighScore );
        
        CC_SYNTHESIZE_RETAIN( cocos2d::Label*, secondLabel, SecondLabel );
        
    public:
        
        GameLayer();
        virtual ~GameLayer();
        CREATE_FUNC( GameLayer );
        
        bool init();
        void onEnterTransitionDidFinish();
        
    private:
        
        void onResult();
        void gameOver(  );
        bool removeEnemy( Enemy* _enemy );
        bool isHIt(Enemy* _enemy);
        
        void addPlayer();
        void addEnemy();
        
        void createTimeLabel();
        void createScoreLabel();
        void createBackground();
        void createGameBar();
        
        void createStartLabel();
        void createGameOverLabel();
        
        void update(float delta);
    };
}

#endif /* GameLayer_hpp */
