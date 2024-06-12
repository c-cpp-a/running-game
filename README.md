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
