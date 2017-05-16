#pragma once
#ifndef _HpStrand_H_
#define _HpStrand_H_

#include"cocos2d.h"
#include"ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;

class HpStrand : public LoadingBar {
public:
	static HpStrand* create(int maxhp)
	{
		HpStrand* hpStrand= new (std::nothrow) HpStrand(maxhp);
		if (hpStrand && hpStrand->init(maxhp))
		{
			hpStrand->autorelease();
			return hpStrand;
		}
		CC_SAFE_DELETE(hpStrand);
		return nullptr;
	}

	virtual bool init(int maxhp) {
		if (!LoadingBar::init())
			return false;

		loadTexture("UI/HealthBar2.png");
		setDirection(LoadingBar::Direction::LEFT);

		backgroundBar = Sprite::create("UI/HealthBar1.png");
		backgroundBar->setAnchorPoint(Vec2::ZERO);
		addChild(backgroundBar, -1);

		setPercent(100 * ((float)nowHp / maxHp));

		text = Text::create(StringUtils::format("%d/%d", nowHp, maxHp) , "fonts/Marker Felt.ttf", 20);
		text->setColor(Color3B::BLACK);
		//text->setAnchorPoint(Vec2::ZERO);
		addChild(text);
		text->setPosition(Vec2(backgroundBar->getTextureRect().size.width / 2, backgroundBar->getTextureRect().size.height * 2));

		return true;

	}

	void updateHp(int hp) {
		nowHp = hp;
		setPercent(100 * ((float)nowHp / maxHp));
		text->setString(StringUtils::format("%d/%d", nowHp, maxHp));
	}


public:
	Sprite* backgroundBar;
	Text* text;

	int maxHp;
	int nowHp;

	

private:
	HpStrand(int maxhp) :
		maxHp(maxhp),
		nowHp(maxhp)
	{}

};

#endif // !_HpStrand_H_

