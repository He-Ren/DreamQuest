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
			msg.push_back("论文给了你启发，你产生了一个新的 idea！");
			delta_H = 10;
		}
		else
		{
			msg.push_back("在思政课深邃思想的启示下，你产生了一个新的 idea！");
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

/*
打游戏
*/
void action_play_game(Lesson_id)
{
	vector<string> msg;
	
	int delta_E = rnd(10, 20);
	int delta_H = rnd(-3, 2);
	int delta_G = rnd(1,2);
	
	if(rndbool(0.05))
	{
		msg.push_back("__ __，启动！");
	}
	else
	{
		msg.push_back("你玩了一会游戏");
	}
	
	if(delta_G == 2)
		msg.push_back("今天手感很好");
	
	if(delta_E <= 15)
		msg.push_back("你的体能恢复了");
	else
		msg.push_back("你的体能恢复了很多");
	
	if(delta_H < 0)
		msg.push_back("这样的生活让你对未来感到迷茫");
	if(delta_H > 0)
		msg.push_back("游戏让你心情大好");
	
	update_energe_value(delta_E);
	update_hope_value(delta_H);
	game_value += delta_G;
	
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
	
	int delta_E = rnd(10, 20);
	int delta_H = rnd(-2, 2);
	int delta_M = rnd(1,2);
	
	msg.push_back("你练了一会琴");
	
	if(delta_M == 2)
		msg.push_back("今天手感很好");
	
	if(delta_E <= 15)
		msg.push_back("你的体能恢复了");
	else
		msg.push_back("你的体能恢复了很多");
	
	if(delta_H < 0)
		msg.push_back("你对未来感到迷茫");
	if(delta_H > 0)
		msg.push_back("琴声让你心情舒畅");
	
	update_energe_value(delta_E);
	update_hope_value(delta_H);
	music_value += delta_M;
	
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
	
	int delta_E = rnd(10, 20);
	int delta_H = rnd(-2, 2);
	int delta_S = rnd(1,2);
	
	msg.push_back("你读了一些新闻");
	
	if(delta_S == 2)
		msg.push_back("你对社会现状有了一些思考");
	
	if(delta_E <= 15)
		msg.push_back("你的体能恢复了");
	else
		msg.push_back("你的体能恢复了很多");
	
	if(delta_H < 0)
		msg.push_back("你对未来感到迷茫");
	if(delta_H > 0)
		msg.push_back("你充满决心");
	
	update_energe_value(delta_E);
	update_hope_value(delta_H);
	society_value += delta_S;
	
	display(msg, {
		"确定"
	});
	
	check_alive();
}

/*
参加社工活动
*/
void action_do_social_activities(Lesson_id)
{
	vector<string> msg;
	
	int delta_E = -2;
	int delta_H = 5;
	int delta_S = 5;
	
	msg.push_back("你参加了一些社工活动");
	
	msg.push_back("你对未来充满希望");
	
	update_energe_value(delta_E);
	update_hope_value(delta_H);
	society_value += delta_S;
	
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
	
	int delta_E = -2;
	int delta_H = 5;
	int delta_C = 3;
	
	msg.push_back("你参加了一场数学讲座");
	
	if(rndbool(0.5))
	{
		idea_count += 1;
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
	
	int delta_E = -2;
	int delta_H = 5;
	int delta_M = 3;
	
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

/*
微积分课
*/
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
				action_read_paper(Calculus);
			}
			else if(t2 == 3)// 运动
			{
				action_do_sport(Calculus);
			}
			else if(t2 == 4)// 打游戏
			{
				action_play_game(Calculus);
			}
			else if(t2 == 5)// 练琴
			{
				action_practice_music(Calculus);
			}
			else if(t2 == 6)// 阅读一些时政新闻
			{
				action_read_news(Calculus);
			}
			else if(t2 == 7)// 休息一天
			{
				action_do_nothing(Calculus);
			}
			else if(t2 == 8)// 花3个idea写篇论文
			{
				action_write_paper(Calculus);
			}
		}
		
		break;
	}
}

/*
思想道德与法治课
*/
void lesson_development(int, int)
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
			energy_value = max(0, energy_value - 5);
			
			if(energy_value <= 0)
			{
				display_lose({
					"你太累了，在课堂上晕倒了",
					"学校为你安排了休学"
				});
			}
			
			update_hope_value(7);
			society_value += 2;
			
			vector<string> msg2;
			msg2.push_back("思政深邃的思想让你对未来充满希望");
			
			display(msg2, {"确定"});
			
			check_alive();
		}
		else
		{
			vector<string> opt2;
			opt2.push_back("做微积分作业");
			opt2.push_back("复习微积分");
			opt2.push_back("读论文");
			opt2.push_back("睡觉");
			if(idea_count >= 3)
				opt2.push_back("花3个idea写篇论文");
			opt2.push_back("返回上一页");
			
			int t2 = display({"你决定要在课上干点别的，但是干点啥呢？"}, opt2);
			
			if(t2 == (int)opt2.size() - 1)
			{
				continue;
			}
			
			if(t2 == 0)// 做微积分作业
			{
				action_do_calculus_homework(Development);
			}
			else if(t2 == 1)// 复习微积分
			{
				action_review_calculus(Development);
			}
			else if(t2 == 2)// 读论文
			{
				action_read_paper(Development);
			}
			else if(t2 == 3)// 睡觉
			{
				action_do_nothing(Development);
			}
			else if(t2 == 4)// 花3个idea写篇论文
			{
				action_write_paper(Development);
			}
		}
		
		break;
	}
}

