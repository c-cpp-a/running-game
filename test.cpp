#include "engine.h"
vector<RotateLaser> rotatelasers={
//	RotateLaser(makeline(400,400,degtorad(0)),degtorad(0),degtorad(0),degtorad(1)),
//	RotateLaser(makeline(400,400,degtorad(0)),degtorad(0),degtorad(0),degtorad(3)),
//	RotateLaser(makeline(400,400,degtorad(0)),degtorad(0),degtorad(0),degtorad(7)),
//	RotateLaser(makeline(400,400,degtorad(0)),degtorad(0),degtorad(0),degtorad(11)),
//	RotateLaser(makeline(400,400,degtorad(0)),degtorad(0),degtorad(0),degtorad(13)),
//	RotateLaser(makeline(400,400,degtorad(0)),degtorad(0),degtorad(0),degtorad(23)),
	RotateLaser(makeline(400,400,degtorad(-50.1)),degtorad(-170),degtorad(-50),degtorad(170))
};
vector<SegLaser> seglasers={
	SegLaser(makeline(500,100,degtorad(10)),700),
	SegLaser(makeline(600,100,degtorad(170)),700),
	SegLaser(makeline(700,100,degtorad(-10)),700),
	SegLaser(makeline(800,100,degtorad(-170)),700),
//	SegLaser(makeline(600,700,degtorad(91)),700),
//	SegLaser(makeline(3000,700,degtorad(165)),700),
//	SegLaser(makeline(3500,100,degtorad(-40)),700),
//	SegLaser(makeline(1000,300,degtorad(180)),700),
//	SegLaser(makeline(1000,500,degtorad(180)),700),
//	SegLaser(makeline(1000,700,degtorad(180)),700),
//	SegLaser(makeline(1100,100,degtorad(-135)),100),
//	SegLaser(makeline(1200,600,degtorad(-135)),100),
//	SegLaser(makeline(1400,400,degtorad(135)),100),
//	SegLaser(makeline(1800,700,degtorad(100)),100),
//	SegLaser(makeline(3000,700,degtorad(-85)),100)
};
vector<Laser> reallasers={
//	Laser(makeline(3200,200,degtorad(-91)))
//	Laser(makeline(1000,100,degtorad(89))),
};
vector<Point> points={
};
#include "runner.h"
int main(){
//	cerr << tocircle(degtorad(120)) << '\n' << tocircle(degtorad(-120)) << '\n' << tocircle(degtorad(-180));
	for(int i=-180;i<=360;i++){
		cout << tocircle(degtorad(i))/PI*180.0 << '\n';
	}
	
	gamemain(rotatelasers,seglasers,reallasers,points,6000,"test engine");
	return 0;
}
