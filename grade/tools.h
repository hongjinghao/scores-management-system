#ifndef TOOLS_H
#define TOOLS_H

#if DDEBUG
	#define debug(...) printf(__VA_ARGS__)
#else
	#define debug(...)
#endif

#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
#include<getch.h>
#include<stdbool.h>
#include"dingyi.h"

// 任意键继续
void go_on(void);

// 读取数据
int Read(void);
	
// 运行程序
int run_system(void);
	
// 保存数据
void Write(void);

// 输入密码
bool pw_in(char* str,int min,int max);

// 清空输入缓冲区
void clear_stdin(void);

// 两次输入工号、学号
bool _dou_id_in(int *id,char* str);

// 输入密码并判断是否有误，以及锁定
bool is_error_pwin(int* cnt,char* str);

// 判断成绩是否正确
bool is_right_grade(int num);

// 根据学号找位置
bool _id_to_index_stu(Student* stu,int len,int id,int* index);
	
// 结构体声明
extern Student* stu;
extern UnStudent* ustu;
extern Teacher* tch;
extern Adim ad;

#endif //TOOLS_H
