#ifdef RUN_GOBANG
#include<iostream>
#include <chrono>
#include <thread>
#include <map>
#include <conio.h>
#include <windows.h>

using namespace std;





//C/C++:
// -------------------- 数据设计 --------------------
/*
    棋盘:
        board[i][j]表示坐标(i,j)的值
        0表示空地
        1表示黑子
        2表示白子
    如: board[3][6] = 1  表示(3,6)的位置是黑子
*/
int board[19][19];

// 表示当前回合数  偶数表示黑棋落子  奇数表示白棋落子
// 如: flag = 20 表示当前是第[20]次落子  由黑方落子
int flag;

//建立board中数字与棋子的对应关系
//0 -> 空, 1 -> 黑旗(B), 2 -> 白棋(W)
char chess[4] = " BW";

// -------------------- 数据设计 --------------------


// -------------------- service --------------------
/*
    负责人: 张三
    功能: init: 初始化游戏数据
        将棋盘的值初始化为0
        当前回合设为黑棋(flag设为0)
    参数: void
    返回值: void
*/
void init();

/*
    *难点1
    负责人: 张三
    功能: isWin: 根据传入的坐标(board对应位置)和flag值 判断落点后是否获胜
    参数:
        x: 当前回合落子的x坐标
        y: 当前回合落子的y坐标
    返回值:
        0表示没有获胜
        1表示黑子胜利
        2表示白子胜利
*/
int isWin(int x, int y);

/*
    负责人: 张三
    功能: playerMove: 在指定位置落子
        如果board[x][y]是空地 则修改board[x][y]的值:改为相应颜色(flag对应颜色)        否则不操作
    参数:
        x: 当前回合落子的x坐标
        y: 当前回合落子的y坐标
    返回值:
        0表示落子失败 (棋盘已经有子)
        1表示落子成功

*/
int playerMove(int x, int y);
// -------------------- service --------------------



// -------------------- view --------------------
/*
    负责人: 张三
    功能: menuView: 展示选项, 玩家可以在这里选择进入游戏, 进入设置或退出游戏
        while(1){
            1. 展示选项
            2. 用户输入
            3. 根据输入进行对应处理
                进入游戏: 调用游戏界面函数gameView();
                进入设置: 打印敬请期待... 重新循环
                退出游戏: 调用exit(0);
        }
    参数: void
    返回值: void
*/
void menuView();

/*
    负责人: 张三
    功能: gameView_ShowBoard: 根据board数组 打印游戏棋盘
    参数: void
    返回值: void
*/
void gameView_ShowBoard();

/*
    负责人: 张三
    功能: winView:
        根据flag的值  打印游戏胜利界面  用户可以按任意键(使用getch函数)退出当前界面
    参数: void
    返回值: void
*/
void winView();

/*
    *难点2
    负责人: 张三
    功能: gameView: 游戏界面整合
        初始化游戏数据(调用函数init())
        while(1){
            打印游戏界面(调用函数gameView_ShowBoard())
            接收玩家坐标输入

            落子(调用落子函数playerMove())
                (如果落子失败 重新开始循环)

            判断游戏是否胜利(调用胜利判断函数isWin())
                (如果游戏胜利 调用胜利界面函数 然后结束当前界面)
            切换玩家(修改flag值)
        }
    参数: void
    返回值: void
*/
void gameView();
// -------------------- view --------------------

int main()
{
	SetConsoleOutputCP(65001); // 强制控制台使用 UTF-8
    cout << u8"中文输出测试" << endl;
    menuView();
    return 0;
}

void init() 
{
    memset(board, 0, 19 * 19);
    flag = 0;
}

int chessaround(int x, int y, int next_x, int next_y)
{
    int my_chess;
    
    if (flag % 2)
        my_chess = 2;
    else
        my_chess = 1;

    if ((x + next_x) >= 0 && (x + next_x) <= 18 && (y + next_y) >= 0 && (y + next_y) <= 18)
    {
        if(board[x + next_x][y + next_y] == my_chess)
            return 1 + chessaround(x + next_x, y + next_y, next_x, next_y);
    }
    return 0;
}

