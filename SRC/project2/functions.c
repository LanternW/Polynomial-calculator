#include "head.h"

/*英文注释与中文注释来自不同小组成员*/
/*Get Expressions And Store in List*/
/*从图形界面部分获取字符串转换为链表，进行核心计算*/



int base1[20] = { 0 };
int ex1[20] = { 0 };
char str1[40] = { 0 };

int base2[20] = { 0 };
int ex2[20] = { 0 };
char str2[40] = { 0 };

char anstring[100] = { 0 };

int idiv = 1; //可以整除的标志

void deal(char* input , int num) //标准化输入数据 ，即将-x+3等简写转化为 -1x^1+3x^0方便提取出指数、底数信息
{
	int flag = 1;
	int first = 1;
	int i = 0, index = 0;
	for (; input[i] != '\0'; i++)
	{
		if (input[i] == 'x' && first == 1)
		{
			first = 0;
			if(num == 1)
			    str1[index++] = '1';
			if (num == 2)
				str2[index++] = '1';
		}
		first = 0;
		if ((input[i] == '-' || input[i] == '+') && input[i + 1] == 'x')
		{
			if (num == 1)
			{
				str1[index++] = input[i];
				str1[index++] = '1';
			}
			if(num == 2)
			{
				str2[index++] = input[i];
				str2[index++] = '1';
			}
			continue;
		}
		else if (input[i] == 'x' && input[i + 1] != '^')
		{
			if (num == 1)
			{
				str1[index++] = input[i];
				str1[index++] = '^';
				str1[index++] = '1';
			}
			if (num == 2)
			{
				str2[index++] = input[i];
				str2[index++] = '^';
				str2[index++] = '1';
			}
		}
		else
		{
			if(num == 1)
				str1[index++] = input[i];
			if(num ==2)
				str2[index++] = input[i];
		}
	}
	for (i--; input[i] != '+' && input[i] != '-' && i >= 0; i--)
	{
		if (input[i] == '^' || input[i] == 'x')
			flag = 0;
	}
	if (flag)
	{
		if (num == 1)
		{
			str1[index++] = 'x';
			str1[index++] = '^';
			str1[index++] = '0';
		}
		if (num == 2)
		{
			str2[index++] = 'x';
			str2[index++] = '^';
			str2[index++] = '0';
		}
	}
	if (num == 1)
		str1[index] = '#';
	if (num == 2)
		str2[index] = '#';
}

void getData(int* a, int* b, char* input) //从字符串中提取出指数、底数信息
{

	char num[40] = { 0 };
	int indexnum = 0;
	int dat = 6;
	int index1 = 0, index2 = 0;
	int i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == 'x')
		{
			num[indexnum] = '\0';
			indexnum = 0;
			sscanf(num, "%d", &dat);
			i = i + 2;
			a[index1++] = dat;
			continue;
		}
		if (i != 0 && (input[i] == '+' || input[i] == '-' || input[i] == '#'))
		{
			num[indexnum] = '\0';
			sscanf(num, "%d", &dat);
			indexnum = 0;
			num[indexnum++] = input[i];
			i++;
			b[index2++] = dat;
			continue;
		}
		num[indexnum++] = input[i];
		i++;
	}
	sscanf(num, "%d", &dat);
	b[index2++] = dat;

} 

void ClearAnStr() //清除答案字符串，再次点击“=”时按照新的输入计算结果
{
	for (int i = strlen(anstring); i >= 0; i--)
	{
		anstring[i] = '\0';
	}
}  

//从字符串中提取到的信息建立链表
item* Read(int num)
{
	item* head, *tail, *p;
	head = tail = NULL;
	int indexbase = 0, indexex = 0;
	if (num == 1)
	{
		while (base1[indexbase] != 0)
		{
			p = (item*)malloc(sizeof(item));
			p->num = base1[indexbase];
			p->symbol = '^';
			p->ex = ex1[indexex];
			p->next = NULL;
			if (head == NULL)
				head = tail = p;
			else
			{
				tail->next = p;
				tail = p;
			}
			indexbase++;
			indexex++;
		}
		return head;
	}
	if(num == 2)
	{
		while (base2[indexbase] != 0)
		{
			p = (item*)malloc(sizeof(item));
			p->num = base2[indexbase];
			p->symbol = '^';
			p->ex = ex2[indexex];
			p->next = NULL;
			if (head == NULL)
				head = tail = p;
			else
			{
				tail->next = p;
				tail = p;
			}
			indexbase++;
			indexex++;
		}
		return head;
	}
	return head;
} 

