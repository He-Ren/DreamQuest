#include"display.h"
#include<bits/stdc++.h>
using namespace std;

int main(void)
{
	display_init();
	
	{
		string s = 
			"▏""▎""▍""▌""▋""▊""▉""█"
			"┏━┳┓"
			"┃┃┃"
			"┣━╋┫"
			"┗━┻┛"
			"┯"
			"│"
			"┷";
		vector< vector<int> > vec; 
		for(int i=0; i<(int)s.size(); i+=get_utf8_len(s[i]))
		{
			vector<int> cur;
			for(int j=0; j<get_utf8_len(s[i]); ++j)
				cur.push_back((unsigned char)s[i+j]);
			vec.push_back(cur);
		}
		
		sort(vec.begin(), vec.end());
		vec.erase(unique(vec.begin(), vec.end()), vec.end());
		
		for(auto tt: vec)
		{
			for(auto t: tt)
				printf("%d ",t);
			printf("\n");
		}
		
		system("pause");
	}
	hope_value_lim = 100;
	hope_value = 0;
	
	game_value = 1;
	// music_value = 1;
	society_value = 1;
	
	game_value_lvl_next = 2;
	music_value_lvl_next = 2;
	society_value_lvl_next = 2;
	
	while(hope_value < 100)
	{
		display_basic1({
			"test",
			"很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长",
			"1很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长111"
		}, {
			"test2",
			"BBB",
			"C选项"
		}, 1);
		
		++hope_value;
		Sleep(10);
	}
	
	display_basic1({
		"test",
		"很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长",
		"1很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长111"
	}, {
		"test2",
		"BBB",
		"C选项"
	}, 1);
	
	system("pause");
	return 0;
}