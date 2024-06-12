#ifndef __ROTATELASER_HEADER_FILE_
#define __ROTATELASER_HEADER_FILE_
#include<iostream>
#include "laser.h"
using std::cout;
using std::swap;
class RotateLaser: public Laser{
public:
	SPRITEID("RotateLaser")
private:
	double dirbeg,dirend,dirdelta;//开始；结尾；变化量
public:
	RotateLaser(const line_t &_line,double _b,double _e,double _d):Laser(_line),dirbeg(tocircle(_b)),dirend(tocircle(_e)),dirdelta(_d/Map::Gamefps){
		if(dirbeg>dirend)	swap(dirbeg,dirend);
		getlaser().direct+=dirdelta/10;
	}
	RotateLaser(const Laser &laser):Laser(laser),dirbeg(laser.getlaser().direct),dirend(dirbeg),dirdelta(0){}
	virtual ~RotateLaser(){}
	virtual void update(){
		double _ndir=tocircle(getlaser().direct+dirdelta),_odir=getlaser().direct;
		if((dirbeg<=_ndir && _ndir<=dirend)!=((dirbeg<=_odir && _odir<=dirend))){
			dirdelta=-dirdelta;
			if(abs(_ndir-dirbeg)<abs(_ndir-dirend)){
				_ndir=dirbeg+dirdelta/10;
			} else{
				_ndir=dirend+dirdelta/10;
			}
		}
		getlaser().direct=tocircle(_ndir);
	}
	virtual void debug() const{
		cout << "[debug] spriteid=" << spriteid() << ": \n";
		cout << "laser now direct=" << getlaser().direct*180/PI << ".\n";
		Laser(makeline(getlaser().pos.x,getlaser().pos.y,dirbeg)).show(BLACK);
		Laser(makeline(getlaser().pos.x,getlaser().pos.y,dirend)).show(BLACK);
	}
};
#endif
