#include"Serber.h"
#include"AI\WarmMonster.h"
#include"UI\JoyStick.h"

Serber* Serber::create() {
	Serber* sprite = new Serber();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Serber::init() {
	if (!Hero::init()) return false;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("player/player_1.plist");
	//initWithSpriteFrameName("1-1.png");

	//--------------------------
	initUpStandAnimation();
	initDownStandAnimation();
	initLeftStandAnimation();
	initRightStandAnimation();

	initWakeUpAnimation();
	initWakeDownAnimation();
	initWakeLeftAnimation();
	initWakeRightAnimation();

	initUpFightAnimation();
	initDownFightAnimation();
	initLeftFightAnimation();
	initRightFightAnimation();

	//----------------------------


	p_hero->setScale(0.4f);

	collideBox = Size(10, 10);
	upCollideBox = Size(15, 15);
	leftCollideBox = Size(15, 15);

	upFightCollideBox = Size(10, 20);
	leftFightCollodeBox = Size(20, 10);

	UpRectPos = Vec2(-upFightCollideBox.width / 2, upCollideBox.height / 2);
	DownRectPos = Vec2(-upFightCollideBox.width / 2, -upCollideBox.height / 2 - upFightCollideBox.height);
	LeftRectPos = Vec2(-leftCollideBox.width / 2 - leftFightCollodeBox.width, -leftFightCollodeBox.height / 2);
	RightRectPos = Vec2(leftCollideBox.width / 2, -leftFightCollodeBox.height / 2);



	UpStand();
	setHeroDir(HeroDir::UP);

	tileMap = MyTileMap::getInstance()->getMap();
	background = tileMap->getLayer("background");

	mapData = MyTileMap::getInstance()->getMapdata();
	collideKeys = MyTileMap::getInstance()->getTilesCollideKeys();

	tileSize = MyTileMap::getInstance()->getTileSize();
	mapSize = MyTileMap::getInstance()->getMapLayerSize();
	winSize = Director::getInstance()->getWinSize();
	mapXXSize = MyTileMap::getInstance()->getMapSize();






	//----------
	auto Key_listener = EventListenerKeyboard::create();
	Key_listener->onKeyPressed = CC_CALLBACK_2(Serber::onKeyPressed, this);
	Key_listener->onKeyReleased = CC_CALLBACK_2(Serber::onKeyReleased, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(Key_listener, this);
	//-------------




	//------------
	scheduleUpdate();
	//----------------

	return true;
}

void Serber::update(float delta) {
	//updateDirFormUI(delta);

	updateHeroPosition(delta);
	hpStrand->updateHp(nowHp);
	//setViewCenter();

}

inline void Serber::updateHeroPosition(float delta) {

	if (!updateFight(delta))
		return;

	if (heroDirVec == Vec2(0, 0)) {//stand
		//if ((keys[EventKeyboard::KeyCode::KEY_W] && keys[EventKeyboard::KeyCode::KEY_S]) ||
		//	(keys[EventKeyboard::KeyCode::KEY_A] && keys[EventKeyboard::KeyCode::KEY_D]) ||
		//	!(keys[EventKeyboard::KeyCode::KEY_W] && keys[EventKeyboard::KeyCode::KEY_S]) ||
		//	!(keys[EventKeyboard::KeyCode::KEY_A] && keys[EventKeyboard::KeyCode::KEY_D])) {
		//}

		if ((keys[EventKeyboard::KeyCode::KEY_W] && keys[EventKeyboard::KeyCode::KEY_S]) &&
			(!keys[EventKeyboard::KeyCode::KEY_A] && !keys[EventKeyboard::KeyCode::KEY_D])) {
			if (p_hero->getActionByTag(HERO_UPWAKE_TAG)) {
				p_hero->stopActionByTag(HERO_UPWAKE_TAG);
				stopActionByTag(HERO_UPMOVE_TAG);
			}
			if (p_hero->getActionByTag(HERO_DOWNWAKE_TAG)) {
				p_hero->stopActionByTag(HERO_DOWNWAKE_TAG);
				stopActionByTag(HERO_DOWNMOVE_TAG);
			}
		}
		else if ((keys[EventKeyboard::KeyCode::KEY_A] && keys[EventKeyboard::KeyCode::KEY_D]) && 
			(!keys[EventKeyboard::KeyCode::KEY_W] && !keys[EventKeyboard::KeyCode::KEY_S])) {
			if (p_hero->getActionByTag(HERO_LEFTWAKE_TAG)) {
				p_hero->stopActionByTag(HERO_LEFTWAKE_TAG);
				stopActionByTag(HERO_LEFTMOVE_TAG);
			}
			if (p_hero->getActionByTag(HERO_RIGHTWAKE_TAG)) {
				p_hero->stopActionByTag(HERO_RIGHTWAKE_TAG);
				stopActionByTag(HERO_RIGHTMOVE_TAG);
			}
		}

		if (heroDir == HeroDir::UP) {
			if (p_hero->getActionByTag(HERO_UPSTAND_TAG)) {
				if (!p_hero->getActionByTag(HERO_UPSTAND_TAG)->isDone())
					UpStand();
			}
			else
				UpStand();
		}
		else if (heroDir == HeroDir::DOWN) {
			if (p_hero->getActionByTag(HERO_DOWNSTAND_TAG)) {
				if (p_hero->getActionByTag(HERO_DOWNSTAND_TAG)->isDone())
					DownStand();
			}
			else
				DownStand();
		}
		else if (heroDir == HeroDir::LEFT) {
			if (p_hero->getActionByTag(HERO_LEFTSTAND_TAG)) {
				if (p_hero->getActionByTag(HERO_LEFTSTAND_TAG)->isDone())
					LeftStand();
			}
			else
				LeftStand();
		}
		else if (heroDir == HeroDir::RIGHT) {
			if (p_hero->getActionByTag(HERO_RIGHTSTAND_TAG)) {
				if (p_hero->getActionByTag(HERO_RIGHTSTAND_TAG)->isDone())
					RightStand();
			}
			else
				RightStand();
		}
	}
	else if (heroDirVec == Vec2(0, 1)) {//up
		if (p_hero->getActionByTag(HERO_DOWNWAKE_TAG)) {
			p_hero->stopActionByTag(HERO_DOWNWAKE_TAG);
			stopActionByTag(HERO_DOWNMOVE_TAG);
		}
		if (p_hero->getActionByTag(HERO_LEFTWAKE_TAG)) {
			p_hero->stopActionByTag(HERO_LEFTWAKE_TAG);
			stopActionByTag(HERO_LEFTMOVE_TAG);
		}
		if (p_hero->getActionByTag(HERO_RIGHTWAKE_TAG)) {
			p_hero->stopActionByTag(HERO_RIGHTWAKE_TAG);
			stopActionByTag(HERO_RIGHTMOVE_TAG);
		}

		if (p_hero->getActionByTag(HERO_UPWAKE_TAG)) {
			if (p_hero->getActionByTag(HERO_UPWAKE_TAG)->isDone())
				WakeUp();
		}
		else
			WakeUp();

		updateCollide(delta);
	}
	else if (heroDirVec == Vec2(0, -1)) {//down
		if (p_hero->getActionByTag(HERO_UPWAKE_TAG)) {
			p_hero->stopActionByTag(HERO_UPWAKE_TAG);
			stopActionByTag(HERO_UPMOVE_TAG);
		}
		if (p_hero->getActionByTag(HERO_LEFTWAKE_TAG)) {
			p_hero->stopActionByTag(HERO_LEFTWAKE_TAG);
			stopActionByTag(HERO_LEFTMOVE_TAG);
		}
		if (p_hero->getActionByTag(HERO_RIGHTWAKE_TAG)) {
			p_hero->stopActionByTag(HERO_RIGHTWAKE_TAG);
			stopActionByTag(HERO_RIGHTMOVE_TAG);
		}

		if (p_hero->getActionByTag(HERO_DOWNWAKE_TAG)) {
			if (p_hero->getActionByTag(HERO_DOWNWAKE_TAG)->isDone())
				WakeDown();
		}
		else
			WakeDown();

		updateCollide(delta);
	}
	else if (heroDirVec == Vec2(-1, 0)) {//left
		if (p_hero->getActionByTag(HERO_UPWAKE_TAG)) {
			p_hero->stopActionByTag(HERO_UPWAKE_TAG);
			stopActionByTag(HERO_UPMOVE_TAG);
		}
		if (p_hero->getActionByTag(HERO_DOWNWAKE_TAG)) {
			p_hero->stopActionByTag(HERO_DOWNWAKE_TAG);
			stopActionByTag(HERO_DOWNMOVE_TAG);
		}
		if (p_hero->getActionByTag(HERO_RIGHTWAKE_TAG)) {
			p_hero->stopActionByTag(HERO_RIGHTWAKE_TAG);
			stopActionByTag(HERO_RIGHTMOVE_TAG);
		}

		if (p_hero->getActionByTag(HERO_LEFTWAKE_TAG)) {
			if (p_hero->getActionByTag(HERO_LEFTWAKE_TAG)->isDone())
				WakeLeft();
		}
		else
			WakeLeft();

		updateCollide(delta);
	}
	else if (heroDirVec == Vec2(1, 0)) {//right
		if (p_hero->getActionByTag(HERO_UPWAKE_TAG)) {
			p_hero->stopActionByTag(HERO_UPWAKE_TAG);
			stopActionByTag(HERO_UPMOVE_TAG);
		}
		if (p_hero->getActionByTag(HERO_DOWNWAKE_TAG)) {
			p_hero->stopActionByTag(HERO_DOWNWAKE_TAG);
			stopActionByTag(HERO_DOWNMOVE_TAG);
		}
		if (p_hero->getActionByTag(HERO_LEFTWAKE_TAG)) {
			p_hero->stopActionByTag(HERO_LEFTWAKE_TAG);
			stopActionByTag(HERO_LEFTMOVE_TAG);
		}

		if (p_hero->getActionByTag(HERO_RIGHTWAKE_TAG)) {
			if (p_hero->getActionByTag(HERO_RIGHTWAKE_TAG)->isDone())
				WakeRight();
		}
		else
			WakeRight();

		updateCollide(delta);
	}
	else if (heroDirVec == Vec2(-1, 1)) {//up_left

		if (heroDir == HeroDir::UP) {
			if (p_hero->getActionByTag(HERO_LEFTWAKE_TAG)) {
				p_hero->stopActionByTag(HERO_LEFTWAKE_TAG);
				stopActionByTag(HERO_LEFTMOVE_TAG);
			}

			if (p_hero->getActionByTag(HERO_UPWAKE_TAG)) {
				if (p_hero->getActionByTag(HERO_UPWAKE_TAG)->isDone())
					WakeUp();
			}
			else
				WakeUp();
		}
		else if (heroDir == HeroDir::LEFT) {
			if (p_hero->getActionByTag(HERO_UPWAKE_TAG)) {
				p_hero->stopActionByTag(HERO_UPWAKE_TAG);
				stopActionByTag(HERO_UPMOVE_TAG);
			}

			if (p_hero->getActionByTag(HERO_LEFTWAKE_TAG)) {
				if (p_hero->getActionByTag(HERO_LEFTWAKE_TAG)->isDone())
					WakeLeft();
			}
			else
				WakeLeft();
		}
		updateCollide(delta);
	}
	else if (heroDirVec == Vec2(1, 1)) {//up_right

		if (heroDir == HeroDir::UP) {
			if (p_hero->getActionByTag(HERO_RIGHTWAKE_TAG)) {
				p_hero->stopActionByTag(HERO_RIGHTWAKE_TAG);
				stopActionByTag(HERO_RIGHTMOVE_TAG);
			}

			if (p_hero->getActionByTag(HERO_UPWAKE_TAG)) {
				if (p_hero->getActionByTag(HERO_UPWAKE_TAG)->isDone())
					WakeUp();
			}
			else
				WakeUp();
		}
		else if (heroDir == HeroDir::RIGHT) {
			if (p_hero->getActionByTag(HERO_UPWAKE_TAG)) {
				p_hero->stopActionByTag(HERO_UPWAKE_TAG);
				stopActionByTag(HERO_UPMOVE_TAG);
			}

			if (p_hero->getActionByTag(HERO_RIGHTWAKE_TAG)) {
				if (p_hero->getActionByTag(HERO_RIGHTWAKE_TAG)->isDone())
					WakeRight();
			}
			else
				WakeRight();
		}
		updateCollide(delta);
	}
	else if (heroDirVec == Vec2(-1, -1)) {//down_left

		if (heroDir == HeroDir::DOWN) {
			if (p_hero->getActionByTag(HERO_LEFTWAKE_TAG)) {
				p_hero->stopActionByTag(HERO_LEFTWAKE_TAG);
				stopActionByTag(HERO_LEFTMOVE_TAG);
			}

			if (p_hero->getActionByTag(HERO_DOWNWAKE_TAG)) {
				if (p_hero->getActionByTag(HERO_DOWNWAKE_TAG)->isDone())
					WakeDown();
			}
			else
				WakeDown();
		}
		else if (heroDir == HeroDir::LEFT) {
			if (p_hero->getActionByTag(HERO_DOWNWAKE_TAG)) {
				p_hero->stopActionByTag(HERO_DOWNWAKE_TAG);
				stopActionByTag(HERO_DOWNMOVE_TAG);
			}

			if (p_hero->getActionByTag(HERO_LEFTWAKE_TAG)) {
				if (p_hero->getActionByTag(HERO_LEFTWAKE_TAG)->isDone())
					WakeLeft();
			}
			else
				WakeLeft();
		}
		updateCollide(delta);
	}
	else if (heroDirVec == Vec2(1, -1)) {//down_right

		if (heroDir == HeroDir::DOWN) {
			if (p_hero->getActionByTag(HERO_RIGHTWAKE_TAG)) {
				p_hero->stopActionByTag(HERO_RIGHTWAKE_TAG);
				stopActionByTag(HERO_RIGHTMOVE_TAG);
			}

			if (p_hero->getActionByTag(HERO_DOWNWAKE_TAG)) {
				if (p_hero->getActionByTag(HERO_DOWNWAKE_TAG)->isDone())
					WakeDown();
			}
			else
				WakeDown();
		}
		else if (heroDir == HeroDir::RIGHT) {
			if (p_hero->getActionByTag(HERO_DOWNWAKE_TAG)) {
				p_hero->stopActionByTag(HERO_DOWNWAKE_TAG);
				stopActionByTag(HERO_DOWNMOVE_TAG);
			}

			if (p_hero->getActionByTag(HERO_RIGHTWAKE_TAG)) {
				if (p_hero->getActionByTag(HERO_RIGHTWAKE_TAG)->isDone())
					WakeRight();
			}
			else
				WakeRight();
		}
		updateCollide(delta);
	}
}

inline void Serber::updateCollide(float delta) {
	float x = getPosition().x;
	float y = getPosition().y;
	Vec2 position1 = Vec2(x, y);
	Vec2 position2 = Vec2(x, y);
	Vec2 position3 = Vec2(x, y);

	switch (heroDir)
	{
	case HeroDir::UP:
		position1 = tileMapPosition(Vec2(x, y + upCollideBox.height / 2 + speed*delta));
		position2 = tileMapPosition(Vec2(x - upCollideBox.width / 2, y + speed*delta + upCollideBox.height / 2));
		position3 = tileMapPosition(Vec2(x + upCollideBox.width / 2, y + speed*delta + upCollideBox.height / 2));
		if (collideKeys[Vec2(position1.x, position1.y)]) {
			//stopActionByTag(HERO_UPMOVE_TAG);
			stopActionsByFlags(HERO_MOVE_FLAG);
			stopActionByTag(HERP_BEHURTMOVE_TAG);
		}
		else if (collideKeys[Vec2(position2.x, position2.y)]) {
			//stopActionByTag(HERO_UPMOVE_TAG);
			stopActionsByFlags(HERO_MOVE_FLAG);
			stopActionByTag(HERP_BEHURTMOVE_TAG);
		}
		else if (collideKeys[Vec2(position3.x, position3.y)]) {
			//stopActionByTag(HERO_UPMOVE_TAG);
			stopActionsByFlags(HERO_MOVE_FLAG);
			stopActionByTag(HERP_BEHURTMOVE_TAG);
		}
		break;
	case HeroDir::DOWN:
		position1 = tileMapPosition(Vec2(x, y - upCollideBox.height / 2 - speed*delta));
		position2 = tileMapPosition(Vec2(x - upCollideBox.width / 2, y - speed*delta - upCollideBox.height / 2));
		position3 = tileMapPosition(Vec2(x + upCollideBox.width / 2, y - speed*delta - upCollideBox.height / 2));
		if (collideKeys[Vec2(position1.x, position1.y)]) {
			//stopActionByTag(HERO_DOWNMOVE_TAG);
			stopActionsByFlags(HERO_MOVE_FLAG);
			stopActionByTag(HERP_BEHURTMOVE_TAG);
		}
		else if (collideKeys[Vec2(position2.x, position2.y)]) {
			//stopActionByTag(HERO_DOWNMOVE_TAG);
			stopActionsByFlags(HERO_MOVE_FLAG);
			stopActionByTag(HERP_BEHURTMOVE_TAG);
		}
		else if (collideKeys[Vec2(position3.x, position3.y)]) {
			//stopActionByTag(HERO_DOWNMOVE_TAG);
			stopActionsByFlags(HERO_MOVE_FLAG);
			stopActionByTag(HERP_BEHURTMOVE_TAG);
		}
		break;
	case HeroDir::LEFT:
		position1 = tileMapPosition(Vec2(x - leftCollideBox.width / 2 - speed*delta, y));
		position2 = tileMapPosition(Vec2(x - speed*delta - leftCollideBox.width / 2, y + leftCollideBox.height / 2));
		position3 = tileMapPosition(Vec2(x - speed*delta - leftCollideBox.width / 2, y - leftCollideBox.height / 2));
		if (collideKeys[Vec2(position1.x, position1.y)]) {
			//stopActionByTag(HERO_LEFTMOVE_TAG);
			stopActionsByFlags(HERO_MOVE_FLAG);
			stopActionByTag(HERP_BEHURTMOVE_TAG);
		}
		else if (collideKeys[Vec2(position2.x, position2.y)]) {
			//stopActionByTag(HERO_LEFTMOVE_TAG);
			stopActionsByFlags(HERO_MOVE_FLAG);
			stopActionByTag(HERP_BEHURTMOVE_TAG);
		}
		else if (collideKeys[Vec2(position3.x, position3.y)]) {
			//stopActionByTag(HERO_LEFTMOVE_TAG);
			stopActionsByFlags(HERO_MOVE_FLAG);
			stopActionByTag(HERP_BEHURTMOVE_TAG);
		}
		break;
	case HeroDir::RIGHT:
		position1 = tileMapPosition(Vec2(x + leftCollideBox.width / 2 +speed*delta, y));
		position2 = tileMapPosition(Vec2(x - speed*delta + leftCollideBox.width / 2, y + leftCollideBox.height / 2));
		position3 = tileMapPosition(Vec2(x - speed*delta + leftCollideBox.width / 2, y - leftCollideBox.height / 2));
		if (collideKeys[Vec2(position1.x, position1.y)]) {
			//stopActionByTag(HERO_RIGHTMOVE_TAG);
			stopActionsByFlags(HERO_MOVE_FLAG);
			stopActionByTag(HERP_BEHURTMOVE_TAG);
		}
		else if (collideKeys[Vec2(position2.x, position2.y)]) {
			//stopActionByTag(HERO_RIGHTMOVE_TAG);
			stopActionsByFlags(HERO_MOVE_FLAG);
			stopActionByTag(HERP_BEHURTMOVE_TAG);
		}
		else if (collideKeys[Vec2(position3.x, position3.y)]) {
			//stopActionByTag(HERO_RIGHTMOVE_TAG);
			stopActionsByFlags(HERO_MOVE_FLAG);
			stopActionByTag(HERP_BEHURTMOVE_TAG);
		}
		break;
	default:
		break;
	}
}

inline bool Serber::updateFight(float delta) {
	Rect upFightRect;
	Rect leftFightRect;
	Vec2 heroPos = getPosition();


	if (p_hero->getActionByTag(HERO_UPFIGHT_TAG)) {
		if (!p_hero->getActionByTag(HERO_UPFIGHT_TAG)->isDone()) {
			CCLOG("WarmPatrol Execute%d", upfight->getCurrentFrameIndex());
			if (upfight->getCurrentFrameIndex() >= 1 && upfight->getCurrentFrameIndex() <= 5) {

				for (auto monster : *p_vecWarm) {
					if (Rect(monster->getPosition(), monster->getMonsterBoundingBox().size).intersectsRect(
						Rect(Vec2(heroPos.x - p_hero->getBoundingBox().size.width / 2, 
							heroPos.y + p_hero->getBoundingBox().size.height / 4),
							Size(p_hero->getBoundingBox().size.width, p_hero->getBoundingBox().size.height * 2 / 3)))) {
						if (monster->beHurt(mAttack))
							if (monster->isDie())
								return true;
					}
				}
			}
			return false;
		}
	}
	if (p_hero->getActionByTag(HERO_DOWNFIGHT_TAG)) {
		if (!p_hero->getActionByTag(HERO_DOWNFIGHT_TAG)->isDone()) {
			if (downfight->getCurrentFrameIndex() >= 1 && downfight->getCurrentFrameIndex() <= 5) {

				for (auto monster : *p_vecWarm) {
					if (Rect(monster->getPosition(), monster->getMonsterBoundingBox().size).intersectsRect(
						Rect(Vec2(heroPos.x - p_hero->getBoundingBox().size.width / 2,
							heroPos.y - p_hero->getBoundingBox().size.height * 2 / 3 - p_hero->getBoundingBox().size.height / 4),
							Size(p_hero->getBoundingBox().size.width, p_hero->getBoundingBox().size.height * 2 / 3)))) {
						if (monster->beHurt(mAttack))
							if (monster->isDie())
								return true;
					}
				}
			}
			return false;
		}
	}
	if (p_hero->getActionByTag(HERO_LEFTFIGHT_TAG)) {
		if (!p_hero->getActionByTag(HERO_LEFTFIGHT_TAG)->isDone()) {
			if (leftfight->getCurrentFrameIndex() >= 1 && leftfight->getCurrentFrameIndex() <= 5) {

				for (auto monster : *p_vecWarm) {
					if (Rect(monster->getPosition(), monster->getMonsterBoundingBox().size).intersectsRect(
						Rect(Vec2(heroPos.x - p_hero->getBoundingBox().size.width * 2 / 3 - p_hero->getBoundingBox().size.width / 4,
							heroPos.y - p_hero->getBoundingBox().size.height / 2),
							Size(p_hero->getBoundingBox().size.width * 2 / 3, p_hero->getBoundingBox().size.height)))) {
						if (monster->beHurt(mAttack))
							if (monster->isDie())
								return true;
					}
				}
			}
			return false;
		}
	}
	if (p_hero->getActionByTag(HERO_RIGHTFIGHT_TAG)) {
		if (!p_hero->getActionByTag(HERO_RIGHTFIGHT_TAG)->isDone()) {
			if (rightfight->getCurrentFrameIndex() >= 1 && rightfight->getCurrentFrameIndex() <= 5) {

				for (auto monster : *p_vecWarm) {
					if (Rect(monster->getPosition(), monster->getMonsterBoundingBox().size).intersectsRect(
						Rect(Vec2(heroPos.x + p_hero->getBoundingBox().size.width/4,
							heroPos.y - p_hero->getBoundingBox().size.height / 2),
							Size(p_hero->getBoundingBox().size.width * 2 / 3, p_hero->getBoundingBox().size.height)))) {
						if (monster->beHurt(mAttack))
							if (monster->isDie())
								return true;
					}
				}
			}
			return false;
		}
	}
	return true;
}

void Serber::fight() {
	stopAllActions();
	if (heroDir == HeroDir::UP) {
		if (p_hero->getActionByTag(HERO_UPFIGHT_TAG)) {
			if (p_hero->getActionByTag(HERO_UPFIGHT_TAG)->isDone())
				UpFight();
		}
		else
			UpFight();
	}
	else if (heroDir == HeroDir::DOWN) {
		if (p_hero->getActionByTag(HERO_DOWNFIGHT_TAG)) {
			if (p_hero->getActionByTag(HERO_DOWNFIGHT_TAG)->isDone())
				DownFight();
		}
		else
			DownFight();
	}
	else if (heroDir == HeroDir::LEFT) {
		if (p_hero->getActionByTag(HERO_LEFTFIGHT_TAG)) {
			if (p_hero->getActionByTag(HERO_LEFTFIGHT_TAG)->isDone())
				LeftFight();
		}
		else
			LeftFight();
	}
	else if (heroDir == HeroDir::RIGHT) {
		if (p_hero->getActionByTag(HERO_RIGHTFIGHT_TAG)) {
			if (p_hero->getActionByTag(HERO_RIGHTFIGHT_TAG)->isDone())
				RightFight();
		}
		else
			RightFight();
	}
}

void Serber::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {

	keys[keyCode] = true;

	p_hero->stopActionsByFlags(HERO_STAND_FLAG);

	if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		heroDirVec += Vec2(-1, 0);
		setHeroDir(HeroDir::LEFT);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		heroDirVec += Vec2(0, 1);
		setHeroDir(HeroDir::UP);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S || keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		heroDirVec += Vec2(0, -1);
		setHeroDir(HeroDir::DOWN);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D || keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		heroDirVec += Vec2(1, 0);
		setHeroDir(HeroDir::RIGHT);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_J) {
		fight();
	}
}

void Serber::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {

	if (keys[keyCode])
		keys[keyCode] = false;

	p_hero->stopActionsByFlags(HERO_STAND_FLAG);


	if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		heroDirVec += Vec2(1, 0);
		p_hero->stopActionByTag(HERO_LEFTWAKE_TAG);
		stopActionByTag(HERO_LEFTMOVE_TAG);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		heroDirVec += Vec2(0, -1);
		p_hero->stopActionByTag(HERO_UPWAKE_TAG);
		stopActionByTag(HERO_UPMOVE_TAG);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S || keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		heroDirVec += Vec2(0, 1);
		p_hero->stopActionByTag(HERO_DOWNWAKE_TAG);
		stopActionByTag(HERO_DOWNMOVE_TAG);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D || keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		heroDirVec += Vec2(-1, 0);
		p_hero->stopActionByTag(HERO_RIGHTWAKE_TAG);
		stopActionByTag(HERO_RIGHTMOVE_TAG);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_J) {

	}
}

