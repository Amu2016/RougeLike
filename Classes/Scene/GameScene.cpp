#include"GameScene.h"
#include"Layer\GameLayer.h"
#include"Layer\UILayer.h"

USING_NS_CC;

Scene* GameScene::createScene() {
	auto scene = Scene::create();

	auto uiLayer = UILayer::create();
	auto gameLayer = GameLayer::create();
	
	//gameLayer->setUILayer(uiLayer);
	//uiLayer->setGameLayer(gameLayer);

	scene->addChild(gameLayer, 0);
	scene->addChild(uiLayer, 1);

	return scene;
}

//bool GameScene::init() {
//
//	return true;
//}