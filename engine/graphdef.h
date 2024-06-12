#ifndef __GRAPH_DEF_HEADER_FILE_
#define __GRAPH_DEF_HEADER_FILE_
#include<cmath>
static constexpr const double _G_PI=3.1415926535897932384626433832795l;
double tocircle(const double &x){
	static constexpr const double PI2=2*3.1415926535897932384626433832795l;
	double tmp=x;
	while(abs(tmp)>_G_PI){
		tmp-=PI2;
	}
	tmp=fmod(tmp,_G_PI);
	if(tmp<0)	return PI2+tmp;
	return tmp;
}
double degtorad(const double &x){
	return x*_G_PI/180.0;
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
#endif