inline Vec2 Serber::tileMapPosition(Vec2 position) {
	int x = position.x / tileMap->getTileSize().width;
	int y = ((tileMap->getMapSize().height * tileMap->getTileSize().height) - position.y) / tileMap->getTileSize().height;
	return Vec2(x, y);
}

inline void Serber::UpStand() {
	auto upstand = Animate::create(AnimationCache::getInstance()->getAnimation("serber_UpStand"));
	auto repeatanimate = RepeatForever::create(upstand);

	repeatanimate->setFlags(HERO_STAND_FLAG);
	repeatanimate->setTag(HERO_UPSTAND_TAG);

	p_hero->runAction(repeatanimate);
}

inline void Serber::DownStand() {
	auto downstand = Animate::create(AnimationCache::getInstance()->getAnimation("serber_DownStand"));
	auto repeatanimate = RepeatForever::create(downstand);
	repeatanimate->setTag(HERO_DOWNSTAND_TAG);

	repeatanimate->setFlags(HERO_STAND_FLAG);
	p_hero->runAction(repeatanimate);
}

inline void Serber::LeftStand() {
	auto leftstand = Animate::create(AnimationCache::getInstance()->getAnimation("serber_LeftStand"));
	auto repeatanimate = RepeatForever::create(leftstand);

	repeatanimate->setFlags(HERO_STAND_FLAG);
	repeatanimate->setTag(HERO_LEFTSTAND_TAG);

	p_hero->runAction(repeatanimate);
}

