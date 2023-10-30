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

void update_idea_count(int k = 1)
{
	idea_count += k;
	idea_tot += max(k,0);
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
		
		int delta_E, delta_H;
		
		msg.push_back("你的体力恢复了不少");
		
		if(curlesson != Development)
		{
			delta_E = 15;
			delta_H = -2;
			msg.emplace_back("你感到迷茫");
		}
		else
		{
			delta_E = 20;
			delta_H = 2;
			msg.emplace_back("思政给你力量，你感到充满希望");
		}
		
		update_hope_value(delta_H);
		update_energe_value(delta_E);
	}
	else
	{
		int num;
		if(curlesson != Development)
		{
			msg.push_back("体力值加成：" + to_string(energy_value / 15));
			msg.push_back("能力值加成：" + to_string(calculus_value / 5));
			num = energy_value / 15 + calculus_value / 5 + rnd(10, 15);
		}
		else
		{
			msg.push_back("体力值加成：" + to_string(energy_value / 15));
			msg.push_back("能力值加成：" + to_string(calculus_value / 5));
			num = energy_value / 15 + calculus_value / 5 + 5;
		}
		
		num = min(num, homework_tot - homework_finished);
		
		int delta_E;
		int delta_H;
		
		if(curlesson != Development)
		{
			if(homework_finished + num != homework_tot)
				msg.push_back("你做了 " + to_string(num) + " 道题");
			else
				msg.push_back("你做了 " + to_string(num) + " 道题，完成了作业");
			delta_E = -5;
			delta_H = -2;
		}
		else
		{
			if(homework_finished + num != homework_tot)
			{
				msg.push_back("课上做作业影响了效率");
				msg.push_back("你做了 " + to_string(num) + " 道题");
			}
			else
			{
				msg.push_back("你做了 " + to_string(num) + " 道题，完成了作业");
			}
			msg.push_back("思政课深邃的思想让你充满希望");
			delta_E = -5;
			delta_H = 3;
		}
		
		int delta_C = num / 20;
		if(delta_C > 0)
			msg.push_back("你的微积分能力值提升了！");
		
		homework_finished += num;
		update_hope_value(delta_H);
		update_energe_value(delta_E);
		update_calculus_value(delta_C);
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
	
	msg.push_back("你复习了微积分");
	
	int delta_E;
	int delta_H;
	int delta_C;
	
	if(curlesson != Development)
	{
		delta_E = -5;
		delta_H = -2;
		delta_C = rnd(1,2);
		if(delta_C == 2)
			msg.push_back("你今天效率很高");
	}
	else
	{
		msg.push_back("课上做复习影响了效率");
		msg.push_back("但是思政课深邃的思想让你充满希望");
		delta_E = -5;
		delta_H = 3;
		delta_C = 1;
	}
	
	update_hope_value(delta_H);
	update_energe_value(delta_E);
	update_calculus_value(delta_C);
	
	
	display(msg, {
		"确定"
	});
	
	check_alive();
}

/*
读论文
*/
void action_read_paper(Lesson_id)
{
	vector<string> msg;
	
	int delta_H;
	int delta_E = -5;
	
	string paper_name = rand_paper_name();
	msg.push_back("你找到了一篇论文，《"  + paper_name + "》");
	
	double prob = 0;
	prob += (double)hope_value / hope_value_lim * 5;
	prob += (double)energy_value / energy_value_lim * 5;
	prob += max(0, 90 - idea_tot * 20);
	prob /= 100;
	
	if(rndbool(prob))
	{
		update_idea_count();
		
		msg.push_back("论文给了你启发，你产生了一个新的 idea！");
		delta_H = 10;
	}
	else
	{
		msg.push_back("你对未来充满希望");
		delta_H = 2;
	}
	
	update_energe_value(delta_E);
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
	
	update_idea_count(-3);
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
	
	int delta_E, delta_H;
	
	msg.push_back("你的体力恢复了不少");
	
	if(curlesson != Development)
	{
		delta_E = 15;
		delta_H = -2;
		msg.emplace_back("你感到迷茫");
	}
	else
	{
		delta_E = 20;
		delta_H = 2;
		msg.emplace_back("思政给你力量，你感到充满希望");
	}
		
	update_hope_value(delta_H);
	update_energe_value(delta_E);
	
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
	update_hope_value(-2);
	
	display(msg, {
		"确定"
	});
	
	check_alive();
}

