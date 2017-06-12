//
//  Tools.h
//  Gekiyokekun
//
//  Created by vantan on 2016/09/23.
//
//

#ifndef Tools_h
#define Tools_h

#include <random>

namespace Lib
{
    enum WindowSize
    {
        WIDTH = 1080,
        HEIGHT = 1920
    };
    
    enum class ObjType
    {
        PLAYER,
        ENEMY,
        ALL
    };
    
    enum class EnemyType
    {
        ENEMY_1 = 0,
        ENEMY_2,
        ENEMY_3,
        
        MAX
    };
    
    enum class GameState
    {
        READY,
        PLAYING,
        END,
        RESULT
    };
    
    enum class Direction
    {
        FRONT = 0,
        LEFT,
        RIGHT
    };
    
    enum ScoreType
    {
        SCORE,
        HIGH_SCORE
    };
    
    enum LayerType
    {
        BACKGROUND,
        OBJECT,
        UI,
        FOREGROUND,
    };
    

}
#endif /* Tools_h */
