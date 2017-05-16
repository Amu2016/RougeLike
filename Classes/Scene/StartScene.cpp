#include"StartScene.h"
#include"Layer\StartLayer.h"

USING_NS_CC;

Scene* StartScene::createScene() {
	auto scene = Scene::create();

	auto startLayer = StartLayer::create();

	scene->addChild(startLayer, 0);

	return scene;
}