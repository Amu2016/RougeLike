#include"GameLoadingLayer.h"
#include"Scene\GameScene.h"

bool GameLoadingLayer::init() {
	if (!Layer::init())
		return false;

	Sprite* sprite = Sprite::create("UI/2132123.png");
	addChild(sprite, 1);

	
	scheduleOnce(schedule_selector(GameLoadingLayer::startGame), 0.1f);

	return true;
}

void GameLoadingLayer::startGame(float delta) {
	auto scene = GameScene::createScene();

	Director::getInstance()->replaceScene(scene);
}