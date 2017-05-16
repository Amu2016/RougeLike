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
		//初始化摇杆x坐标
		bnjs->vx = 0;
		//初始化摇杆y坐标
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

//获取矩形区域
Rect JoyStick::getRect()
{

	//return getTextureRect();
	//获取纹理图的尺寸大小
	auto s = getTextureRect().size;
	return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

//判断触点的位置方法
bool JoyStick::containsTouchLocation(Touch* touch)
{
	//判断触摸点是否在矩形区域内
	return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

//每次精灵进入时被回调
void JoyStick::onEnter()
{
	//调用父类的onEnter方法
	Sprite::onEnter();

	//创建一个单点触控监听
	auto listener = EventListenerTouchOneByOne::create();
	//设置下传触摸
	listener->setSwallowTouches(true);
	//开始触摸时回调onTouchBegan方法
	listener->onTouchBegan = CC_CALLBACK_2(JoyStick::onTouchBegan, this);
	//触摸移动时回调onTouchMoved方法
	listener->onTouchMoved = CC_CALLBACK_2(JoyStick::onTouchMoved, this);
	//触摸结束时回调onTouchEnded方法
	listener->onTouchEnded = CC_CALLBACK_2(JoyStick::onTouchEnded, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

//每次精灵退出时被回调
void JoyStick::onExit()
{
	//调用父类的onExit方法
	Sprite::onExit();
}

//开始触控事件的处理方法
bool JoyStick::onTouchBegan(Touch* touch, Event* event)
{
	if (!containsTouchLocation(touch)) return false;
	return true;
}

//触控移动事件的处理方法
void JoyStick::onTouchMoved(Touch* touch, Event* event)
{
	//限制移动事件，没两次才调用一次，以提高游戏速度
	if (yhCount % 2 == 0)
	{
		//获取触控点的位置
		Vec2 tp = touch->getLocation();
		//tp = convertToWorldSpace(tp);
		//调用calCenterPosition方法
		calCenterPosition(tp.x, tp.y);
		yhCount = 0;
	}
	yhCount++;
}

//触控结束事件的处理方法
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

	//获取精灵锚点坐标
	Vec2 anchor = getAnchorPoint();
	//获取纹理图的尺寸大小
	Size size = getTextureRect().size;
	//矩形区域中心的横坐标
	float centerX = p.x - anchor.x * size.width + size.width / 2.0f;
	//矩形区域中心的纵坐标
	float centerY = p.y - anchor.y * size.height + size.height / 2.0f;
	//矩形区域内触控点到中心的横坐标
	float dx = tx - centerX;
	//矩形区域内触控点到中心的纵坐标
	float dy = ty - centerY;

	//当前坐标与坐标原点的距离
	float spanP2 = dx * dx + dy * dy;
	//判断当前坐标点的距离是否超出范围
	if (spanP2 > rRange * rRange)
	{
		float span = sqrt(spanP2);
		//设置矩形区域内的横坐标
		dx = dx * rRange / span;
		//设置矩形区域内的纵坐标
		dy = dy * rRange / span;
	}
	//设置摇杆离原点距离的横坐标
	vx = dx / rRange;
	//设置摇杆离原点距离的纵坐标
	vy = dy / rRange;

	//设置摇杆中心摇杆的位置
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
	//获取纹理图的尺寸大小
	Size s = getTextureRect().size;
	//获取纹理图的中心的x坐标
	float centerXTemp = s.width / 2.0f;
	//获取纹理图的中心的y坐标
	float centerYTemp = s.height / 2.0f;
	//设置中心摇杆的位置
	centerPoint->setPosition(Vec2(centerXTemp, centerYTemp));
	//获取纹理图半径
	rRange = s.width / 2.0f;
}


