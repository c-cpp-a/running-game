#include<iostream>
#define __NO_RUNNING__
#include "level1.cpp"
#include "level2.cpp"
#include "level3.cpp"
#include "level4.cpp"
using namespace std;
constexpr int maxlevel=4;
constexpr int MapLength[]={0,3400,3700,3000,3000};
pair<vector<Laser *>,vector<Point>> getgamedata(int id){
	switch(id){
	case 1:
		return Level1::getgamedata();
	case 2:
		return Level2::getgamedata();
	case 3:
		return Level3::getgamedata();
	case 4:
		return Level4::getgamedata();
	}
	return make_pair(vector<Laser *>(),vector<Point>());
}
const string getgametitle(int id){
	switch(id){
	case 1:
		return "Level 1";
	case 2:
		return "Level 2";
	case 3:
		return "Level 3";
	case 4:
		return "Level 4";
	}
	return string();
}
void destroy(pair<vector<Laser *>,vector<Point>> &tmp){
	for(int i=0,siz=tmp.first.size();i<siz;i++){
		delete tmp.first[i];
	}
}
pair<vector<Laser *>,vector<Point>> gamemapdata;
int main(){
	int nowid=1;
	double usetime=0;
	for(;nowid<=maxlevel;++nowid){
		gamemapdata=getgamedata(nowid);
		usetime+=gamemain(gamemapdata.first,gamemapdata.second,MapLength[nowid],getgametitle(nowid));
//		destroy(gamemapdata);
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