/*
打游戏
*/
void action_play_game(Lesson_id)
{
	vector<string> msg;
	
	int delta_E = 10 + game_value_lvl * 5;
	int delta_H = -10;
	int delta_G = rnd(1,2);
	
	if(rndbool(0.1))
	{
		msg.push_back("__ __，启动！");
	}
	else
	{
		msg.push_back("你玩了一会游戏");
	}
	
	msg.push_back("游戏等级对体力值加成：" + to_string(game_value_lvl * 5));
	
	if(delta_G == 2)
		msg.push_back("今天手感很好");
	
	update_energe_value(delta_E);
	update_hope_value(delta_H);
	game_value += delta_G;
	
	bool lvl_up = 0;
	while(game_value >= game_value_lvl_next)
	{
		lvl_up = 1;
		++game_value_lvl;
		game_value_lvl_next = 2 * (game_value_lvl + 1) * (game_value_lvl + 1);
	}
	
	if(lvl_up)
		msg.push_back("你的游戏等级提升了！");
	
	msg.push_back("你感到迷茫");
	
	display(msg, {
		"确定"
	});
	
	check_alive();
}

/*
练琴
*/
void action_practice_music(Lesson_id)
{
	vector<string> msg;
	
	int delta_E = -3;
	int delta_H = 1 + music_value_lvl * 2;
	int delta_M = rnd(1,2);
	
	msg.push_back("你练了一会琴");
	
	msg.push_back("音乐等级对希望值加成：" + to_string(music_value_lvl * 2));
	
	if(delta_M == 2)
		msg.push_back("今天手感很好");
	
	msg.push_back("琴声让你心情舒畅");
	
	update_energe_value(delta_E);
	update_hope_value(delta_H);
	music_value += delta_M;
	
	bool lvl_up = 0;
	while(music_value >= music_value_lvl_next)
	{
		lvl_up = 1;
		++music_value_lvl;
		music_value_lvl_next = 2 * (music_value_lvl + 1) * (music_value_lvl + 1);
	}
	
	if(lvl_up)
		msg.push_back("你的音乐等级提升了！");
	
	display(msg, {
		"确定"
	});
	
	check_alive();
}

/*
阅读时政新闻
*/
void action_read_news(Lesson_id)
{
	vector<string> msg;
	
	int delta_E = -2;
	int delta_H = rnd(-2, 4);
	int delta_S = 1;
	
	msg.push_back("你读了一些新闻");
	
	if(delta_H < 0)
		msg.push_back("负能量的新闻影响了你的心情");
	if(delta_H > 0)
		msg.push_back("正能量的新闻让你充满希望");
	
	update_energe_value(delta_E);
	update_hope_value(delta_H);
	society_value += delta_S;
	
	bool lvl_up = 0;
	while(society_value >= society_value_lvl_next)
	{
		lvl_up = 1;
		++society_value_lvl;
		society_value_lvl_next = 2 * (society_value_lvl + 1) * (society_value_lvl + 1);
	}
	
	if(lvl_up)
	{
		msg.push_back("你的社交等级提升了！");
		msg.push_back("tips: 社交等级可以增加日常出现活动的概率");
	}
	
	display(msg, {
		"确定"
	});
	
	check_alive();
}

