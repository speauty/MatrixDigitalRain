#include <iostream>
#include <ctime>
#include <easyx.h>

constexpr unsigned short WIN_WIDTH = 960;
constexpr unsigned short WIN_HIGH = 640;

constexpr unsigned char RAINSLOT_COUNT = 64;
constexpr unsigned char RAINDROP_COUNT = 20;
constexpr unsigned short RAIN_ROW_PITCH= 15;

struct RainDrop
{
	short AxisX;
	short AxisY;
	short AxisYStride;
	unsigned char Str[RAINDROP_COUNT];
};

struct RainDrop RainSlot[RAINSLOT_COUNT];

/* 生成随机字符 */
char GenerateRandomChar()
{
	switch (rand()%3)
	{
	case 0:
		return rand() % 10 + '0'; break;
	case 1:
		return rand() % 26 + 'A'; break;
	case 2:
		return rand() % 26 + 'a'; break;
	default:
		return rand() % 10 + '0'; break;
		break;
	}
	
}

/* 初始化数字雨 */
void InitRain()
{
	for (unsigned char i = 0; i < RAINSLOT_COUNT; i++)
	{
		RainSlot[i].AxisX = i * RAIN_ROW_PITCH;
		RainSlot[i].AxisY = rand() % getheight();
		RainSlot[i].AxisYStride = rand() % 4 + 1;
		for (unsigned char j = 0; j < RAINDROP_COUNT - 1; j++)
		{
			RainSlot[i].Str[j] = GenerateRandomChar();
		}
	}
}

void RainUpdate()
{
	for (unsigned char i = 0; i < RAINSLOT_COUNT; i++)
	{
		/* 字符更新 */
		RainSlot[i].Str[rand() % RAINDROP_COUNT] = GenerateRandomChar();

		/* 纵向变速 */
		RainSlot[i].AxisY += RainSlot[i].AxisYStride;
		if ((RainSlot[i].AxisY - RAINDROP_COUNT * RAIN_ROW_PITCH) > getheight()) RainSlot[i].AxisY = 0;
	}
}

void RainDraw()
{
	for (unsigned char i = 0; i < RAINSLOT_COUNT; i++)
	{
		for (unsigned char j = 0; j < RAINDROP_COUNT; j++)
		{
			settextcolor(RGB(0, 255 - j * 13, 0));
			outtextxy(RainSlot[i].AxisX, RainSlot[i].AxisY - j * RAIN_ROW_PITCH, RainSlot[i].Str[j]);

		}
	}
}

void Draw()
{
	cleardevice();
	RainDraw();
}

int main()
{
	srand((unsigned int)time(NULL)); /* 随机播种 */
	/* 创建窗口 */
	initgraph(WIN_WIDTH, WIN_HIGH);
	setbkmode(TRANSPARENT);
	InitRain();

	BeginBatchDraw();
	while (1) {
		Draw();
		RainUpdate();
		FlushBatchDraw();
	}
	EndBatchDraw();
}