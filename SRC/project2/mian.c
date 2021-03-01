#include "head.h"


char input1[100] = "\0";
char input2[100] = "\0";
char answer[100] = "\0";
char result[300] = "\0";
char op = '\0';
int error = 0;
int terror = 0; //特殊的“错误”


bool NoX()
{
	for (int i = 0; answer[i] != 0; i++)
	{
		if (answer[i] == 'x')
			return FALSE;
	}
	for (int i = 0; input1[i] != 0; i++)
	{
		if (input1[i] == 'x')
			return FALSE;
	}
	for (int i = 0; input2[i] != 0; i++)
	{
		if (input2[i] == 'x')
			return FALSE;
	}

	return TRUE;
}


void Show()  //模仿手写输出表达式
{
	bool ex = FALSE;
	double lenth = 0; //当前已经输出的字符串的英寸长度
	double base = 1;
	char output[2];
	sprintf(result, "%s@%c#%s%s", input1, op, input2,answer);
	SetPointSize(30);
	MovePen(1, 1);
	SetPenColor("black");
	for (int i = 0; result[i] != '\0'; i++)
	{
		if (result[i] == '^')
		{
			ex = TRUE;
			continue;
		}
		if (result[i] == '@') {
			ex = FALSE;
			SetPenColor("red"); 
			lenth += 0.1;
			continue;
              }
		if (result[i] == '#') {
			ex = FALSE;
			SetPenColor("black"); 
			lenth += 0.1;
			continue;
		}
		if (result[i] == '$') {
			ex = FALSE;
			base = 0.5;
			lenth = 0;
			continue;
		}
		if (result[i] == '+' || result[i] == '-' || result[i] == '*' || result[i] == '/') {		
			ex = FALSE; lenth += 0.03;
			if (result[i] == '-' && i != 0 && result[i - 1] == '^') // 负指数
			{
				ex = TRUE;
				lenth -= 0.03;
			}
		}
		if (ex) //显示指数模式，调整字符大小和位置
		{
			SetPointSize(20);
			MovePen(lenth + 1, base + 0.1);
			sprintf(output, "%c\0", result[i]);
			DrawTextString(output);
			lenth = lenth + 0.1;
		}
		else
		{
			SetPointSize(30);
			MovePen(lenth + 1, base);
			sprintf(output, "%c\0", result[i]);
			DrawTextString(output);
			lenth = lenth + 0.15;

		}
	}
}  

void Help()
{
	MovePen(1, 5);
	DrawTextString("输入格式：[系数]x^[指数] ，系数为1可以省略，指数降幂排列，指数为1可以省略，常数项不用带x");
	MovePen(1, 4.5);
	DrawTextString("输入样例: -x^4+3x^3-25x+7   ,注意符号间不要加空格");
}

void display()
{
	DisplayClear();
	SetFont("宋体");
	SetPointSize(20);
	Help();
	MovePen(1,3.65);
	DrawTextString("在此输入第一个多项式");	
	MovePen(1, 2.65);
	DrawTextString("在此输入第二个多项式");
	MovePen(1, 3.15);
	DrawTextString("                操作");
	textbox(GenUIID(0), 3.2, 3.55, 8, 0.3, input1, sizeof(input1));
	textbox(GenUIID(0), 3.2, 2.55, 8, 0.3, input2, sizeof(input2));
	SetPointSize(20);
	if (button(GenUIID(1), 9.2, 4.2, 1.5, 0.3, "information")) MessageBox(NULL,"作者信息：Minecart队","提示",MB_OK);
	SetPointSize(30);
	if (button(GenUIID(1), 4, 3.05, 1, 0.3, "+")) op = '+';
	if (button(GenUIID(1), 5.4, 3.05, 1, 0.3, "-")) op = '-';
	if (button(GenUIID(1), 6.8, 3.05, 1, 0.3, "*")) op = '*';
	if (button(GenUIID(1), 9.6, 3.05, 1, 0.3, "="))
	{
		if (op != '+' && op != '-' && op != '*' && op != '/')
			error = ERROP;
		else
		{
			error = checkError(input1,input2);  //检测一些常见错误
			ClearAnStr();
			if(!error)   //没有checkError检测到的错误才打印结果
			    sprintf(answer,"$@=#%s",getAnswer(input1, input2, op));
			error = checkError(input1, input2); //再次检测
			if (strlen(answer) < 5)
				sprintf(answer, "$@=#0");
			if (NoX())
				terror = ERRLOSEFACE;
			else
				terror = 0;
		
		}
	}
	SetPointSize(20); //这个除号太过分了，用30码的字打印出来会超过按钮边框
	if (button(GenUIID(1), 8.2, 3.05, 1, 0.3, "/")) op = '/';
	SetPointSize(30); 

	Show();	 //实时展示表达式
	switch (error)  //显示错误信息
	{
	case ERROP:
		MovePen(1, 2);
		SetPenColor("red");
		DrawTextString("未选择运算法则");
		break;

	case ERRNULL:

		MovePen(1, 2);
		SetPenColor("red");
		DrawTextString("输入不应为空");
		break;
	case ERRCHAR:

		MovePen(1, 2);
		SetPenColor("red");
		DrawTextString("表达式包含非法字符");
		break;
	case ERRNDIV:

		MovePen(1, 2);
		SetPenColor("red");
		DrawTextString("不可整除");
		break;
	
	}
	if (terror == ERRLOSEFACE)
	{
		MovePen(1, 1.7);
		SetPenColor("green");
		SetPointSize(20);
		DrawTextString("想要更好地计算常数？本多项式计算器不够完美，推荐使用windows自带软件：“计算器”");
		SetPointSize(30);
	}

	SetPenColor("black");

}



void CharEP(char ch)
{
	uiGetChar(ch); // GUI字符输入
	display(); //刷新显示
}

void KeyboardEP(int key, int event)
{
	uiGetKeyboard(key, event); // GUI获取键盘
	display(); // 刷新显示
}

// 用户的鼠标事件响应函数
void MouseEP(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event); //GUI获取鼠标
	display(); // 刷新显示
}

void TimerEP(int id)
{
	switch (id)
	{
	case 1:
		display();
	}
} //保证屏幕有一定的刷新率

void Main()
{
	SetWindowSize(12,6);
	SetWindowTitle("基于链表的多项式四则运算器");
	InitGraphics();
	registerCharEvent(CharEP); // 字符
	registerKeyboardEvent(KeyboardEP);// 键盘
	registerMouseEvent(MouseEP);      // 鼠标
	registerTimerEvent(TimerEP);      // 定时器
	startTimer(1, 10); //保证屏幕有一定的刷新率
	setButtonColors("yellow", "black", "green", "blue", 1);
}
