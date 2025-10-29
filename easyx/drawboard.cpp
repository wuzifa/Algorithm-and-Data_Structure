#include <drawboard.h>


const vector<int>* now_colorset = &white;
int now_color = now_colorset->size() - 1;
Imagedeque cancel(50);

bool ignoreNextLbuttonup = false;

COLORREF RGBtoColorRef(int rgb) {
	int r = (rgb >> 16) & 0xFF;
	int g = (rgb >> 8) & 0xFF;
	int b = rgb & 0xFF;
	return RGB(r, g, b); // GDI 的 RGB 宏会生成 BGR 顺序
}

void leftbuttonpressed()
{
	
	solidcircle(msg.x, msg.y, now_radius);
	flag = 1;
	last_x = msg.x;
	last_y = msg.y;
}

void leftbuttonup()
{
	
	cancel.loadnowpicture();
	flag = 0;
}

void drawline()
{

	if (flag)
	{
		if (msg.lbutton == true)//后面发现的bug,如果仅靠flag,当按着鼠标拖出屏幕的时候系统会认为鼠标信息突然断掉
//此时没有lbuttonup来改变flag,当鼠标拖回屏幕(左键并不处于按下状态)，仍会一直画画
//靠msg.lbutton，只要鼠标在屏幕内的每一帧都会判断鼠标是否处于被按下状态，就不会有上面问题，并且仅靠lbutton也可以实现按住画画
		{
			line(last_x, last_y, msg.x, msg.y);
			last_x = msg.x;
			last_y = msg.y;
		}
	}
}

void changepenRADIUS()
{
	if (msg.wheel < 0)
	{
		if (now_radius + msg.wheel / 120 >= MIN_RADIUS)
			now_radius += msg.wheel / 120;

	}
	else
	{
		if (now_radius + msg.wheel / 120 <= MAX_RADIUS)
			now_radius += msg.wheel / 120;

	}
	setlinestyle(PS_SOLID, now_radius * 2);
}

void changecolor(BYTE character)
{
	if (character == 'Q')
	{
		now_color = (now_color + now_colorset->size() - 1) % now_colorset->size();
	}
	else if (character == 'E')
	{
		now_color = (now_color + 1) % now_colorset->size();
	}
	int color = (*now_colorset)[now_color];
	setfillcolor(RGBtoColorRef(color));
	setlinecolor(RGBtoColorRef(color));
}

void changecolorset(BYTE character)
{
	switch (character)
	{
	case 'R':
		now_colorset = &red;
		break;
	case 'B':
		now_colorset = &blue;
		break;
	case 'G':
		now_colorset = &green;
		break;
	case 'P':
		now_colorset = &purple;
		break;
	case 'W':
		now_colorset = &white;
		break;
	case 'Y':
		now_colorset = &yello;
		break;
	case 'O':
		now_colorset = &orange;
		break;
	}
	now_color = now_colorset->size() - 1;
	int color = (*now_colorset)[now_color];
	setfillcolor(RGBtoColorRef(color));
	setlinecolor(RGBtoColorRef(color));
}


void createboard()
{
	setlinestyle(PS_SOLID, now_radius * 2);
	setlinecolor(RGBtoColorRef((*now_colorset)[now_color]));
	string text("back");
	roundrect_button back(20, 20, 60, 40, text, 0xC7804A, 0x296061, 10);
	cancel.init();
	while (true)
	{
		BeginBatchDraw();
		setfillcolor(WHITE);
		solidcircle(getwidth() - (MAX_RADIUS + 20), (MAX_RADIUS + 20), MAX_RADIUS);
		setfillcolor(RGBtoColorRef((*now_colorset)[now_color]));
		solidcircle(getwidth() - (MAX_RADIUS + 20), (MAX_RADIUS + 20), now_radius);
		back.draw();
		if (peekmessage(&msg, EX_MOUSE | EX_KEY))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				leftbuttonpressed();
				break;
			case WM_MOUSEMOVE:
				drawline();
				break;
			case WM_LBUTTONUP:
				if (ignoreNextLbuttonup)//此处只希望在画板上左键弹起时触发WM_LBUTTONUP，所以这里的意思是防止在点击撤销或者前进按钮时也触发WM_LBUTTONUP
				{
					ignoreNextLbuttonup = false;//将下一个"忽略左键弹起开关"设置为假,否则画布上的左键弹起也会被忽略了
				}
				else
				{
					leftbuttonup();
					break;
				}
			
			case WM_MOUSEWHEEL:
				changepenRADIUS();
				break;
			case WM_KEYDOWN:
				switch (msg.vkcode)
				{
				case 'Q':
				case 'E':
					changecolor(msg.vkcode);
					break;
				case 'C':
					cleardevice();
					cancel.loadnowpicture();
					break;
				default:
					changecolorset(msg.vkcode);
					break;
				}
				break;
			}

		}
		
		if (back.ispressed())
		{
			cleardevice();
			EndBatchDraw();
			cancel.clearundoqueue();
			msg.message = 0;
			break;
		}
		cancel.button();
		EndBatchDraw();
		msg.message = 0;
	}
}

