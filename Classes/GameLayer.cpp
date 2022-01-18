#include "GameLayer.h"

bool GameLayer::init()
{

    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto safeArea = Director::getInstance()->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;



    //create sprite
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    //create new shader with default vertex shader
    auto colorShader = CustomShader::createWithFragmentShader("shaders/simple.fsh");

    //set float uniform
    //shader->setUniform("speed", 1.0f);

    //set texture uniform (SimpleShader will manage the texture slots for you)
    //auto tex = Director::getInstance()->getTextureCache()->addImage("textures/2.png");
    //shader->setUniform("someTexture", tex);

    //apply shader to a sprite 
    sprite->setProgramState(colorShader->programState);

    //add sprite to scene
    this->addChild(sprite);

    scheduleUpdate();

	return true;
}

void GameLayer::update(float delta)
{
    //CustomShaderManager::getInstance()->updateShaderTime();
}