inline void Serber::RightStand() {
	auto rightstand = Animate::create(AnimationCache::getInstance()->getAnimation("serber_RightStand"));
	auto repeatanimate = RepeatForever::create(rightstand);

	repeatanimate->setFlags(HERO_STAND_FLAG);
	repeatanimate->setTag(HERO_RIGHTSTAND_TAG);

	p_hero->runAction(repeatanimate);
}

inline void Serber::initWakeSpeed() {
	AnimationCache::getInstance()->getAnimation("serber_wakeUp")->setDelayPerUnit((1.0f / 6.0f)*(normalSpeed / speed));
	AnimationCache::getInstance()->getAnimation("serber_wakeDown")->setDelayPerUnit((1.0f / 6.0f)*(normalSpeed / speed));
	AnimationCache::getInstance()->getAnimation("serber_wakeLeft")->setDelayPerUnit((1.0f / 6.0f)*(normalSpeed / speed));
	AnimationCache::getInstance()->getAnimation("serber_wakeRight")->setDelayPerUnit((1.0f / 6.0f)*(normalSpeed / speed));
}

inline void Serber::WakeUp() {
	auto wakeup = Animate::create(AnimationCache::getInstance()->getAnimation("serber_wakeUp"));
	//wakeup->setDelayPerUnit((1.0f / 6.0f)*(normalSpeed / speed));
	auto repeatanimate = RepeatForever::create(wakeup);
	auto move = MoveBy::create(maxTime, Vec2(0, maxTime*speed));
	move->setFlags(HERO_WAKE_FLAG);
	repeatanimate->setTag(HERO_UPWAKE_TAG);
	move->setTag(HERO_UPMOVE_TAG);
	repeatanimate->setFlags(HERO_WAKE_FLAG);

	p_hero->runAction(repeatanimate);
	runAction(move);
}

