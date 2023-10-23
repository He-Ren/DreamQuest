#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include<vector>
#include<string>
#include<iostream>
#include<windows.h>
#include<conio.h>
#include"variable.h"
using namespace std;

void gotoxy(short x, short y) {
	COORD coord = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void display_init(void)
{
	system("chcp 65001");
	system("cls");
}

int display(vector<string> msg, vector<string> opt)
{
	system("cls");
	
	cout << "当前是第 " << current_date / 7 + 1 << " 周的第 " << current_date % 7 + 1 << " 天" << endl;
	cout << "共 " << finish_date / 7 << " 周" << endl; 
	cout << "作业总数：" << homework_tot << endl;
	cout << "作业截止日期：" << homework_ddl << endl;
	cout << "已完成作业总数" << homework_finished << endl;
	cout << "逾期作业数" << homework_failed_count << endl;
	cout << "微积分能力值：" << calculus_ability << endl;
	cout << "下次考试时间：" << next_exam_date << endl;
	cout << "下次考试需要的能力值：" << next_exam_require << endl;
	cout << "疲劳度：" << tired_value << endl;
	cout << "希望值：" << hope_value << endl;
	cout << "当前 idea 总数：" << idea_count << endl;
	cout << "当前论文总数：" << paper_count << endl;
	
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