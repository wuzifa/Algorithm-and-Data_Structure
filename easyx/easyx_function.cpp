#include <easyx_function.h>
#include <time.h>
extern ExMessage msg;


extern const vector<int>* now_colorset;

extern int now_color;

extern bool ignoreNextLbuttonup;

extern Staticobj wall;

extern const int Grid_size = 32;
extern const int map_width = 20;
extern const int map_height = 16;

Grid map[map_width][map_height];

//将颜色淡化
int lightenColor(int hexColor, double factor = 0.2) 
{
	// 提取 R、G、B
	int r = (hexColor >> 16) & 0xFF;
	int g = (hexColor >> 8) & 0xFF;
	int b = hexColor & 0xFF;

	// 计算更淡的颜色（往 255 靠近）
	r = r + (int)((255 - r) * factor);
	g = g + (int)((255 - g) * factor);
	b = b + (int)((255 - b) * factor);

	// 防止溢出
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;

	// 重新组合为 0xRRGGBB
	return (r << 16) | (g << 8) | b;
}
COLORREF RGBtoColorRef(int rgb);

void roundrect_button::draw()
{
	if (inarea())
	{
		setfillcolor(lightenColor(m_buttoncolor, 0.6));
		
	}
	else
	{
		setfillcolor(RGBtoColorRef(m_buttoncolor));
		
	}
	solidroundrect(lefttopx, lefttopy, lefttopx + m_width, lefttopy + m_height, m_radius, m_radius);
	settextcolor(RGBtoColorRef(m_textcolor));
	setbkmode(TRANSPARENT);
	outtextxy(lefttopx + (m_width - textwidth(m_text.c_str())) / 2, lefttopy + (m_height - textheight(m_text.c_str())) / 2, m_text.c_str());
	settextcolor(BLACK);
	setbkmode(OPAQUE);
	setfillcolor(RGBtoColorRef((*now_colorset)[now_color]));
}

bool roundrect_button::inarea()
{
	if (msg.x > lefttopx && msg.x < lefttopx + m_width && msg.y > lefttopy && msg.y < lefttopy + m_height)
	{
		return true;
	}
	return false;
}

bool roundrect_button::ispressed()
{
	if (inarea() && msg.message == WM_LBUTTONDOWN)
	{
		return true;
	}
	return false;
}

USHORT MoveKey::statement()
{
	return msg.message;
}

BYTE MoveKey::value()
{
	return msg.vkcode;
}

void Ball::draw()
{
	setfillcolor(RGB(GetRValue(m_color), GetGValue(m_color), GetBValue(m_color)));
	solidcircle(m_x, m_y, m_radius);
}

void Ball::move()
{
	if (msg.message == WM_KEYDOWN)
	{
		switch (msg.vkcode)
		{
		case VK_UP:
			move_y = -1;
			break;
		case VK_DOWN:
			move_y = 1;
			break;
		case VK_RIGHT:
			move_x = 1;
			break;
		case VK_LEFT:
			move_x = -1;
			break;
		}
	}
	else if (msg.message == WM_KEYUP)
	{
		switch (msg.vkcode)
		{
		case VK_UP:
			move_y = 0;
			break;
		case VK_DOWN:
			move_y = 0;
			break;
		case VK_RIGHT:
			move_x = 0;
			break;
		case VK_LEFT:
			move_x = 0;
			break;
		}
	}
	m_x += m_speed * move_x;
	m_y += m_speed * move_y;
}

normal_picture::normal_picture(const string& path, int width, int height):
	m_path(path)
{
	loadimage(&m_img, path.c_str(), width, height);
}

void normal_picture::draw(int x, int y)
{
	putimage(x, y, &m_img);
}



transbkjpg_picture::transbkjpg_picture(const string& original, const string& mask, int width, int height)
{
	m_path[0] = mask;
	m_path[1] = original;
	loadimage(m_img, m_path[0].c_str(), width, height);
	loadimage(m_img + 1, m_path[1].c_str(), width, height);
}

