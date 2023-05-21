#ifndef SOORT_H
#define SOORT_H
#include <stdio.h>
#include "../library_code/zylib.h"
#include "../library_code/zyrandom.h"
#include "../library_code/dynarray.h"
#include <stdlib.h>

int Login();/*登录函数，用于判定是否成功登录，即用户名是否存在和其对应密码是否正确*/


int Menu();/*在成功登录后，显示主菜单函数*/

int Menu1();/*在成功登录后，选择查询选课整体情况时，显示菜单的函数*/


void BacktoMenu(int h);/*完成一次操作后，判定是否返回主菜单*/


void Select(int t);/*选课操作函数，用于判定选课是否合理，以及将选课信息输入选课信息文件*/

void SearchI(int t);/*查询个人信息*/

void SearchAll(int id);/*查询整体信息*/


void Sort1();/*查询选课量排序*/

void Sort2();/*查询总学分数学生排序（只显示当前已选课学生）*/


void Sort3();/*查询最受男女生欢迎课程*/


void Sort31();


void Sort32();


int Whether(STRING* q,STRING s,int o);/*选课操作函数的辅助函数，处理用户输入的数据，转化为有用信息,也是主体的控制部分*/


int CopyOut(int i,STRING q);


void CopyIn(int j);


void ChangeSortAll(int id,int sex,int z);/*改变原来记录的数据*/


int Detect(int id);/*检测是否曾经进行过选课操作*/


void SortI(STRING* a,int sum,int t,int i);/*将信息输入到学生选课信息文件里*/


void SortAll(STRING* q,int sex,int i);/*将信息输入到选课信息汇总文件里*/


void SortAll2(STRING* a,int sex,int i);


void IF(int t);



#endif // SOORT_H
