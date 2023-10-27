#include<bits/stdc++.h>
#include"variable.h"
#include"display.h"
#include"rnd.h"
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

enum Lesson_id
{
	Nolesson, Calculus, Development
};

set<int> exam_set = {15, 30};

void update_energe_value(int delta)
{
	energy_value = max(0, min(energy_value_lim, energy_value + delta));
}
void update_hope_value(int delta)
{
	hope_value = max(0, min(hope_value_lim, hope_value + delta));
}
void update_calculus_value(int delta)
{
	calculus_value = max(0, calculus_value + delta);
}

map<string,int> paper_name_count;

vector<string> ImpressiveFoodName = {
	#include"ImpressiveFoodName.txt"
};
vector<string> ImpressiveFieldName = {
	#include"ImpressiveFieldName.txt"
};

string rand_paper_name(void)
{
	string s;
	s += "论";
	s += rnd_among(ImpressiveFoodName);
	s += "在";
	s += rnd_among(ImpressiveFieldName);
	s += "中的应用";
	
	int t = ++paper_name_count[s];
	if(t > 1)
	{
		s += "（第 " + to_string(t) + " 部）";
	}
	
	return s;
}

/*
检查 energy_value 和 hope_value，如果不达标直接失败
*/
void check_alive(void)
{
	if(energy_value <= 0 && hope_value <= 0)
	{
		display_lose({
			"你抑郁了，并且因为疲劳而患上重病，学校为你安排了休学"
		});
	}
	if(hope_value <= 0)
	{
		display_lose({
			"你抑郁了，学校为你安排了休学"
		});
	}
	if(energy_value <= 0)
	{
		display_lose({
			"你累倒了，学校为你安排了休学"
		});
	}
}

/*
做微积分作业
curlesson 为进入这个分支的课程
*/
void action_do_calculus_homework(Lesson_id curlesson)
{
	vector<string> msg;
	
	if(homework_finished == homework_tot)
	{
		if(curlesson != Development)
			msg.emplace_back("当前没有微积分作业，于是你休息了一天");
		else
			msg.emplace_back("当前没有微积分作业，于是你决定在课上睡觉");
		
		int delta;
		if(curlesson != Development)
			delta = rnd(-2, 2);
		else
			delta = 2;
		
		energy_value = min(energy_value_lim, energy_value + 25);
		hope_value = min(hope_value_lim, max(0, hope_value + delta));
		
		msg.push_back("你的体力恢复了不少");
		
		if(delta < 0)
		{
			msg.emplace_back("没有事可干，你对未来充满迷茫");
		}
		if(delta > 0)
		{
			if(curlesson != Development)
				msg.emplace_back("休闲的时光让你感到享受");
			else
				msg.emplace_back("深邃的思想浸入你的梦境，你对未来充满希望");
		}
	}
	else
	{
		int num;
		if(curlesson != Development)
			num = rnd(10, 15 + energy_value / 15);
		else
			num = rnd(15, 15 + energy_value / 15);
		
		num = min(num, homework_tot - homework_finished);
		
		int delta_H;
		if(curlesson != Development)
			delta_H = rnd(-2, 2);
		else
			delta_H = 2;
		
		int delta_C = num / 15 + rnd(0,1);
		
		homework_finished += num;
		energy_value = max(0, energy_value - 5);
		hope_value = max(0, min(hope_value_lim, hope_value + delta_H));
		calculus_value = calculus_value + delta_C;
		
		if(curlesson != Development)
			msg.push_back("你做了 " + to_string(num) + " 道题");
		else
			msg.push_back("深邃的思想给你动力，你做了 " + to_string(num) + " 道题");
		
		if(delta_C > 0)
			msg.push_back("你的微积分能力值提升了");
		
		if(delta_H < 0)
			msg.push_back("做不完的作业让你对未来感到迷茫");
		if(delta_H > 0)
			msg.push_back("作业让你感到充实，你对未来充满希望");
	}
	
	display(msg, {
		"确定"
	});
	
	check_alive();
}

