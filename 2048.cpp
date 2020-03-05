#define _CRT_SECURE_NO_WARNINGS		//去掉编译器内扩增问题
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>	//图形库
#include <conio.h>		//按键库
#include <time.h>
#include <iostream>

using namespace std;
IMAGE img[12];	//存储12张照片
int imgIndex[12] = { 0,2,4,8,16,32,64,128,256,512,1024,2048 };
int i, j;
int map[4][4] = { 0 };
string str;
//int flag = 0;
//加载资源
void loadResource() {
	for (i = 0; i < 12; i++) {
		//批量加载
		char fileName[20] = "";
		sprintf(fileName, "%d.bmp", imgIndex[i]);
		loadimage(img + i, fileName,60,60);
	}
}

//随机函数，随机产生2或者4或者0
int randIntNum() {
	srand((unsigned int)time(NULL));	//随机函数种子
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (map[i][j] == 0) {
				map[i][j] = (rand() % 3) * 2;
				//产生0的话就继续随机
				if (map[i][j] == 0)
					continue;
				return 0;
			}
		}
	}
	return 0;
}

//合并数字，根据上下左右键做合并
//在移动的过程中有以下两种情况（以右键为例）：
//	[2 2 4 4]--->[0 4 0 8]
//	[0 4 0 8]--->[0 0 4 8]
int moveRight() {
	//flag = 0;
	int flag = 2;	//游戏结束标记
	for (i = 0; i < 4; i++) {
		for (j = 4 - 1; j >= 0; j--) {
			int curKey = map[i][j];		//当前元素的值
			if (curKey != 0) {
				int k = j - 1;
				while (k >= 0) {
					//当前元素的下一个
					int curKeyNext = map[i][k];
					if (curKeyNext != 0) {
						//如果相邻的是相同，那么久合并
						if (curKey == curKeyNext) {
							//[2 2 4 4] --->[0 4 0 8]
							flag = 3;
							map[i][j] += map[i][k];
							map[i][k] = 0;
						}
						k = -1;		//退出循环
						break;
					}
					k--;		//判断其他的位置
				}
			}
			
		}
	}
	//[0 4 0 8]--->[0 0 4 8]
	for (i = 0; i < 4; i++) {
		for (j = 4 - 1; j >= 0; j--) {
			int curKey = map[i][j];
			if (curKey == 0) {
				int k = j - 1;
				while (k >= 0) {
					int curKeyNext = map[i][k];
					if (curKeyNext != 0) {
						flag = 3;
						map[i][j] = curKeyNext;	//把非0元素移到0的位置
						map[i][k] = 0;	//移动后变为0
						k = -1;		
					}
					k--;	//其他位置也需要判断
				}
			}
		}
	}
	//str.(_T("游戏结束，您的分数为:%d\n"), n);
	return flag;
	
}

//往左走
int moveLeft() {
	//flag = 0;
	int flag = 2;	//游戏结束标记
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			int curKey = map[i][j];		//当前元素的值
			if (curKey != 0) {
				int k = j + 1;
				while (k < 4) {
					//当前元素的下一个
					int curKeyNext = map[i][k];
					if (curKeyNext != 0) {
						//如果相邻的是相同，那么久合并
						if (curKey == curKeyNext) {
							//[2 2 4 4] --->[0 4 0 8]
							flag = 3;
							map[i][j] += map[i][k];
							map[i][k] = 0;
						}
						k = 4;		//退出循环
						break;
					}
					k++;		//判断其他的位置
				}
			}
			
		}
	}
	//[0 4 0 8]--->[0 0 4 8]
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			int curKey = map[i][j];
			if (curKey == 0) {
				int k = j + 1;
				while (k < 4) {
					int curKeyNext = map[i][k];
					if (curKeyNext != 0) {
						flag = 3;
						map[i][j] = curKeyNext;	//把非0元素移到0的位置
						map[i][k] = 0;	//移动后变为0
						k = 4;
					}
					k++;	//其他位置也需要判断
				}
			}
		}
	}
	return flag;
	//flag = 0;
}

