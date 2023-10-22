#include<bits/stdc++.h>
#include"Ustring.h"
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int main(void)
{
	system("chcp 65001");
	string s = "这是测试测试测试1111测试aaaa你好";
	auto t = convert_to_Ustring(s);
	cout << "t = " << t;
	system("pause");
	return 0;
}