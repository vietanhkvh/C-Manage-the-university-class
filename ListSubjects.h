#pragma once
#include <string>
#define MAXSUBJECTS 300
#define TRUE 1
#define FALSE 0
using namespace std;

struct Subject {
	char idSubject[11];
	char nameSubject[100];
	float numTheoryCredits;
	float numPracticeCredits;
};
typedef struct Subject SUBJECT;

struct ListSubject{
	int n = -1;
	SUBJECT* nodes[MAXSUBJECTS];
};

