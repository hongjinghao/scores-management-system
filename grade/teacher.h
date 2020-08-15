#ifndef TEACHER_H
#define TEACHER_H

// 教师主函数
void main_teacher(void);

// 添加学生
bool add_stu(Student* stu,int* len);

// 删除学生
bool del_stu(Student* stu,int* slen,UnStudent* ustu,int* uslen);

// 查找学生
void qurey_stu(Student* stu,int len);

// 修改学生信息
void change_infor_stu(Student* stu,int len,int cmd);

// 修改教师密码
bool modify_pw_tch(Teacher* tch,int id);

// 显示在校学生信息
void show_stu(Student* stu,int len);

// 显示退学学生
void show_ustu(UnStudent* ustu,int len);

// 成绩排名
void rank_grade(Student* stu,int len);

// 重置学生密码
bool reset_pw_stu(Student* stu,int id,int len);
#endif // TEACHER_H
