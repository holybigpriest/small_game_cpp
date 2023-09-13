#pragma once
#include<windows.h>
#include<time.h>
#include<conio.h>
#define H 22
#define W 22
using namespace std;
//界面类
class chessboard{
public:
    char qp[H][W];//蛇蛇运动板子
    int i, j, x1 = 0, y1 = 0;
    chessboard();
    void food();//随机生成给蛇蛇吃
    void prt(int grade, int score, int gamespeed);//每次蛇动一次，刷新一次页面
};
//蛇类
class snake :public chessboard{
public:
    int zb[2][100];//记录蛇坐标
    long start;//计时用的，或者说用来设置刷新页面时间
    //head蛇头在记录蛇身坐标zb的下标，tail记录蛇尾，x,y记录当前蛇头走到的位置
    int head = 3, tail = 0,grade=1,score =0, gamespeed=500,length = 4, direction = 77, timeover = 1, x = 0, y = 0;
    snake();
    void move();//蛇蛇运动的函数
};
