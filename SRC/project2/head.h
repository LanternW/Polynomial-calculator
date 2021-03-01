#pragma once
#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include<math.h>
#include<string.h>
#include<time.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include "strlib.h"
#include "imgui.h"

#define ERROP 1
#define ERRNULL 2
#define ERRCHAR 3
#define ERRNDIV 4
#define ERRLOSEFACE 5

typedef struct a       //表达式的每一项 
{
	int ex, num;
	char symbol;
	char base;
	struct a *next;
} item;


int checkError(char*a, char*b);
char* getAnswer(char* a , char* b,char op);
void ClearAnStr();