/*
参加社交活动
*/
void action_do_social_activities(Lesson_id)
{
	vector<string> msg;
	
	int delta_E = -5;
	int delta_H = 8;
	
	msg.push_back("你参加了活动");
	msg.push_back("你对未来充满希望");
	
	update_energe_value(delta_E);
	update_hope_value(delta_H);
	
	display(msg, {
		"确定"
	});
	
	check_alive();
}

/*
参加数学讲座
*/
void action_attend_math_lecture(Lesson_id)
{
	vector<string> msg;
	
	int delta_E = -5;
	int delta_H = 5;
	int delta_C = 3;
	
	msg.push_back("你参加了一场数学讲座");
	
	if(rndbool(0.5))
	{
		update_idea_count();
		delta_H += 10;
		msg.push_back("讲座给了你启发，你产生了一个新的 idea！");
	}
	
	msg.push_back("你对未来充满希望");
	
	update_energe_value(delta_E);
	update_hope_value(delta_H);
	calculus_value += delta_C;
	
	display(msg, {
		"确定"
	});
	
	check_alive();
}

/*
参加音乐会
*/
void action_attend_concert(Lesson_id)
{
	vector<string> msg;
	
	int delta_E = 2;
	int delta_H = 5;
	int delta_M = 5;
	
	msg.push_back("你参加了一场音乐会");
	
	msg.push_back("你对未来充满希望");
	
	update_energe_value(delta_E);
	update_hope_value(delta_H);
	music_value += delta_M;
	
	display(msg, {
		"确定"
	});
	
	check_alive();
}


bool decide_do_nothing(Lesson_id curlesson, vector<string> msg, int /*week_id*/, int weekday_id)
{
	vector<string> opt;
	vector<int> opt_id;
	
	auto push = [&] (int id, string s)
	{
		opt.push_back(s);
		opt_id.push_back(id);
	};
	
	push(0, "做微积分作业");
	push(1, "复习微积分");
	push(2, "读论文");
	
	if(curlesson != Development)
	{
		push(3, "运动");
		push(4, "打游戏");
		push(5, "练琴");
		push(6, "阅读一些时政新闻");
		push(7, "休息一天");
	}
	else
	{
		push(7, "睡觉");
	}
	
	if(idea_count >= 3)
		push(8, "花3个idea写篇论文");
	
	if(curlesson == Nolesson)
	{
		double prob = min(100, 5 + society_value_lvl * 2);
		prob /= 100;
		if(rndbool(prob))
		{
			int oth = rnd(0, 100 - 1);
			
			if(0 <= oth && oth < 70)
			{
				if(weekday_id == 6 || weekday_id == 7)
				{
					msg.push_back("群公告：今天有团建活动，大家自愿参加");
					push(9, "参加团建活动");
				}
				else
				{
					msg.push_back("群公告：今天有社工活动，大家自愿参加");
					push(9, "参加社工活动");
				}
			}
			else if(70 <= oth && oth < 85)
			{
				msg.push_back("群公告：今天有数学讲座，大家自愿参加");
				push(10, "参加数学讲座");
			}
			else if(70 <= oth && oth < 85)
			{
				msg.push_back("群公告：今天有音乐会，大家自愿参加");
				push(11, "参加音乐会");
			}
		}
	}
	
	if(curlesson == Calculus || curlesson == Development)
	{
		push(12, "返回上一页");
	}
	
	int t = display(msg, opt);
	
	if(opt_id[t] == 0)// 做微积分作业
	{
		action_do_calculus_homework(curlesson);
	}
	else if(opt_id[t] == 1)// 复习微积分
	{
		action_review_calculus(curlesson);
	}
	else if(opt_id[t] == 2)// 读论文
	{
		action_read_paper(curlesson);
	}
	else if(opt_id[t] == 3)// 运动
	{
		action_do_sport(curlesson);
	}
	else if(opt_id[t] == 4)// 打游戏
	{
		action_play_game(curlesson);
	}
	else if(opt_id[t] == 5)// 练琴
	{
		action_practice_music(curlesson);
	}
	else if(opt_id[t] == 6)// 阅读一些时政新闻
	{
		action_read_news(curlesson);
	}
	else if(opt_id[t] == 7)// 休息一天
	{
		action_do_nothing(curlesson);
	}
	else if(opt_id[t] == 8)// 花3个idea写篇论文
	{
		action_write_paper(curlesson);
	}
	else if(opt_id[t] == 9)// 参加活动
	{
		action_do_social_activities(curlesson);
	}
	else if(opt_id[t] == 10)// 参加数学讲座
	{
		action_attend_math_lecture(curlesson);
	}
	else if(opt_id[t] == 11)// 参加音乐会
	{
		action_attend_concert(curlesson);
	}
	else if(opt_id[t] == 12)
	{
		return 0;
	}
	
	check_alive();
	
	return 1;
}

