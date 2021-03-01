#include "head.h"


char input1[100] = "\0";
char input2[100] = "\0";
char answer[100] = "\0";
char result[300] = "\0";
char op = '\0';
int error = 0;
int terror = 0; //����ġ�����


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


void Show()  //ģ����д������ʽ
{
	bool ex = FALSE;
	double lenth = 0; //��ǰ�Ѿ�������ַ�����Ӣ�糤��
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
			if (result[i] == '-' && i != 0 && result[i - 1] == '^') // ��ָ��
			{
				ex = TRUE;
				lenth -= 0.03;
			}
		}
		if (ex) //��ʾָ��ģʽ�������ַ���С��λ��
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
	DrawTextString("�����ʽ��[ϵ��]x^[ָ��] ��ϵ��Ϊ1����ʡ�ԣ�ָ���������У�ָ��Ϊ1����ʡ�ԣ�������ô�x");
	MovePen(1, 4.5);
	DrawTextString("��������: -x^4+3x^3-25x+7   ,ע����ż䲻Ҫ�ӿո�");
}

void display()
{
	DisplayClear();
	SetFont("����");
	SetPointSize(20);
	Help();
	MovePen(1,3.65);
	DrawTextString("�ڴ������һ������ʽ");	
	MovePen(1, 2.65);
	DrawTextString("�ڴ�����ڶ�������ʽ");
	MovePen(1, 3.15);
	DrawTextString("                ����");
	textbox(GenUIID(0), 3.2, 3.55, 8, 0.3, input1, sizeof(input1));
	textbox(GenUIID(0), 3.2, 2.55, 8, 0.3, input2, sizeof(input2));
	SetPointSize(20);
	if (button(GenUIID(1), 9.2, 4.2, 1.5, 0.3, "information")) MessageBox(NULL,"������Ϣ��Minecart��","��ʾ",MB_OK);
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
			error = checkError(input1,input2);  //���һЩ��������
			ClearAnStr();
			if(!error)   //û��checkError��⵽�Ĵ���Ŵ�ӡ���
			    sprintf(answer,"$@=#%s",getAnswer(input1, input2, op));
			error = checkError(input1, input2); //�ٴμ��
			if (strlen(answer) < 5)
				sprintf(answer, "$@=#0");
			if (NoX())
				terror = ERRLOSEFACE;
			else
				terror = 0;
		
		}
	}
	SetPointSize(20); //�������̫�����ˣ���30����ִ�ӡ�����ᳬ����ť�߿�
	if (button(GenUIID(1), 8.2, 3.05, 1, 0.3, "/")) op = '/';
	SetPointSize(30); 

	Show();	 //ʵʱչʾ���ʽ
	switch (error)  //��ʾ������Ϣ
	{
	case ERROP:
		MovePen(1, 2);
		SetPenColor("red");
		DrawTextString("δѡ�����㷨��");
		break;

	case ERRNULL:

		MovePen(1, 2);
		SetPenColor("red");
		DrawTextString("���벻ӦΪ��");
		break;
	case ERRCHAR:

		MovePen(1, 2);
		SetPenColor("red");
		DrawTextString("���ʽ�����Ƿ��ַ�");
		break;
	case ERRNDIV:

		MovePen(1, 2);
		SetPenColor("red");
		DrawTextString("��������");
		break;
	
	}
	if (terror == ERRLOSEFACE)
	{
		MovePen(1, 1.7);
		SetPenColor("green");
		SetPointSize(20);
		DrawTextString("��Ҫ���õؼ��㳣����������ʽ�����������������Ƽ�ʹ��windows�Դ����������������");
		SetPointSize(30);
	}

	SetPenColor("black");

}



void CharEP(char ch)
{
	uiGetChar(ch); // GUI�ַ�����
	display(); //ˢ����ʾ
}

void KeyboardEP(int key, int event)
{
	uiGetKeyboard(key, event); // GUI��ȡ����
	display(); // ˢ����ʾ
}

// �û�������¼���Ӧ����
void MouseEP(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event); //GUI��ȡ���
	display(); // ˢ����ʾ
}

void TimerEP(int id)
{
	switch (id)
	{
	case 1:
		display();
	}
} //��֤��Ļ��һ����ˢ����

void Main()
{
	SetWindowSize(12,6);
	SetWindowTitle("��������Ķ���ʽ����������");
	InitGraphics();
	registerCharEvent(CharEP); // �ַ�
	registerKeyboardEvent(KeyboardEP);// ����
	registerMouseEvent(MouseEP);      // ���
	registerTimerEvent(TimerEP);      // ��ʱ��
	startTimer(1, 10); //��֤��Ļ��һ����ˢ����
	setButtonColors("yellow", "black", "green", "blue", 1);
}
