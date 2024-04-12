#define _CRT_SECURE_NO_WARNINGS

#include "snake.h"		// �����Զ���ͷ�ļ�

int main(void)
{
	// ȥ����ꡣ
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = sizeof(cci);
	cci.bVisible = FALSE;  // TRUE :
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	srand(time(NULL));  // ������������ӡ�

	initSnake();	// ��ʼ����
	initFood();		// ��ʼ��ʳ��

	initWall();		// ��ǽ
	initUI();		// ���ߺ�ʳ��

	playGame();		// ������Ϸ

	showScore();	// ��ӡ����

	system("pause");
	return EXIT_SUCCESS;
}

void showScore(void)
{
	// �����Ĭ��λ���ƶ��� ��������Ϸ������λ�á�
	COORD coord;

	coord.X = 0;
	coord.Y = HIGH + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	printf("Game Over!!!\n");
	printf("�ɼ�Ϊ��%d\n\n\n", score);
}

void initWall(void)
{
	for (size_t i = 0; i <= HIGH; i++)	// ����
	{
		for (size_t j = 0; j <= WIDE; j++)			// һ���еĶ���
		{
			if (j == WIDE)
			{
				printf("|");
			}
			else if (i == HIGH)
			{
				printf("_");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}

void playGame(void)
{
	char key = 'd';

	// �ж���ײǽ
	while (snake.body[0].X >= 0 && snake.body[0].X < WIDE
		&& snake.body[0].Y >= 0 && snake.body[0].Y < HIGH)
	{
		// ������
		initUI();

		// �����û���������  asdw 
		if (_kbhit()) {				// Ϊ��ʱ��˵���û����°�����
			key = _getch();
		}
		switch (key)
		{
		case 'w': kx = 0; ky = -1; break;
		case 's': kx = 0; ky = +1; break;
		case 'd': kx = +1; ky = 0; break;
		case 'a': kx = -1; ky = 0; break;
		default:
			break;
		}

		// ��ͷײ���壺 ��ͷ == ����һ������
		for (size_t i = 1; i < snake.size; i++)
		{
			if (snake.body[0].X == snake.body[i].X
				&& snake.body[0].Y == snake.body[i].Y)
			{
				return;		// ��Ϸ������
			}
		}

		// ��ͷײʳ��
		if (snake.body[0].X == food1.X && snake.body[0].Y == food1.Y)
		{
			initFood();		// ʳ����ʧ
			snake.size++;	// ��������
			score += 10;	// �ӷ�

			sleepSecond -= 100;	// ����
		}

		// �洢��β����
		lastX = snake.body[snake.size - 1].X;
		lastY = snake.body[snake.size - 1].Y;

		// ���ƶ���ǰһ���������һ�����帳ֵ��
		for (size_t i = snake.size - 1; i > 0; i--)
		{
			snake.body[i].X = snake.body[i - 1].X;
			snake.body[i].Y = snake.body[i - 1].Y;
		}
		snake.body[0].X += kx;		// ��ͷ��������û��������޸ġ�
		snake.body[0].Y += ky;

		Sleep(sleepSecond);
		// ����
		//system("cls");	
	}

	return;
}

// �����ʼ���ߺ���
void initSnake(void)
{
	snake.size = 2;

	snake.body[0].X = WIDE / 2;		//��ͷ��ʼ��
	snake.body[0].Y = HIGH / 2;

	snake.body[1].X = WIDE / 2 - 1;	// ��һ�������ʼ��
	snake.body[1].Y = HIGH / 2;

	return;
}

// ��ʼ������ؼ�
void initUI(void)
{
	COORD coord = {0};					// ����ƶ���λ�á�

	// ����
	for (size_t i = 0; i < snake.size; i++)
	{
		coord.X = snake.body[i].X;
		coord.Y = snake.body[i].Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

		if (i == 0)
			putchar('@');
		else
			putchar('*');
	}
	// ȥ����β
	coord.X = lastX;
	coord.Y = lastY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar(' ');

	// ��ʳ��
	coord.X = food1.X;
	coord.Y = food1.Y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar('#');
}

// ʳ��ĳ�ʼ������
void initFood(void)
{
	food1.X = rand() % WIDE;  // 0-59
	food1.Y = rand() % HIGH;  // 0-59
	return;
}

