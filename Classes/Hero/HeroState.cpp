#include"HeroState.h"
#include"Hero.h"


void Wake::Enter(Hero* hero) {
	//CCLOG("Wake Enter");
}

void Wake::Execute(Hero* hero) {
	//CCLOG("Wake Execute");

}

void Wake::Exit(Hero* hero) {
	//CCLOG("Wake Exit");
}



//--------------

void Stand::Enter(Hero* hero) {
	//CCLOG("Stand Enter");
}

void Stand::Execute(Hero* hero) {
	//CCLOG("Stand Execute");

}

void Stand::Exit(Hero* hero) {
	//CCLOG("Stand Exit");
}


//--------------

void Fight::Enter(Hero* hero) {
	//CCLOG("Fight Enter");
}

void Fight::Execute(Hero* hero) {
	//CCLOG("Fight Execute");

}

void Fight::Exit(Hero* hero) {
	//CCLOG("Fight Exit");
}