#include "engine.h"
namespace Level2{
	vector<RotateLaser> rotatelasers={
		RotateLaser(makeline(600,350,degtorad(90)),degtorad(90),degtorad(-90),degtorad(20)),
		RotateLaser(makeline(710,350,degtorad(-120)),degtorad(120),degtorad(-120),degtorad(20)),
		RotateLaser(makeline(1000,450,degtorad(25-90)),degtorad(90-25),degtorad(-(90-25)),degtorad(14)),
		RotateLaser(makeline(2300,20,degtorad(-180+30)),degtorad(-180+30),degtorad(-25),degtorad(-10))
	};
	vector<SegLaser> seglasers={
		SegLaser(makeline(1250,10,degtorad(-180+60)),450),
		SegLaser(makeline(2000,0,degtorad(-60)),350),
		SegLaser(makeline(2450,800,degtorad(90+45)),550),
		SegLaser(makeline(2700,4000,degtorad(120)),300),
		SegLaser(makeline(2700,450,degtorad(180)),500),
		SegLaser(makeline(3200,1000,degtorad(120)),300)
	};
	vector<Laser> reallasers={
//	Laser(makeline(3200,200,degtorad(-91)))
	};
	vector<Point> points={
		Point(makepoint(300,400),30),
		Point(makepoint(800,400),30),
		Point(makepoint(900,400),35)
	};
	pair<vector<Laser *>,vector<Point>> getgamedata(){
		vector<Laser *> lasers;
#define REGISTERLASER(X) \
		for(auto &sth:X){\
		lasers.push_back(&sth);\
		}
		
		REGISTERLASER(rotatelasers);
		REGISTERLASER(seglasers);
		REGISTERLASER(reallasers);
		
#undef REGISTERLASER
		return make_pair(lasers,points);
	}
}
#include "runner.h"

#ifndef __NO_RUNNING__
int main(){
	auto tmp=Level2::getgamedata();
	gamemain(tmp.first,tmp.second,3700,"Level 2");
	return 0;
}
#endif
