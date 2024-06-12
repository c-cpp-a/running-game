#ifndef __SPRITE_BASE_HEADER_FILE_
#define __SPRITE_BASE_HEADER_FILE_
#include<string>
#include<graphics.h>
#include "../graphdef.h"
//角色类型id
#define SPRITEID(X) \
virtual const std::string spriteid() const{\
return X;\
}
//角色大类的id
#define CLASSID(X) \
virtual const std::string classid() const{\
return X;\
}
class Sprite{
public:
	SPRITEID("Sprite")
	CLASSID("Sprite")
private:
	point_t pos;
protected:
	point_t &getpos(){
		return pos;
	}
public:
	Sprite(const point_t &_pos):pos(_pos){}
	virtual ~Sprite(){}
	virtual void show(color_t color) const=0;
	virtual void show(const Sprite &,color_t color) const{};
	virtual bool hit(const Sprite &) const=0;
	virtual void update(){
		
	}
	virtual void debug() const{
		
	}
	const point_t &getpos() const{
		return pos;
	} 
	const point_t &cgetpos() const{
		return getpos();
	}
};
double distance(const Sprite &a,const Sprite &b){
	return distance(a.getpos(),b.getpos());
}
#endif
