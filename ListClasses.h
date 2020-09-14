
#include <string>
#define MAXCLASS 1000
#include "ListRegisters.h"
using namespace std;

struct Class {
	unsigned int idClass;
	char idSubject[11];
	char schoolYear[10];
	int numberSemester;
	int idGroup;
	int maxNumStudents;
	int minNumStudents;
	//ds sv dk
	listRegister listRegisters;		
};

struct NodeClass{
    Class clAss;
	struct NodeClass *left;
	struct NodeClass *right;
};
typedef NodeClass* TREECLASS;

//DSLKD cua lop tin chi
typedef Class CLASS;
struct nodeClass{
	CLASS IFCLASS;
	struct nodeClass* Next;
};
typedef struct nodeClass NODE_CLASS;

struct listClassLK{
	int n=0;
	NODE_CLASS *Head, *Tail;
};