inline void Serber::WakeDown() {
	auto wakedown = Animate::create(AnimationCache::getInstance()->getAnimation("serber_wakeDown"));
	auto repeatanimate = RepeatForever::create(wakedown);
	auto move = MoveBy::create(maxTime, Vec2(0, -maxTime*speed));
	move->setFlags(HERO_WAKE_FLAG);
	repeatanimate->setTag(HERO_DOWNWAKE_TAG);
	move->setTag(HERO_DOWNMOVE_TAG);
	repeatanimate->setFlags(HERO_WAKE_FLAG);

	p_hero->runAction(repeatanimate);
	runAction(move);
}

inline void Serber::WakeLeft() {

	auto wakeleft = Animate::create(AnimationCache::getInstance()->getAnimation("serber_wakeLeft"));
	auto repeatanimate = RepeatForever::create(wakeleft);
	auto move = MoveBy::create(maxTime, Vec2(-maxTime*speed, 0));
	move->setFlags(HERO_WAKE_FLAG);
	repeatanimate->setTag(HERO_LEFTWAKE_TAG);
	move->setTag(HERO_LEFTMOVE_TAG);
	repeatanimate->setFlags(HERO_WAKE_FLAG);

	p_hero->runAction(repeatanimate);
	runAction(move);
}

inline void Serber::WakeRight() {
	auto wakeright = Animate::create(AnimationCache::getInstance()->getAnimation("serber_wakeRight"));
	auto repeatanimate = RepeatForever::create(wakeright);
	auto move = MoveBy::create(maxTime, Vec2(maxTime*speed, 0));
	move->setFlags(HERO_WAKE_FLAG);
	repeatanimate->setTag(HERO_RIGHTWAKE_TAG);
	move->setTag(HERO_RIGHTMOVE_TAG);
	repeatanimate->setFlags(HERO_WAKE_FLAG);

	p_hero->runAction(repeatanimate);
	runAction(move);
}

