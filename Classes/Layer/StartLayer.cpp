#include"StartLayer.h"
#include"GameLoadingLayer.h"

bool StartLayer::init() {
	if (!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto startGameItem = MenuItemImage::create(
		"UI/beginGame.png",
		"UI/beginGameDown.png",
		CC_CALLBACK_0(StartLayer::startGame, this));

	startGameItem->setPosition(Vec2(visibleSize.width / 2 ,
		visibleSize.height / 2));

	auto menu = Menu::create(startGameItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void StartLayer::startGame() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto gameLoadingLayer = GameLoadingLayer::create();

	gameLoadingLayer->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height / 2));

	getParent()->addChild(gameLoadingLayer, 1);
}