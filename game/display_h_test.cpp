#include"display.h"
#include<bits/stdc++.h>
using namespace std;

int main(void)
{
	system("chcp 65001");
	system("cls");
	while(1)
	{
		int res = display({"11111111111111111111111111111111111111111111111111111111111111111111111111111111111111",
			"22这是很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长的中文",
			"333这是很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长的中文"},
			{"this is A 并且有中文", "this is B"});
		printf("res = %d\n",res);
		Sleep(100);
	}
	return 0;
}