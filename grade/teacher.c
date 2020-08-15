#include"tools.h"
#include"teacher.h"


static void _rank(int* arr,int* rank_,int byte,int len)
{
	int rank = 1;
	for(int i=0; i<len; i++)
	{
		for(int j=0; j<len; j++)
		{
			if(*(arr+byte*i/4) < *(arr+byte*j/4))
			{
				++rank;
			}

		}
		int* temp = (rank_+byte*i/4);
		*temp = rank;
		rank = 1;
	}
}

// 成绩排名
void rank_grade(Student* stu,int len)
{
	_rank(&stu[0].math,&stu[0].rank_math,sizeof(Student),len);
	_rank(&stu[0].ch,&stu[0].rank_ch,sizeof(Student),len);
	_rank(&stu[0].en,&stu[0].rank_en,sizeof(Student),len);
	_rank(&stu[0].sum,&stu[0].rank,sizeof(Student),len);
}

// 添加学生
bool add_stu(Student* stu,int* len)
{
	debug("\n%s\n",__func__);
	
	int cmd = 0;
	
	// 判断学生人数是否到达上限
	if(*len >= STU_MAX+Num_ustu)
	{
		return false;
	}
	
	// 选择添加方式
	printf("1、单个添加\n2、批量添加\n请选择:");
	scanf("%d",&cmd);
	
	switch(cmd)
	{
		case 1:
		{
			printf("请依次输入该学生的姓名与性别(m/w):\n");
		
			// 初始化新增学生的信息
			memset(&stu[*len],'\0',sizeof(Student));
			scanf("%s %c",stu[*len].name,&stu[*len].sex);
			stu[*len].id = STU_ID+*len;
			strcpy(stu[Num_stu].pw,"000000");
			
			// 判断输入性别是否有误
			if('m'!=stu[*len].sex && 'w'!=stu[*len].sex) return false;	
		
			printf("该学生的学号为:%d\n",stu[*len].id);
			*len+=1;
			return true;
		}
		case 2:
		{
			char file[255] = {};
			int num = 0;
			char name[20] = {};
			char sex = 0;
			int cnt = 0;
			printf("请输入文件名(文件需要在当前目录下 格式为：姓名 性别)：");
			clear_stdin();
			scanf("%s",file);
			
			FILE* frp = fopen(file,"r");
			
			if(NULL == frp)
			{
				return false;
			}

			// 如果录入人数大于最大人数，需要减少录入人数
			printf("请输入录入人数：");
			clear_stdin();
			scanf("%d",&num);
			if(num+*len > STU_MAX)
			{

				
				num = STU_MAX - *len;
			}
			
			
			// 依次录入学生信息
			for(int i=0; i<num; i++)
			{

				fscanf(frp,"%s %c\n",name,&sex);
				if(sex != 'w' && sex != 'm')
				{
					
					continue;
				}
				
				strcpy(stu[*len].name,name);
				stu[*len].sex = sex;
				stu[*len].id = STU_ID + *len;
				*len += 1;

				cnt++;
			}
			printf("成功%d个学生",cnt);
			return true;
		}
	}
	return false;
}

// 删除学生
bool del_stu(Student* stu,int* slen,UnStudent* ustu,int* uslen)
{
	int id = 0;
	int i=0;
	// 没人不能删
	if(*slen<0) return false;
	
	// 获取要删除学生的学号
	_dou_id_in(&id,"要删除的学生学号");
	
	// 根据学号找学生
	for(i=0;i<*slen;i++)
	{
		if(stu[i].id == id)
		{
			break;
		}
	}
	if(i == *slen) return false;
	
	strcpy(ustu[*uslen].name,stu[i].name);
	ustu[*uslen].sex = stu[i].sex;
	ustu[Num_ustu].id = stu[i].id;
	
	memmove(&stu[i],&stu[i+1],sizeof(Student)*(*slen-i));
	*uslen+=1;
	*slen-=1;
	return true;
}


// 查找学生
void qurey_stu(Student* stu,int len)
{
	int cmd = 0;
	int flag = 0;
	system("clear");
	
	printf("1、姓名查找\n2、学号查找\n请输入命令:\n");
	scanf("%d",&cmd);
	
	switch(cmd)
	{
		case 1:
		{
			char name[20] = {};
			
			printf("请输入学生的姓名（支持模糊查找）:");
			clear_stdin();
			scanf("%s",name);
			
			// 显示
			Show_information_list;
			for(int i=0;i<len;i++)
			{
				if(NULL != strstr(stu[i].name,name))
				{
					Show_stu_information(i);
					flag++;
				}
			}
			
			if(flag)
			{
				printf("一共找到%d 位匹配的学生",flag);
			}
			else
			{
				printf("再想想吧，没有您要找的学生\n");
			}
			break;
		}
		case 2:
		{
			int id = 0;
			int i = 0;
			
			printf("请输入要查找的学生学号:\n");
			clear_stdin();
			scanf("%d",&id);
			
			if(_id_to_index_stu(stu,len,id,&i))
			{
				Show_information_list;
				Show_stu_information(i);
			}
			else
			{	
				printf("没有这个学号，去问问你的学生他学号是多少\n");
			}
			break;
		}
		default :
		{
			printf("别乱输指令!\n");
			break;
		}
	}
	go_on();
	return;
}

