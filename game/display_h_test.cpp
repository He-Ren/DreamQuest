#include"display.h"
#include<bits/stdc++.h>
using namespace std;

int main(void)
{
	display_init();
	
	for(auto s: process_symbols)
	{
		for(auto t: s)
			printf("%d ",(int)(unsigned char)t);
		printf("\n");
	}
	
	system("pause");
	
	hope_value_lim = 100;
	hope_value = 0;
	
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