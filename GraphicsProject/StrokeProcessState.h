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
	void clearStrokeList();
	void visStrokePosition();
	void visFinalResults();
	void updatePramsOnly(ParamBox);
public:
	ParamBox curParam;
	ParamBox prevParam;
	ImageData * imgData;
	std::vector<myStroke> StrokeList;
	bool laterUpdate_graph = false;
	bool laterUpdate_size = false;

};