inline void Serber::UpFight() {
	upfight = Animate::create(AnimationCache::getInstance()->getAnimation("serber_UpFight"));
	auto repeatanimate = EaseBackOut::create(upfight);
	upfight->setFlags(HERO_FIGHT_FLAG);
	upfight->setTag(HERO_UPFIGHT_TAG);

	p_hero->runAction(upfight);
}

inline void Serber::DownFight() {
	downfight = Animate::create(AnimationCache::getInstance()->getAnimation("serber_DownFight"));
	auto repeatanimate = EaseBackOut::create(downfight);
	downfight->setFlags(HERO_FIGHT_FLAG);
	downfight->setTag(HERO_DOWNFIGHT_TAG);

	p_hero->runAction(downfight);
}

inline void Serber::LeftFight() {
	leftfight = Animate::create(AnimationCache::getInstance()->getAnimation("serber_LeftFight"));
	auto repeatanimate = EaseBackOut::create(leftfight);
	leftfight->setFlags(HERO_FIGHT_FLAG);
	leftfight->setTag(HERO_LEFTFIGHT_TAG);

	p_hero->runAction(leftfight);
}

inline void Serber::RightFight() {
	rightfight = Animate::create(AnimationCache::getInstance()->getAnimation("serber_RightFight"));
	auto repeatanimate = EaseBackOut::create(rightfight);
	rightfight->setFlags(HERO_FIGHT_FLAG);
	rightfight->setTag(HERO_RIGHTFIGHT_TAG);

	p_hero->runAction(rightfight);
}

