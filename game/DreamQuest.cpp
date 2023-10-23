#include<bits/stdc++.h>
#include"variable.h"
#include"display.h"
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;



int main(void)
{
	display_init();
	for(int i=0; i<finish_date; ++i)
	{
		current_date = i;
		display({}, {"确定"});
	}
	return 0;
}