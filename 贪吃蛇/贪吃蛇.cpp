#include<iostream>
#include"贪吃蛇.h"
//界面类，构造函数
chessboard::chessboard(){
    //将中心设置为空白，旁边设置为#
    for (i = 1; i <= H - 2; i++)
        for (j = 1; j <= W - 2; j++)
            qp[i][j] = ' ';
    for (i = 0; i <= H - 1; i++)
        qp[0][i] = qp[H - 1][i] = '#';
    for (i = 1; i <= H - 2; i++)
        qp[i][0] = qp[i][W - 1] = '#';
}
//在界面中，随机生成食物的位置，将一个随机空白位位置变成食物
void chessboard::food(){
    srand(time(0));
    do{
        x1 = rand() % W - 2 + 1;
        y1 = rand() % H - 2 + 1;
    } while (qp[x1][y1] != ' ');
    qp[x1][y1] = '$';
}
//打印当前界面
void chessboard::prt(int grade, int score, int gamespeed){
    system("cls");
    cout << endl;
    for (i = 0; i < H; i++){
        cout << "\t";
        for (j = 0; j < W; j++)
            cout << qp[i][j] << ' ';
        if (i == 0) cout << "\tGrade:" << grade;//在第一行最后显示分数
        if (i == 2) cout << "\tScore:" << score;//在第三行最后显示等级
        if (i == 4) cout << "\tAutomatic forward";//在第五行最后显示朝向
        if (i == 5) cout << "\ttime interval:" << gamespeed << "ms"; // 在第六行最后,游戏时间间隔，也就是蛇的运行速度
        cout << endl;
    }
}
//蛇的构造函数
snake::snake(){
    cout << "\n\n\t\tThe game is about to begin!" << endl;
    for (i = 3; i >= 0; i--){
        start = clock();//记录程序运行的时间
        while (clock() - start <= 1000);//在此处停顿一千个时钟周期
        system("cls");//清空上一帧屏幕
        if (i > 0)
            cout << "\n\n\t\tCountdown:" << i << endl;//倒计时3s
    }
    for (i = 1; i <= 3; i++)
        qp[1][i] = '*';
    qp[1][4] = '@';
    for (i = 0; i < 4; i++){//记录蛇的坐标，第一行x坐标，第二行y坐标
        zb[0][i] = 1;
        zb[1][i] = i + 1;
    }
    food();
}
void snake::move(){
    while (1) {
        timeover = 1;
        start = clock();
        //当按键按下或者超过时间间隔的时候会跳出循环
        while ((timeover = (clock() - start <= gamespeed)) && !_kbhit());//每次蛇停顿gamespeed个时钟周期，kbhit() 是一个库函数，通常用于检测在控制台中是否有按键被按下
        if (timeover) {
            if(_getch()==224) direction = _getch();
            //getch() 是一个函数，通常用于从控制台获取单个字符输入，而不需要用户按下回车键。它通常用于编写控制台程序，以便与用户进行交互性输入
            //当按下的不是上下左右键的时候无视这次操作
            //方向键由两个字符控制，第一个读出来的都是224,第二字符才有方向上的区别
        }
        switch (direction) {//M的ascii码，代表右移，72 可以代表上移动，75 可以代表左移动，80 可以代表下移动
            case 72: x = zb[0][head] - 1; y = zb[1][head]; break;//向上横坐标减一，向下横坐标加一
            case 80: x = zb[0][head] + 1; y = zb[1][head]; break;
            case 75: x = zb[0][head]; y = zb[1][head] - 1; break;
            case 77: x = zb[0][head]; y = zb[1][head] + 1; break;
        }
        if (qp[x][y] != ' ' && !(x == x1 && y == y1)) {//(x1,y1)记录的是食物的坐标，当碰到不是食物的也不是空白的位置的时候，失败，可能是碰到尾巴
            cout << "\tGame over!" << endl; break;
        }
        if (x == x1 && y == y1 ){//判断当前是否吃到了食物
            length++;
            score = score + 100;
            if (length >= 8){//当长度每次提升8将会加一级
                length -= 8;
                grade++;
                if (gamespeed >= 200) gamespeed = 550 - grade * 50;//时间间隔越小速度越快，但是不能小于200（自定义的）
            }
            qp[x][y] = '@';//将走到的位置设为蛇头
            qp[zb[0][head]][zb[1][head]] = '*';//将之前蛇头的位置设置为蛇身
            head = (head + 1) % 100;//记录蛇头的下标往前移动一位
            zb[0][head] = x;
            zb[1][head] = y;
            food();
            prt(grade, score, gamespeed);
        }else {//前方不是食物的时候，尾巴变空，记录尾巴的位置在之前下标的前一位，头的操作和上面一样
            qp[zb[0][tail]][zb[1][tail]] = ' ';
            tail = (tail + 1) % 100;
            qp[zb[0][head]][zb[1][head]] = '*';
            head = (head + 1) % 100;
            zb[0][head] = x;
            zb[1][head] = y;
            qp[zb[0][head]][zb[1][head]] = '@';
            prt(grade, score, gamespeed);
        }
    }
}
int main(){
    snake s;
    s.move();
    return 0;
}
