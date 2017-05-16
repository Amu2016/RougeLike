#include"GameLoadingScene.h"

Scene* GameLoadingScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = GameLoadingScene::create();

	scene->addChild(layer);
	return scene;
}

bool GameLoadingScene::init()
{
	if (!Layer::init()) return false;

	return true;
}