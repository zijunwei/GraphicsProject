#include "stdafx.h"
#include "ComponetTests.h"
#include "utils.h"

void t_LCHColorSpace(std::vector<myStroke> StrokeList)
{
	double range0 = 0;
	double range1 = 2 * PI;
	double H, MaxH = -1*INFINITY , MinH= INFINITY;
	int failCount = 0;
	std::vector<double> HList;
	for (int i = 0; i < StrokeList.size();i++)
	{
		H = StrokeList.at(i).lchColor(2);
		if (H>=range0 && H <= range1)
		{
			failCount = failCount + 1;

		}

		if (H<MinH)
		{
			MinH = H;
		}
		if (H>MaxH)
		{
			MaxH = H;
		}
		HList.push_back(H);

	}

	if (HList.size()>0){
	// nothing done here, just work as break point;
	}
}
