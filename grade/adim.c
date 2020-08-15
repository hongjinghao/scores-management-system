#include"tools.h"
#include"adim.h"
#include"teacher.h"

#define Show_tch_information "%12s|%11s|%14d|\n",tch[i].name,('w'==tch[i].sex?"女":"男"),tch[i].id

/*
static bool _dou_tchid_in(int *id)
{
	int id1 = 0;
	int id2 = 0;
	printf("请输入老师的工号:\n");
	scanf("%d",&id1);
	printf("请再次输入老师的工号:\n");
	scanf("%d",&id2);
	*id = id1;
	return id1==id2;
}

// 读取存储校长数据的文件
bool file_read_adim(Adim* adim)
{
	FILE* frp = fopen("./data/adim.txt","r");
	// 若不存在校长数据文件则创建并返回假
	if(NULL == frp)
	{
		FILE* fap = fopen("adim.txt","a+");
		fclose(fap);
		return false;
	}
	fread(adim,sizeof(Adim),1,frp);
	fclose(frp);
	return true;
}

// 将校长的数据写入文件中
bool file_write_adim(Adim* adim)
{
	FILE* fwp = fopen("./data/adim.txt","w");
	fwrite(adim,sizeof(Adim),1,fwp);
	fclose(fwp);
	return true;
}*/

// 重置校长密码
bool reset_pw_adim(Adim* adim)
{
	debug("\n%s\n",__func__);
	adim->cnt = 0;
	adim->flag = 0;
	strcpy(adim->pw,"000000");
	return true;
}

// 修改校长密码
bool modify_pw_adim(Adim* adim)
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
	if(strcmp(pw1,pw2) || !strcmp(adim->pw,pw1)) 
	{
		return false;
	}
	strcpy(adim->pw,pw1);
	return true;
}

// 重置教师密码
bool reset_pw_tch(Teacher* tch,int id)
{
	debug("\n%s\n",__func__);
	for(int i=0; i<Num_tch;i++)
	{
		if(tch[i].id == id && tch[i].flag>=0)
		{
			strcpy(tch[i].pw,"000000");
			tch[i].cnt = 0;
			tch[i].flag = 0;
			return true;
		}
	}
	return false;
}
/*
// 读取教师数据文件
void file_write_tch(Teacher** tch)
{
	FILE* frp = fopen("./data/tch.txt","r");
	fread(*tch,sizeof(Teacher),Num_tch,frp);
	fclose(frp);
}*/

// 添加教师
bool add_tch(Teacher* tch,int len)
{
	debug("\n%s\n",__func__);
	if(Num_tch >= TCH_MAX+Num_utch)
	{
		return false;
	}
	printf("请依次输入该教师的姓名与性别(m/w):\n");
	
	// 初始化新增老师的信息
	scanf("%s %c",tch[Num_tch].name,&tch[Num_tch].sex);
	if('m'!=tch[Num_tch].sex && 'w'!=tch[Num_tch].sex) 
	{
		return false;
	}
	
	tch[Num_tch].id = TCH_ID+Num_tch;
	
	strcpy(tch[Num_tch].pw,"000000");
	
	tch[Num_tch].cnt = 0;

	tch[Num_tch].flag = 0;
		
	printf("该老师的工号为:%d\n",tch[Num_tch].id);
	Num_tch++;
	return true;
}

// 删除教师
bool del_tch(Teacher* tch,int id)
{
	debug("\n%s\n",__func__);
	for(int i=0;i<Num_tch;i++)
	{
		if((id == tch[i].id) && (tch[i].flag >= 0))
		{
			// 将i后面的数据往前移动一个单位
			//memmove(&tch[i],&tch[i+1],sizeof(Teacher)*(Num_tch-i));
			Num_utch++;
			tch[i].flag = -1;
			return true;
		}
	}
	return false;
}

