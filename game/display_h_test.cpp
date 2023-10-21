#include"display.h"
#include<bits/stdc++.h>
using namespace std;

int main(void)
{
	while(1)
	{
		int res = display({"111", "222", "333"}, {"this is A", "this is B"});
		printf("res = %d\n",res);
		Sleep(100);
	}
	return 0;
}