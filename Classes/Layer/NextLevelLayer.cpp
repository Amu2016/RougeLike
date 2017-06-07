#include"NextLevelLayer.h"
#include"Scene\GameScene.h"
#include"Scene\StartScene.h"
#include"ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;

bool NextLevelLayer::init() {
	if (!LayerColor::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Sprite* sprite = Sprite::create("UI/2132123.png");
	//addChild(sprite, 1);

	LayerColor* layer = LayerColor::create(Color4B::WHITE, visibleSize.width + origin.x, visibleSize.height + origin.y);
	addChild(layer);

	auto text = Text::create(StringUtils::format("Next Level"), "fonts/Marker Felt.ttf", 100);
	text->setColor(Color3B::GREEN);
	//text->setAnchorPoint(Vec2::ZERO);
	addChild(text);
	text->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height / 2));

	//setColor(Color3B::WHITE);
	scheduleOnce(schedule_selector(NextLevelLayer::startGame), 1.0f);

	return true;
}

void NextLevelLayer::startGame(float delta) {
	auto scene = GameScene::createScene();

	Director::getInstance()->replaceScene(scene);
}