#ifndef __SEGLASER_HEADER_FILE_
#define __SEGLASER_HEADER_FILE_
#include "laser.h"
using std::min;
class SegLaser:public Laser{
public:
	SPRITEID("SegLaser")
private:
	double length;
protected:
	double &getlength(){
		return length;
	}
public:
	SegLaser(const line_t &_line,const double &l):Laser(_line),length(l){}
	virtual ~SegLaser(){}
	virtual void show(color_t color=BLACK) const{
		Laser::_show_base(color);
		point_t p2;
		if(cos(getlaser().direct)<0){
			p2=topoint(getlaser(),getlaser().pos.x+length);
		} else{
			p2=topoint(getlaser(),getlaser().pos.x-length);
		}
//		line(laser.pos.x,laser.pos.y,p2.x,p2.y);
		Map::draw_line(getlaser().pos,p2);
		return;
	}
	virtual void show(const Point &end_point,color_t color=BLACK) const{
		Laser::_show_base(color);
		pair<point_t,point_t> res;
		double x0=end_point.getpos().x,y0=end_point.getpos().y,r=end_point.getr();
		double k=tan(getlaser().direct),b=getlaser().pos.y-k*getlaser().pos.x;
		double delta=-b*b+2*(y0*(b+k*x0)-b*k*x0)+k*k*(r-x0)*(r+x0)+(r-y0)*(r+y0);
		if(fabs(delta)<=1e-6)	delta=0;
		if(!hit(end_point)){
			show(color);
			return;
		} else{
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
		}
		double dis1=distance(res.first,getlaser().pos),dis2=distance(res.second,getlaser().pos);
		if(min(dis1,dis2)>=distance(getlaser().pos,topoint(getlaser(),getlaser().pos.x+length))){
			show(color);
		} else if(dis1<=dis2){
			Map::draw_line(getlaser().pos,res.first);
		} else{
			Map::draw_line(getlaser().pos,res.second);
		}
	}
	virtual bool hit(const Point &rhs) const{
		if(cos(getlaser().direct)<0){
			return distance(getlaser().pos,rhs.getpos())<=distance(getlaser().pos,topoint(getlaser(),getlaser().pos.x+length)) && Laser::hit(rhs);
		} else{
			return distance(getlaser().pos,rhs.getpos())<=distance(getlaser().pos,topoint(getlaser(),getlaser().pos.x-length)) && Laser::hit(rhs);
		}
	}
	virtual bool hit(const Laser &rhs) const{
		return false;
	}
	virtual bool hit(const Sprite &rhs) const{
		return rhs.hit(*this);
	}
	const double &getlength() const{
		return length;
	}
};
#include "moveseglaser.h"
#endif