void drawhelp()
{
	string text("back");
	roundrect_button back(20, 20, 60, 40, text, 0xC7804A, 0x296061, 10);
	transbkpng_picture help("assets/illustration.png",783, 495);
	back.draw();
	help.draw(150, 150);
	while (true)
	{
		BeginBatchDraw();
		peekmessage(&msg, EX_MOUSE);
		back.draw();
		
		if (back.inarea())
		{
			
			if (back.ispressed())
			{
				msg.message = 0;
				return;
			}
		}
		EndBatchDraw();
		
	}


}

void drawhomepage()
{
	initgraph(1280, 960, EX_SHOWCONSOLE | EX_DBLCLKS);
	setbkcolor(WHITE);
	cleardevice();
	string hometext[4] = { "start", "help", "more", "exit"};
	roundrect_button start(900, 300, 100, 50, hometext[0], 0x8AC4D4, 0xFF7F27, 20);
	roundrect_button help(900, 500, 100, 50, hometext[1], 0x8AC4D4, 0xFF7F27, 30);
	roundrect_button more(900, 700, 100, 50, hometext[2], 0x8AC4D4, 0xFF7F27, 40);
	
	roundrect_button exit(20, 20, 60, 40, hometext[3], 0xC7804A, 0x296061, 20);
	transbkpng_picture homepage("assets/homepage.png", 1280, 960);
	int isfromboard = 1;
	while (true)
	{
		peekmessage(&msg, EX_MOUSE);
		BeginBatchDraw();
		if (isfromboard)
		{
			homepage.draw(0, 0);
			isfromboard = 0;
		}
		start.draw();
		help.draw();
		more.draw();
		exit.draw();
		if (start.ispressed())
		{
			cleardevice();
			EndBatchDraw();
			ignoreNextLbuttonup = true;//在按下开始键后需要忽略下一个WM_LBUTTONUP，否则在createboard循环中会误触发WM_LBUTTONUP
			createboard();
			isfromboard = 1;
		}
		if (help.ispressed())
		{
			cleardevice();
			EndBatchDraw();
			drawhelp();
			isfromboard = 1;
		}
		if (exit.ispressed())
		{
			cleardevice();
			EndBatchDraw();
			break;
		}
		EndBatchDraw();
		msg.message = 0;
		Sleep(10);
	}
}

void Imagedeque::loadnowpicture()
{
	IMAGE img(1280, 960);
	getimage(&img, 0, 0, 1280, 960);
	if (nowframe != undoqueue.size() - 1)
	{
		undoqueue.erase(undoqueue.begin() + nowframe + 1, undoqueue.end());
		nowframe++;
	}
	else
	{
		if (undoqueue.size() >= MAX_SIZE)
			undoqueue.pop_front();
		else
			nowframe++;
	}

	undoqueue.push_back(img);
}



void Imagedeque::button()
{
	previous.draw();
	next.draw();
	if (previous.ispressed())
	{
		ignoreNextLbuttonup = true;//在按下createbiard中的按钮时就要忽略下一个WM_LBUTTONUP，否则会被createboard循环误捕获
		if (nowframe > 0)
		{
			nowframe--;
			putimage(0, 0, &undoqueue[nowframe]);
		}
	}
	if (next.ispressed())
	{
		ignoreNextLbuttonup = true;
		if (nowframe < undoqueue.size() - 1)
		{
			nowframe++;
			putimage(0, 0, &undoqueue[nowframe]);
		}
	}
}

Imagedeque::Imagedeque(unsigned int maxsize) :
	MAX_SIZE(maxsize), nowframe(0), 
	previous(20, 110, 60, 40, string("<"), 0xC7804A, 0x296061, 10),
	next(20, 200, 60, 40, string(">"), 0xC7804A, 0x296061, 10) {}

void Imagedeque::init()
{
	undoqueue.push_back(IMAGE(1280, 960));
	getimage(&undoqueue[0], 0, 0, 1280, 960);
}

void Imagedeque::clearundoqueue()
{
	nowframe = 0;
	undoqueue.clear();
}

