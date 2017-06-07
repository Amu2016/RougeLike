#include"GameLayer.h"
#include"UI\JoyStick.h"
#include"MyRandom.h"
#include"Map\Map2D.h"
#include"Map\AStar.h"
#include"Layer\GameOverLayer.h"

bool GameLayer::init() {
	if (!Layer::init()) return false;

	winSize = Director::getInstance()->getWinSize();


	//-----------------------
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Monster/monster_2.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Gore/Core.plist");

	//---------------------
	setPosition(0, 0);

	tileMap = MyTileMap::getInstance()->getNewMap();

	tileMap->setAnchorPoint(Vec2(0, 0));
	tileMap->setPosition(0, 0);

	mapSize = Size(tileMap->getMapSize().width*tileMap->getTileSize().width,
		tileMap->getMapSize().height*tileMap->getTileSize().height);

	addChild(tileMap, -1);

	auto position = MyTileMap::getInstance()->getHeroPosition();



	serber = Serber::create();

	serber->setPosition(Vec2((position.x + 0.5) * tileMap->getTileSize().width ,
		(tileMap->getMapSize().height * tileMap->getTileSize().height) - (position.y + 0.5) * tileMap->getTileSize().height));
	addChild(serber, 2);

	JoyStick::getInstance()->setHero(serber);


	auto mapDate = MyTileMap::getInstance()->getMapdata();
	

	for (int i = 1; i < 30; i++) {
		WarmMonster* monster = WarmMonster::create();
		monster->SetTraget(serber);

		Vec2 randPos;

		while (true) {

			randPos = Vec2(getMyRandomInt(rng, 0, tileMap->getMapSize().width - 1),
				getMyRandomInt(rng, 0, tileMap->getMapSize().width - 1));
			if (mapDate[randPos.x + tileMap->getMapSize().width * randPos.y] == Tiles::DirtFloor) {
				randPos = tilePosToCenterPos(randPos, tileMap);
				break;
			}
		}
		vecWarm.push_back(monster);

		monster->setPosition(randPos);
		monster->setMonsterVec(&vecWarm);
		addChild(monster);
	}


	serber->setMonsterVec(&vecWarm);

	//-------------------------------------------------------------------------------
	auto Key_listener = EventListenerKeyboard::create();
	Key_listener->onKeyPressed = CC_CALLBACK_2(GameLayer::onKeyPressed, this);
	Key_listener->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(Key_listener, this);
	//-------------------------------------------------------------------------------


	//---------------------
	scheduleUpdate();
	//---------------------

	return true;
}

void GameLayer::update(float delta) {
	setViewCenter();
}

void GameLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {

	keys[keyCode] = true;

	if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {

	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {

	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S || keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {

	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D || keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {

	}
}

void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
	if (keys[keyCode])
		keys[keyCode] = false;

	if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {

	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {

	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S || keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {

	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D || keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {

	}
}

inline Vec2 GameLayer::tileMapPosition(Vec2 position) {
	int x = position.x / tileMap->getTileSize().width;
	int y = ((tileMap->getMapSize().height * tileMap->getTileSize().height) - position.y) / tileMap->getTileSize().height;
	return Vec2(x, y);
}

inline Vec2 GameLayer::getChildWinPosition(float x, float y) {

	float layerX = getPosition().x;
	float layerY = getPosition().y;

	return Vec2(x + layerX, y + layerY);
}

inline void GameLayer::setViewCenter() {
	const float maxTime = serber->getMaxTime();
	const float speed = serber->getSpeed();

	float x = serber->getPosition().x;
	float y = serber->getPosition().y;

	float layerX = getPosition().x;
	float layerY = getPosition().y;

	Vec2 heroWinPosition = getChildWinPosition(x, y);



	if (heroWinPosition.x < (winSize.width * 1 / 5)) {
		if (getActionByTag(GAMELAYER_LEFTMOVE_TAG))
			stopActionByTag(GAMELAYER_LEFTMOVE_TAG);
		if (getActionByTag(GAMELAYER_RIGHTMOVE_TAG)) {
			if (getActionByTag(GAMELAYER_RIGHTMOVE_TAG)->isDone())
				layerMoveRight();
		}
		else 
			layerMoveRight();
	}
	else if (heroWinPosition.x > (winSize.width * 4 / 5)) {
		if (getActionByTag(GAMELAYER_RIGHTMOVE_TAG))
			stopActionByTag(GAMELAYER_RIGHTMOVE_TAG);
		if (getActionByTag(GAMELAYER_LEFTMOVE_TAG)) {
			if (getActionByTag(GAMELAYER_LEFTMOVE_TAG)->isDone())
				layerMoveLeft();
		}
		else
			layerMoveLeft();
	}

	if (heroWinPosition.y < (winSize.height * 1 / 5)) {
		if (getActionByTag(GAMELAYER_DOWNMOVE_TAG))
			stopActionByTag(GAMELAYER_DOWNMOVE_TAG);
		if (getActionByTag(GAMELAYER_UPMOVE_TAG)) {
			if (getActionByTag(GAMELAYER_UPMOVE_TAG)->isDone())
				layerMoveUp();
		}
		else
			layerMoveUp();
	}
	else if (heroWinPosition.y > (winSize.height * 4 / 5)) {
		if (getActionByTag(GAMELAYER_UPMOVE_TAG))
			stopActionByTag(GAMELAYER_UPMOVE_TAG);
		if (getActionByTag(GAMELAYER_DOWNMOVE_TAG)) {
			if (getActionByTag(GAMELAYER_DOWNMOVE_TAG)->isDone())
				layerMoveDown();
		}
		else
			layerMoveDown();
	}

	//if (layerX >= 0)
	//	stopActionByTag(GAMELAYER_RIGHTMOVE_TAG);
	//else if (layerX <= -(mapSize.width - winSize.width))
	//	stopActionByTag(GAMELAYER_LEFTMOVE_TAG);

	//if (layerY >= 0)
	//	stopActionByTag(GAMELAYER_UPMOVE_TAG);
	//else if (layerY <= -(mapSize.height - winSize.height))
	//	stopActionByTag(GAMELAYER_DOWNMOVE_TAG);

	if ((layerX >= 0) || (heroWinPosition.x > (winSize.width * 2 / 5)))
		stopActionByTag(GAMELAYER_RIGHTMOVE_TAG);
	if ((layerX <= -(mapSize.width - winSize.width)) || (heroWinPosition.x < (winSize.width * 3 / 5)))
		stopActionByTag(GAMELAYER_LEFTMOVE_TAG);

	if ((layerY >= 0) || (heroWinPosition.y > (winSize.height * 2 / 5)))
		stopActionByTag(GAMELAYER_UPMOVE_TAG);
	if ((layerY <= -(mapSize.height - winSize.height)) || (heroWinPosition.y < (winSize.height * 3 / 5)))
		stopActionByTag(GAMELAYER_DOWNMOVE_TAG);


}


inline void GameLayer::layerMoveUp() {
	const float maxTime = serber->getMaxTime();
	const float speed = serber->getSpeed();
	auto move = MoveBy::create(maxTime, Vec2(0, maxTime*speed));
	move->setTag(GAMELAYER_UPMOVE_TAG);
	runAction(move);
}

inline void GameLayer::layerMoveDown() {
	const float maxTime = serber->getMaxTime();
	const float speed = serber->getSpeed();
	auto move = MoveBy::create(maxTime, Vec2(0, -maxTime*speed));
	move->setTag(GAMELAYER_DOWNMOVE_TAG);
	runAction(move);
}

inline void GameLayer::layerMoveLeft() {
	const float maxTime = serber->getMaxTime();
	const float speed = serber->getSpeed();
	auto move = MoveBy::create(maxTime, Vec2(-maxTime*speed, 0));
	move->setTag(GAMELAYER_LEFTMOVE_TAG);
	runAction(move);
}

inline void GameLayer::layerMoveRight() {
	const float maxTime = serber->getMaxTime();
	const float speed = serber->getSpeed();
	auto move = MoveBy::create(maxTime, Vec2(maxTime*speed, 0));
	move->setTag(GAMELAYER_RIGHTMOVE_TAG);
	runAction(move);
}