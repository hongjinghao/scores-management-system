#ifndef ADIM_H
#define ADIM_H

// 校长系统主函数
void main_adim(Adim* ad);

// 读取存储校长数据的文件
//bool file_read_adim(Adim* adim);

// 将校长的数据写入文件中
//bool file_write_adim(Adim* adim);

// 重置校长密码
bool reset_pw_adim(Adim* adim);

// 修改校长密码
bool modify_pw_adim(Adim* adim);

// 重置教师密码
bool reset_pw_tch(Teacher* tch,int id);

// 读取教师数据文件
//void file_write_tch(Teacher** tch);

// 添加教师
bool add_tch(Teacher* tch,int len);

// 删除教师
bool del_tch(Teacher* tch,int id);

// 显示在职/离职教师
void show_tch_untch(Teacher* tch,int modify,int Num_tch);

// 解锁老师
bool unlock_tch(Teacher* tch,int id);

#endif // ADIM_H