/*Plus And Substraction, Output a New List*/
item *Pl_or_Sub(int mode, item *head_1, item* head_2)
{
	item *p, *ptr1, *ptr2, *head, *tail, *temp;//initialize
	head = (item*)malloc(sizeof(item));
	tail = (item*)malloc(sizeof(item));
	head->base = tail->base = 'x';
	head->ex = 1;
	tail->ex = 0;
	head->num = tail->num = 0;
	head->symbol = tail->symbol = '^';
	head->next = tail;
	tail->next = NULL;//initialization done
	//copy expression_1
	for (p = head_1; p != NULL; p = p->next)
	{
		for (ptr1 = head, ptr2 = head->next; ptr2 != NULL; ptr1 = ptr1->next, ptr2 = ptr2->next)
		{
			if (ptr1->ex < p->ex)  //attach before head
			{
				temp = (item*)malloc(sizeof(item));
				temp->ex = p->ex;
				temp->base = 'x';
				temp->symbol = '^';
				temp->num = p->num;
				temp->next = head;
				head = temp;
				break;
			}
			if (ptr1->ex == p->ex)
			{
				ptr1->num += p->num;
				break;
			}
			if (ptr2->ex == p->ex)
			{
				ptr2->num += p->num;
				break;
			}
			if (ptr1->ex > p->ex && ptr2->ex < p->ex) //put between two items
			{
				temp = (item*)malloc(sizeof(item));
				temp->ex = p->ex;
				temp->base = 'x';
				temp->symbol = '^';
				temp->num = p->num;
				ptr1->next = temp;
				temp->next = ptr2;
				break;
			}
		}
	}
	//plus or substract expression 2
	for (p = head_2; p != NULL; p = p->next)
	{
		for (ptr1 = head, ptr2 = head->next; ptr2 != NULL; ptr1 = ptr1->next, ptr2 = ptr2->next)
		{
			if (ptr1->ex < p->ex)  //attach before head
			{
				temp = (item*)malloc(sizeof(item));
				temp->ex = p->ex;
				temp->base = 'x';
				temp->symbol = '^';
				temp->num = (mode)*(p->num); //either to plus or to substract, chose by "mode"
				temp->next = head;
				head = temp;
				break;
			}
			if (ptr1->ex == p->ex) //plus or substract
			{
				ptr1->num += (mode)*(p->num); //either to plus or to substract
				break;
			}
			if (ptr2->ex == p->ex)
			{
				ptr2->num += (mode)*(p->num); //either to plus or to substract
				break;
			}
			if (ptr1->ex > p->ex && ptr2->ex < p->ex) //put between two items
			{
				temp = (item*)malloc(sizeof(item));
				temp->ex = p->ex;
				temp->base = 'x';
				temp->symbol = '^';
				temp->num = (mode)*(p->num); //either to plus or to substract
				ptr1->next = temp;
				temp->next = ptr2;
				break;
			}
		}
	}
	return head;
}
/*Mutiplication, Output a New List*/
item *Multi(item *head_1, item *head_2)
{
	item *p, *ptr1, *ptr2, *pexps[100], *head, *tail;//initialize
	int count = 0;
	ptr1 = head_1;//initialization done
	while (ptr1 != NULL) //multiply lists by dismissing the 1st one into item, creating and adding up product lists
	{
		head = NULL;
		tail = NULL;
		ptr2 = head_2;
		while (ptr2 != NULL)   //create a node to store the product of head_2 and an item from head_1
		{
			p = (item*)malloc(sizeof(item));
			p->base = 'x';
			p->num = (ptr2->num) * (ptr1->num);
			p->ex = (ptr2->ex) + (ptr1->ex);
			p->symbol = '^';
			p->next = NULL; //multiply by item
			if (head == NULL)
			{
				head = p;
			}
			else
			{
				tail->next = p;
			}
			tail = p;
			ptr2 = ptr2->next;
		}
		pexps[count] = head;
		if (count != 0)    //add the sum and the current product 
		{
			*pexps = Pl_or_Sub(1, pexps[0], pexps[count]);
		}
		ptr1 = ptr1->next;
		count++;
	}
	return pexps[0];
}
/*Division, Delete the 1st List（The Dividend）*/
item *Divis(item*head_1, item*head_2)
{
	item *head_m, *p, *ptr1, *ptr2, *tail, *del;
	int numtst = 0;
	ptr1 = head_1;
	ptr2 = head_2;
	head_m = NULL;
	tail = NULL;
	if (ptr1 == NULL || ptr2 == NULL)
	{
		idiv = 0;
		return NULL;
	}
	if (ptr1->ex < ptr2->ex) //dividend is SUBORDINATE to divisor 
	{
		idiv = 0;  //NULL = Indivisible 除式次数高于被除式，不可整除
		return NULL;
	}
	while (ptr1 != NULL && ptr2 != NULL && ptr1->num != 0)
	{
		ptr2 = head_2;
		p = (item*)malloc(sizeof(item));
		numtst = (ptr1->num) % (ptr2->num);
		if (numtst != 0) ////result of dividing coefficents is NOT intenger 不可整除
		{
			idiv = 0;  
			return NULL;
		}
		p->num = (ptr1->num) / (ptr2->num);
		p->ex = (ptr1->ex) - (ptr2->ex);
		p->symbol = '^';
		p->base = 'x';
		p->next = NULL;
		ptr1 = Pl_or_Sub(-1, ptr1, Multi(ptr2, p)); //this won't change the 2nd node
		while (ptr1 != NULL && ptr1->num == 0) //delete the higher item with coefficient equaling 0
		{
			del = ptr1;
			ptr1 = ptr1->next;
			free(del);
		} 									//delete done
		if (head_m == NULL)
		{
			head_m = p;
		}
		else
		{
			tail->next = p;
		}
		tail = p;
	}
	idiv = 1;
	return head_m;
}