/*
复习微积分
*/
void action_review_calculus(Lesson_id curlesson)
{
	vector<string> msg;
	
	int delta_C, delta_H;
	
	if(curlesson != Development)
	{
		if(rndbool(0.05))
		{
			delta_C = 3;
			delta_H = 2;
		}
		else
		{
			if(rndbool(0.1))
				delta_C = 2;
			else
				delta_C = 1;
			
			delta_H = rnd(-1,1);
		}
	}
	else
	{
		if(rndbool(0.1))
		{
			delta_C = 3;
			delta_H = 2;
		}
		else
		{
			delta_C = rnd(1,2);
			delta_H = rnd(0,1);
		}
	}
	
	msg.push_back("你决定复习微积分");
	
	if(curlesson == Development)
		msg.push_back("深邃的思想给了你帮助");
	
	if(delta_C == 3)
	{
		if(curlesson != Development)
			msg.push_back("你的状态非常好");
		else
			msg.push_back("你的状态非常好");
	}
	else if(delta_C == 2)
	{
		if(curlesson != Development)
			msg.push_back("你的状态不错");
		else
			msg.push_back("你的状态不错");
	}
	
	if(delta_H > 0)
		msg.push_back("微积分的巧妙让你对未来充满希望");
	if(delta_H < 0)
		msg.push_back("微积分的困难让你感到迷茫");
	
	update_energe_value(-5);
	update_hope_value(delta_H);
	update_calculus_value(delta_C);
	
	display(msg, {
		"确定"
	});
	
	check_alive();
}

/*
读论文
*/
void action_read_paper(Lesson_id curlesson)
{
	vector<string> msg;
	
	int delta_H;
	
	string paper_name = rand_paper_name();
	msg.push_back("你找到了一篇论文，《"  + paper_name + "》");
	
	double prob;
	if(curlesson != Development)
		prob = ((double)hope_value / hope_value_lim * 5 + (double)energy_value / energy_value_lim * 5) / 100;
	else
		prob = ((double)hope_value / hope_value_lim * 10 + (double)energy_value / energy_value_lim * 5) / 100;
	
	if(rndbool(prob))
	{
		++idea_count;
		
		if(curlesson != Development)
		{
			msg.push_back("你产生了一个新的 idea！");
			delta_H = 10;
		}
		else
		{
			msg.push_back("深邃的思想给了你启发，你产生了一个新的 idea！");
			delta_H = 10;
		}
	}
	else
	{
		if(curlesson != Development)
		{
			msg.push_back("你对未来充满希望");
			delta_H = 2;
		}
		else
		{
			msg.push_back("你对未来充满希望");
			delta_H = 2;
		}
	}
	
	update_energe_value(-5);
	update_hope_value(delta_H);
	
	display(msg, {
		"确定"
	});
	
	check_alive();
}

/*
写论文
*/
void action_write_paper(Lesson_id )
{
	assert(idea_count >= 3);
	
	vector<string> msg;
	
	msg.push_back("你使用了 3 个 idea 写了一篇论文");
	
	int delta_H;
	
	double prob = 0.8;
	if(rndbool(prob))
	{
		msg.push_back("你的论文通过了审核");
		delta_H = 20;
		paper_count += 1;
	}
	else
	{
		if(rndbool(0.5))
		{
			msg.push_back("你发现这个想法别人已经写过了");
			msg.push_back("你非常沮丧");
		}
		else
		{
			msg.push_back("评审认为你的想法过于平凡，你的论文没有通过审核");
			msg.push_back("你非常沮丧");
		}
		delta_H = - max(5, min(20, hope_value - 5));
	}
	
	idea_count -= 3;
	update_energe_value(-5);
	update_hope_value(delta_H);
	
	display(msg, {
		"确定"
	});
	
	check_alive();
}

/*
休息一天
*/
void action_do_nothing(Lesson_id curlesson)
{
	vector<string> msg;
	
	if(curlesson != Development)
		msg.emplace_back("你休息了一天");
	else
		msg.emplace_back("你决定在课上睡觉");
	
	int delta;
	if(curlesson != Development)
		delta = rnd(-2, 2);
	else
		delta = 2;
	
	energy_value = min(energy_value_lim, energy_value + 25);
	hope_value = min(hope_value_lim, max(0, hope_value + delta));
	
	msg.push_back("你的体力恢复了不少");
	
	if(delta < 0)
	{
		msg.emplace_back("没有事可干，你对未来充满迷茫");
	}
	if(delta > 0)
	{
		if(curlesson != Development)
			msg.emplace_back("休闲的时光让你感到享受");
		else
			msg.emplace_back("深邃的思想浸入你的梦境，你对未来充满希望");
	}
	
	display(msg, {
		"确定"
	});
	
	check_alive();
}


/*
运动
*/
void action_do_sport(Lesson_id)
{
	vector<string> msg;
	
	msg.push_back("你做了一些运动");
	
	msg.push_back("虽然很累，但是体能上限提升了！");
	
	energy_value_lim += 5;
	update_energe_value(-5);
	
	display(msg, {
		"确定"
	});
	
	check_alive();
} 


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
				action_do_calculus_homework(Calculus);
			}
			else if(t2 == 1)// 复习微积分
			{
				action_review_calculus(Calculus);
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