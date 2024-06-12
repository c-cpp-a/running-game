#ifndef __PLAYER_HEADER_FILE_
#define __PLAYER_HEADER_FILE_
#include "../gamemap.h"
#include "point/points.h"
class Player: public Point{
public:
	SPRITEID("Player")
public:
	static constexpr const double move_speed=5.0;
public:
	Player():Point(makepoint(90,Map::ScreenHeight/2.0),20){}
//	Player():Point(makepoint(2000,Map::ScreenHeight/2.0),20){Map::basex=-getpos().x+Map::ScreenWidth/3.0;}//test
	virtual ~Player(){}
	void move(int dx,int dy){
		if(getpos().x>=Map::ScreenWidth/3.0){
			Map::basex-=dx;
//			Map::basey+=dy;
		}
//		if(getpos().y>=Map::ScreenHeight*5.0/6 || getpos().y<=Map::ScreenHeight*1.0/6){
//			Map::basey-=dy;
//		}
		getpos().x+=dx;
		getpos().y+=dy;
	}
	void move(const key_msg &msg){
//		if(msg.msg&key_msg_down){
		if(msg.key==key_left || msg.key==key_A ){
			//左
			move(-move_speed,0);
		}
		if(msg.key==key_right || msg.key==key_D){
			//右
			move(move_speed,0);
		}
		if(msg.key==key_up || msg.key==key_W){
			//上
			move(0,-move_speed);
		}
		if(msg.key==key_down || msg.key==key_S){
			//下
			move(0,move_speed);
		}
//		}
	}
};
#endif
