#ifndef _VARIABLE_H_
#define _VARIABLE_H_

const int finish_date = 7 * 50;
int current_date;// 当前日期（天数，从 0 开始计）

int homework_tot;// 作业总数
int homework_ddl;// 作业截止日期
int homework_finished;// 已完成作业总数
int homework_failed_count;// 逾期作业数

int calculus_ability;// 微积分能力值
int next_exam_date;// 下次考试时间
int next_exam_require;// 下次考试需要的能力值

int tired_value;// 疲劳度
int hope_value;// 希望值

int idea_count; // 当前 idea 总数
int paper_count; // 当前论文总数

#endif