inline void Serber::initUpStandAnimation() {
	auto serber_UpStand = Animation::create();
	for (int i = 1; i < 7; i++)
		serber_UpStand->addSpriteFrame(SpriteFrameCache::getInstance()->
			getSpriteFrameByName(StringUtils::format("1-%d.png", i)));
	serber_UpStand->setDelayPerUnit(1.0f / 6.0f);
	serber_UpStand->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(serber_UpStand, "serber_UpStand");
}

inline void Serber::initDownStandAnimation() {
	auto serber_DownStand = Animation::create();
	for (int i = 19; i < 25; i++)
		serber_DownStand->addSpriteFrame(SpriteFrameCache::getInstance()->
			getSpriteFrameByName(StringUtils::format("1-%d.png", i)));
	serber_DownStand->setDelayPerUnit(1.0f / 6.0f);
	serber_DownStand->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(serber_DownStand, "serber_DownStand");
}

inline void Serber::initLeftStandAnimation() {
	auto serber_LeftStand = Animation::create();
	for (int i = 25; i < 31; i++)
		serber_LeftStand->addSpriteFrame(SpriteFrameCache::getInstance()->
			getSpriteFrameByName(StringUtils::format("1-%d.png", i)));
	serber_LeftStand->setDelayPerUnit(1.0f / 6.0f);
	serber_LeftStand->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(serber_LeftStand, "serber_LeftStand");
}

