#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "SimpleShader.h"

USING_NS_CC;

class GameLayer : public cocos2d::Scene
{
public:
    virtual bool init() override;
    virtual void update(float delta);
};


#endif // !__GAMELAYER_H__
