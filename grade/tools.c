#include"tools.h"
#include"teacher.h"
#include"student.h"
#include"adim.h"

Student* stu;
UnStudent* ustu;
Teacher* tch;
Adim ad = {"000000",0};

// 任意键继续
void go_on(void)
{
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	puts("任意键继续。。。");
	getch();
	return;
}

// 分配堆内存
static void send(int unstu)
{
	stu = malloc(sizeof(Student)*STU_MAX);
	ustu = malloc(sizeof(UnStudent)*(STU_MAX+unstu));
	tch = malloc(sizeof(Teacher)*100);
}

// 读取数据
int Read(void)
{

	// 创建文件
	FILE* fasp = fopen("./date/student.txt","a+");
	FILE* fausp = fopen("./date/unstudent.txt","a+");
	FILE* fatp = fopen("./date/teacher.txt","a+");
	FILE* faop = fopen("./date/other.txt","a+");
	FILE* faap = fopen("./date/adim.txt","a+");
	fclose(fasp);
	fclose(fausp);
	fclose(fatp);
	fclose(faop);
	fclose(faap);
	// 打开文件
	FILE* fsrp = fopen("./date/student.txt","r");
	FILE* fusrp = fopen("./date/unstudent.txt","r");
	FILE* ftrp = fopen("./date/teacher.txt","r");
	FILE* forp = fopen("./date/other.txt","r");
	FILE* farp = fopen("./date/adim.txt","r");
	if((NULL==fsrp)||(NULL==fusrp)||(NULL==ftrp)||(NULL==forp)||(NULL==farp))
	{
		printf("有关键文件被删除啦，请联系管理员...\n");
		return ERROR;
	}
	
	int arr[13] = {};
	
	// 读取数据
	fread(arr,sizeof(arr),13,forp);
	Ave = arr[0];
	Max = arr[1];
	Max_m = arr[2];
	Max_c = arr[3];
	Max_e = arr[4];
	Min = arr[5];
	Min_m = arr[6];
	Min_c = arr[7];
	Min_e = arr[8];
	Num_stu = arr[9];
	Num_ustu = arr[10];
	Num_tch = arr[11];
	Num_utch = arr[12];
	send(Num_ustu);
	
	fread(tch,sizeof(tch[0]),Num_tch,ftrp);
	fread(stu,sizeof(stu[0]),Num_stu,fsrp);
	fread(ustu,sizeof(ustu[0]),Num_ustu,fusrp);
	fread(&ad,sizeof(ad),1,farp);
	
	return OK;
}
	
// 运行程序
int run_system(void)
{
	if(ERROR == Read())
	{
		return ERROR;
	}
	while(1)
	{
		system("clear");
		int cmd = 0;
		printf("||=======================================||\n");
		printf("||           欢迎使用古德学校的系统      ||\n");
		printf("||=======================================||\n");
		printf("||           请选择您的登录方式          ||\n");
		printf("||                 1、学生               ||\n");
		printf("||                 2、教师               ||\n");
		printf("||                 3、校长               ||\n");
		printf("||                 4、退出               ||\n");
		printf("||=======================================||\n");
		scanf(" %d",&cmd);
		switch(cmd)
		{
			case 1 : main_student();break;
			case 2 : main_teacher();break;
			case 3 : main_adim(&ad);break;
			case 4 : Write();return OK;
			default  : run_system();
		}
		debug("%s\n",__func__);
	}
}
	
// 保存数据、释放内存
void Write(void)
{
	// 打开并清空other文件
	FILE* fowp = fopen("./date/other.txt","w");
	FILE* fswp = fopen("./date/student.txt","w");
	FILE* fuswp = fopen("./date/unstudent.txt","w");
	FILE* ftwp = fopen("./date/teacher.txt","w");
	FILE* fawp = fopen("./date/adim.txt","w");
	
	int arr[13] = {};
	arr[0] = Ave;
	arr[1] = Max;
	arr[2] = Max_m;
	arr[3] = Max_c;
	arr[4] = Max_e;
	arr[5] = Min;
	arr[6] = Min_m;
	arr[7] = Min_c;
	arr[8] = Min_e;
	arr[9] = Num_stu;
	arr[10] = Num_ustu;
	arr[11] = Num_tch;
	arr[12] = Num_utch;
	
	// 保存数据
	fwrite(arr,sizeof(arr[0]),13,fowp);
	fwrite(&ad,sizeof(Adim),1,fawp);
	fwrite(stu,sizeof(Student),Num_stu,fswp);
	fwrite(ustu,sizeof(UnStudent),Num_ustu,fuswp);
	fwrite(tch,sizeof(Teacher),Num_tch,ftwp);
	
	
	// 释放内存
	free(stu);
	free(ustu);
	free(tch);
	//return i;
	debug("%s\n",__func__);
}

// 清空输入缓冲区
void clear_stdin(void)
{
	stdin->_IO_read_ptr = stdin->_IO_read_end;;
}

// 输入密码
bool pw_in(char* str,int min,int max)
{
	clear_stdin();
    for(int i=0;i<max;i++)
    {
        scanf("%c",&str[i]);
        if(strlen(str)>min && str[i] == '\n')
        {
        	str[i] = 0;
            return true;
        }
        if(str[i] == '\n' || str[i] == ' ')
        {
        	bzero(str,max);
            return false;
        }
    }
    bzero(str,max);
    return false;
    debug("%s\n",__func__);
}

// 两次输入工号、学号
bool _dou_id_in(int *id,char* str)
{
	int id1 = 0;
	int id2 = 0;
	printf("请输入%s:\n",str);
	scanf("%d",&id1);
	printf("请再次输入%s:\n",str);
	scanf("%d",&id2);
	*id = id1;
	return id1==id2;
}

// 输入密码并判断是否有误，以及锁定
bool is_error_pwin(int* cnt,char* str)
{
	char pw[13] = {};
	*cnt = 0;
	
	printf("请输入您的密码:");
	while(pw_in(pw,6,12))
	{
		if(!strcmp(pw,str))
		{
			break;
		}
		if(++*cnt>=3)
		{
			printf("账号已锁定，请联系您的上一级管理员\n");
			go_on();
			return false;
		}
		printf("密码输入错误，请重新输入（还有%d次机会）\n",3-*cnt);
	}
	return true;
}

// 判断成绩是否正确
bool is_right_grade(int num)
{
	if(num<0 || num>150)
	{
		return false;
	}
	return true;
}

// 根据学号找位置
bool _id_to_index_stu(Student* stu,int len,int id,int* index)
{
	for(int i=0;i<len;i++)
	{
		if(stu[i].id == id)
		{
			*index = i;
			return true;
		}
	}
	return false;
}
