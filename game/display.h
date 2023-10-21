#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;

void gotoxy(short x, short y) {
  COORD coord = {x, y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*
msg: 对话框中的信息，分行
opt: 每个选项的文字
curopt: 当前选项编号，从 0 开始
显示当前信息
*/
void basic_display(vector<string> msg, vector<string> opt, int curopt)
{
	/*
	┏━┳┓
	┃ ┃┃
	┣━╋┫
	┗━┻┛
	*/
	vector<string> s = {
		"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
		"┃                                                                ┃",
		"┃                                                                ┃",
		"┃                                                                ┃",
		"┃                                                                ┃",
		"┃                                                                ┃",
		"┃                                                                ┃",
		"┃                                                                ┃",
		"┃                                                                ┃",
		"┃                                                                ┃",
		"┃                                                                ┃",
		"┃                                                                ┃",
		"┃                                                                ┃",
		"┃                                                                ┃",
		"┃                                                                ┃",
		"┃                                                                ┃",
		"┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫",
		"┃                                                                ┃",
		"┃                                                                ┃",
		"┃                                                                ┃",
		"┃                                                                ┃",
		"┃                                                                ┃",
		"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛",
	}
	
	const int W = 64;
	const int msg_beg_x = 1, msg_beg_y = 2;
	const int opt_beg_x = 17, opt_beg_y = 2;
	
	int curx = msg_beg_x;
	for(int i=0; i<(int)msg.size(); ++i)
	{
		s[curx][0] = '*';
		
		int cury = msg_beg_y + 2;
		for(int j=0; j<(int)msg[i].size(); ++j)
		{
			if(msg[i][j] == 0) break;
			
			if(0 < msg[i][j] && msg[i][j] < 127)
			{
				if(cury >= msg_beg_y + W)
					++curx, cury = msg_beg_y + 2;
				
				s[curx][cury++] = msg[i][j];
			}
			else
			{
				if(cury + 1 >= msg_beg_y + W)
					++curx, cury = msg_beg_y + 2;
				
				s[curx][cury++] = msg[i][j];
				s[curx][cury++] = msg[i][j+1];
				j += 1;
			}
		}
		
		curx += 2;
	}
	
	int curx = opt_beg_x;
	for(int i=0; i<(int)opt.size(); ++i)
	{
		int cury = opy_beg_y + 2;
		s[curx][cury++] = 'A' + i;
		s[curx][cury++] = ' ';
		for(auto c: opt[i])
			s[curx][cury++] = c;
		s[curx][cury++] = ' ';
		
		if(i == curopt)
		{
			s[curx][0] = '-';
			s[curx][cury] = '-';
		}
	}
	
	gotoxy(0,0);
	for(auto t: s)
		cout << t << "\n";
	fflush(stdout);
}

/*
msg: 对话框中的信息，分行
opt: 每个选项的文字
返回玩家选择的编号，从 0 开始
*/
int display(std::vector<std::string> msg, std::vector<std::string> opt)
{
	bool reprint = 0;
	int curopt = 0;
	
	auto print_opt = [&] (void)
	{
		for(int i=0; i<(int)opt.size(); ++i)
		{
			auto t = opt[i];
			t = std::string(1, char('A' + i)) + ". " + t;
			if(i == curopt)
				t = "- " + t + " -";
			else
				t = "  " + t + "  ";
			std::cout << t << std::string(50 - (int)t.size(), ' ') << std::endl;
		}
		for(int i=(int)opt.size(); i<7; ++i)
		{
			std::cout << std::string(50, ' ') << std::endl;
		}
	};
	
	gotoxy(0,0);
	for(int i=0; i<10; ++i)
	{
		std::cout << std::string(50, ' ') << std::endl;
	}
	print_opt();
	
	for(int i=0; i<(int)msg.size(); ++i)
	{
		gotoxy(0,0);
		for(int j=0; j<=i; ++j)
		{
			std::cout << msg[j] << std::endl;
		}
		if(i+1<(int)opt.size())
			Sleep(50);
	}
	for(int j=(int)msg.size(); j<10; ++j)
	{
		std::cout << std::string(50, ' ') << std::endl;
	}
	print_opt();
	
	while(1)
	{
		if(reprint)
		{
			reprint = 0;
			
			gotoxy(0,0);
			for(const auto &t: msg)
			{
				std::cout << t << std::endl;
			}
			for(int i=(int)msg.size(); i<10; ++i)
			{
				std::cout << std::string(10, ' ') << std::endl;
			}
			print_opt();
		}
		
		if(kbhit() != 0)
		{
			int c = getch();
			if(c == VK_RETURN)
			{
				return curopt;
			}
			if(c == 'Q')
			{
				exit(0);
			}
			
			int type = -10; // -1: up, -2: down
			
			if(c == 'W' || c == 'w') type = -1;
			if(c == VK_UP) type = -1;
			
			if(c == 'S' || c == 's') type = -2;
			if(c == VK_DOWN) type = -2;
			
			else if(type == -1 && curopt - 1 >= 0)
			{
				curopt -= 1;
				reprint = 1;
			}
			else if(type == -2 && curopt + 1 < (int)opt.size())
			{
				curopt += 1;
				reprint = 1;
			}
		}
	}
}

#endif