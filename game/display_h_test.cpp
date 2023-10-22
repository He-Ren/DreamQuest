#include"display.h"
#include<bits/stdc++.h>
using namespace std;

int main(void)
{
	printf("%d\n",(int)string("111").size());
	system("pause");
	
	system("chcp 65001");
	system("cls");
	while(1)
	{	
		vector<string> msg = {"11111111111111111111111111111111111111111111111111111111111111111111111111111111111111",
			"22这是很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长的中文",
			"333这是很长很长很长很长很长很长很长很长很长很长很长很长很长很长很长的中文"};
		vector<string> opt = {"this is A 并且有中文", "this is B"};
		int res = display(convert_to_vector_Ustring(msg), convert_to_vector_Ustring(opt));
		printf("res = %d\n",res);
		Sleep(100);
	}
	return 0;
}