int isWin(int x, int y) 
{
    int horizon = 1 + chessaround(x, y, -1, 0) + chessaround(x, y, 1, 0);
    int plumb_line = 1 + chessaround(x, y, 0, 1) + chessaround(x, y, 0, -1);
    int main_diagonal = 1 + chessaround(x, y, -1, 1) + chessaround(x, y, 1, -1);
    int sub_diagonal = 1 + chessaround(x, y, 1, 1) + chessaround(x, y, -1, -1);
    if (horizon == 5 || plumb_line == 5 || main_diagonal == 5 || sub_diagonal == 5)
        return 1;
    
    return 0;
}

int playerMove(int x, int y) 
{
    if ((x >= 0 && x <= 18) && (y >= 0 && y <= 18))
    {
        if (board[x][y] == 0)
        {
            if (flag % 2)
                board[x][y] = 2;
            else
                board[x][y] = 1;
            return 1;
        }
    }
    cout << "你TM棋落哪了" << endl;
    this_thread::sleep_for(std::chrono::seconds(3)); // 等待 3 秒
    return 0;
}

void menuView() 
{
    while (true)
    {
        cout << "--------------------------五子棋游戏-----------------------------------------" << endl;
        cout << "1.开始游戏" << endl << "2.游戏设置" << endl << "3.退出游戏" << endl;
        //表示菜单界面用户选择的数字，决定由菜单导向哪
        int menu_next;
        cin >> menu_next;
        switch (menu_next)
        {
        case 1:
            gameView();
            break;
        case 2:
            system("cls");
            cout << "敬请期待............";
            this_thread::sleep_for(std::chrono::seconds(3)); // 等待 3 秒
            system("cls");
            break;
        case 3:
            exit(0);
        default:
            cout << "请输入1-3！！！" << endl;
            this_thread::sleep_for(std::chrono::seconds(3)); // 等待 3 秒
            system("cls");
            break;
        }
    }
}

void gameView_ShowBoard() 
{
    cout << "  ";
    for (int i = 0; i < 11; i++)
    {
        cout << "   " << i;
    }
    for (int i = 11; i < 19; i++)
    {
        cout << "  " << i;
    }
    cout << endl << endl;
    for (int i = 0; i < 10; i++)
    {
        cout<< ' ' << i;
        for (int j = 0; j < 19; j++)
        {
            cout << "   " << chess[board[i][j]];
        }
        cout << endl << endl;
    }
	for (int i = 10; i < 19; i++)
	{
		cout << i;
		for (int j = 0; j < 19; j++)
		{
			cout << "   " << chess[board[i][j]];
		}
		cout << endl << endl;
	}
}

void winView() 
{
    if (flag % 2)
        cout << "白棋玩家赢了！！！" << endl;
    else
        cout << "黑棋玩家赢了！！！" << endl;
    cout << "按任意键返回菜单......" << endl;
    _getch();
    system("cls");
}

void gameView()
{
    double x, y;
    init();
    while (true)
    {
        gameView_ShowBoard();
        if (flag % 2 == 0)
            cout << "黑棋玩家请落子:" << endl;
        else
            cout << "白棋玩家请落子:" << endl;
        cout << "x: ";
        cin >> x;
        cout << "y: ";
        cin >> y;
        if (!playerMove(x, y))
        {
            system("cls");
            continue;
        }
		if (isWin(x, y))
		{
            system("cls");
            gameView_ShowBoard();
			winView();
			break;
		}
        flag++;
        system("cls");
    }
}


//if (board[x + next_x][x + next_y] == 0 || board[x + next_x][x + next_y] == my_chess)
//    return 0;
//
//return 1 + chessaround(x + next_x, y + next_y, next_x, next_y);

#endif