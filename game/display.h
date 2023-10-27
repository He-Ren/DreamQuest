#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include<vector>
#include<string>
#include<iostream>
#include<windows.h>
#include<conio.h>
#include"variable.h"
using namespace std;
typedef pair<int,int> pii;

void gotoxy(short x, short y) {
	COORD coord = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int get_utf8_len(char c)
{
	if(!(c & (1 << 7))) return 1;
	if(!(c & (1 << 5))) return 2;
	if(!(c & (1 << 4))) return 3;
	return 4;
}

int get_utf8_width(const char *c)
{
	if((unsigned char)c[0] == 226 && (unsigned char)c[1] == 150 &&
		136 <= (unsigned char)c[2] && (unsigned char)c[2] <= 143)
		return 1;
	return min(2, get_utf8_len(*c));
}

vector<string> process_symbols = {
	"▏","▎","▍","▌","▋","▊","▉","█"
};

string get_process_string(int len,int a,int b)
{
	double p = b == 0? 0: (double)a / b;
	p = max(0.0, min(1.0, p));
	
	int cnt = (len / 2 * 8) * p;
	
	string res;
	while(cnt >= 8)
		res += process_symbols[7] + ' ', cnt -= 8;
	if(cnt)
		res += process_symbols[cnt - 1] + ' ';
	
	return res;
}

vector<string> cut_string(string s, int W)
{
	vector<string> res;
	
	int curlen = 0;
	string curstr;
	for(int i=0; i<(int)s.size(); i+=get_utf8_len(s[i]))
	{
		int w = get_utf8_width(s.c_str() + i);
		if(curlen + w > W)
		{
			if(curstr.size())
				res.push_back(curstr);
			curlen = 0;
			curstr.clear();
		}
		curstr.insert(curstr.end(), s.begin() + i, s.begin() + i + get_utf8_len(s[i]));
		curlen += w;
	}
	if(curstr.size())
		res.push_back(curstr);
	return res;
}

void paste_string_idx(string &s, int pos, string t)
{
	int totw = 0;
	for(int i=0; i<(int)t.size(); i+=get_utf8_len(t[i]))
		totw += get_utf8_width(t.c_str() + i);
	
	s.erase(s.begin() + pos, s.begin() + pos + totw);
	s.insert(s.begin() + pos + 1, t.begin(), t.end());
}
void paste_string_coord(string &s, int y, string t)
{
	int curpos = 0;
	for(int i=0; i<(int)s.size(); i+=get_utf8_len(s[i]))
	{
		if(curpos == y)
		{
			paste_string_idx(s, i, t);
			return;
		}
		curpos += get_utf8_width(s.c_str() + i);
	}
}

void paste_string_coord(vector<string> &s, int x, int y, string t)
{
	paste_string_coord(s[x], y, t);
}

vector<pii> get_key_coord(vector<string> &s)
{
	vector<pii> res;
	for(int i=0; i<(int)s.size(); ++i)
	{
		int y = 0;
		for(int j=0; j<(int)s[i].size(); j+=get_utf8_len(s[i][j]))
		{
			if('0' <= s[i][j] && s[i][j] <= '9')
			{
				int id = s[i][j] - '0';
				if(id+1 >= (int)res.size())
					res.resize(id+1, {0,0});
				res[id] = {i, y};
				s[i][j] = ' ';
			}
			y += get_utf8_width(s[i].c_str() + j);
		}
	}
	return res;
}

vector<string> weekday_chinese_name = {
	"一","二","三","四","五","六","日"
};

void display_init(void)
{
	system("chcp 65001");

	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// 获取当前控制台字体信息
	GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

	// 设置新的字体属性
	fontInfo.nFont = 0; // 字体索引
	fontInfo.dwFontSize.X = 10; // 宽度
	fontInfo.dwFontSize.Y = 20; // 高度
	fontInfo.FontFamily = FF_DONTCARE; // 字体族
	fontInfo.FontWeight = FW_NORMAL; // 字体粗细
	wcscpy_s(fontInfo.FaceName, L"新宋体"); // 字体名称

	// 应用新的字体
	SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

	system("cls");
}

void display_basic1(vector<string> msg, vector<string> opt, int curopt)
{
 	/*
 	┏━┳┓
 	┃ ┃┃
 	┣━╋┫
 	┗━┻┛
 	┯
 	│
 	┷
 	*/
	vector<string> s = {
		"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
		"┃ 9                                                                                              ┃",
		"┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫",
		"┃ 0                                                             1  ┃ 3                           ┃",
		"┃                                                                  ┃                             ┃",
		"┃                                                                  ┃                             ┃",
		"┃                                                                  ┃                             ┃",
		"┃                                                                  ┃                             ┃",
		"┃                                                                  ┃                             ┃",
		"┃                                                                  ┃                             ┃",
		"┃                                                                  ┃                             ┃",
		"┃                                                                  ┃                             ┃",
		"┃                                                                  ┃                             ┃",
		"┃                                                                  ┃                             ┃",
		"┃                                                                  ┃                             ┃",
		"┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫                             ┃",
		"┃ 2                                                                ┃                             ┃",
		"┃                                                                  ┃                             ┃",
		"┃                                                                  ┃                             ┃",
		"┃                                                                  ┃                             ┃",
		"┃                                                                  ┃                             ┃",
		"┃                                                                  ┃                             ┃",
		"┃                                                                  ┃                             ┃",
		"┃                                                                  ┃                             ┃",
		"┃                                                                  ┃                             ┃",
		"┃                                                                  ┃                             ┃",
		"┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━┯━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫",
		"┃ 4                        7 │ 5                                                               6 ┃",
		"┃                            │                                                                   ┃",
		"┃                            │                                                                   ┃",
		"┃                            │                                                                   ┃",
		"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┷━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛",
	};
	
	auto key = get_key_coord(s);
	
	paste_string_coord(s, key[9].first, key[9].second, "DreamQuest - by 德法34组");
	
	int W = key[1].second - key[0].second - 1;
	int curx = key[0].first;
	
	for(int i=0; i<(int)msg.size(); ++i)
	{
		auto t = cut_string(msg[i], W);
		paste_string_coord(s, curx, key[0].second, "* " + t[0]);
		for(int j=1; j<(int)t.size(); ++j)
			paste_string_coord(s, ++curx, key[0].second, "  " + t[j]);
		curx += 2;
	}
	
	curx = key[2].first;
	for(int i=0; i<(int)opt.size(); ++i)
	{
		string t = opt[i];
		t = "  " + string(1, 'A' + i) + ". " + t + "  ";
		if(i == curopt)
			t[0] = t[(int)t.size() - 1] = '-';
		
		paste_string_coord(s, curx, key[2].second, t);
		++curx;
	}
	
	vector<string> riglist;
	riglist.push_back("第" + to_string(current_date / 7 + 1) + "/" + to_string(finish_date / 7) + "周 周" + weekday_chinese_name[current_date % 7]);
	
	riglist.push_back("idea个数：" + to_string(idea_count));
	riglist.push_back("论文数：" + to_string(paper_count));
	
	if(next_exam_date >= current_date)
	{
		riglist.push_back("距离考试还有：" + to_string(next_exam_date - current_date) + "天");
	}
	else
	{
		riglist.push_back("下次考试日期未知");
	}
	
	if(homework_ddl > current_date)
	{
		riglist.push_back("距离作业ddl还有" + to_string(homework_ddl - current_date - 1) + "天");
	}
	else
	{
		riglist.push_back("当前没有作业");
	}
	
	riglist.push_back("作业逾期：" + to_string(homework_failed_count) + "次");
	
	curx = key[3].first;
	for(int i=0; i<(int)riglist.size(); ++i)
	{
		string t = riglist[i];
		paste_string_coord(s, curx, key[3].second, t);
		curx += 2;
	}
	
	vector<string> ldlist, rdlist;
	int process_W = key[6].second - key[5].second + 1;
	
	ldlist.push_back("希望值（" + to_string(hope_value) + "/" + to_string(hope_value_lim) + "）");
	rdlist.push_back(get_process_string(process_W, hope_value, hope_value_lim));
	
	ldlist.push_back("体力值（" + to_string(energy_value) + "/" + to_string(energy_value_lim) + "）");
	rdlist.push_back(get_process_string(process_W, energy_value, energy_value_lim));
	
	if(homework_ddl > current_date)
	{
		ldlist.push_back("作业题（" + to_string(homework_finished) + "/" + to_string(homework_tot) + "）");
		rdlist.push_back(get_process_string(process_W, homework_finished, homework_tot));
	}
	else
	{
		ldlist.push_back("当前无作业");
		rdlist.push_back("");
	}
	
	if(next_exam_date >= current_date)
	{
		ldlist.push_back("微积分能力值/要求（" + to_string(calculus_value) + "/" + to_string(next_exam_require) + "）");
		rdlist.push_back(get_process_string(process_W, calculus_value, next_exam_require));
	}
	else
	{
		ldlist.push_back("微积分能力值/要求（" + to_string(calculus_value) + "/ ?");
		rdlist.push_back("无已知考试");
	}
	
	curx = key[4].first;
	for(int i=0; i<(int)ldlist.size(); ++i)
	{
		string t = ldlist[i];
		
		int rem = key[7].second - key[4].second + 1;
		for(int j=0; j<(int)t.size(); j+=get_utf8_len(t[j]))
			rem -= get_utf8_width(t.c_str() + j);
		
		t.insert(t.begin(), rem, ' ');
		
		paste_string_coord(s, curx, key[4].second, t);
		curx += 1;
	}
	
	curx = key[5].first;
	for(int i=0; i<(int)rdlist.size(); ++i)
	{
		string t = rdlist[i];
		paste_string_coord(s, curx, key[5].second, t);
		curx += 1;
	}
	
	
	gotoxy(0,0);
	for(auto t: s)
		cout << t << endl;
}

int display(vector<string> msg, vector<string> opt)
{
	system("cls");
	
	cout << "当前天数：" << current_date << endl;
	cout << "结束天数：" << finish_date << endl;
	cout << "当前是第 " << current_date / 7 + 1 << " 周的第 " << current_date % 7 + 1 << " 天 " << endl;
	cout << "共 " << finish_date / 7 << " 周" << endl; 
	
	cout << "希望值：     " << hope_value << endl;
	cout << "希望值上限： " << hope_value_lim << endl;
	
	
	cout << "体力值：     " << energy_value << endl;
	cout << "体力值上限： " << energy_value_lim << endl;
	
	cout << "微积分能力值：     " << calculus_value << endl;
	
	cout << "idea 个数： " << idea_count << endl;
	cout << "paper 个数：" << paper_count << endl;
	
	cout << "（隐藏）游戏能力值：" << game_value << endl;
	cout << "（隐藏）音乐能力值：" << music_value << endl;
	cout << "（隐藏）社会能力值：" << society_value << endl;
	
	cout << "下次考试时间：" << next_exam_date << endl;
	cout << "下次考试需要的能力值" << next_exam_require << endl;
	
	cout << "作业总数：     " << homework_tot << endl;
	cout << "作业ddl：      " << homework_ddl << endl;
	cout << "当前完成作业数：" << homework_finished << endl;
	cout << "作业逾期次数  ：" << homework_failed_count << endl;
	
	cout << endl;
	cout << "对话框：" << endl;
	for(auto t: msg)
		cout << t << endl;
	
	cout << "选项：" << endl;
	for(int i=0; i<(int)opt.size(); ++i)
	{
		cout << (char)(i + 'A') << ". " << opt[i] <<endl;
	}
	
	while(1)
	{
		string t;
		getline(cin, t);
		if(t.size() && 'A' <= t[0] && t[0] <= 'A' + (int)opt.size() - 1)
			return t[0] - 'A';
	}
}

void display_lose(vector<string> msg)
{
	cout << "当前天数：" << current_date << endl;
	cout << "结束天数：" << finish_date << endl;
	cout << "当前是第 " << current_date / 7 + 1 << " 周的第 " << current_date % 7 + 1 << " 天 " << endl;
	cout << "共 " << finish_date / 7 << " 周" << endl; 
	
	cout << "希望值：     " << hope_value << endl;
	cout << "希望值上限： " << hope_value_lim << endl;
	
	
	cout << "体力值：     " << energy_value << endl;
	cout << "体力值上限： " << energy_value_lim << endl;
	
	cout << "微积分能力值：     " << calculus_value << endl;
	
	cout << "idea 个数： " << idea_count << endl;
	cout << "paper 个数：" << paper_count << endl;
	
	cout << "（隐藏）游戏能力值：" << game_value << endl;
	cout << "（隐藏）音乐能力值：" << music_value << endl;
	cout << "（隐藏）社会能力值：" << society_value << endl;
	
	cout << "下次考试时间：" << next_exam_date << endl;
	cout << "下次考试需要的能力值" << next_exam_require << endl;
	
	cout << "作业总数：     " << homework_tot << endl;
	cout << "作业ddl：      " << homework_ddl << endl;
	cout << "当前完成作业数：" << homework_finished << endl;
	cout << "作业逾期次数  ：" << homework_failed_count << endl;
	
	cout << endl;
	cout << "失败" << endl;
	cout << "失败信息：" << endl;
	for(auto t: msg)
	{
		cout << t << endl;
	}
	system("pause");
	exit(0);
}

void display_win(vector<string> msg)
{
	cout << "当前天数：" << current_date << endl;
	cout << "结束天数：" << finish_date << endl;
	cout << "当前是第 " << current_date / 7 + 1 << " 周的第 " << current_date % 7 + 1 << " 天 " << endl;
	cout << "共 " << finish_date / 7 << " 周" << endl; 
	
	cout << "希望值：     " << hope_value << endl;
	cout << "希望值上限： " << hope_value_lim << endl;
	
	
	cout << "体力值：     " << energy_value << endl;
	cout << "体力值上限： " << energy_value_lim << endl;
	
	cout << "微积分能力值：     " << calculus_value << endl;
	
	cout << "idea 个数： " << idea_count << endl;
	cout << "paper 个数：" << paper_count << endl;
	
	cout << "（隐藏）游戏能力值：" << game_value << endl;
	cout << "（隐藏）音乐能力值：" << music_value << endl;
	cout << "（隐藏）社会能力值：" << society_value << endl;
	
	cout << "下次考试时间：" << next_exam_date << endl;
	cout << "下次考试需要的能力值" << next_exam_require << endl;
	
	cout << "作业总数：     " << homework_tot << endl;
	cout << "作业ddl：      " << homework_ddl << endl;
	cout << "当前完成作业数：" << homework_finished << endl;
	cout << "作业逾期次数  ：" << homework_failed_count << endl;
	
	cout << endl;
	cout << "获胜" << endl;
	cout << "获胜信息：" << endl;
	for(auto t: msg)
	{
		cout << t << endl;
	}
	system("pause");
	exit(0);
}

// /*
// 将 t 粘贴在 s 中
// begx, begy: 起点坐标
// W: 长度限制，达到这个长度将从下一行的 begy 重新开始
// 返回结尾的下一行编号
// */
// int paste_sting(vector<Ustring> &s, const Ustring &t, int begx, int begy, int W)
// {
// 	for(int i=0; i<(int)t.size(); ++i)
// 		s[begx + i / W][begy + i % W] = t[i];
// 	return begx + ((int)t.size() - 1) / W + 1;
// }

// /*
// msg: 对话框中的信息，分行
// opt: 每个选项的文字
// curopt: 当前选项编号，从 0 开始
// 显示当前信息
// */
// void basic_display(vector<Ustring> msg, vector<Ustring> opt, int curopt)
// {
// 	/*
// 	┏━┳┓
// 	┃ ┃┃
// 	┣━╋┫
// 	┗━┻┛
// 	*/
// 	auto s = convert_to_vector_Ustring(vector<string>{
// 		"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
// 		"┃                                                                ┃",
// 		"┃                                                                ┃",
// 		"┃                                                                ┃",
// 		"┃                                                                ┃",
// 		"┃                                                                ┃",
// 		"┃                                                                ┃",
// 		"┃                                                                ┃",
// 		"┃                                                                ┃",
// 		"┃                                                                ┃",
// 		"┃                                                                ┃",
// 		"┃                                                                ┃",
// 		"┃                                                                ┃",
// 		"┃                                                                ┃",
// 		"┃                                                                ┃",
// 		"┃                                                                ┃",
// 		"┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫",
// 		"┃                                                                ┃",
// 		"┃                                                                ┃",
// 		"┃                                                                ┃",
// 		"┃                                                                ┃",
// 		"┃                                                                ┃",
// 		"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛",
// 	});
	
// 	const int msg_beg_x = 2, msg_beg_y = 4, msg_W = 60;
// 	const int opt_beg_x = 17, opt_beg_y = 4;
	
// 	int curx = msg_beg_x;
// 	for(int i=0; i<(int)msg.size(); ++i)
// 	{
// 		s[curx][msg_beg_y] = "*";
// 		curx = paste_sting(s, msg[i], curx, msg_beg_y + 2, msg_W) + 1;
// 	}
	
// 	curx = opt_beg_x;
// 	for(int i=0; i<(int)opt.size(); ++i)
// 	{
// 		int cury = opt_beg_y + 2;
// 		s[curx][cury++] = Uchar(1, 'A' + i);
// 		s[curx][cury++] = Uchar(1, '.');
// 		s[curx][cury++] = Uchar(1, ' ');
		
// 		paste_sting(s, opt[i], curx, cury, 1e9);
		
// 		s[curx][cury++] = " ";
		
// 		if(i == curopt)
// 		{
// 			s[curx][opt_beg_y] = "-";
// 			s[curx][cury] = "-";
// 		}
		
// 		++curx;
// 	}
	
// 	gotoxy(0,0);
// 	for(auto t: s)
// 		cout << t << "\n";
// 	fflush(stdout);
// }

// /*
// msg: 对话框中的信息，分行
// opt: 每个选项的文字
// 返回玩家选择的编号，从 0 开始
// */
// int display(vector<Ustring> msg, vector<Ustring> opt)
// {
// 	bool reprint = 0;
// 	int curopt = 0;
	
// 	for(int i=-1; i<(int)msg.size(); ++i)
// 	{
// 		basic_display(vector<Ustring>(msg.begin(), msg.begin() + i + 1), opt, -1);
// 		Sleep(100);
// 	}
	
// 	while(kbhit()) getch();
	
// 	reprint = 1;
	
// 	while(1)
// 	{
// 		if(reprint)
// 		{
// 			reprint = 0;
// 			basic_display(msg, opt, curopt);
// 		}
		
// 		if(kbhit() != 0)
// 		{
// 			int c = getch();
// 			if(c == VK_RETURN)
// 			{
// 				return curopt;
// 			}
// 			if(c == 'Q')
// 			{
// 				exit(0);
// 			}
			
// 			int type = -10; // -1: up, -2: down
			
// 			if(c == 'W' || c == 'w') type = -1;
// 			if(c == VK_UP) type = -1;
			
// 			if(c == 'S' || c == 's') type = -2;
// 			if(c == VK_DOWN) type = -2;
			
// 			else if(type == -1 && curopt - 1 >= 0)
// 			{
// 				curopt -= 1;
// 				reprint = 1;
// 			}
// 			else if(type == -2 && curopt + 1 < (int)opt.size())
// 			{
// 				curopt += 1;
// 				reprint = 1;
// 			}
// 		}
// 	}
// }

#endif