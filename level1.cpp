#include<vector>
#include "engine.h"
using std::vector;
namespace Level1{
	vector<RotateLaser> rotatelasers={
		RotateLaser(makeline(1000,400,degtorad(180)),degtorad(180),degtorad(180),degtorad(20)),
		RotateLaser(makeline(1500,200,degtorad(67)),degtorad(67),degtorad(-68),degtorad(10))
	};
	vector<SegLaser> seglasers={
		SegLaser(makeline(500,0,degtorad(-30)),100),
		SegLaser(makeline(500,800,degtorad(30+90)),100),
		SegLaser(makeline(1400,800,degtorad(45+90)),400),
		SegLaser(makeline(1800,0,degtorad(-45-90)),400),
		SegLaser(makeline(2200,800,degtorad(45+90)),400),
		SegLaser(makeline(2600,0,degtorad(-45-90)),400),
		SegLaser(makeline(3200,200,degtorad(-45)),400)
	};
	vector<Laser> reallasers={
//	Laser(makeline(3200,200,degtorad(-91)))
	};
	vector<Point> points={
		Point(makepoint(800,400),25),
	};
	leveldata getgamedata(){
		leveldata res=makelevel("Level 1",3400,vector<Laser *>(),points);
		registers(res.lasers,rotatelasers);
		registers(res.lasers,seglasers);
		registers(res.lasers,reallasers);
		return res;
	}
}
#include "runner.h"
#ifndef __NO_RUNNING__
int main(){
	gamemain(Level1::getgamedata());
	return 0;
}
#endif