/*Output the Answer*/
char* PutAnsw(item *head)
{
	item *p;
	char number[15] = { 0 };
	p = head;
	if (head == NULL)
	{
		return ""; //wrong input
	}
	while (p != NULL)
	{
		if (p != head && p->num > 0 && strlen(anstring) != 0 )
		{
			strcat(anstring, "+"); //not the first
		}
		if (p->num != 0)
		{
			sprintf(number, "%d", p->num);
			strcat(anstring, number);
			if (p->ex != 0)
			{
				sprintf(number, "x^%d", p->ex);
				strcat(anstring, number);
			}
		}
		p = p->next;
	}
	return anstring;
}

//接口函数
char* getAnswer(char* input1 , char* input2 , char op)
{
	item *ex_1 = NULL, *ex_2 = NULL, *answ = NULL;//initialization done
	
	deal(input1, 1);
	deal(input2, 2);
	getData(base1, ex1, str1);
	getData(base2, ex2, str2);
	ex_1 = Read(1);
	ex_2 = Read(2);
	switch (op)//choose operation 
	{
	case '+': {
		answ = Pl_or_Sub(1, ex_1, ex_2);
		break;
	}
	case '-': {
		answ = Pl_or_Sub(-1, ex_1, ex_2);
		break;
	}
	case '*': {
		answ = Multi(ex_1, ex_2);
		break;
	}
	case '/': {
		answ = Divis(ex_1, ex_2);
		break;
	}
	}
	free(ex_1);
	free(ex_2);
	return PutAnsw(answ); //get the answer string

	
}

//检查常见的错误
int checkError(char*a, char*b)
{
	if (idiv == 0)
		return ERRNDIV;
	if (strlen(a) == 0 || strlen(b) == 0)
		return ERRNULL;
	for (int i = 0; i < strlen(a); i++)
	{
		if (!((a[i] <= '9' && a[i] >= '0') || a[i] == 'x' || a[i] == '^' || a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/'))
			return ERRCHAR;  //输入中含有非法字符
	}
	for (int i = 0; i < strlen(b); i++)
	{
		if (!((b[i] <= '9' && b[i] >= '0') || b[i] == 'x' || b[i] == '^' || b[i] == '+' || b[i] == '-' || b[i] == '*' || b[i] == '/'))
			return ERRCHAR;  //输入中含有非法字符
	}
	
	return 0;
}