void transbkjpg_picture::draw(int x, int y)
{
	putimage(x, y, m_img, NOTSRCERASE);
	putimage(x, y, m_img + 1, SRCINVERT);
}

void drawAlpha(int picture_x, int picture_y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{

	// 变量初始化
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
    int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}



transbkpng_picture::transbkpng_picture(const string& path, int width, int height)
	: m_path(path)
{
	loadimage(&m_img, m_path.c_str(), width, height);
}

void transbkpng_picture::draw(int x, int y)
{
	drawAlpha(x, y, &m_img);
}

//------------------------------------------------------------------------------------

Animation::Animation(const string& path, int picture_num, int width, int height):
	m_path(path)
{
	for(int i = 0; i < picture_num; i++)
	{
		m_path.replace(m_path.size() - 5, 1, to_string(i + 1));
		if (i > 9)
		{
			m_path.erase(m_path.size() - 7, 1);
		}
		m_picture.push_back(new transbkpng_picture(m_path, width, height));
	}
}

void Animation::draw(int x, int y, int speed)//speed:一秒几张动画
{
	int frame_start = clock();
	int index = (clock() / (1000 / speed)) % m_picture.size();
	drawAlpha(x, y, &(m_picture[index]->m_img));
}

Animation::~Animation()
{
	for (auto i : m_picture)
	{
		delete i;
		i = nullptr;
	}
}

//---------------------------------------------------------





void Elf_Animation::draw(int x, int y, int speed)
{
	int index = (clock() / (1000 / speed)) % m_frames;
	SetWorkingImage(&m_temimg);
	putimage(0, 0, m_single_width, m_single_height, &m_img, index * m_single_width, 0);//上面两步: 先根据当前时间将小图片裁剪到临时画布，因为drawalpha没有裁剪功能
	SetWorkingImage(nullptr);//！！把绘图目标切换回主屏幕
	drawAlpha(x, y, &m_temimg);//利用drawalpha函数将带透明通道的png图片画到主屏幕
}

Elf_Animation::Elf_Animation(const string& path, int single_width, int single_height, int frames):
	m_path(path), m_single_width(single_width), m_single_height(single_height), m_frames(frames)
{
	m_temimg = IMAGE(m_single_width, m_single_height);//赋值m_temimg,否则上面已经默认初始化，这块临时画布长和宽都是0
	loadimage(&m_img, m_path.c_str());
}
//---------------------------------------------------------------------------------







Entity::Entity(int x, int y, int width, int height, bool check):
	m_x(x), m_y(y), m_width(width), m_height(height), m_checkcollision(check) {}

void Entity::LocateInGrid(const Entity* entity)
{
	pair<int, int> start_grid(m_x / Grid_size, m_y / Grid_size);
	pair<int, int> end_grid((m_x + m_width - 1) / Grid_size, (m_y + m_height - 1) / Grid_size);
	for (int j = start_grid.second; j <= end_grid.second; j++)
	{
		for (int i = start_grid.first; i <= end_grid.first; i++)
		{
			map[i][j].entities.push_back(entity);
		}
	}
}

bool iscolliding(const Entity& a, const Entity& b)
{
	return!(a.m_x + a.m_width - 1 < b.m_x  ||  //a在b左边
		    b.m_x + b.m_width - 1 < a.m_x  ||  //a在b右边
		    a.m_y + a.m_height - 1 < b.m_y ||  //a在b上面
		    b.m_y + b.m_height - 1 < a.m_y );  //a在b下面
}

Spritesheet_player::Spritesheet_player(const string& path, int single_width, int single_height, int frames, int x, int y, bool checkcollision):
	Entity(x, y, single_width, single_height, checkcollision),
	m_path(path), m_frames(frames), direction(BACK),
	move_x(0), move_y(0), move_left(0), move_right(0), move_front(0), move_back(0),
	start_grid(make_pair(0, 0)), end_grid(make_pair(0, 0))
{
	for (int i = 0; i < 4; i++)
	{
		m_path.replace(m_path.size() - 5, 1, to_string(i + 1));
		fourviews.push_back(Elf_Animation(m_path, m_width, m_height, m_frames));
	}
}

void Spritesheet_player::move(int speed)
{
	bool collision = false;
	if (GetAsyncKeyState('W') & 0x8000)
		move_front = -1;
	else
		move_front = 0;
	if (GetAsyncKeyState('S') & 0x8000)
		move_back = 1;
	else
		move_back = 0;
	if (GetAsyncKeyState('A') & 0x8000)
		move_left = -1;
	else
		move_left = 0;
	if (GetAsyncKeyState('D') & 0x8000)
		move_right = 1;
	else
		move_right = 0;
	move_x = 0 + move_left + move_right;
	move_y = 0 + move_front + move_back;
	if (move_x != 0 || move_y != 0)
	{
		setsearchrange();
		Entity future(m_x + speed * move_x, m_y + speed * move_y, m_width, m_height, true);
		for (int i = start_grid.first; i <= end_grid.first; i++)
		{
			for (int j = start_grid.second; j <= end_grid.second; j++)
			{
				for (const Entity* grid_entities : map[i][j].entities)
				{
					if (iscolliding(future, *grid_entities))
					{
						collision = true;
					}
				}
			}
		}
		if (!collision)
		{
			int new_x = m_x + move_x * speed;
			int new_y = m_y + move_y * speed;
			if (new_x >= 0 && new_x + m_width - 1 < MAP_WIDTH_PIXEL && new_y >= 0 && new_y + m_height - 1 < MAP_HEIGHT_PIXEL)
			{
				m_x += move_x * speed;
				m_y += move_y * speed;
			}
		}
	}
	switch (move_x)
	{
	case 1:
		direction = RIGHT;
		break;
	case -1:
		direction = LEFT;
		break;
	case 0:
		switch (move_y)
		{
		case 0:
			direction = FRONT;
			break;
		case -1:
			direction = BACK;
			break;
		case 1:
			direction = FRONT;
		}
	}
	fourviews[direction].draw(m_x, m_y, m_frames);
}







void Spritesheet_player::setsearchrange()
{
	start_grid = make_pair(m_x / Grid_size, m_y / Grid_size);
	end_grid = make_pair((m_x + m_width - 1) / Grid_size, (m_y + m_height - 1) / Grid_size);
	if (start_grid.first - 1 >= 0)
		start_grid.first -= 1;
	if (start_grid.second - 1 >= 0)
		start_grid.second -= 1;
	if (end_grid.first + 1 < map_width)
		end_grid.first += 1;
	if (end_grid.second + 1 < map_height)
		end_grid.second += 1;
}

Staticobj::Staticobj(int x, int y, int width, int height, const char* path, bool checkcollision)
	: Entity(x, y, width, height, checkcollision), png_picture(nullptr), ispng(false)
{
	loadimage(&m_img, path, width, height);
	if(checkcollision)
		LocateInGrid(this);
}



Staticobj::Staticobj(int x, int y, int width, int height, const char* path, bool checkcollision, int)
	: Entity(x, y, width, height, checkcollision), png_picture(new transbkpng_picture(path, width, height)), 
	  m_img(IMAGE(0, 0)), ispng(true)
{
	if (checkcollision)
		LocateInGrid(this);
}


void Staticobj::draw()
{
	if (!ispng)
		putimage(m_x, m_y, &m_img);
	else
		png_picture->draw(m_x, m_y);
}



Staticobj::~Staticobj()
{
	delete png_picture;
	png_picture = nullptr;
}

//void Staticobj::setdrawnobj(vector<pair<int, int >>& coordinaies)
//{
//	if (m_checkcollision)
//	{
//		for (auto val : coordinaies)
//		{
//			drawnobj.push_back(new Entity(val.first, val.second, m_width, m_height, true));
//			LocateInGrid(*(drawnobj.end() - 1));
//		}
//	}
//	else
//	{
//		for (auto val : coordinaies)
//		{
//			drawnobj.push_back(new Entity(val.first, val.second, m_width, m_height, false));
//		}
//	}
//}


