#ifndef __MOVESEGLASER_HEADER_FILE_
#define __MOVESEGLASER_HEADER_FILE_
#include "seglaser.h"
using std::swap;
class MoveSegLaser: public SegLaser{
public:
	SPRITEID("MoveSegLaser")
private:
	point_t begp,endp,delta;
public:
	MoveSegLaser(const line_t &line,const double &length,const point_t &_beg,const point_t &_end,double _d):
	SegLaser(line,length),begp(_beg),endp(_end){
		_d/=Map::Gamefps;
		if(begp.x>endp.x)	swap(begp,endp);
		if(fabs(endp.y-begp.y)<=1e-6){
			delta=makepoint(sqrt(_d),0);
			return;
		}
		if(fabs(endp.x-begp.x)<=1e-6){
			delta=makepoint(0,(endp.y>begp.y?1:-1)*sqrt(_d));
			return;
		}
		double tmp=(begp.x-endp.x)/(begp.y-endp.y);
		delta.y=(endp.y>begp.y?1:-1)*sqrt(_d/(1+tmp*tmp));
		delta.x=sqrt(_d-delta.y*delta.y);
	}
	virtual ~MoveSegLaser(){}
	virtual void update(){
		point_t cur=getpos()+delta;
		if(!(begp.x<=cur.x && cur.x<=endp.x && ((begp.y<=cur.y && cur.y<=endp.y) || (begp.y>=cur.y && cur.y>=endp.y)))){
			delta=makepoint(-delta.x,-delta.y);
			if(fabs(cur.x-begp.x)<=fabs(cur.x-endp.x)){
				cur=begp;
			} else{
				cur=endp;
			}
		}
		getlaser().pos=getpos()=cur;
	}
	const point_t &getdelta() const{
		return delta;
	}
};
#endif
