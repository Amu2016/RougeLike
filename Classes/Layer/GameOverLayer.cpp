#include"GameOverLayer.h"
#include"Scene\GameScene.h"
#include"Scene\StartScene.h"
#include"ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;

bool GameOverLayer::init() {
	if (!LayerColor::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Sprite* sprite = Sprite::create("UI/2132123.png");
	//addChild(sprite, 1);
	
	LayerColor* layer = LayerColor::create(Color4B::WHITE, visibleSize.width + origin.x, visibleSize.height + origin.y);
	addChild(layer);
	//layer->setAnchorPoint(Vec2(0, 0));

	auto text = Text::create(StringUtils::format("Game Over"), "fonts/Marker Felt.ttf", 100);
	text->setColor(Color3B::GREEN);
	//text->setAnchorPoint(Vec2::ZERO);
	addChild(text);
	text->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height / 2));

	//setColor(Color3B::WHITE);
	scheduleOnce(schedule_selector(GameOverLayer::startGame), 3.0f);

	return true;
}

void GameOverLayer::startGame(float delta) {
	auto scene = StartScene::createScene();

	Director::getInstance()->replaceScene(scene);
}