// 修改学生信息
void change_infor_stu(Student* stu,int index,int cmd)
{
	switch(cmd)
	{	
		case 1:
		{
			char sex = 0;
			char name[20] = {};
			
			Show_information_list;
			Show_stu_information(index);
			
			printf("请分别输入修改后的姓名与性别(w/m):");
			scanf("%s %c",name,&sex);
			
			// 判断性别是否有误
			while(sex!='w' && sex!='m')
			{
				printf("性别有误，重新输入\n");
				scanf("%s %c",name,&sex);
			}
			
			printf("修改成功\n");
			stu[index].sex = sex;
			strcpy(stu[index].name,name);
			break;
		}
		case 2:
		{
			Show_grade_list;
			Show_stu_grade(index);
			
			printf("请输入修改后的数学、语文、英语成绩\n");
			scanf("%d%d%d",&stu[index].math,&stu[index].ch,&stu[index].en);
			
			// 判断成绩是否有误
			while(!(is_right_grade(stu[index].math)&&is_right_grade(stu[index].ch)&&is_right_grade(stu[index].en)))
			{
				printf("成绩格式输入有误请重新输入\n");
				scanf("%d%d%d",&stu[index].math,&stu[index].ch,&stu[index].en);
			}
			stu[index].sum = stu[index].math+stu[index].ch+stu[index].en;
			printf("修改成功\n");			
		}
	}
	go_on();
	return;
}

// 录入学生成绩
bool sign_in_stuinfor(Student* stu,int len)
{
	int cmd = 0;
	printf("1、单个录入\n2、批量录入\n请选择：");
	clear_stdin();
	scanf("%d",&cmd);
	
	system("clear");
	switch(cmd)
	{
		case 1 :
		{
			int id = 0;
			int i = 0;
			if(!_dou_id_in(&id,"学生的学号"))
			{
				printf("输入错误\n");
				go_on();
				return false;
			}
			
			// 打印学生的成绩
			_id_to_index_stu(stu,len,id,&i);
			Show_grade_list;
			Show_stu_grade(i);
			
			// 修改学生成绩
			change_infor_stu(stu,Num_stu,2);
			return true;
			break;
		}
		case 2 : 
		{
			char file[255] = {};
			printf("请输入文件名(在当前目录下，文件格式：学号 数学成绩 语文成绩 英语成绩 ):");
			int id = 0;
			int math = 0;
			int ch = 0;
			int en = 0;
			int num = 0;
			int cnt = 0;
			
			// 获取文件位置
			clear_stdin();
			scanf("%s",file);
			FILE* frp = fopen(file,"r");
			if(NULL == frp)
			{
				printf("输入路径有误\n");
				go_on();
				return false;
			}
			
			printf("录入的人数：");
			clear_stdin();
			scanf("%d",&num);
			
			// 依次录入学生成绩，不符合要求的不会录入
			for(int i=0; i<num; i++)
			{
				fscanf(frp,"%d %d %d %d\n",&id,&math,&ch,&en);
				for(int j=0; j<len; j++)
				{
					if(id == stu[j].id)
					{
						if(is_right_grade(math) && is_right_grade(ch) && is_right_grade(en))
						{
							stu[j].math = math;
							stu[j].ch = ch;
							stu[j].en = en;
							stu[j].sum = math+ch+en;
							cnt++;
						}
					}
				}
			}
		
			printf("成功录入%d个学生的成绩\n",cnt);
			go_on();
			break;
		}
	}
	return false;
}

// 重置学生密码
bool reset_pw_stu(Student* stu,int id,int len)
{
	debug("\n%s\n",__func__);
	int i = 0;
	if(!_id_to_index_stu(stu,len,id,&i))
	{
		return false;
	}
	strcpy(stu[i].pw,"000000");
	stu[i].flag = 0;
	stu[i].cnt = 0;
	return true;
}

// 修改教师密码
bool modify_pw_tch(Teacher* tch,int id)
{
	debug("\n%s\n",__func__);
	char pw1[13] = {};
	char pw2[13] = {};
	
	// 两次输入密码
	printf("密码为6~12位字符或数字\n");
	printf("请输入您的新密码：");
	while(!pw_in(pw1,6,12))
	{
		printf("密码格式错误，请再次输入您的新密码:");
	}
	
	printf("\n请再次输入您的新密码：");
	pw_in(pw2,6,12);
	
	// 对输入密码进行比较
	if(strcmp(pw1,pw2) || !strcmp(tch[id].pw,pw1)) 
	{
		return false;
	}
	strcpy(tch[id].pw,pw1);
	return true;
}

