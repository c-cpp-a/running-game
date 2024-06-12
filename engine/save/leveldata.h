#ifndef __LEVELDATA_HEADER_FILE_
#define __LEVELDATA_HEADER_FILE_
#include<string>
#include<vector>
#include "../sprite/point/points.h"
#include "../sprite/laser/laser.h"
struct leveldata{
	std::string levelname;
	int MapLength;
	std::vector<Laser *> lasers;
	std::vector<Point> points;
};
leveldata makelevel(const std::string &_name,const int &l,const std::vector<Laser *> &ls,const std::vector<Point> &ps){
	return leveldata({_name,l,ls,ps});
}
template<typename T>
void registers(std::vector<Laser *> &lasers,std::vector<T> &_add){
	for(auto &sth:_add){
		lasers.push_back(&sth);
	}
}
const leveldata defaultdata=makelevel("default",0,std::vector<Laser *>(),std::vector<Point>());
#endif
