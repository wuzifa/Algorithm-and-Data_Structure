#pragma once
#include <easyx.h>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#define MAP_WIDTH_PIXEL (Grid_size * map_width)
#define MAP_HEIGHT_PIXEL (Grid_size * map_height)
using namespace std;


class button
{
public:
	int lefttopx, lefttopy, m_height, m_width, m_radius;
	unsigned int m_buttoncolor, m_textcolor;
	string m_text;

	virtual void draw() = 0;

	virtual bool inarea() = 0;

	virtual bool ispressed() = 0;

	button(int lefttop_x, int lefttop_y, int width, int height, const string& text, unsigned int buttoncolor, unsigned int textcolor, int radius = 0):
		lefttopx(lefttop_x), lefttopy(lefttop_y), m_width(width), m_height(height), m_text(text), m_buttoncolor(buttoncolor), m_textcolor(textcolor), m_radius(radius) {}

}; 

//-------------------------------------------------------------------------------

class roundrect_button : public button
{
public:
	roundrect_button(int lefttop_x, int lefttop_y, int width, int height, const string& text, unsigned int buttoncolor, unsigned int textcolor, int radius):
		button(lefttop_x, lefttop_y, width, height, text, buttoncolor, textcolor, radius) { }
	

	void draw() override;
	bool inarea() override;
	bool ispressed() override;
};



class MoveKey
{
public:
	USHORT statement();
	BYTE value();
};

class Ball
{
private:
	int m_x, m_y, m_radius, m_speed, m_color, move_x, move_y;
public:
	Ball(int x, int y, int radius, int color, int speed) :
		m_x(x), m_y(y), m_radius(radius), m_speed(speed), m_color(color), move_x(0), move_y(0) { }

	void draw();
	void move(); 
};

//-------------------------------------------------------------------------------

class picture
{
public:
	virtual void draw(int x, int y) = 0;
};

class normal_picture: public picture
{
private:
	IMAGE m_img;
	string m_path;
public:
	normal_picture(const string& path, int width, int height);
	void draw(int x, int y) override;
};

class transbkjpg_picture:public picture
{
private:
	IMAGE m_img[2];
	string m_path[2];
public:
	void draw(int x, int y) override;
	transbkjpg_picture(const string& original, const string& mask, int width, int height);
};

class transbkpng_picture : public picture 
{
	
	friend class Animation;
private:
	IMAGE m_img;
	string m_path;
public:
	transbkpng_picture(const string& path, int width, int height);
	void draw(int x, int y) override;
};

//-----------------------------------------------------------------
class Animation//png图像动画
{
	friend void drawAlpha(int  picture_x, int picture_y, IMAGE* picture);
private:
	vector<transbkpng_picture*> m_picture;
	string m_path;
	
public:
	Animation(const string& path, int picture_num, int width, int height);
	void draw(int x, int y, int speed);//可根据当前时间判断画出的是图片数组的哪一张
	~Animation();
};

//-----------------------------------------------------------------------

class Elf_Animation//精灵表动画
{
private:
	IMAGE m_img, m_temimg;
	string m_path;
	int m_single_width, m_single_height, m_frames;//frames表示这一张大图片里总共几帧小图片
public:
	void draw(int x, int y, int speed);//speed为每秒多少张小动画图片
	Elf_Animation(const string& path, int single_width, int single_height, int frames);
};

//===========================================================================================
//格子map[grid_x, grid_y]所属像素范围: x:[grid_x * Grid_size, (grid_x + 1) * Grid_size - 1]
//									 y:[grid_y * Grid_size, (grid_y + 1) * Grid_size - 1]
//判断实体或者玩家所占格子: png图片矩形所涵盖的格子	
//              实际求法: 获取左上角右下角顶点所属格子坐标索引,这两个索引间的格子都属于所占格子(在二维上遍历索引)
//判断是否会collide(穿模),即选取碰撞对传入iscolliding函数时,选取玩家所占格子扩大一圈后的格子内不可穿模物体












class Entity
{
public:
	int m_width, m_height, m_x, m_y;//m_width, m_height: 单张实物png图片的宽度和高度, m_x/y:图片左上角的x或y坐标
	bool m_checkcollision;//是否进行碰撞检测
	Entity(int x, int y, int width, int height, bool check);
	void LocateInGrid(const Entity* entity);
};


class Grid
{
public:
	vector<const Entity*> entities;
	
};


class Spritesheet_player : public Entity
{
private:
	int m_frames, move_x, move_y;//m_frames: 从一个方向看向人物的精灵表的小图片个数, move_x(水平方向是否移动,只有-1,0,1 三个值)
	string m_path;
	vector<Elf_Animation> fourviews;
	enum Direction{FRONT, BACK, LEFT, RIGHT} direction;//对应从哪个方向看向人物的视图
	int move_left, move_right, move_front, move_back;//在屏幕的前后左右方向上是否移动,例如move_left有0或-1两个值,move_back有0或1两个值
	pair<int, int> start_grid;
	pair<int, int> end_grid;
public:
	Spritesheet_player(const string& path, int single_width, int single_height, int frames, int x, int y, bool checkcollision = true);
	void move(int speed);//包括处理输入并根据输入绘制相应动画到屏幕上
	void setsearchrange();
};

class Staticobj : public Entity
{
private:
	IMAGE m_img;
	transbkpng_picture* png_picture;
	bool ispng;
public:
	Staticobj(int x, int y, int width, int height, const char* path, bool checkcollision = true);
	Staticobj(int x, int y, int width, int height, const char* path, bool checkcollision, int);//占位参数版本，用来构造图片是png的staticobj(更好的写法是把这个类写成模板)
	void draw();
	
	~Staticobj();
	//void setdrawnobj(vector<pair<int , int >>& coordinaies);
};




