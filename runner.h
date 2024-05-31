#ifndef __RUNNER_HEADER_FILE_
#define __RUNNER_HEADER_FILE_
#include<graphics.h>
#include<vector>
#include "engine.h"
using namespace std;
void init(){
	setfont(20,0,"微软雅黑");
//	setlinewidth(.0);
	init_console();
	show_console();
	initgraph(1000,800);
	setbkcolor(SKYBLUE);
}
void showtext(float x,float y,const string &s){
	outtextxy(x-textwidth(s.c_str())/2.0,y-textheight(s.c_str())/2.0,s.c_str());
}
double gamemain(vector<Laser *> &lasers,vector<Point> &points,const int &Maplength,const string &title){
	Player player;
	init();
	setcaption(title.c_str());
	clock_t beg=clock();
	for(;is_run() && player.cgetpos().x<Maplength;delay_fps(Map::Gamefps)){
		cleardevice();
		for(auto &it:lasers){
			if(Map::inMap(it->cgetpos())){
				it->show(player,RED);
				if(it->hit(player)){
					player=Player();
					Map::basex=Map::basey=0;
				}
			}
			
		}
		for(auto &point:points){
			if(Map::inMap(point.cgetpos())){
				point.show(WHITESMOKE);
				if(point.hit(player)){
					player=Player();
					Map::basex=Map::basey=0;
				}
			}
		}
		player.show(BROWN);
		setcolor(WHITE);
		outtextxy(10.0,10.0,(to_string((1.0*clock()-beg)/CLOCKS_PER_SEC)+"s").c_str());
		key_msg msg;
		while(kbmsg()){
			msg=getkey();
			player.move(msg);
		}
		for(auto &it:lasers){
			it->update();
		}
	}
	beg=clock()-beg;
	cleardevice();
	setcolor(WHITE);
	setfont(100,0,"微软雅黑");
	showtext(Map::ScreenWidth/2.0,Map::ScreenHeight/2.0,"You win!");
	setfont(20,0,"微软雅黑");
	showtext(500,500,"using time: "+to_string(1.0*beg/CLOCKS_PER_SEC)+"s");
	for(;is_run();delay_fps(Map::Gamefps)){
		bool flag=false;
		key_msg msg;
		while(kbmsg()){
			msg=getkey();
			if(msg.msg&key_msg_down){
				if(msg.key==key_Q){
					flag=true;
					break;
				}
			}
		}
		if(flag)	break;
	}
	closegraph();
	close_console();
	return 1.0*beg/CLOCKS_PER_SEC;
}
#endif
