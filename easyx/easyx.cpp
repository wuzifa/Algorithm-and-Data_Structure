
#include <drawboard.h>
using namespace std;


ExMessage msg = { 0 };

extern const int Grid_size;

extern const int map_width;
extern const int map_height;






//int main(void)
//{
//	initgraph(1280, 960);
//	setbkcolor(WHITE);
//	cleardevice();
//	int x = 100;
//	int y = 100;
//	int move_x = 0;
//	int move_y = 0;
//	int speed = 3;
//	Elf_Animation pikaqiu("assets/pikachu.png", 32, 32, 7);
//	Elf_Animation coins("assets/coins.png", 16, 16, 8);
//	while (true)
//	{
//		peekmessage(&msg, EX_KEY);
//		if (msg.message == WM_KEYDOWN)
//		{
//			switch (msg.vkcode)
//			{
//			case VK_UP:
//				move_y = -1;
//				break;
//			case VK_DOWN:
//				move_y = 1;
//				break;
//			case VK_RIGHT:
//				move_x = 1;
//				break;
//			case VK_LEFT:
//				move_x = -1;
//				break;
//			}
//		}
//		else if (msg.message == WM_KEYUP)
//		{
//			switch (msg.vkcode)
//			{
//			case VK_UP:
//				move_y = 0;
//				break;
//			case VK_DOWN:
//				move_y = 0;
//				break;
//			case VK_RIGHT:
//				move_x = 0;
//				break;
//			case VK_LEFT:
//				move_x = 0;
//				break;
//			}
//		}
//		x += speed * move_x;
//		y += speed * move_y;
//		BeginBatchDraw();
//		cleardevice();
//		pikaqiu.draw(x, y, 4);
//		coins.draw(400, 400, 4);
//		EndBatchDraw();
//		Sleep(15);
//	}
//
//	return 0;
//}


// ==================== 核心界面函数 ====================

/*
 * 功能: 显示主菜单界面
 * 负责人: wzf
 * 参数: 无
 * 返回值: 无
 * 详细流程:
 *   1. 显示游戏标题和Logo
 *   2. 提供主要选项:
 *      - "开始游戏": 直接进入第一关游戏
 *      - "关卡选择": 进入关卡选择界面
 *      - "排行榜": 进入排行榜界面
 *      - "设置": 进入设置界面
 *      - "团队介绍": 进入团队介绍界面
 *      - "退出游戏": 退出程序
 *   3. 处理键盘输入和选项导航
 *   4. 支持鼠标点击选择
 *   5. 添加菜单选项高亮效果
 *   6. 根据用户选择切换到对应状态
 */

 //class transbkpng_picture//可透明贴图的Png图像类
 //{
 //private:
 //	IMAGE m_img;
 //	string m_path;
 //public:
 //	transbkpng_picture(const string& path, int width, int height);
 //	void draw(int x, int y);
 //};
 //
 //transbkpng_picture::transbkpng_picture(const string& path, int width, int height)
 //	: m_path(path)
 //{
 //	loadimage(&m_img, m_path.c_str(), width, height);
 //}
 //
 //void drawAlpha(int picture_x, int picture_y, IMAGE* picture) //显示带透明通道的png图像，x为载入图片的X坐标，y为Y坐标
 //{
 //
 //	// 变量初始化
 //	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
 //	DWORD* draw = GetImageBuffer();
 //	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
 //	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
 //	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
 //	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
 //	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
 //	int dstX = 0;    //在显存里像素的角标
 //
 //	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
 //	for (int iy = 0; iy < picture_height; iy++)
 //	{
 //		for (int ix = 0; ix < picture_width; ix++)
 //		{
 //			int srcX = ix + iy * picture_width; //在显存里像素的角标
 //			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
 //			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
 //			int sg = ((src[srcX] & 0xff00) >> 8);   //G
 //			int sb = src[srcX] & 0xff;              //B
 //			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
 //			{
 //				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
 //				int dr = ((dst[dstX] & 0xff0000) >> 16);
 //				int dg = ((dst[dstX] & 0xff00) >> 8);
 //				int db = dst[dstX] & 0xff;
 //				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
 //					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
 //					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
 //			}
 //		}
 //	}
 //}
 //
 //void transbkpng_picture::draw(int x, int y)
 //{
 //	drawAlpha(x, y, &m_img);
 //}


