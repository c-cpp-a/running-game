#ifndef __LASER_HEADER_FILE_
#define __LASER_HEADER_FILE_
#include "../spritebase.h"
#include "../point/points.h"
using std::pair;
class Laser: public Sprite{
public:
	SPRITEID("Laser")
	CLASSID("Laser")
private:
	line_t laser;
protected:
	line_t &getlaser(){
		return laser;
	}
	void _show_base(color_t color=BLACK) const{
		Point(getpos(),10).show(GRAY);
		setcolor(color);
	}
public:
	Laser(const line_t &_line):Sprite(_line.pos),laser(_line){}
	virtual ~Laser(){}
	virtual void show(color_t color=BLACK) const{
		_show_base(color);
		point_t p2;
		if(cos(laser.direct)<0){
			p2=topoint(laser,Map::ScreenWidth-Map::basex);
		} else{
			p2=topoint(laser,0);
		}
//		line(laser.pos.x,laser.pos.y,p2.x,p2.y);
		Map::draw_line(laser.pos,p2);
		return;
	}
	virtual void show(const Point &end_point,color_t color=BLACK) const{
		_show_base(color);
		if(!hit(end_point)){
			show(color);
			return;
		}
		pair<point_t,point_t> res;
		double x0=end_point.getpos().x,y0=end_point.getpos().y,r=end_point.getr();
		double k=tan(laser.direct),b=laser.pos.y-k*laser.pos.x;
		double delta=-b*b+2*(y0*(b+k*x0)-b*k*x0)+k*k*(r-x0)*(r+x0)+(r-y0)*(r+y0);
		if(fabs(delta)<=1e-6)	delta=0;
		delta=sqrt(delta);
		double extra=-b*k+k*y0+x0;
		if(fabs(delta)<=1e-6){
			x0=extra/(k*k+1);
			y0=k*x0+b;
			res.first=res.second=point_t({x0,y0});
		} else{
			res.first.x=(extra-delta)/(k*k+1);
			res.first.y=k*res.first.x+b;
			res.second.x=(extra+delta)/(k*k+1);
			res.second.y=k*res.second.x+b;
		}
		
		if(distance(res.first,laser.pos)<=distance(res.second,laser.pos)){
			Map::draw_line(laser.pos,res.first);
		} else{
			Map::draw_line(laser.pos,res.second);
		}
	}
	virtual void show(double length,color_t color=BLACK){
		_show_base(color);
		point_t p2;
		if(cos(laser.direct)<0){
			p2=topoint(laser,laser.pos.x+length);
		} else{
			p2=topoint(laser,laser.pos.x-length);
		}
//		line(laser.pos.x,laser.pos.y,p2.x,p2.y);
		Map::draw_line(laser.pos,p2);
		return;
	}
	virtual bool hit(const point_t &rhs) const{
		if(cos(laser.direct)<0){
			return rhs.x>laser.pos.x && fabs(topoint(laser,rhs.x).y-rhs.y)<=1e-6;
		} else{
			return rhs.x<laser.pos.x && fabs(topoint(laser,rhs.x).y-rhs.y)<=1e-6;
		}
//		return fabs(topoint(laser,rhs.x).y-rhs.y)<=1e-6;
	}
	virtual bool hit(const Point &rhs) const{
		pair<point_t,point_t> res;
		double x0=rhs.getpos().x,y0=rhs.getpos().y,r=rhs.getr();
		double k=tan(laser.direct),b=laser.pos.y-k*laser.pos.x;
		double delta=-b*b+2*(y0*(b+k*x0)-b*k*x0)+k*k*(r-x0)*(r+x0)+(r-y0)*(r+y0);
//		if(fabs(delta)<=1e-6)	delta=0;
//		if(delta<0 || fabs(k*k+1)<=1e-6){
//			return false;
//		} else{
//			if(cos(laser.direct)<=0){
//				return rhs.getpos().x>laser.pos.x;
//			} else{
//				return rhs.getpos().x<laser.pos.x;
//			}
//		}
//		pair<point_t,point_t> res;
//		double x0=rhs.getpos().x,y0=end_point.getpos().y,r=end_point.getr();
//		double k=tan(laser.direct),b=laser.pos.y-k*laser.pos.x;
//		double delta=-b*b+2*(y0*(b+k*x0)-b*k*x0)+k*k*(r-x0)*(r+x0)+(r-y0)*(r+y0);
		if(fabs(delta)<=1e-6)	delta=0;
		if(delta<0 || fabs(k*k+1)<=1e-6){
			return false;
		}
		delta=sqrt(delta);
		double extra=-b*k+k*y0+x0;
		if(fabs(delta)<=1e-6){
			x0=extra/(k*k+1);
			y0=k*x0+b;
			res.first=res.second=point_t({x0,y0});
		} else{
			res.first.x=(extra-delta)/(k*k+1);
			res.first.y=k*res.first.x+b;
			res.second.x=(extra+delta)/(k*k+1);
			res.second.y=k*res.second.x+b;
		}
		return hit(res.first) || hit(res.second);
	}
	virtual bool hit(const Laser &rhs) const{
		return false;
	}
	virtual bool hit(const Sprite &rhs) const{
		return rhs.hit(*this);
	}
	const line_t &getlaser() const{
		return laser;
	}
};
Laser make_laser(double x,double y,double direct){
	return Laser(line_t({point_t({x,y}),direct}));
}
#include "seglaser.h"
#include "rotatelaser.h"
#endif
