#ifndef __SPRITE_POINT_HEADER_FILE_
#define __SPRITE_POINT_HEADER_FILE_
#include<iostream>
#include "../../gamemap.h"
#include "../spritebase.h"
class Point: public Sprite{
public:
	SPRITEID("Point")
	CLASSID("Point")
private:
	int radius;//点半径
protected:
	void setr(int _r){
		radius=_r;
	}
public:
	Point(const point_t &_pos,int _r):Sprite(_pos),radius(_r){}
	virtual ~Point(){}
	virtual void show(color_t color=BLACK) const{
		setfillcolor(color);
		setcolor(color);
//		fillellipse(getpos().x,getpos().y,radius,radius);
		Map::draw_circle(getpos(),radius);
	}
	virtual bool hit(const Point &rhs) const{
		return distance((*this),rhs)<=radius+rhs.radius;
	}
	virtual bool hit(const Sprite &rhs) const{
		return rhs.hit((*this));
	}
	virtual void debug() const{
		std::cout << "[debug] spriteid=" << spriteid() << ": \n";
		std::cout << "sprite pos=(" << getpos().x << ", " << getpos().y << ") radius=" << radius << ".\n";
	}
	const int getr() const{
		return radius;
	}
};
#endif