/*
微积分课
*/
void lesson_calculus(int week_id, int weekday_id)
{
	if(current_date == homework_ddl && homework_finished != homework_tot)
	{
		update_hope_value(-30);
		homework_failed_count += 1;
		
		vector<string> msg = {
			"今天是微积分课",
			"但是你的微积分作业没有完成",
			"你非常郁闷，希望值减30"
		};
		
		if(homework_failed_count < 3)
		{
			msg.push_back("这是你的第"
				+ to_string(homework_failed_count)
				+ "次逾期，3次逾期将被劝退");
		}
		else
		{
			msg.push_back("这是你的第"
				+ to_string(homework_failed_count)
				+ "次逾期");
		}
		
		display(msg,{
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
				"由于你3次没有完成作业，这门课不及格，被劝退"
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
			homework_ddl = -1;
		}
		else
		{
			int t = rnd2(20 + 2 * week_id, 40 + 2 * week_id);
			msg.push_back("这周的作业有 " + to_string(t) + " 道题");
			homework_tot = t;
			homework_finished = 0;
			homework_ddl = current_date + 7;
		}
	}
	
	if(week_id == 1 && weekday_id == 1)
	{
		msg.push_back("教授：“期中考试的时间是第 15 周的周日，大家做好准备。”");
		next_exam_date = 15 * 7 - 1;
		next_exam_require = 40;
	}
	if(week_id == 16 && weekday_id == 1)
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
			int delta_E = -7;
			int delta_H = -3;
			
			update_energe_value(delta_E);
			update_hope_value(delta_H);
			
			if(energy_value <= 0)
			{
				display_lose({
					"你太累了，在课堂上晕倒了",
					"学校为你安排了休学"
				});
			}
			
			vector<string> msg2;
			
			msg2.push_back("你听了课");
			calculus_value += 3;
			
			display(msg2, {"确定"});
			
			check_alive();
		}
		else
		{
			bool flag = decide_do_nothing(Calculus, {
				"干点什么呢？"
			}, week_id, weekday_id);
			
			if(flag == 0)
			{
				continue;
			}
		}
		
		break;
	}
}

/*
思想道德与法治课
*/
void lesson_development(int week_id, int weekday_id)
{
	vector<string> msg;
	
	msg.push_back("今天是思想道德与法治课");
	
	while(1)
	{
		int t = display(msg, {
			"听课",
			"摸鱼"
		});
		
		if(t == 0)
		{
			int delta_E = -5;
			int delta_H = 7;
			int delta_S = 1;
			
			update_energe_value(delta_E);
			update_hope_value(delta_H);
			
			if(energy_value <= 0)
			{
				display_lose({
					"你太累了，在课堂上晕倒了",
					"学校为你安排了休学"
				});
			}
			
			vector<string> msg2;
			msg2.push_back("你听了课");
			msg2.push_back("思政老师生动的讲解让你充满希望");
			
			society_value += delta_S;
			
			bool lvl_up = 0;
			while(society_value_lvl >= society_value_lvl_next)
			{
				lvl_up = 1;
				++society_value_lvl;
				society_value_lvl_next = 2 * (society_value_lvl + 1) * (society_value_lvl + 1);
			}
			
			if(lvl_up)
			{
				msg2.push_back("你的社交等级提升了！");
				msg2.push_back("tips: 社交等级可以增加日常出现活动的概率");
			}
			
			display(msg2, {"确定"});
			
			check_alive();
		}
		else
		{
			bool flag = decide_do_nothing(Development, {
				"干点啥呢？"
			}, week_id, weekday_id);
			
			if(flag == 0)
			{
				continue;
			}
		}
		
		break;
	}
}

