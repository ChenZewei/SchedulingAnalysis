#ifndef TYPES_H
#define TYPES_H

#include <string.h>
//including GNU Multiple Precision Arithmetic Library
#include <gmpxx.h>
#include <vector>
#include <list>
#include <math.h>
#include <time.h>

#define uint unsigned int
#define ulong unsigned long

#define MAX_LONG 0xffffffffffffffff
#define MAX_INT  0xffffffff
#define _EPS 0.000001

//output file format
#define PNG 	0x01
#define EPS 	0x02
#define SVG 	0x04
#define TGA 	0x08
#define JSON 	0x10

//VNode type
#define P_NODE 0x02
#define C_NODE 0x04
#define J_NODE 0x08

#define S_NODE 0x00
#define E_NODE 0x01

//Graph type
#define G_TYPE_P 0 //Paralleled
#define G_TYPE_C 1 //Conditional

#define P_EDF 0
#define BCL_FTP 1
#define BCL_EDF 2
#define WF_DM 3
#define WF_EDF 4
#define RTA_GFP 5
#define FF_DM 6

#define TPS_TASK_MODEL 0 //Three Parameters Sporadic Task Model
#define DAG_TASK_MODEL 1

#define PRIORITY 0

#define INCREASE 0
#define DECREASE 1

using namespace std;

typedef mpz_class int_t;		//multiple precision integer
typedef mpq_class fraction_t;		//multiple precision rational number
typedef mpf_class floating_t;		//multiple precision float number

class Task;
class TaskSet;
class Processor;
class ProcessorSet;
class Resource;
class ResourceSet;

typedef struct
{
	double min;
	double max;
}Range;

typedef struct
{
	double x;
	double y;
}Result;

typedef struct
{
	int test_method;
	int test_type;
	string remark;
}Test_Attribute;

typedef vector<int> Int_Set;
typedef vector<double> Double_Set;
typedef vector<Range> Range_Set;
typedef vector<Result> Result_Set;
typedef vector<Result_Set> Result_Sets;
typedef vector<Test_Attribute> Test_Attribute_Set;
typedef list<void*> TaskQueue;//之所以用list是因为list是双向链表，适合增删比较频繁的情况



#endif
