#define _CRT_SECURE_NO_WARNINGS		//ȥ������������������
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>	//ͼ�ο�
#include <conio.h>		//������
#include <time.h>
#include <iostream>

using namespace std;
IMAGE img[12];	//�洢12����Ƭ
int imgIndex[12] = { 0,2,4,8,16,32,64,128,256,512,1024,2048 };
int i, j;
int map[4][4] = { 0 };
string str;
//int flag = 0;
//������Դ
void loadResource() {
	for (i = 0; i < 12; i++) {
		//��������
		char fileName[20] = "";
		sprintf(fileName, "%d.bmp", imgIndex[i]);
		loadimage(img + i, fileName,60,60);
	}
}

//����������������2����4����0
int randIntNum() {
	srand((unsigned int)time(NULL));	//�����������
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (map[i][j] == 0) {
				map[i][j] = (rand() % 3) * 2;
				//����0�Ļ��ͼ������
				if (map[i][j] == 0)
					continue;
				return 0;
			}
		}
	}
	return 0;
}

//�ϲ����֣������������Ҽ����ϲ�
//���ƶ��Ĺ�����������������������Ҽ�Ϊ������
//	[2 2 4 4]--->[0 4 0 8]
//	[0 4 0 8]--->[0 0 4 8]
int moveRight() {
	//flag = 0;
	int flag = 2;	//��Ϸ�������
	for (i = 0; i < 4; i++) {
		for (j = 4 - 1; j >= 0; j--) {
			int curKey = map[i][j];		//��ǰԪ�ص�ֵ
			if (curKey != 0) {
				int k = j - 1;
				while (k >= 0) {
					//��ǰԪ�ص���һ��
					int curKeyNext = map[i][k];
					if (curKeyNext != 0) {
						//������ڵ�����ͬ����ô�úϲ�
						if (curKey == curKeyNext) {
							//[2 2 4 4] --->[0 4 0 8]
							flag = 3;
							map[i][j] += map[i][k];
							map[i][k] = 0;
						}
						k = -1;		//�˳�ѭ��
						break;
					}
					k--;		//�ж�������λ��
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
						map[i][j] = curKeyNext;	//�ѷ�0Ԫ���Ƶ�0��λ��
						map[i][k] = 0;	//�ƶ����Ϊ0
						k = -1;		
					}
					k--;	//����λ��Ҳ��Ҫ�ж�
				}
			}
		}
	}
	//str.(_T("��Ϸ���������ķ���Ϊ:%d\n"), n);
	return flag;
	
}

//������
int moveLeft() {
	//flag = 0;
	int flag = 2;	//��Ϸ�������
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			int curKey = map[i][j];		//��ǰԪ�ص�ֵ
			if (curKey != 0) {
				int k = j + 1;
				while (k < 4) {
					//��ǰԪ�ص���һ��
					int curKeyNext = map[i][k];
					if (curKeyNext != 0) {
						//������ڵ�����ͬ����ô�úϲ�
						if (curKey == curKeyNext) {
							//[2 2 4 4] --->[0 4 0 8]
							flag = 3;
							map[i][j] += map[i][k];
							map[i][k] = 0;
						}
						k = 4;		//�˳�ѭ��
						break;
					}
					k++;		//�ж�������λ��
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
						map[i][j] = curKeyNext;	//�ѷ�0Ԫ���Ƶ�0��λ��
						map[i][k] = 0;	//�ƶ����Ϊ0
						k = 4;
					}
					k++;	//����λ��Ҳ��Ҫ�ж�
				}
			}
		}
	}
	return flag;
	//flag = 0;
}

//������
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

//������
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

//����ͼ�����ݶ�ά�����е�ֵȥ����ͼ
void drawMap() {
	setbkcolor(RGB(255, 225, 187));
	cleardevice();
	settextcolor(WHITE);
	settextstyle(35, 0, "����");
	outtextxy(50, 10, "2048��Ϸ");
	//���ݶ�ά�����е�ֵȥ��ͼ
	int x, y, k;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			x = 60 * j;
			y = 60 * i + 60;
			for (k = 0; k < 12; k++) {
				//�����ǰԪ�ض�Ӧ��ͼƬ���
				if (imgIndex[k] == map[i][j])
					break;
			}
			//����Ӧ��ŵ�ͼƬ
			putimage(x, y, img + k);
		}
	}
}

//������Ӧ
void keyDown() {
	char key = _getch();	//���������û�����
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
	//���������ʾͼƬ
	//	1.����ͼƬ����
	//IMAGE bacground;
	//	2.������Դ������loadimage����
	//loadimage(&background, "class.jpg", 800, 400);
	//	3.��ʾͼƬputimage��ʾͼƬ
	//putimage(0, 0, img+11);
	randIntNum();
	drawMap();
	
	while (1) {
		
		keyDown();
		drawMap();
	}
	getchar();	//��ֹ����
	system("pause");
	return 0;
}