#ifndef __GAMEMAP_HEADER_FILE_
#define __GAMEMAP_HEADER_FILE_
#include<graphics.h>
#include "graphdef.h"
namespace Map{
	double basex,basey;//坐标偏移量
	constexpr int ScreenWidth=1000,ScreenHeight=800;
	constexpr int Gamefps=60;
	void draw_circle(const point_t &pos,int radius){
		fillellipse(pos.x+basex,pos.y+basey,radius,radius);
	}
	void draw_line(const point_t &p1,const point_t &p2){
		line(p1.x+basex,p1.y+basey,p2.x+basex,p2.y+basey);
	}
	bool inMap(const point_t &pos){
		return (pos.x+basex>=0 && pos.x+basex<=ScreenWidth);
	}
}
#endif
