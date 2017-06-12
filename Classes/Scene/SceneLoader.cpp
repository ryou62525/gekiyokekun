//
//  SceneLoader.cpp
//  Gekiyokekun
//
//  Created by 小松亮太 on 2017/04/18.
//
//

#include "SceneLoader.hpp"
#include "Game/GameScene.hpp"
#include "TitleScene.hpp"
USING_NS_CC;

namespace User
{
    void SceneLoader::createSystemAppDelegate()
    {
        //craeteGame();
        createTitle();
    }
    
    void SceneLoader::createDebugTitle()
    {
        createScene<TitleScene>();
    }
    
    void SceneLoader::createTitle()
    {
        createScene<TitleScene, TransitionFade>(2.0f);
    }
    
    void SceneLoader::craeteGame()
    {
        createScene<GameScene, TransitionFade>(1.0f);
        //createScene<GameScene, TransitionFlipX>(1.0f);
    }
}
