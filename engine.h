#ifndef __ENGINE_HEADER_FILE_
#define __ENGINE_HEADER_FILE_
#include<iostream>
#include<cmath>
#include<graphics.h>
#include<vector>
using namespace std;
double tocircle(const double &x){
	static constexpr const double PI2=2*3.1415926535897932384626433832795l;
	double tmp=x;
	while(abs(tmp)>PI){
		tmp-=PI2;
	}
	tmp=fmod(tmp,PI);
	if(tmp<0)	return PI2+tmp;
	return tmp;
}
double degtorad(const double &x){
	return x*PI/180.0;
}
struct point_t{
	double x,y;
};
struct line_t{
	//一条射线
	point_t pos;//起点坐标
	double direct;//方向（与x轴夹角）
};
point_t makepoint(double x,double y){
	return point_t({x,y});
}
point_t operator+(const point_t &lhs,const point_t &rhs){
	return makepoint(lhs.x+rhs.x,lhs.y+rhs.y);
}
line_t makeline(double x,double y,double dir){
	return line_t({makepoint(x,y),dir});
}
double cross(const point_t &p1,const point_t &p2){
	return p1.x*p2.y-p2.x*p1.y;
}
double distance(const point_t &p1,const point_t &p2){
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
point_t topoint(const line_t &l,double x){
	double k=tan(l.direct),b=l.pos.y-k*l.pos.x;
	return point_t({x,k*x+b});
}
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
//角色类型id
#define SPRITEID(X) \
virtual const string spriteid() const{\
return X;\
}
//角色大类的id
#define CLASSID(X) \
virtual const string classid() const{\
return X;\
}
class Sprite{
public:
	SPRITEID("Sprite")
	CLASSID("Sprite")
private:
	point_t pos;
protected:
	point_t &getpos(){
		return pos;
	}
public:
	Sprite(const point_t &_pos):pos(_pos){}
	virtual ~Sprite(){}
	virtual void show(color_t color) const=0;
	virtual void show(const Sprite &,color_t color) const{};
	virtual bool hit(const Sprite &) const=0;
	virtual void update(){
		
	}
	virtual void debug() const{
		
	}
	const point_t &getpos() const{
		return pos;
	} 
	const point_t &cgetpos() const{
		return getpos();
	}
};
double distance(const Sprite &a,const Sprite &b){
	return distance(a.getpos(),b.getpos());
}
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
		cout << "[debug] spriteid=" << spriteid() << ": \n";
		cout << "sprite pos=(" << getpos().x << ", " << getpos().y << ") radius=" << radius << ".\n";
	}
	const int getr() const{
		return radius;
	}
};
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
struct leveldata{
	string levelname;
	int MapLength;
	vector<Laser *> lasers;
	vector<Point> points;
};
leveldata makelevel(const string &_name,const int &l,const vector<Laser *> &ls,const vector<Point> &ps){
	return leveldata({_name,l,ls,ps});
}
template<typename T>
void registers(vector<Laser *> &lasers,vector<T> &_add){
	for(auto &sth:_add){
		lasers.push_back(&sth);
	}
}
#endif
