#ifndef _LW_UTILS_H
#define _LW_UTILS_H

#include <iostream>
#include <vector>

using namespace std;

class lwUtils
{
public:
	// 向量归一化操作
	static void Normalize(vector<double>& v);

	// 向量叉乘操作
	static  vector<double> CrossProduct(vector<double>& a, vector<double>& b);

};

#endif // !_LW_UTILS_H
