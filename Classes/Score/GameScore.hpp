//
//  GameScore.hpp
//  Gekiyokekun
//
//  Created by 小松亮太 on 2017/04/26.
//
//

#ifndef GameScore_hpp
#define GameScore_hpp

#include <cocos2d.h>

namespace User
{
    class GameScore : public cocos2d::Label
    {
    public:
        
        GameScore();
        ~GameScore();
        CREATE_FUNC( GameScore );
        
        bool init();
        
    private:
        
        CC_SYNTHESIZE( int, point, Point );
        CC_SYNTHESIZE( int, highScorePoint, HighScorePoint );
        CC_SYNTHESIZE( cocos2d::Label*, scoreFont,      ScoreFont       );
        CC_SYNTHESIZE( cocos2d::Label*, score,          Score           );
        CC_SYNTHESIZE( cocos2d::Label*, highScoreFont,  HighScoreFont   );
        CC_SYNTHESIZE( cocos2d::Label*, highScore,      HighScore       );
        
        cocos2d::Size winSize;
        
        void createScoreLabel( const std::string _scoreLabel, const std::string _highScoreLabel );
        
    };
}


#endif /* GameScore_hpp */