//void showMenu()
//{
//	initgraph(1280, 960);
//	IMAGE img;
//	loadimage(&img, "assets/menubackground.png", 1280, 960);
//	transbkpng_picture title("assets/gametitle.png", 453, 167);
//	setbkcolor(WHITE);
//	setbkmode(TRANSPARENT);
//	settextstyle(50, 0, "方正舒体");
//	settextcolor(WHITE);
//	setfillcolor(RGB(227, 225, 76));
//	int highlight_y = 391;
//	int highlight_x = 145;
//	while (true)
//	{
//		peekmessage(&msg, EX_KEY | EX_MOUSE);
//		if (msg.message == WM_KEYDOWN)
//		{
//			switch (msg.vkcode)
//			{
//			case 'W':
//				if (highlight_x > 145)
//				{
//					highlight_y -= 100;
//					highlight_x -= 20;
//				}
//				break;
//			case 'S':
//				if (highlight_x < 185)
//				{
//					highlight_y += 100;
//					highlight_x += 20;
//				}
//				break;
//			case VK_RETURN:
//				switch (highlight_x)
//				{
//				case 145:
//					cout << "开始游戏" << endl;
//					//initLevel(1)
//					break;
//				case 165:
//					cout << "关卡选择" << endl;
//					//showLevelSelect();
//					break;
//				case 185:
//					cout << "退出游戏" << endl;
//					//return;
//					break;
//				}
//			}
//		}
//		
//		BeginBatchDraw();
//		cleardevice();
//		putimage(0, 0, &img);
//		title.draw(544, 36);
//		solidrectangle(highlight_x, highlight_y, highlight_x + 192, highlight_y + 50);
//		outtextxy(145, 391, "开始游戏");//高度50, 宽度192
//		outtextxy(165, 491, "关卡选择");
//		outtextxy(185, 591, "退出游戏");
//		EndBatchDraw();
//		msg.message = 0;
//		Sleep(15);
//	}
//	
//	
//	
//	
//	
//}


static int x = 500;
static int y = 512 - 50;
static int move_h = 0;
static int move_v = 0;
static int speed = 2;
static bool main_exit = false;
//void moveelement(Staticobj& entity)
//{
//	if (msg.message == WM_KEYDOWN)
//	{
//		switch (msg.vkcode)
//		{
//		case VK_UP:
//			move_v = -1;
//			break;
//		case VK_DOWN:
//			move_v = 1;
//			break;
//		case VK_RIGHT:
//			move_h = 1;
//			break;
//		case VK_LEFT:
//			move_h = -1;
//			break;
//		case VK_ESCAPE:
//			main_exit = true;
//			break;
//		}
//	}
//	else if (msg.message == WM_KEYUP)
//	{
//		switch (msg.vkcode)
//		{
//		case VK_UP:
//			move_v = 0;
//			break;
//		case VK_DOWN:
//			move_v = 0;
//			break;
//		case VK_RIGHT:
//			move_h = 0;
//			break;
//		case VK_LEFT:
//			move_h = 0;
//			break;
//		}
//	}
//	int new_x = x + move_h * speed;
//	int new_y = y + move_v * speed;
//	if (new_x >= 0 && new_x + entity.m_width - 1 < MAP_WIDTH_PIXEL && new_y >= 0 && new_y + entity.m_height - 1 < MAP_HEIGHT_PIXEL)
//	{
//		x += move_h * speed;
//		y += move_v * speed;
//	}
//	entity.draw(x, y);
//	cout << x << ' ' << y << endl;
//}


