#include"Gore.h"
#include"MyRandom.h"

Gore* Gore::create(GoreType type) {
	Gore* gore = new Gore(type);
	if (gore && gore->init())
	{
		gore->autorelease();
		return gore;
	}
	CC_SAFE_DELETE(gore);
	return nullptr;
}

bool Gore::init() {
	if (!Node::init()) return false;

	switch (goreType)
	{
	case GoreType::Warm:
		runWarmDieGore();
		break;
	default:
		break;
	}

	return true;
}

void Gore::update(float delta) {


}

void Gore::runWarmDieGore() {
	int count = 2;
	while (count)
	{
		count--;
		for (int i = 8; i <= 10; i++) {
			auto WarmGore = Sprite::createWithSpriteFrameName(StringUtils::format("Gore_%d.png", i));
			WarmGore->setScale(0.2f);
			addChild(WarmGore);

			Vec2 randVec = Vec2(getRandomFloat(rng, -50.0f, 50.0f), getRandomFloat(rng, -50.0f, 50.0f));
			auto move = MoveBy::create(0.5f, randVec);
			auto jump = JumpBy::create(0.5f, Vec2(0, 0), 5.0f, 2);
			auto rota = RotateBy::create(0.5f, getRandomFloat(rng, -700.0f, 700.0f));
			WarmGore->runAction(move);
			WarmGore->runAction(jump);
			WarmGore->runAction(rota);
		}
	}


	scheduleOnce(schedule_selector(Gore::visibility), 3.0f);
}

void Gore::visibility(float delta) {
	auto visi = ToggleVisibility::create();
	runAction(visi);

	scheduleOnce(schedule_selector(Gore::disappear), 2.0f);
}

void Gore::disappear(float delta) {
	removeFromParent();
}