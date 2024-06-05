#include "engine.h"
namespace Level5{
	vector<RotateLaser> rotatelasers={
		RotateLaser(makeline(300,1000,degtorad(-46)),degtorad(-45),degtorad(-135),degtorad(12)),
		RotateLaser(makeline(300,2000,degtorad(45)),degtorad(45),degtorad(135),degtorad(6)),
		RotateLaser(makeline(700,1500,degtorad(45)),degtorad(45),degtorad(-45),degtorad(-12)),
		RotateLaser(makeline(700,1500,degtorad(135)),degtorad(135),degtorad(-135),degtorad(12)),
		RotateLaser(makeline(300,-700,degtorad(0)),degtorad(0),degtorad(0),degtorad(27)),
	};
	vector<SegLaser> seglasers={
		SegLaser(makeline(0,0,degtorad(179.9)),100),
		SegLaser(makeline(100,-100,degtorad(179.9)),100),
		SegLaser(makeline(0,800,degtorad(179.9)),100),
		SegLaser(makeline(100,900,degtorad(179.9)),100),
		SegLaser(makeline(1000,1100,degtorad(-135)),900),
		SegLaser(makeline(1000,-1100,degtorad(135)),900),
	};
	vector<Laser> reallasers={
		Laser(makeline(2100,500,degtorad(179.9))),
		Laser(makeline(3000,-100,degtorad(135))),
		Laser(makeline(2800,800,degtorad(-89.9))),
		Laser(makeline(2800,0,degtorad(89.9)))
	};
	vector<MoveSegLaser> moveseglasers={
		MoveSegLaser(makeline(300,-100,degtorad(89.9)),20,makepoint(300,-100),makepoint(700,-100),30),
	};
	vector<Point> points={
		Point(makepoint(1001,400),700),
		Point(makepoint(2800,1300),700),
		Point(makepoint(2800,-300),700),
		Point(makepoint(4000,400),650),
		Point(makepoint(3000,0),100)
	};
	leveldata getgamedata(){
		leveldata res=makelevel("Level 5",3400,vector<Laser *>(),points);
		registers(res.lasers,rotatelasers);
		registers(res.lasers,seglasers);
		registers(res.lasers,reallasers);
		registers(res.lasers,moveseglasers);
		return res;
	}
}
#include "runner.h"
#ifndef __NO_RUNNING__
int main(){
	gamemain(Level5::getgamedata());
	return 0;
}
#endif
