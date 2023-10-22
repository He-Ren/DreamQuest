#ifndef _USTRING_H_
#define _USTRING_H

#include<string>
#include<vector>
#include<iostream>

int get_utf8_len(int c)
{
	if((c & 128) == 0) return 1;
	if((c & 32) == 0) return 2;
	if((c & 16) == 0) return 3;
	if((c & 8) == 0) return 4;	
	return -1;
}

struct Uchar
{
	string c;
	int w;
	Uchar(void){ w = 0; c = "\0";}
	Uchar(char _c){ w = 1; c = string(1, _c);}
	Uchar(string _c)
	{
		c = _c;
		w = min(get_utf8_len(c[0]), 2);
	}
};
using Uchar = std::string;
using Ustring = std::vector<Uchar>;

std::ostream& operator << (std::ostream &os, const Ustring &s)
{
	for(const auto &t: s)
		os << t;
	return os;
}

Ustring convert_to_Ustring(const std::string &s)
{
	Ustring res;
	for(int i=0; i<(int)s.size(); ++i)
	{
		int k = get_utf8_len(s[i]);
		res.push_back(Uchar(s.begin()+i, s.begin()+i+k));
		i += k-1;
	}
	return res;
}

std::vector<Ustring> convert_to_vector_Ustring(const std::vector<std::string> &s)
{
	std::vector<Ustring> res;
	for(const auto &t: s)
		res.emplace_back(convert_to_Ustring(t));
	return res;
}

#endif