#pragma once
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

#define TRUE 1
#define FALSE 0

struct Student {
	char idStudent[13];
	string lastName;//ho
	string firstName;//tên
	int gender;
	int numberPhone;
	char idClass[16];
	int yearStudy;
};

struct nodeStudent{
	Student IFStudent;
	struct nodeStudent* Next;
};
typedef struct nodeStudent NODE_STUDENT;

struct listStudent{
	int n=0;
	NODE_STUDENT *Head, *Tail;
};