/*
平时
*/
void lesson_no_lesson(int week_id, int weekday_id)
{
	vector<string> msg;
	
	msg.push_back("今天没有课");
	
	decide_do_nothing(Nolesson, msg, week_id, weekday_id);
}

/*
微积分考试
*/
void lesson_calculus_exam(int,int)
{
	vector<string> msg;
	
	msg.push_back("今天是微积分考试");
	
	msg.push_back("考试要求的能力值为 " + to_string(next_exam_require));
	
	if(calculus_value < next_exam_require)
	{
		msg.push_back("很可惜，你没有达到要求");
		
		display(msg, {
			"确定"
		});
		
		display_lose({
			"你挂科了，学校将你劝退"
		});
	}
	
	int delta_H = 10;
	int delta_E = -5;
	
	update_hope_value(delta_H);
	update_energe_value(delta_E);
	
	msg.push_back("你通过了考试");
	
	display(msg, {
		"确定"
	});
	
	check_alive();
	
	next_exam_date = -1;
	next_exam_require = -1;
}

/*
体育课
*/
void lesson_physical_education(int,int)
{
	vector<string> msg;
	
	msg.push_back("今天是体育课");
	
	int delta_E;
	int delta_H;
	
	if(energy_value >= 60)
	{
		delta_E = -10;
		delta_H = rnd(1,3);
		msg.push_back("你的状态很好");
		msg.push_back("运动让你心情舒畅");
	}
	else if(energy_value >= 40)
	{
		delta_E = -9;
		delta_H = rnd(0,2);
		msg.push_back("你的状态不错");
		if(delta_H > 0)
			msg.push_back("运动让你心情舒畅");
	}
	else if(energy_value >= 20)
	{
		delta_E = -8;
		delta_H = rnd(-1, 1);
		
		msg.push_back("你感觉有点疲劳");
		if(delta_H < 0)
			msg.push_back("这影响了你的心态");
		if(delta_H > 0)
			msg.push_back("但是运动让你心情舒畅");
	}
	else if(energy_value >= 8)
	{
		delta_E = -7;
		delta_H = rnd(-1, 0);
		
		msg.push_back("你感觉很累");
		if(delta_H < 0)
			msg.push_back("这影响了你的心态");
	}
	else
	{
		delta_E = energy_value - 1;
		delta_H = -10;
		
		msg.push_back("你力竭了，体育老师让你休息一会");
		msg.push_back("你的心情很差");
	}
	
	update_energe_value(delta_E);
	update_hope_value(delta_H);
	
	display(msg, {
		"确定"
	});
	
	check_alive();
}

