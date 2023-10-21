#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include<vector>
#include<string>
#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;

void gotoxy(short x, short y) {
	COORD coord = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int get_utf8_len(int c)
{
	if((c & 128) == 0) return 1;
	if((c & 32) == 0) return 2;
	if((c & 16) == 0) return 3;
	if((c & 8) == 0) return 4;
	return -1;
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
	};
	
	const int W = 60;
	const int msg_beg_x = 2, msg_beg_y = 4;
	const int opt_beg_x = 17, opt_beg_y = 4;
	
	int curx = msg_beg_x;
	for(int i=0; i<(int)msg.size(); ++i)
	{
		s[curx][msg_beg_y] = '*';
		
		int cury = msg_beg_y + 2;
		int curlen = 2;
		
		for(int j=0; j<(int)msg[i].size(); ++j)
		{
			if(msg[i][j] == 0) break;
			
			int k = get_utf8_len(msg[i][j]);
			if(curlen + k > W)
			{
				++curx;
				cury = msg_beg_y + 2;
				curlen = 2;
			}
			
			if(k == 1)
			{
				s[curx][cury++] = msg[i][j];
				curlen += 1;
			}
			else
			{
				s[curx][cury++] = msg[i][j];
				s[curx][cury++] = msg[i][j+1];
				for(int l=2; l<k; ++l)
					s[curx].insert(s[curx].begin() + cury, msg[i][j+l]), ++cury;
				j += k-1;
				curlen += 2;
			}
		}
		
		curx += 2;
	}
	
	curx = opt_beg_x;
	for(int i=0; i<(int)opt.size(); ++i)
	{
		int cury = opt_beg_y + 2;
		s[curx][cury++] = 'A' + i;
		s[curx][cury++] = '.';
		s[curx][cury++] = ' ';
		
		for(int j=0; j<(int)opt[i].size(); ++j)
		{
			if(opt[i][j] == 0) break;
			
			int k = get_utf8_len(opt[i][j]);
			if(k == 1)
			{
				s[curx][cury++] = opt[i][j];
			}
			else
			{
				s[curx][cury++] = opt[i][j];
				s[curx][cury++] = opt[i][j+1];
				for(int l=2; l<k; ++l)
					s[curx].insert(s[curx].begin() + cury, opt[i][j+l]), ++cury;
				j += k-1;
			}
		}
		
		s[curx][cury++] = ' ';
		
		if(i == curopt)
		{
			s[curx][opt_beg_y] = '-';
			s[curx][cury] = '-';
		}
		
		++curx;
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
	
	for(int i=-1; i<(int)msg.size(); ++i)
	{
		basic_display(vector<string>(msg.begin(), msg.begin() + i + 1), opt, curopt);
		if(i+1<(int)msg.size())
			Sleep(100);
	}
	
	while(1)
	{
		if(reprint)
		{
			reprint = 0;
			basic_display(msg, opt, curopt);
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