#pragma once
#ifndef _Serber_H_
#define _Serber_H_

#include"Hero.h"

class WarmMonster;

class Serber : public Hero {
public:

	static Serber* create();

	virtual bool init();

	void update(float delta);

	inline void updateHeroPosition(float delta);
	
	inline void updateCollide(float delta);

	inline bool updateFight(float delta);

	void fight();



	void setHeroDirVec(Vec2 vec) { heroDirVec = vec; }



	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);

	inline Vec2 tileMapPosition(Vec2 position);


	inline void initWakeSpeed();

	inline void UpStand();

	inline void DownStand();

	inline void LeftStand();

	inline void RightStand();

	inline void WakeUp();

	inline void WakeDown();

	inline void WakeLeft();

	inline void WakeRight();

	inline void UpFight();

	inline void DownFight();

	inline void LeftFight();

	inline void RightFight();





	~Serber() {}

private:

	TMXTiledMap* tileMap;
	TMXLayer* background;

	std::vector<Tiles> mapData;
	std::map<Vec2, bool> collideKeys;

	Size tileSize;
	Size mapSize;
	Size winSize;
	Size mapXXSize;

	//--------------
	Size upCollideBox;
	Size leftCollideBox;
	Size collideBox;

	Size upFightCollideBox;
	Size leftFightCollodeBox;

	Vec2 UpRectPos;
	Vec2 DownRectPos;
	Vec2 LeftRectPos;
	Vec2 RightRectPos;

	//--------------

	//-------------------
	Animate* upfight;
	Animate* downfight;
	Animate* leftfight;
	Animate* rightfight;

	

	inline void initUpStandAnimation();
	inline void initDownStandAnimation();
	inline void initLeftStandAnimation();
	inline void initRightStandAnimation();

	inline void initWakeUpAnimation();
	inline void initWakeDownAnimation();
	inline void initWakeLeftAnimation();
	inline void initWakeRightAnimation();

	inline void initUpFightAnimation();
	inline void initDownFightAnimation();
	inline void initLeftFightAnimation();
	inline void initRightFightAnimation();
};

#endif // !_Serber_H_