void guide(void)
{
	bool reprint = 1;
	
	while(1)
	{
		if(reprint)
		{
			reprint = 0;
			
			system("cls");
			
			cout << "DreamQuest - by 德法34组" << endl;
			cout << endl;
			
			cout << "游戏内容完全虚构，如有雷同，纯属巧合。" << endl;
			
			cout << "游戏过程中请不要调整窗口大小或者滚动窗口，否则可能造成显示问题。" << endl;
			cout << "作者技术力有限，如有字体等问题，我们深感抱歉。" << endl;
			
			cout << endl;
			cout << "抵制不良游戏，拒绝盗版游戏。" << endl;
			cout << "注意自我保护，谨防受骗上当。" << endl;
			cout << "适度游戏益脑，沉迷游戏伤身。" << endl;
			cout << "合理安排时间，享受健康生活。" << endl;
			cout << endl;
			
			cout << "按 Enter 键开始游戏 . . ." << endl;
		}
		
		if(kbhit() != 0)
		{
			int c = getch();
			if(c == VK_RETURN)
			{
				break;
			}
			reprint = 1;
		}
	}
	
	display({
		"欢迎进入大学生活！",
		"使用 W/S 或数字键切换选项",
		"使用 Enter 键选择"
	},{
		"确定",
		"不取消",
		"同意",
		"不反对",
		"已知晓",
	},0);
	
	int skipguide = display({
		"跳过新手教程？"
	},{
		"否",
		"是"
	},0);
	
	if(skipguide == 1)
	{
		display({
			"欢迎来到 DreamQuest，祝您游玩愉快！",
		},{
			"开始游戏",
		},0);
		return;
	}
	
	int pageid = 0, curopt = 0;
	vector< vector<string> > all_pages;
	
	all_pages.push_back({
		"看到下面的一栏了吗？",
		"你需要保持希望值和体力值大于 0",
	});
	
	all_pages.push_back({
		"本游戏中，大学生活有30周",
		"这是你的课表：",
		"|  周一  | 周二 |  周三  | 周四 | 周五 | 周六 | 周日 |",
		"| 微积分 | 思政 | 微积分 |      | 体育 |      |      |",
		"注：思政表示思想道德与法治"
	});
	
	all_pages.push_back({
		"周一周三：微积分",
		"微积分会有作业和考试",
		"微积分有属性“能力值”，上课、做作业、复习都会提高能力值",
	});
	
	all_pages.push_back({
		"微积分作业：",
		"周一布置，考试周除外",
		"能力值会增加做作业的效率",
		"每次作业的ddl为下周一，请注意：逾期3次会被劝退！",
	});
	
	all_pages.push_back({
		"微积分考试：",
		"共有两次考试，每次考试有对应的能力值要求",
		"达不到要求会直接被劝退",
	});
	
	all_pages.push_back({
		"周二：思想道德与法治",
		"你可以选择上课摸鱼，去干一些平时的事情，但是效果略有不同"
	});
	
	all_pages.push_back({
		"周五：体育",
		"体育课不能翘，并且会消耗体力值"
	});
	
	all_pages.push_back({
		"没课时，你可以做各种活动",
		"专精某一方面可以触发隐藏结局！"
	});
	
	all_pages.push_back({
		"读论文有概率产生idea",
		"3个idea可以写一篇论文",
		"idea和论文可以大幅提高希望值",
		"注意，写论文有小概率失败，此时会大幅减少希望值",
		"结束时有5篇及以上的论文会触发隐藏结局！"
	});
	
	all_pages.push_back({
		"运动可以提升体能上限"
	});
	
	all_pages.push_back({
		"游戏可以恢复体力，恢复的量和当前游戏等级有关",
		"结束时达到8级会触发隐藏结局！"
	});
	
	all_pages.push_back({
		"练琴可以恢复体力，恢复的量和当前音乐等级有关",
		"结束时达到8级会触发隐藏结局！"
	});
	
	all_pages.push_back({
		"社交等级可以通过读新闻和上思政课来提升",
		"社交等级可以增加出现额外活动的概率，包括社工、团建、数学讲座、音乐会",
		"这些活动往往有很大的增益！",
		"结束时达到8级会触发隐藏结局！"
	});
	
	all_pages.push_back({
		"欢迎来到 DreamQuest，祝您游玩愉快！",
	});
	
	while(1)
	{
		if(pageid == (int)all_pages.size() - 1)
		{
			int t = display(all_pages[pageid], {
				"开始游戏",
				"上一页"
			},0,curopt);
			if(t == 0) break;
			
			curopt = t;
			pageid -= 1;
		}
		else if(pageid == 0)
		{
			int t = display(all_pages[pageid], {
				"下一页"
			},0,0);
			curopt = t;
			++pageid;
		}
		else
		{
			int t = display(all_pages[pageid], {
				"下一页",
				"上一页"
			},0,curopt);
			curopt = t;
			if(t == 0) ++pageid;
			else --pageid;
		}
	}
}

