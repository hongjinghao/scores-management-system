#ifndef DINGYI_H
#define DINGYI_h

// 输出学生信息
#define Show_stu_information(i) printf("%14d|%12s|%12s|%5d|%7d|\
\n---------------------------------------------------\n",stu[i].id,stu[i].name,'w'==stu[i].sex?"女":"男",\
stu[i].sum,stu[i].rank)

#define Show_stu_grade(i) printf("%14d|%5d|%8d|%5d|%8d|%5d|%8d|%5d|%8d|\
\n----------------------------------------------------------------------------\n",\
stu[i].id,stu[i].math,stu[i].rank_math,stu[i].ch,stu[i].rank_ch,stu[i].en,stu[i].rank_ch,stu[i].sum,stu[i].rank)

#define Show_ustu_information(i) printf("%10d|%12s|%5s|\n--------------------------\n",\
ustu[i].id,ustu[i].name,'w'==ustu[i].sex?"女":"男")

#define Show_information_list printf("          学号|      姓名|       性别| 总分| 总排名|\
\n---------------------------------------------------\n")

#define Show_grade_list	printf("          学号| 数学|数学排名| 语文|语文排名| 英语|英语排名| 总分|总分排名|\
\n----------------------------------------------------------------------------\n")

// 交换宏函数
#define swap(a,b) {typeof (a);t=a;a=b;b=t;}

// 学生结构体
typedef struct Student
{
	// 姓名
	char name[20];
	
	// 性别
	char sex;
	
	// 学号
	int id;
	
	// 密码
	char pw[13];
	
	// 数学、语文、英语、总分
	int math;
	int ch;
	int en;
	int sum;
	
	// 	排名（数学、语文、英语、总）
	int rank_math;
	int rank_ch;
	int rank_en;
	int rank;
	
	// 登录错误次数
	int cnt;
	
	// 状态（0是第一次登录）
	int flag;
}Student;

// 退学学生结构体
typedef struct UnStudent
{
	// 姓名
	char name[20];
	
	// 性别
	char sex;
	
	// 学号
	int id;
	
}UnStudent;

// 教师结构体
typedef struct Teacher
{
	// 姓名
	char name[20];
	
	// 性别
	char sex;
	
	// 工号
	int id;
	
	// 密码
	char pw[13];
	
	// 登录错误次数
	int cnt;
	
	// 状态（0是第一次登录、负数离职、正数在职）
	int flag;
}Teacher;

// 校长结构体
typedef struct Adim
{
	// 密码
	char pw[13];
	
	// 登录错误次数
	int cnt;
	
	// 是否第一次登录
	int flag;
}Adim;

int Ave;		// 平均分

int Max;		// 最高分(总、数学、英语、语文)
int Max_m;
int Max_c;
int Max_e;

int Min;		// 最低分(总、数学、英语、语文)
int Min_m;
int Min_c;
int Min_e;

int Num_stu;	// 学生个数
int Num_ustu;	// 退学学生个数
int Num_tch;	// 教师个数
int Num_utch;	// 离职教师个数

#define STU_MAX (500)
#define TCH_MAX	(100)
#define STU_ID	(201000)	// 学生学号前缀
#define TCH_ID	(202000)	// 教师工号前缀
#define ERROR	(-1)		// 返回值错误
#define OK		(0)			// 返回值正确
#endif // DINGYI_H
