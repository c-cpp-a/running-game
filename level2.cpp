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
	leveldata getgamedata(){
		leveldata res=makelevel("Level 2",3700,vector<Laser *>(),points);
		registers(res.lasers,rotatelasers);
		registers(res.lasers,seglasers);
		registers(res.lasers,reallasers);
		return res;
	}
}
#include "runner.h"
#ifndef __NO_RUNNING__
int main(){
	gamemain(Level2::getgamedata());
	return 0;
}
#endif