//往上走
int moveUp() {
	//flag = 0;
	int flag = 2;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			int curKey = map[i][j];
			if (curKey != 0) {
				int k = i + 1;
				while (k < 4) {
					int curKeyNext = map[k][j];
					if (curKeyNext != 0) {
						if (curKey == curKeyNext) {
							flag = 3;
							map[i][j] += map[k][j];
							map[k][j] = 0;
						}
						k = 4;
						break;
					}
					k++;
				}
			}
		}
	}
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			int curKey = map[i][j];
			if (curKey == 0) {
				int k = i + 1;
				while (k < 4) {
					int curKeyNext = map[k][j];
					if (curKeyNext != 0) {
						flag = 3;
						map[i][j] = curKeyNext;
						map[k][j] = 0;
						k = 4;
					}
					k++;
				}
			}
		}
	}
	return flag;
	//flag = 0;
}

//往下走
int moveDown() {
	//flag = 0;
	int flag = 2;
	for (i = 4 - 1; i >= 0; i--) {
		for (j = 0; j < 4; j++) {
			int curKey = map[i][j];
			if (curKey != 0) {
				int k = i - 1;
				while (k >= 0) {
					int curKeyNext = map[k][j];
					if (curKeyNext != 0) {
						if (curKey == curKeyNext) {
							flag = 3;
							map[i][j] += map[k][j];
							map[k][j] = 0;
						}
						k = 0;
						break;
					}
					k--;
				}
			}
		}
	}
	for (i = 3; i >= 0; i--) {
		for (j = 0; j < 4; j++) {
			int curKey = map[i][j];
			if (curKey == 0) {
				int k = i - 1;
				while(k >= 0) {
					int curKeyNext = map[k][j];
					if (curKeyNext != 0) {
						flag = 3;
						map[i][j] = curKeyNext;
						map[k][j] = 0;
						k = 0;
					}
					k--;
				}
			}
		}
	}
	return flag;
	//flag = 0;
}

//画地图，根据二维数组中的值去画地图
void drawMap() {
	setbkcolor(RGB(255, 225, 187));
	cleardevice();
	settextcolor(WHITE);
	settextstyle(35, 0, "楷体");
	outtextxy(50, 10, "2048游戏");
	//根据二维数据中的值去画图
	int x, y, k;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			x = 60 * j;
			y = 60 * i + 60;
			for (k = 0; k < 12; k++) {
				//求出当前元素对应的图片序号
				if (imgIndex[k] == map[i][j])
					break;
			}
			//贴相应序号的图片
			putimage(x, y, img + k);
		}
	}
}

//按键响应
void keyDown() {
	char key = _getch();	//用来接收用户按键
	switch (key) {
	case 'W':
	case 'w':
	case 72:
		moveUp();
		if (moveUp() == 3) {
			randIntNum();
			//drawMap();
		}
		
		break;
	case 'S':
	case 's':
	case 80:
		moveDown();
		if (moveDown() == 3) {
			randIntNum();
			//drawMap();
		}
		
		break;
	case 'A':
	case 'a':
	case 75:
		moveLeft();
		if (moveLeft() == 3) {
			randIntNum();
			//drawMap();
		}
		
		break;
	case 'D':
	case 'd':
	case 77:
		moveRight();
		if (moveRight() == 3) {
			randIntNum();
			//drawMap();
		}
		
		//drawMap();
		
		break;
	}
}



int main() {
	loadResource();
	initgraph(60*4, 60*5);
	//程序如何显示图片
	//	1.声明图片变量
	//IMAGE bacground;
	//	2.加载资源到变量loadimage加载
	//loadimage(&background, "class.jpg", 800, 400);
	//	3.显示图片putimage显示图片
	//putimage(0, 0, img+11);
	randIntNum();
	drawMap();
	
	while (1) {
		
		keyDown();
		drawMap();
	}
	getchar();	//防止闪屏
	system("pause");
	return 0;
}