int main(void)
{
	initgraph(MAP_WIDTH_PIXEL, MAP_HEIGHT_PIXEL);
	setbkcolor(WHITE);
	Spritesheet_player wizard("assets/wizard/wizardn.png", 40, 40, 3, 100, 100);
	Staticobj pool(200, 450, 40, 40, "assets/map_elements/pool.png", true, 0);
	Staticobj grass(400, 420, 50, 50, "assets/map_elements/grass5.png", false, 0);
	vector<Staticobj> path;
	for (int i = 0; i <= 600; i += 50)
	{
		for (int j = 412; j <= 462; j += 50)
		{
			path.emplace_back(i, j, 50, 50, "assets/map_elements/path1.png", false);
		}
	}
	path.emplace_back(150, 362, 50, 50, "assets/map_elements/path1.png", false);
	path.emplace_back(350, 362, 50, 50, "assets/map_elements/path1.png", false);
	path.emplace_back(350, 362, 50, 50, "assets/map_elements/path1.png", false);
	vector<Staticobj> trees;
	cout << trees.size() << ' ' << trees.capacity() << endl;
	//trees.reserve(4);
	trees.emplace_back(90, 465, 40, 40, "assets/map_elements/tree0.png", true, 0);
	cout << trees.size() << ' ' << trees.capacity() << endl;
	trees.emplace_back(130, 465, 40, 40, "assets/map_elements/tree0.png", true, 0);
	cout << trees.size() << ' ' << trees.capacity() << endl;
	//trees.emplace_back(130, 425, 40, 40, "assets/map_elements/tree0.png", true, 0);
	//trees.emplace_back(170, 465, 40, 40, "assets/map_elements/tree0.png", true, 0);
	trees.emplace_back(0, 0, 40, 40, "assets/map_elements/tree0.png", true, 0);
	while (true)
	{
		peekmessage(&msg, EX_KEY);
		
		BeginBatchDraw();
		cleardevice();
		
		
		for (Staticobj& val : path)
		{
			val.draw();
		}
		grass.draw();
		pool.draw();
		wizard.move(2);
		EndBatchDraw();
		msg.message = 0;
		//if (main_exit)
		//	break;
		Sleep(10);
	}
	return 0;
}

//测试情况：人物不在static_obj附近也算成碰撞了
//问题:
//玩家的构造函数会触发entity构造函数,而entity构造函数中有LocateInGrid()函数，导致future对象和player对象被判定为碰撞，故玩家无法移动
//解决方案：将LocateInGrid()函数移出entity构造函数,转为放在static_obj构造函数内调用
//
//调试查看监视的变量时也有作用域？✓
// 
//静态类变量定义在不同文件的时候,他们在运行时构造函数初始化有顺序吗，如果一个变量的构造函数需要对另一个变量操作，但那个变量还没有调用构造函数怎么办
//！！！此时：构造顺序未定义,要么崩溃要么出现未定义行为
//解决方案：比如b要用a，那么就写一个
//btype& getb()
//{
//    static btype b;
//	  return b;
//}
//然后在a的构造函数里：
//{ 
//    ......
//    getb.dosomething(); 
//    ...... 
//}
//现在程序中存在的定时炸弹
//类中有裸指针成员没有正确处理
//考虑三个问题：谁分配，谁释放，能被拷贝吗
//手写三件套：拷贝构造，赋值运算符，析构函数 [来避免]: 重复释放，内存泄漏，访问悬空指针(内存已释放但指针还指向那块内存，然后解应用指针)
//现代C++下还要额外定义移动构造，移动赋值
//不能delete不是new出来的内存
// 
//上面staticobj里面有一个裸指针成员，正确写了他的析构但是没写他的拷贝构造，导致在vector<staticobj>扩容的时候使用默认拷贝构造造成浅拷贝，
//后面在扩容的时候当一个元素经历第一次扩容时它内部的指针指向的地址已经释放过了，在经历第二次扩容时又释放这个内存一遍，出错
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
//

