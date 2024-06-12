#include<iostream>
#define __NO_RUNNING__
#include "level1.cpp"
#include "level2.cpp"
#include "level3.cpp"
#include "level4.cpp"
#include "level5.cpp"
using namespace std;
constexpr int maxlevel=5;
constexpr int MapLength[]={0,3400,3700,3000,3000,3400};
leveldata getgamedata(int id){
	switch(id){
	case 1:
		return Level1::getgamedata();
	case 2:
		return Level2::getgamedata();
	case 3:
		return Level3::getgamedata();
	case 4:
		return Level4::getgamedata();
	case 5:
		return Level5::getgamedata();
	}
	return defaultdata;
}
leveldata gameMapdata;
int main(){
	int nowid=1;
	double usetime=0;
	for(;nowid<=maxlevel;++nowid){
		usetime+=gamemain(getgamedata(nowid));
	}
	init();
	setcaption("happy!");
	cleardevice();
	setcolor(WHITE);
	setfont(80,0,"微软雅黑");
	showtext(Map::ScreenWidth/2.0,Map::ScreenHeight/2.0,"You cross all the level!");
	setfont(20,0,"微软雅黑");
	showtext(500,500,"using time: "+to_string(usetime)+"s");
	for(;is_run();delay_fps(Map::Gamefps)){
		
	}
	return 0;
}
