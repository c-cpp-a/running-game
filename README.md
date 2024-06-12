# running-game
ege做的一个跑酷游戏
## 游玩方法
- [releases](https://github.com/c-cpp-a/running-game/releases)下载最新版本游玩。
- 下载本项目，里面有exe，或者编译你想玩的那个关卡。
## 关卡说明
- 目前只更新至第 5 关。
- `level xxx` 格式的 `.cpp`  文件和 `.exe` 文件，文件名是该关卡的名称。打开 `.exe` 结尾的文件即可直接游玩。
- `main.exe` 是整合关卡，打开可以逐关游玩关卡。
- 当你通关一个关卡后，会显示本关卡计时；当你通关 `main.exe` 时，在最后会显示所有关卡的累计用时。
- 当你通过一个关卡时，可以按 `q` 键退出。
## 游玩说明
- 移动方式： 方向键或 `WASD`。**不稳定**地支持组合键（就是大部分时候不灵）
- 你需要躲过红色的激光和白色的球，到达终点。
- 本游戏没有边界限制！发挥自己的想象力去设计行动路线吧！只要横坐标大于等于关卡长度即可通关！
- 当你遇到困境时，试一试重开再来一遍。
## 使用自定义结构体说明
- 如果你不想编写关卡，可以跳过此节。
- 使用的结构体都定义在 `./engine/graphdef.h` 中。
### point_t
- 定义
```cpp
struct point_t{
	double x,y;//相对于屏幕左上角的横坐标(x)偏移量和纵坐标(y)偏移量
};
```
用于描述一个点的位置。
- 构造方式
可以直接构造 `point_t({x,y})`，也可以使用 `makepoint(x,y)` 来构造，两种方法是等价的。
### line_t
- 定义
```cpp
struct line_t{
	//一条射线
	point_t pos;//起点坐标
	double direct;//方向（与x轴负方向夹角，大于pi弧度可以用(-0,-pi)描述，也可以继续使用(pi,2*pi)描述）
};
```
用于描述一条射线的位置。
- 构造方式
可以直接构造（类似 `point_t`），也可以使用 `makeline(pos,direct)` 来构造，两种方法是等价的。
## 障碍物说明
- 无特殊说明，参数均按照以下单位：位置的单位是像素；角度的单位是弧度（提供 `degtorad` 进行角度-弧度转换）。
### Point
- 外观是一个球，有着圆形的判定区。
- 构造方式 `Point(const point_t &_pos,int _r)`，分别是圆心位置和半径。
### Laser
- 一个射线激光，判定只有红色部分。
- 构造方式 `Laser(const line_t &_line)`，为射线的描述（起始坐标和方向）。
### SegLaser
- 一个线段激光，判定区为线段部分。
- 构造方式 `SegLaser(const line_t &_line,const double &l)`，分别是射线的描述（起始坐标和方向），以及延伸的长度。
- 构造方式类似于极坐标系，带来的不便见谅。
### MoveSegLaser
- 会移动的线段激光，随着时间在两处间移动。
- 构造方式 `MoveSegLaser(const line_t &line,const double &length,const point_t &_beg,const point_t &_end,double _d)`，分别是和 `SegLaser` 一样的两个参数（作用相同）、起始坐标移动起点、起始坐标移动终点、每秒起始坐标移动距离。
### RotateLaser
- 会旋转的激光，随着时间在一个角度区间中旋转。
- 构造方式 `RotateLaser(const line_t &_line,double _b,double _e,double _d)`，分别是射线的描述（起始坐标和方向）、延伸的长度、角度的区间上下界、每秒旋转弧度。
## 关卡编写说明
- 你可能想自己写一个关卡。下面可以帮助你编写一个关卡。
```cpp
#include<vector>
#include "engine.h"
using std::vector;
namespace ALevel{//为你的关卡数据设计一个独一无二的命名空间名称方便管理
	vector<RotateLaser> rotatelasers={
	
	};
	vector<SegLaser> seglasers={
		
	};
	vector<Laser> reallasers={
	};
	vector<MoveSegLaser> moveseglasers={
	
	};
	vector<Point> points={
	};
	leveldata getgamedata(){
		leveldata res=makelevel("Put your level name here",put your map length here,vector<Laser *>(),points);//不要直接copy，第一个参数填关卡名称，第二个参数填关卡长度
		registers(res.lasers,rotatelasers);//注册这个类型的障碍物
		registers(res.lasers,seglasers);
		registers(res.lasers,reallasers);
		registers(res.lasers,moveseglasers);
		return res;
	}
}
#include "runner.h"
#ifndef __NO_RUNNING__
int main(){
	gamemain(ALevel::getgamedata());
	return 0;
}
#endif
```
这是一个作者在使用的关卡模板。其中使用到了四种障碍物类型：`RotateLaser`，`SegLaser`，`MoveSegLaser`，`Point`。您可以按照自己喜好删除或保留。已经添加的障碍物只有注册（见注释）才会在关卡中出现。每种类型的障碍物可以查看它的构造函数及名称确定自己要填什么。
- 希望您编写关卡愉快！
## 广告
- 作者希望收到关卡投稿。
- 作者希望您分享各个关卡通关时间。
