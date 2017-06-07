#include"GameLoadingLayer.h"
#include"Scene\GameScene.h"
#include"ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;

bool GameLoadingLayer::init() {
	if (!LayerColor::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Sprite* sprite = Sprite::create("UI/2132123.png");
	//addChild(sprite, 1);

	auto text = Text::create(StringUtils::format("Loading"), "fonts/Marker Felt.ttf", 100);
	text->setColor(Color3B::GREEN);
	//text->setAnchorPoint(Vec2::ZERO);
	addChild(text);
	text->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height / 2));

	//setColor(Color3B::WHITE);
	scheduleOnce(schedule_selector(GameLoadingLayer::startGame), 0.1f);

	return true;
}

void GameLoadingLayer::startGame(float delta) {
	auto scene = GameScene::createScene();

	Director::getInstance()->replaceScene(scene);
}