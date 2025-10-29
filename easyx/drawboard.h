#pragma once
//!!!!!!!!!!!!!!!!!:
//1.exmessage中的message变量都是WM_,而这些消息 (WM_XXXX) 判断的依据的是 事件过程（某一瞬间发生的动作），而不是持续状态
//msg.lbutton , 当前左键是否处于按下状态（true/false）

//msg.rbutton , 当前右键是否处于按下状态
//
//msg.shift / msg.ctrl , 键盘修饰键是否按下
//
//msg.vkcode , 键盘虚拟键码
//上面四条才是判断的状态
//2.Windows/EasyX 内部色号的存储形式是 0x00BBGGRR，和一般复制下来的或者网上找的色号顺序不一样！！！
//3.beginbatchdraw引起的过程
//(1).EasyX 在内部启用一个后台缓冲区,此时的缓冲区会先拷贝当前前台窗口的内容作为起点！！！！！！！！！！！！！！
//(2).之后的所有绘图操作会画到这个缓冲区里，而不是马上显示到屏幕
//(3).调用EndBatchDraw()之后,把后台缓冲区画布一次性刷到前台窗口
#include <easyx.h>
#include <iostream>
#include <vector>
#include <easyx_function.h>
#include <deque>
extern ExMessage msg;
using namespace std;
static int last_x = 0, last_y = 0;
static int flag = 0;



static int MAX_RADIUS = 13, MIN_RADIUS = 1, now_radius = 1;//点和笔的宽度要*2，这里是半径


static vector<int> red = { 0xFFE5E5, 0xFFCCCC, 0xFFB2B2, 0xFF9999, 0xFF7F7F,
0xFF6666, 0xFF4C4C, 0xFF3333, 0xFF1919, 0xFF0000 };

static vector<int> blue = { 0xE6F0FF, 0xCCDFFF, 0xB3CCFF, 0x99B8FF, 0x7FA3FF,
0x668CFF, 0x4C73FF, 0x335CFF, 0x1945FF, 0x0033FF };

static vector<int> green = { 0xE6FFE6, 0xCCFFCC, 0xB3FFB3, 0x99FF99, 0x7FFF7F,
0x66FF66, 0x4CFF4C, 0x33FF33, 0x19FF19, 0x00FF00 };

static vector<int> purple = { 0xF2E6FF, 0xE0CCFF, 0xCCB3FF, 0xB899FF, 0xA37FFF,
0x8C66FF, 0x734CFF, 0x5933FF, 0x4019FF, 0x2600FF };

static vector<int> white = { 0xFFFFFF, 0xF2F2F2, 0xE6E6E6, 0xCCCCCC, 0xB3B3B3,
0x999999, 0x7F7F7F, 0x666666, 0x4C4C4C, 0x333333 };

static vector<int> orange = { 0xFFF2E0, 0xFFE0B2, 0xFFCC80, 0xFFB84D, 0xFFA31A,
0xFF8C00, 0xE67A00, 0xCC6600, 0xB35900, 0x994C00 };

static vector<int> yello = { 0xFFFFE5, 0xFFFFCC, 0xFFFFB2, 0xFFFF99, 0xFFFF7F,
0xFFFF66, 0xFFFF4C, 0xFFFF33, 0xFFFF19, 0xFFFF00 };

extern const vector<int>* now_colorset;

extern int now_color;

COLORREF RGBtoColorRef(int rgb);

void leftbuttonpressed();


void leftbuttonup();


void drawline();


void changepenRADIUS();


void changecolor(BYTE character);

void changecolorset(BYTE character);


void drawhomepage();

class Imagedeque
{
private:
	unsigned int MAX_SIZE;
	deque<IMAGE> undoqueue;
	int nowframe;
	roundrect_button previous, next;
public:
	void loadnowpicture();
	void button();
	Imagedeque(unsigned int maxsize);
	void init();
	void clearundoqueue();
};