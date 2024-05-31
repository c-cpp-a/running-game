#include "engine.h"
namespace Level4{
	vector<RotateLaser> rotatelasers={
		RotateLaser(makeline(900,800,degtorad(0.1)),degtorad(0),degtorad(179),degtorad(15)),
		RotateLaser(makeline(1600,350,degtorad(60)),degtorad(60),degtorad(120),degtorad(60)),
		RotateLaser(makeline(2000,100,degtorad(-40)),degtorad(-40),degtorad(-150),degtorad(30)),
	};
	vector<SegLaser> seglasers={
		
	};
	vector<Laser> reallasers={
		Laser(makeline(2300,100,degtorad(-90-45))),
		Laser(makeline(1000,800,degtorad(-89.9))),
		Laser(makeline(2300,800,degtorad(-89.9)))
	};
	vector<MoveSegLaser> moveseglasers={
		MoveSegLaser(makeline(500,100,degtorad(45)),100,makepoint(500,100),makepoint(400,0),50),
		MoveSegLaser(makeline(400,200,degtorad(90+45)),100,makepoint(400,200),makepoint(500,100),50),
		MoveSegLaser(makeline(500,300,degtorad(45)),100,makepoint(500,300),makepoint(400,200),50),
		MoveSegLaser(makeline(400,400,degtorad(90+45)),100,makepoint(400,400),makepoint(500,300),50),
		MoveSegLaser(makeline(500,500,degtorad(45)),100,makepoint(500,500),makepoint(400,400),50),
		MoveSegLaser(makeline(400,600,degtorad(90+45)),100,makepoint(400,600),makepoint(500,500),50),
		MoveSegLaser(makeline(500,700,degtorad(45)),100,makepoint(500,700),makepoint(400,600),50),
		MoveSegLaser(makeline(700,100,degtorad(90+20)),200,makepoint(700,100),makepoint(900,400),55),
		MoveSegLaser(makeline(1300,400,degtorad(0)),200,makepoint(1300,400),makepoint(1400,400),50),
		MoveSegLaser(makeline(1100,600,degtorad(179.9)),200,makepoint(1100,600),makepoint(1000,600),50),
		MoveSegLaser(makeline(1300,600,degtorad(-89.9)),0.349066,makepoint(1300,600),makepoint(1300,200),50),
		MoveSegLaser(makeline(1100,400,degtorad(89.9)),0.349066,makepoint(1100,400),makepoint(1100,800),50),
		MoveSegLaser(makeline(1600,800,degtorad(90+40)),200,makepoint(1600,800),makepoint(3000,800),80),
		MoveSegLaser(makeline(2300,500,degtorad(179.9)),400,makepoint(2300,500),makepoint(2600,500),80),
	};
	vector<Point> points={
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
		REGISTERLASER(moveseglasers);
		
#undef REGISTERLASER
		return make_pair(lasers,Level4::points);
	}
}
#include "runner.h"
#ifndef __NO_RUNNING__
int main(){
	auto tmp=Level4::getgamedata();
	gamemain(tmp.first,tmp.second,3000,"Level 4");
	return 0;
}
#endif