// 显示在校学生信息
void show_stu(Student* stu,int len)
{
	int cmd;
	printf("1、显示个人信息\n");
	printf("2、显示成绩信息\n");
	printf("请选择:");
	scanf("%d",&cmd);
	system("clear");
	switch(cmd)
	{
		case 1:
		{
			Show_information_list;

			for(int i=0;i<len;i++)
			{
				Show_stu_information(i);
			}
			break;
		}
		case 2:
		{
			Show_grade_list;
			for(int i=0;i<len;i++)
			{
				Show_stu_grade(i);
			}
			break;
		}
		default:
		{
			printf("无效操作\n");
		}
	}
	go_on();
	return ;
}

// 显示退学学生
void show_ustu(UnStudent* ustu,int len)
{
	system("clear");
	printf("      学号|      姓名|性别|\n");
	printf("--------------------------\n");
	for(int i=0;i<len;i++)
	{
		Show_ustu_information(i);
	}
	go_on();
	return;
}

// 教师主函数
void main_teacher(void)
{
	int id = 0;
	int i =	0;
	
	// 工号输入以及判断是否正确与锁定
	printf("请输入您的工号:");
	scanf("%d",&id);
	for(i=0;i<Num_tch;i++)
	{
		if(tch[i].id == id)
		{
			break;
		}
	}
	if(i == Num_tch)
	{
		printf("工号输入有误。。。。");
		go_on();
		return;
	}
	if(tch[i].cnt>=3 || tch[i].flag<0)
	{
		printf("登录失败，请联系校长。。。");
		go_on();
		return;
	}
	
	// 输入密码并判断是否有误，以及锁定
	if(!is_error_pwin(&tch[i].cnt,tch[i].pw)) 
	{
		return;
	}

	// 判断是否是第一次登录
	if(0 == tch[i].flag)
	{
		system("clear");
		printf("第一次登陆请修改密码\n");
		while(!modify_pw_tch(tch,i))
		{
			printf("密码修改有误，请重新修改\n");
		}
		tch[i].flag = 1;
	}
	
	printf("登录成功!\n");
	sleep(1);
	while(1)
	{
		system("clear");
		int cmd = 0;
		printf("===========================================\n");
		printf("                教师端		        \n");
		printf("||=======================================||\n");
		printf("||             请选择你的操作            ||\n");
		printf("||              1、添加学生              ||\n");
		printf("||              2、删除学生              ||\n");
		printf("||              3、查找学生              ||\n");
		printf("||              4、修改学生信息          ||\n");
		printf("||              5、录入学生成绩          ||\n");
		printf("||              6、重置学生密码          ||\n");
		printf("||              7、显示在校学生信息      ||\n");
		printf("||              8、显示退学学生信息      ||\n");
		printf("||              9、修改密码              ||\n");
		printf("||              10、返回                 ||\n");
		printf("||=======================================||\n");
		clear_stdin();
		scanf("%d",&cmd);
		switch(cmd)
		{
			case 1 :
			{
				if(add_stu(stu,&Num_stu))
				{
					printf("添加成功\n");
					rank_grade(stu,Num_stu);
				}
				else
				{
					printf("别乱输信息！或文件读取失败!若信息无误请联系管理员！\n添加失败.....\n");
				}
				go_on();
				break;
			}
			case 2 :
			{
				if(del_stu(stu,&Num_stu,ustu,&Num_ustu))
				{
					printf("删除成功^.^\n");
					rank_grade(stu,Num_stu);
				}
				else
				{
					printf("没人你删什么，想要把系统删啦？\n");
				}
				go_on();
				break;
			}
			case 3 :
			{
				qurey_stu(stu,Num_stu);
				rank_grade(stu,Num_stu);
				break;
			}
			case 4 :
			{
				int cmd = 0;
				int index = 0;
				int id_stu = 0;
				printf("1、修改基础信息\n2、修改成绩信息\n请选择修改的方式\n");
				scanf("%d",&cmd);
				system("clear");
	
				if(!_dou_id_in(&id_stu,"要修改的学生学号"))
				{
					printf("输入错误\n");
					go_on();
					return;
				}
				if(!_id_to_index_stu(stu,Num_stu,id_stu,&index)) 
				{
					return;
				}
				change_infor_stu(stu,index,cmd);
				rank_grade(stu,Num_stu);
				break;
			}
			case 5 :
			{
				sign_in_stuinfor(stu,Num_stu);
				rank_grade(stu,Num_stu);
				break;
			}
			case 6 :
			{
				int id_stu = 0;
				_dou_id_in(&id_stu,"学生的学号");
				if(reset_pw_stu(stu,id_stu,Num_stu))
				{
					printf("重置成功\n");
				}
				else
				{
					printf("别乱输学号，爬爬爬\n");
				}				
				break;
			}
			case 7 :
			{
				show_stu(stu,Num_stu);
				break;
			}
			case 8 :
			{
				show_ustu(ustu,Num_ustu);
				break;
			}
			case 9 :
			{
				if(!modify_pw_tch(tch,i))
				{
					printf("别乱改，看清楚条件，忘记密码了你就爬\n");
				}
				else
				{
					printf("修改成功^.^\n");
				}
				go_on();
				break;
			}
			case 10:return;
		}
	}
}