inline void Serber::initRightStandAnimation() {
	auto serber_RightStand = Animation::create();
	for (int i = 7; i < 13; i++)
		serber_RightStand->addSpriteFrame(SpriteFrameCache::getInstance()->
			getSpriteFrameByName(StringUtils::format("1-%d.png", i)));
	serber_RightStand->setDelayPerUnit(1.0f / 6.0f);
	serber_RightStand->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(serber_RightStand, "serber_RightStand");
}

inline void Serber::initWakeUpAnimation() {
	auto serber_WakeUp = Animation::create();
	for (int i = 1; i < 7; i++)
		serber_WakeUp->addSpriteFrame(SpriteFrameCache::getInstance()->
			getSpriteFrameByName(StringUtils::format("2-%d.png", i)));
	serber_WakeUp->setDelayPerUnit((1.0f / 6.0f)*(normalSpeed / speed));
	serber_WakeUp->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(serber_WakeUp, "serber_wakeUp");
}

inline void Serber::initWakeDownAnimation() {
	auto serber_WakeDown = Animation::create();
	for (int i = 19; i < 25; i++)
		serber_WakeDown->addSpriteFrame(SpriteFrameCache::getInstance()->
			getSpriteFrameByName(StringUtils::format("2-%d.png", i)));
	serber_WakeDown->setDelayPerUnit((1.0f / 6.0f)*(normalSpeed / speed));
	serber_WakeDown->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(serber_WakeDown, "serber_wakeDown");
}

