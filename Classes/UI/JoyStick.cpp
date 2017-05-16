#include "JoyStick.h"
#include"Hero\Serber.h"

HeroMoveDir JoyStick::getHeroDir() {
	auto angle = atan2(vy, vx) * 180.0f / PI;

	CCLOG("JoyStick::::%f", atan2(vy, vx) * 180.0f / PI);

	if (angle <= 135.0f && angle >= 45.0f)
		return HeroMoveDir::UPMOVE;
	else if (angle >= -135.0f && angle <= -45.0f)
		return HeroMoveDir::DOWNMOVE;
	else if (angle >= 135.0f || angle <= -135.0f)
		return HeroMoveDir::LEFTMOVE;
	else
		return HeroMoveDir::RIGHTMOVE;
}



JoyStick* JoyStick::create()
{
	JoyStick *bnjs = new JoyStick();
	if (bnjs && bnjs->initWithSpriteFrameName("JoyStick-base.png"))
	{
		bnjs->autorelease();
		//��ʼ��ҡ��x����
		bnjs->vx = 0;
		//��ʼ��ҡ��y����
		bnjs->vy = 0;
		bnjs->centerPoint = Sprite::createWithSpriteFrameName("JoyStick-thumb.png");
		bnjs->addChild(bnjs->centerPoint, 1, 0);
		bnjs->calCenter();
		return bnjs;
	}
	CC_SAFE_DELETE(bnjs);
	return nullptr;
}

JoyStick::~JoyStick() {}

//��ȡ��������
Rect JoyStick::getRect()
{

	//return getTextureRect();
	//��ȡ����ͼ�ĳߴ��С
	auto s = getTextureRect().size;
	return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

//�жϴ����λ�÷���
bool JoyStick::containsTouchLocation(Touch* touch)
{
	//�жϴ������Ƿ��ھ���������
	return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

//ÿ�ξ������ʱ���ص�
void JoyStick::onEnter()
{
	//���ø����onEnter����
	Sprite::onEnter();

	//����һ�����㴥�ؼ���
	auto listener = EventListenerTouchOneByOne::create();
	//�����´�����
	listener->setSwallowTouches(true);
	//��ʼ����ʱ�ص�onTouchBegan����
	listener->onTouchBegan = CC_CALLBACK_2(JoyStick::onTouchBegan, this);
	//�����ƶ�ʱ�ص�onTouchMoved����
	listener->onTouchMoved = CC_CALLBACK_2(JoyStick::onTouchMoved, this);
	//��������ʱ�ص�onTouchEnded����
	listener->onTouchEnded = CC_CALLBACK_2(JoyStick::onTouchEnded, this);
	//��ӵ�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

//ÿ�ξ����˳�ʱ���ص�
void JoyStick::onExit()
{
	//���ø����onExit����
	Sprite::onExit();
}

//��ʼ�����¼��Ĵ�����
bool JoyStick::onTouchBegan(Touch* touch, Event* event)
{
	if (!containsTouchLocation(touch)) return false;
	return true;
}

//�����ƶ��¼��Ĵ�����
void JoyStick::onTouchMoved(Touch* touch, Event* event)
{
	//�����ƶ��¼���û���βŵ���һ�Σ��������Ϸ�ٶ�
	if (yhCount % 2 == 0)
	{
		//��ȡ���ص��λ��
		Vec2 tp = touch->getLocation();
		//tp = convertToWorldSpace(tp);
		//����calCenterPosition����
		calCenterPosition(tp.x, tp.y);
		yhCount = 0;
	}
	yhCount++;
}

//���ؽ����¼��Ĵ�����
void JoyStick::onTouchEnded(Touch* touch, Event* event)
{
	calCenter();
	vx = 0;
	vy = 0;
	hero->setHeroDirVec(Vec2(0, 0));
	//hero->stopActionsByFlags(HERO_WAKE_FLAG);
	//hero->getHeroSprite()->stopActionsByFlags(HERO_WAKE_FLAG);
}

void JoyStick::calCenterPosition(float tx, float ty)
{
	Vec2 p = getPosition();

	//��ȡ����ê������
	Vec2 anchor = getAnchorPoint();
	//��ȡ����ͼ�ĳߴ��С
	Size size = getTextureRect().size;
	//�����������ĵĺ�����
	float centerX = p.x - anchor.x * size.width + size.width / 2.0f;
	//�����������ĵ�������
	float centerY = p.y - anchor.y * size.height + size.height / 2.0f;
	//���������ڴ��ص㵽���ĵĺ�����
	float dx = tx - centerX;
	//���������ڴ��ص㵽���ĵ�������
	float dy = ty - centerY;

	//��ǰ����������ԭ��ľ���
	float spanP2 = dx * dx + dy * dy;
	//�жϵ�ǰ�����ľ����Ƿ񳬳���Χ
	if (spanP2 > rRange * rRange)
	{
		float span = sqrt(spanP2);
		//���þ��������ڵĺ�����
		dx = dx * rRange / span;
		//���þ��������ڵ�������
		dy = dy * rRange / span;
	}
	//����ҡ����ԭ�����ĺ�����
	vx = dx / rRange;
	//����ҡ����ԭ������������
	vy = dy / rRange;

	//����ҡ������ҡ�˵�λ��
	centerPoint->setPosition(Vec2(dx + size.width / 2.0f, dy + size.height / 2.0f));

	auto angle = atan2(vy, vx) * 180.0f / PI;
	if (angle <= 135.0f && angle >= 45.0f) {
		hero->setHeroDirVec(Vec2(0, 1));
		hero->setHeroDir(HeroDir::UP);
	}
	else if (angle >= -135.0f && angle <= -45.0f) {
		hero->setHeroDirVec(Vec2(0, -1));
		hero->setHeroDir(HeroDir::DOWN);
	}
	else if (angle >= 135.0f || angle <= -135.0f) {
		hero->setHeroDirVec(Vec2(-1, 0));
		hero->setHeroDir(HeroDir::LEFT);
	}
	else if (angle >= -45.0f && angle <= 45.0f) {
		hero->setHeroDirVec(Vec2(1, 0));
		hero->setHeroDir(HeroDir::RIGHT);
	}
}

void JoyStick::calCenter()
{
	if (!centerPoint)
	{
		return;
	}
	//��ȡ����ͼ�ĳߴ��С
	Size s = getTextureRect().size;
	//��ȡ����ͼ�����ĵ�x����
	float centerXTemp = s.width / 2.0f;
	//��ȡ����ͼ�����ĵ�y����
	float centerYTemp = s.height / 2.0f;
	//��������ҡ�˵�λ��
	centerPoint->setPosition(Vec2(centerXTemp, centerYTemp));
	//��ȡ����ͼ�뾶
	rRange = s.width / 2.0f;
}


