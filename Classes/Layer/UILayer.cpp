#include"UILayer.h"
//#include"GameLayer.h"

bool UILayer::init() {
	if (!Layer::init())
		return false;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UI/UI.plist");



	//joyStick = JoyStick::getInstance();
	//addChild(joyStick);
	//joyStick->setPosition(Vec2(100, 100));


	



	return true;
}

void UILayer::update(float delta) {

}

void UILayer::updateHero(float delta) {

}