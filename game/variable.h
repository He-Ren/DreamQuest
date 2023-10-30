#ifndef _VARIABLE_H_
#define _VARIABLE_H_

const int finish_date = 7 * 30;
int current_date;// 当前日期（天数，从 0 开始计）

int hope_value;// 希望值
int hope_value_lim;// 希望值上限

int energy_value;// 体力值
int energy_value_lim;// 体力值上限

int calculus_value;// 微积分能力值

int idea_count;// idea 个数
int paper_count;// paper 个数
int idea_tot;// 历史 idea 总数

int game_value;// 游戏能力值
int game_value_lvl;
int game_value_lvl_next;

int music_value;// 音乐能力值
int music_value_lvl;
int music_value_lvl_next;

int society_value;// 社会能力值
int society_value_lvl;
int society_value_lvl_next;

int homework_tot;// 作业总数
int homework_ddl;// 作业ddl
int homework_finished;// 当前完成作业数
int homework_failed_count;// 作业逾期次数

int next_exam_date;// 下次考试时间
int next_exam_require;// 下次考试需要的能力值

#endif