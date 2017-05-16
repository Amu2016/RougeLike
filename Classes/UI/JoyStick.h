#pragma once
#ifndef _JoyStick_H_
#define _JoyStick_H_

#include "cocos2d.h"
#include <cmath>
#include"stdafx.h"
using namespace cocos2d;

class Serber;

class JoyStick : public Sprite
{
public:

	static JoyStick* getInstance() {
		static JoyStick* joyStick = JoyStick::create();
		return joyStick;
	}

	HeroMoveDir getHeroDir();

	void setHero(Serber* h) { hero = h; }

private:
	//static JoyStick* joyStick;

	Serber* hero;

	static JoyStick* create();

	JoyStick() {}
	virtual ~JoyStick(void);

	//����ҡ�˾���
	Sprite* centerPoint;


	//����ҡ���ƶ��¼���Ƶ��
	int yhCount = 0;
	//�����̰뾶
	float rRange;
	//����ҡ���뷽����ԭ�����ĺ�����
	float vx;
	//����ҡ���뷽����ԭ������������
	float vy;
	//��ȡ��������
	Rect getRect();
	//�жϴ�����λ�õķ���
	bool containsTouchLocation(Touch* touch);
	//��ʼ��ҡ��λ�ü���ȡ�뾶
	void calCenter();
	//��������ҡ��������ͼ�����귽��
	void calCenterPosition(float tx, float ty);

	//ÿ�ξ������ʱ���ص�
	virtual void onEnter();
	//ÿ�ξ����˳�ʱ���ص�
	virtual void onExit();
	//��ʼ���㴥���¼��Ĵ�����
	bool onTouchBegan(Touch* touch, Event* event);
	//���㴥���ƶ��¼��Ĵ�����
	void onTouchMoved(Touch* touch, Event* event);
	//���㴥�ؽ����¼��Ĵ�����
	void onTouchEnded(Touch* touch, Event* event);
};


#endif
