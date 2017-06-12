//
//  SceneLoader.hpp
//  Gekiyokekun
//
//  Created by 小松亮太 on 2017/04/18.
//
//

#ifndef SceneLoader_hpp
#define SceneLoader_hpp

#include <cocos2d.h>

namespace User
{
    class SceneLoader
    {
    public:
        
        static void createSystemAppDelegate();
        
        static void createTitle();
        static void createDebugTitle();
        static void craeteGame();
        
    private:
        
        template <class _Ty>
        static void createScene();
        
        template <class _Ty, class... _Args>
        static void createScene(_Args... _args);
        
        template <class _Ty, class _TyTransition, class... _TyTransitionArgs>
        static void createScene( _TyTransitionArgs... _tyTransitionArgs );
    };
    
    template <class _Ty>
    void SceneLoader::createScene()
    {
        auto scene = _Ty::createScene();
        cocos2d::Director::getInstance()->replaceScene( scene );
    }
    
    template <class _Ty, class... _Args>
    void SceneLoader::createScene(_Args... _args)
    {
        auto scene = _Ty::createScene( _args... );
        cocos2d::Director::getInstance()->replaceScene( scene );
    }
    
    template <class _Ty, class _TyTransition, class... _TyTransitionArgs>
    void SceneLoader::createScene( _TyTransitionArgs... _tyTransitionArgs )
    {
        auto scene = _Ty::createScene();
        auto transition = _TyTransition::create( _tyTransitionArgs..., scene );
        cocos2d::Director::getInstance()->replaceScene( transition );
    }

}


#endif /* SceneLoader_hpp */
