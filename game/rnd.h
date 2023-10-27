#ifndef _RND_H_
#define _RND_H_

#include<random>
#include<vector>

mt19937_64 gen((unsigned long long)new char ^ time(0));

int rnd(int l,int r)
{
	return uniform_int_distribution<int>(l,r)(gen);
}
bool rndbool(double prob)
{
	return uniform_real_distribution<double>(0,1)(gen) < prob;
}

template<typename T>
T rnd_among(const std::vector<T> &p)
{
	return p[rnd(0, (int)p.size() - 1)];
}

#endif