/*
结局
*/
void ending(void)
{
	vector<string> msg, opt;
	
	msg.push_back("你顺利毕业了");
	msg.push_back("接下来干什么呢？");
	
	opt.push_back("找工作");
	opt.push_back("做科研");
	opt.push_back("当游戏主播");
	opt.push_back("成为音乐家");
	
	int t = display(msg, opt);
	
	if(t == 0)
	{
		if(society_value_lvl < 5)
		{
			display_normal({
				"你找到了一份工作",
				"你的人生平凡而幸福",
			});
		}
		else if(society_value_lvl < 8)
		{
			display_good({
				"你找到了一份工作",
				"由于你社交能力的积累，你生活富裕的同时为社会做出了贡献",
			});
		}
		else
		{
			display_perfect({
				"你找到了一份工作",
				"由于你出色的社交能力，你在工作的领域做到了顶端，为社会做出了很大贡献",
			});
		}
	}
	else if(t == 1)
	{
		if(paper_count < 1)
		{
			display_normal({
				"你选择做科研",
				"你为科学而奋斗，平凡而幸福"
			});
		}
		else if(paper_count < 4)
		{
			display_good({
				"你选择做科研",
				"由于你在大学科研的基础，你小有成就"
			});
		}
		else
		{
			display_perfect({
				"你选择做科研",
				"由于你出色的科研能力，你成为了领域内的大牛"
			});
		}
	}
	else if(t == 2)
	{
		if(game_value_lvl < 5)
		{
			display_normal({
				"你成为了一名游戏主播",
				"虽然名气不大，但能养家糊口，你的人生平凡而幸福"
			});
		}
		else if(game_value_lvl < 8)
		{
			display_good({
				"你成为了一名游戏主播",
				"由于你的游戏实力，成为了大主播"
			});
		}
		else
		{
			display_perfect({
				"你成为了一名游戏主播",
				"由于你出色的游戏实力，你进入了战队，赢得了荣誉"
			});
		}
	}
	else if(t == 3)
	{
		if(music_value_lvl < 5)
		{
			display_normal({
				"你成为了一名音乐家",
				"你四处演出，虽然名气不大，但能养家糊口，你的人生平凡而幸福"
			});
		}
		else if(music_value_lvl < 8)
		{
			display_good({
				"你成为了一名音乐家",
				"由于你大学的积累，你小有名气"
			});
		}
		else
		{
			display_perfect({
				"你成为了一名音乐家",
				"由于你刻苦的练习，你名声大噪，成为了知名音乐家"
			});
		}
	}
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
	idea_tot = 0;
	paper_count = 0;
	
	game_value = 0;
	game_value_lvl = 0;
	game_value_lvl_next = 2;
	
	music_value = 0;
	music_value_lvl = 0;
	music_value_lvl_next = 2;
	
	society_value = 0;
	society_value_lvl = 0;
	society_value_lvl_next = 2;
	
	next_exam_date = -1;
	next_exam_require = -1;
	
	homework_tot = 0;
	homework_ddl = -1;
	homework_finished = 0;
	homework_failed_count = 0;
	
	guide();
	
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
		else if(weekday_id == 5)
		{
			lesson_physical_education(week_id, weekday_id);
		}
		else if(exam_set.count(week_id) && weekday_id == 7)
		{
			lesson_calculus_exam(week_id, weekday_id);
		}
		else
		{
			lesson_no_lesson(week_id, weekday_id);
		}
	}
	
	ending();
	return 0;
}