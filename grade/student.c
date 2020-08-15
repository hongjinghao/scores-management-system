#include"tools.h"
#include"student.h"


// 显示成绩
void show_grade(Student* stu ,int i)
{
	Show_grade_list;
	Show_stu_grade(i);
}

// 修改密码
bool pw_change(Student* stu,int i)
{
	debug("\n%s\n",__func__);
	char pw1[13] = {};
	char pw2[13] = {};
	printf("密码为6~12位字符或数字\n");
	printf("请输入您的新密码：");
	while(!pw_in(pw1,6,12))
	{
		printf("密码格式错误，请再次输入您的新密码:");
	}
	printf("\n请再次输入您的新密码：");
	pw_in(pw2,6,12);
	if(strcmp(pw1,pw2) || !strcmp(stu[i].pw,pw1)) 
	{
		return false;
	}
	strcpy(stu[i].pw,pw1);
	return true;
}

// 显示个人信息
void show(Student* stu,int i)
{
	Show_information_list;
	Show_stu_information(i);
}
void main_student(void)
{
	int id = 0;
	int i = 0;
	printf("请输入您的学号:");
	scanf("%d",&id);
	
	// 学号转成下标
	_id_to_index_stu(stu,Num_stu,id,&i);
	
	// 输入并判断密码是否正确，错误次数自动累加
	if(!is_error_pwin(&stu[i].cnt,stu[i].pw))
	{
		return;
	}
	
	// 判断是否为第一次登录
	if(!stu[i].flag)
	{
		while(!pw_change(stu,i))
		{
			printf("密码修改有误，请重试\n");
		}
	}
	
	printf("登录成功....\n");
	sleep(1);
	while(1)
	{
		char cmd=0;
		system("clear");
		printf("||=======================================||\n");
		printf("||                学生端                 ||\n");
		printf("||=======================================||\n");
		printf("||             请选择你的操作             ||\n");
		printf("||              1、查询成绩               ||\n");
		printf("||              2、修改密码               ||\n");
		printf("||              3、查看信息               ||\n");
		printf("||              4、返回                   ||\n");
		printf("||=======================================||\n");
		clear_stdin();
		scanf("%c",&cmd);
		switch(cmd)
		{
			case '1' : 
			{
				show_grade(stu,i); 
				go_on();
				break;
			}
			case '2' : 
			{
				if(pw_change(stu,i))
				{
					printf("修改成功\n");
				}
				else
				{
					printf("按格式改密码好吗\n");
				}
				go_on();
				break;
			}
			case '3' : 
			{
				show(stu,i);  
				go_on(); 
				break;
			}
			case '4' : return;
		}
	}
}
