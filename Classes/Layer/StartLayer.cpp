#include"StartLayer.h"
#include"GameLoadingLayer.h"

bool StartLayer::init() {
	if (!LayerColor::init())
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
	menu->setScale(2.0);
	this->addChild(menu, 1);

	//setColor(Color3B::WHITE);
	return true;
}

void StartLayer::startGame() {
	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();

	removeAllChildren();

	auto gameLoadingLayer = GameLoadingLayer::create();

	//gameLoadingLayer->setPosition(Vec2(visibleSize.width / 2,
	//	visibleSize.height / 2));

	getParent()->addChild(gameLoadingLayer, 1);
}