inline void Serber::initWakeLeftAnimation() {
	auto serber_WakeLeft = Animation::create();
	for (int i = 25; i < 31; i++)
		serber_WakeLeft->addSpriteFrame(SpriteFrameCache::getInstance()->
			getSpriteFrameByName(StringUtils::format("2-%d.png", i)));
	serber_WakeLeft->setDelayPerUnit((1.0f / 6.0f)*(normalSpeed / speed));
	serber_WakeLeft->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(serber_WakeLeft, "serber_wakeLeft");
}

inline void Serber::initWakeRightAnimation() {
	auto serber_WakeRight = Animation::create();
	for (int i = 7; i < 13; i++)
		serber_WakeRight->addSpriteFrame(SpriteFrameCache::getInstance()->
			getSpriteFrameByName(StringUtils::format("2-%d.png", i)));
	serber_WakeRight->setDelayPerUnit((1.0f / 6.0f)*(normalSpeed / speed));
	serber_WakeRight->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(serber_WakeRight, "serber_wakeRight");
}

inline void Serber::initUpFightAnimation() {
	auto serber_UpFight = Animation::create();
	for (int i = 1; i < 9; i++)
		serber_UpFight->addSpriteFrame(SpriteFrameCache::getInstance()->
			getSpriteFrameByName(StringUtils::format("3-%d.png", i)));
	serber_UpFight->setDelayPerUnit(1.0f / 10.0f);
	serber_UpFight->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(serber_UpFight, "serber_UpFight");
}

inline void Serber::initDownFightAnimation() {
	auto serber_DownFight = Animation::create();
	for (int i = 25; i < 33; i++)
		serber_DownFight->addSpriteFrame(SpriteFrameCache::getInstance()->
			getSpriteFrameByName(StringUtils::format("3-%d.png", i)));
	serber_DownFight->setDelayPerUnit(1.0f / 10.0f);
	serber_DownFight->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(serber_DownFight, "serber_DownFight");
}

inline void Serber::initLeftFightAnimation() {
	auto serber_LeftFight = Animation::create();
	for (int i = 41; i < 49; i++)
		serber_LeftFight->addSpriteFrame(SpriteFrameCache::getInstance()->
			getSpriteFrameByName(StringUtils::format("3-%d.png", i)));
	serber_LeftFight->setDelayPerUnit(1.0f / 10.0f);
	serber_LeftFight->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(serber_LeftFight, "serber_LeftFight");
}

inline void Serber::initRightFightAnimation() {
	auto serber_RightFight = Animation::create();
	for (int i = 9; i < 17; i++)
		serber_RightFight->addSpriteFrame(SpriteFrameCache::getInstance()->
			getSpriteFrameByName(StringUtils::format("3-%d.png", i)));
	serber_RightFight->setDelayPerUnit(1.0f / 10.0f);
	serber_RightFight->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(serber_RightFight, "serber_RightFight");
}