/*
平时
*/
void lesson_no_lesson(int, int)
{
	vector<string> msg;
	
	msg.push_back("今天没有课");
	
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
	push(3, "运动");
	push(4, "打游戏");
	push(5, "练琴");
	push(6, "阅读一些时政新闻");
	push(7, "休息一天");
	if(idea_count >= 3)
		push(8, "花3个idea写篇论文");
	
	int oth = rnd(0, 100 - 1);
	if(0 <= oth && oth < 5)
	{
		msg.push_back("群公告：今天有社工活动，大家自愿参加");
		push(9, "参加社工活动");
	}
	else if(5 <= oth && oth < 10)
	{
		msg.push_back("群公告：今天有数学讲座，大家自愿参加");
		push(10, "参加数学讲座");
	}
	else if(10 <= oth && oth < 15)
	{
		msg.push_back("群公告：今天有音乐会，大家自愿参加");
		push(11, "参加音乐会");
	}
	else if(15 <= oth && oth < 17 && game_value >= 60)
	{
		msg.push_back("某战队发现了你的游戏天赋，邀请你加入");
		push(12, "接受游戏战队的邀请（结束游戏）");
	}
	else if(17 <= oth && oth < 19 && music_value >= 60)
	{
		msg.push_back("某星探发现了你的音乐才能，邀请你参加演出");
		push(13, "接受星探的邀请（结束游戏）");
	}
	else if(19 <= oth && oth < 21 && energy_value_lim >= 200)
	{
		msg.push_back("校队发现了你的体育天赋，邀请你加入");
		push(14, "接受校队的邀请（结束游戏）");
	}
	
	int t = display(msg, opt);
	
	if(opt_id[t] == 0)// 做微积分作业
	{
		action_do_calculus_homework(Nolesson);
	}
	else if(opt_id[t] == 1)// 复习微积分
	{
		action_review_calculus(Nolesson);
	}
	else if(opt_id[t] == 2)// 读论文
	{
		action_read_paper(Nolesson);
	}
	else if(opt_id[t] == 3)// 运动
	{
		action_do_sport(Nolesson);
	}
	else if(opt_id[t] == 4)// 打游戏
	{
		action_play_game(Nolesson);
	}
	else if(opt_id[t] == 5)// 练琴
	{
		action_practice_music(Nolesson);
	}
	else if(opt_id[t] == 6)// 阅读一些时政新闻
	{
		action_read_news(Nolesson);
	}
	else if(opt_id[t] == 7)// 休息一天
	{
		action_do_nothing(Nolesson);
	}
	else if(opt_id[t] == 8)// 花3个idea写篇论文
	{
		action_write_paper(Nolesson);
	}
	else if(opt_id[t] == 9)// 参加社工活动
	{
		action_do_social_activities(Nolesson);
	}
	else if(opt_id[t] == 10)// 参加数学讲座
	{
		action_attend_math_lecture(Nolesson);
	}
	else if(opt_id[t] == 11)// 参加音乐会
	{
		action_attend_concert(Nolesson);
	}
	else if(opt_id[t] == 12)// 游戏天赋
	{
		display_win({
			"你加入了战队，前途一片光明"
		});
	}
	else if(opt_id[t] == 13)// 音乐天赋
	{
		display_win({
			"你成为了音乐家，前途一片光明"
		});
	}
	else if(opt_id[t] == 14)// 体育天赋
	{
		display_win({
			"你加入了校队，前途一片光明"
		});
	}
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
			"你挂科了，学校为你安排了退学"
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
	opt.push_back("成为公务员");
	if(energy_value_lim >= 200)
		opt.push_back("成为运动员");
	
	int t = display(msg, opt);
	
	if(t == 0)
	{
		display_win({
			"你找到了一份工作",
			"你的人生平凡而幸福"
		});
	}
	else if(t == 1)
	{
		if(paper_count >= 3)
		{
			display_win({
				"你选择做科研",
				"由于你在大学发表了多篇论文，你成为了学界大牛"
			});
		}
		else if(paper_count >= 1)
		{
			display_win({
				"你选择做科研",
				"由于你在大学写论文的基础，你的科研非常顺利"
			});
		}
		else
		{
			display_win({
				"你选择做科研",
				"你成为了一名科研工作者，忙碌而幸福"
			});
		}
	}
	else if(t == 2)
	{
		if(game_value >= 60)
		{
			display_win({
				"你成为了一名游戏主播",
				"因为你的游戏天赋，很快获得了成功"
			});
		}
		else
		{
			display_win({
				"你成为了一名游戏主播",
				"虽然名气不大，但也能养家糊口"
			});
		}
	}
	else if(t == 3)
	{
		if(game_value >= 60)
		{
			display_win({
				"你成为了一名音乐家",
				"因为你的音乐天赋，很快获得了成功"
			});
		}
		else
		{
			display_win({
				"你成为了一名音乐家",
				"虽然名气不大，但也能养家糊口"
			});
		}
	}
	else if(t == 4)
	{
		if(society_value >= 100)
		{
			display_win({
				"你决定成为公务员，投身祖国建设",
				"由于大学时期的积累，你做出了杰出的贡献"
			});
		}
		else
		{
			display_win({
				"你决定成为公务员，投身祖国建设",
				"你的未来忙碌而幸福"
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