// 显示在职/离职教师
void show_tch_untch(Teacher* tch,int modify,int Num_tch)
{
	debug("\n%s\n",__func__);
	for(int i=0;i<Num_tch;i++)
	{
		if(modify == 1 && tch[i].flag>=0)
		{
			printf(Show_tch_information);
			printf("-------------------------------------\n");
		}
		if(modify == -1 && tch[i].flag<0)
		{
			printf(Show_tch_information);
			printf("-------------------------------------\n");
		}
	}
}

// 解锁老师
bool unlock_tch(Teacher* tch,int id)
{
	debug("\n%s\n",__func__);
	for(int i=0;i<Num_tch;i++)
	{
		if((tch[i].id == id) && (tch[i].flag>0) && (tch[i].cnt>3))
		{
			tch[i].cnt = 0;
			tch[i].flag = 0;
			strcpy(tch[i].pw,"000000");
			return true;
		}
	}
	return false;
}

void main_adim(Adim* ad)
{
	char pw[13] = {};
	printf("请输入您的密码\n");
	while(pw_in(pw,6,12))
	{
		if(!strcmp(pw,ad->pw)) break;
		printf("密码输入错误，请重新输入\n");
	}
	debug("\n%s\n",__func__);
	/*
	if(!file_read_adim(&ad))
	{
		printf("没有校长的数据文件或被误删，正在创建中请稍后。。。。。\n初始密码:000000\n");
		sleep(2);
	}*/
	if(0 == ad->flag)
	{
		system("clear");
		printf("第一次登陆，请修改密码\n");
		while(!modify_pw_adim(ad))
		{
			printf("修改失败，请重新修改。。。。\n");
			go_on();
			system("clear");
		}
		ad->flag = 1;
	}
	while(1)
	{
		char cmd=0;
		system("clear");
		printf("||=======================================||\n");
		printf("||                校长端                 ||\n");
		printf("||=======================================||\n");
		printf("||             请选择你的操作             ||\n");
		printf("||              1、重置自己密码           ||\n");
		printf("||              2、修改自己密码           ||\n");
		printf("||              3、重置教师密码           ||\n");
		printf("||              4、添加教师               ||\n");
		printf("||              5、删除教师               ||\n");
		printf("||              6、显示所有在职教师       ||\n");
		printf("||              7、显示所有离职教师       ||\n");
		printf("||              8、返回                   ||\n");
		printf("||=======================================||\n");
		clear_stdin();
		scanf("%c",&cmd);
		switch(cmd)
		{
			case '1' :
			{
				reset_pw_adim(ad);
				printf("已重置....\n");
				sleep(1);
				break;
			}
			case '2' :modify_pw_adim(ad);break;
			case '3' :
			{
				int id = 0;
				if(_dou_id_in(&id,"老师的工号"))
				{
					printf("%s\n",true ==reset_pw_tch(tch,id)?"重置成功":"别乱搞，工号乱输我重置谁的密码？");
					go_on();
				}
				else
				{
					printf("两次输入不一致。。。\n");
					go_on();
				}
				break;
			}
			case '4' :
			{
				printf("%s \n",true == add_tch(tch,TCH_MAX)?"添加成功":"添加失败");
				go_on();
				break;
			}
			case '5' :
			{
				int id = 0;
				if(_dou_id_in(&id,"老师的工号"))
				{
					printf("%s\n",1==del_tch(tch,id)?"删除成功":"别乱删老师，工号都能打错来。。。");
					go_on();
				}
				else
				{
					printf("两次输入不一致。。。\n");
					go_on();
				}
				break;
			}
			case '6' :
			{
				printf("      姓名|      性别|          工号|\n");
				printf("-------------------------------------\n");
				show_tch_untch(tch,1,Num_tch); 
				go_on();
				break;
			}
			case '7' :
			{
				printf("      姓名|      性别|          工号|\n");
				printf("-------------------------------------\n");
				show_tch_untch(tch,-1,Num_tch);
				go_on();
				break;
			}
			case '8' :return;
			default :break;
		}
	}
}
