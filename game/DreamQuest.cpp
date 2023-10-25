#include<bits/stdc++.h>
#include"variable.h"
#include"display.h"
#include"rnd.h"
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

set<int> exam_set = {15, 30};

void lesson_calculus(int week_id, int weekday_id)
{
	if(current_date == homework_ddl && homework_finished != homework_tot)
	{
		calculus_value = max(0, calculus_value - 20);
		hope_value = max(0, hope_value - 20);
		homework_failed_count += 1;
		
		display({
			"今天是微积分课",
			"但是你的微积分作业没有完成",
			"微积分能力值减20",
			"你对生活失去希望，希望值减20"
		},{
			"确定"
		});
		
		if(hope_value == 0)
		{
			display_lose({
				"你抑郁了，学校为你安排了休学"
			});
		}
		
		if(homework_failed_count >= 3)
		{
			display_lose({
				"由于你三次没有完成作业，这门课不及格，学校为你安排了劝退"
			});
		}
	}
	
	
	vector<string> msg;
	
	msg.push_back("今天是微积分课");
	
	if(weekday_id == 1)
	{
		if(exam_set.count(week_id) != 0)
		{
			msg.push_back("教授说，这周是考试周，就不布置作业了");
			homework_tot = 0;
			homework_finished = 0;
			homework_ddl = current_date + 7;
		}
		else
		{
			int t = rnd(20, 50);
			msg.push_back("这周的作业有 " + to_string(t) + " 道题");
			homework_tot = t;
			homework_finished = 0;
			homework_ddl = current_date + 7;
		}
	}
	
	if(week_id == 1)
	{
		msg.push_back("教授：“期中考试的时间是第 15 周的周日，大家做好准备。”");
		next_exam_date = 15 * 7 - 1;
		next_exam_require = 40;
	}
	if(week_id == 16)
	{
		msg.push_back("教授：“期末考试的时间是第 30 周的周日，大家做好准备。”");
		next_exam_date = 30 * 7 - 1;
		next_exam_require = 100;
	}
	
	while(1)
	{
		int t = display(msg, {
			"听课",
			"翘课"
		});
		
		if(t == 0)
		{
			energy_value = max(0, energy_value - 5);
			
			if(energy_value <= 0)
			{
				display_lose({
					"你太累了，在课堂上晕倒了",
					"学校为你安排了休学"
				});
			}
			
			vector<string> msg2;
			if(rndbool(0.3))
			{
				msg2.push_back("你听得很投入");
				calculus_value += 2;
			}
			else
			{
				msg2.push_back("你听了课");
				calculus_value += 1;
			}
			
			if(rndbool(0.05))
			{
				msg2.push_back("微积分给了你启发，你产生了一个新 idea！");
				hope_value = min(hope_value_lim, hope_value + 10);
				idea_count += 1;
			}
			
			display(msg2, {"确定"});
		}
		else
		{
			vector<string> opt2;
			opt2.push_back("做微积分作业");
			opt2.push_back("复习微积分");
			opt2.push_back("读论文");
			opt2.push_back("运动");
			opt2.push_back("打游戏");
			opt2.push_back("练琴");
			opt2.push_back("阅读一些时政新闻");
			opt2.push_back("休息一天");
			if(idea_count >= 3)
				opt2.push_back("花3个idea写篇论文");
			opt2.push_back("返回上一页");
			
			int t2 = display({"你决定要翘课，但是干点啥呢？"}, opt2);
			
			if(t2 == (int)opt2.size() - 1)
			{
				continue;
			}
			
			if(t2 == 0)// 做微积分作业
			{
				if(homework_finished == homework_tot)
				{
					vector<string> msg3;
					
					msg3.emplace_back("当前没有微积分作业，于是你休息了一天");
					
					int delta = rnd(-2, 2);
					
					energy_value = min(energy_value_lim, energy_value + 25);
					hope_value = min(hope_value_lim, max(0, hope_value + delta));
					
					if(delta < 0)
					{
						msg3.emplace_back("没有事可干，你对未来充满迷茫");
					}
					if(delta > 0)
					{
						msg3.emplace_back("休闲的时光让你感到享受");
					}
					
					display(msg3,{
						"确定"
					});
					
					if(hope_value <= 0)
					{
						display_lose({
							"你抑郁了，学校为你安排了休学"
						});
					}
				}
				else
				{
					int num = rnd(10, 15 + energy_value / 15);
					num = min(num, homework_tot - homework_finished);
					
					int delta_H = rnd(-2, 2);
					int delta_C = num / 15 + rnd(0,1);
					
					energy_value = max(0, energy_value - 5);
					
					if(energy_value <= 0)
					{
						display_lose({
							"你在做作业的途中累倒了，学校为你安排了休学"
						});
					}
					
					homework_finished += num;
					hope_value = max(0, min(hope_value_lim, hope_value + delta_H));
					calculus_value = calculus_value + delta_C;
					
					vector<string> msg3;
					
					msg3.push_back("你做了 " + to_string(num) + " 道题");
					if(delta_C > 0)
						msg3.push_back("你的微积分能力值提升了");
					
					if(delta_H < 0)
						msg3.push_back("做不完的作业让你对未来感到迷茫");
					if(delta_H > 0)
						msg3.push_back("你充满动力");
					
					display(msg3, {
						"确定"
					});
					
					if(hope_value <= 0)
					{
						display_lose({
							"你抑郁了，学校为你安排了休学"
						});
					}
				}
			}
			else if(t2 == 1)// 复习微积分
			{
				
			}
			else if(t2 == 2)// 读论文
			{
				
			}
			else if(t2 == 3)// 运动
			{
				
			}
			else if(t2 == 4)// 打游戏
			{
				
			}
			else if(t2 == 5)// 练琴
			{
				
			}
			else if(t2 == 6)// 阅读一些时政新闻
			{
				
			}
			else if(t2 == 7)// 休息一天
			{
				
			}
			else if(t2 == 8)// 花3个idea写篇论文
			{
				
			}
		}
		
		break;
	}
}

void lesson_development(int, int)
{
	
}

int main(void)
{
	display_init();
	
	hope_value = 60;
	hope_value_lim = 100;
	
	energy_value = 100;
	energy_value_lim = 100;
	
	calculus_value = 0;
	idea_count = 0;
	paper_count = 0;
	
	game_value = 0;
	music_value = 0;
	society_value = 0;
	
	next_exam_date = -1;
	next_exam_require = -1;
	
	homework_tot = 0;
	homework_ddl = -1;
	homework_finished = 0;
	homework_failed_count = 0;
		
	for(int i=0; i<finish_date; ++i)
	{
		current_date = i;
		
		int week_id = current_date / 7 + 1;
		int weekday_id = current_date % 7 + 1;
		
		if(weekday_id == 1 || weekday_id == 3)
		{
			lesson_calculus(week_id, weekday_id);
		}
		else if(weekday_id == 2)
		{
			lesson_development(week_id, weekday_id);
		}
		if(exam_set.count(week_id) && weekday_id == 7)
		{
			
		}
	}
	return 0;
}