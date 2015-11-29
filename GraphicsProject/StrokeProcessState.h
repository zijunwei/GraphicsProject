#pragma once
#include "myStroke.h"
#include "ParamBox.h"
#include "ImageData.h"
#include <vector>
class StrokeProcessState
{
public:
	StrokeProcessState();
	~StrokeProcessState();
	void updateState(ParamBox);
public:
	ParamBox curParam;
	ParamBox prevParam;
	ImageData * imgData;
	std::vector<myStroke> StrokeList;

};

