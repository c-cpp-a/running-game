#include<vector>
#include "engine.h"
using std::vector;
namespace Level3{
	vector<RotateLaser> rotatelasers={
		RotateLaser(makeline(400,400,degtorad(0.1)),degtorad(0),degtorad(0),degtorad(1)),
		RotateLaser(makeline(400,400,degtorad(0.1)),degtorad(0),degtorad(0),degtorad(3)),
		RotateLaser(makeline(400,400,degtorad(0.1)),degtorad(0),degtorad(0),degtorad(7)),
		RotateLaser(makeline(400,400,degtorad(0.1)),degtorad(0),degtorad(0),degtorad(11)),
		RotateLaser(makeline(400,400,degtorad(0.1)),degtorad(0),degtorad(0),degtorad(13)),
		RotateLaser(makeline(400,400,degtorad(0.1)),degtorad(0),degtorad(0),degtorad(23)),
		RotateLaser(makeline(700,0,degtorad(-180)),degtorad(-91),degtorad(-180),degtorad(3)),
		RotateLaser(makeline(700,800,degtorad(90)),degtorad(89),degtorad(181),degtorad(8)),
		RotateLaser(makeline(2000,400,degtorad(120)),degtorad(120),degtorad(-120),degtorad(15)),
		RotateLaser(makeline(2200,700,degtorad(80)),degtorad(80),degtorad(110),degtorad(1)),
	};
	vector<SegLaser> seglasers={
		SegLaser(makeline(1000,100,degtorad(180)),700),
		SegLaser(makeline(1000,300,degtorad(180)),700),
		SegLaser(makeline(1000,500,degtorad(180)),700),
		SegLaser(makeline(1000,700,degtorad(180)),700),
		SegLaser(makeline(1100,100,degtorad(-135)),100),
		SegLaser(makeline(1200,600,degtorad(-135)),100),
		SegLaser(makeline(1400,400,degtorad(135)),100),
//	SegLaser(makeline(1800,700,degtorad(100)),100),
	};
	vector<Laser> reallasers={
		Laser(makeline(1000,700,degtorad(-91))),
		Laser(makeline(1000,100,degtorad(89))),
		Laser(makeline(3000,300,degtorad(-85))),
		Laser(makeline(1800,700,degtorad(91))),
	};
	vector<Point> points={
		
	};
	leveldata getgamedata(){
		leveldata res=makelevel("Level 3",3000,vector<Laser *>(),points);
		registers(res.lasers,rotatelasers);
		registers(res.lasers,seglasers);
		registers(res.lasers,reallasers);
		return res;
	}
}
#include "runner.h"
#ifndef __NO_RUNNING__
int main(){
	gamemain(Level3::getgamedata());
	return 0;
}
#endif
