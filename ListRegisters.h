#pragma once
#include <iostream>
#include <string>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define MAX 2000
using namespace std;

struct Register{
	char idStudent[13];
	float point;
	
};
struct NODE_REGISTER{
	Register IFRegister;
	struct NODE_REGISTER* Next;
};
//typedef struct nodeRegister NODE_REGISTER;
 
struct listRegister {
	int n=0;
	NODE_REGISTER *Head, *Tail;
};


