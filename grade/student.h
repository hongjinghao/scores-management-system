#ifndef STUDENT_H
#define STUDENT_H

// 学生程序主函数
void main_student(void);

// 显示成绩
void show_grade(Student* stu ,int i);

// 修改密码
bool pw_change(Student* stu,int i);

// 显示个人信息
void show(Student* stu,int i);

#endif // STUDENT_H
