#include "lwUtils.h"

void lwUtils::Normalize(vector<double>& v)
{
	double sum = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
	if (sum > 0.0)
	{
		sum = sqrt(sum);
		v[0] /= sum;
		v[1] /= sum;
		v[2] /= sum;
	}
}

vector<double> lwUtils::CrossProduct(vector<double>& a, vector<double>& b)
{
	return vector<double>{
		a[1] * b[2] - a[2] * b[1],
			a[2] * b[0] - a[0] * b[2],
			a[0] * b[1] - a[1] * b[0]};
}
