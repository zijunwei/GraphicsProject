#include "stdafx.h"
#include "NUS.h"
#include "utils.h"

BOOL IfOverlap(cv::Point2i p1, cv::Point2i p2){
	if ( pow( abs(p1.x-p2.x),2) + pow( abs(p1.y-p2.y),2)< HALF_STROKE_SIZE* HALF_STROKE_SIZE)
	{
		return TRUE;
	}
	return FALSE;

}

void REORDER(std::vector<myStroke> & vA, std::vector<int>  vOrder)
{
	assert(vA->size() == vOrder->size());

	// for all elements to put in place
	for (int i = 0; i < vA.size() - 1; ++i)
	{
		// while the element i is not yet in place 
		while (i != vOrder[i])
		{
			// swap it with the element at its final place
			int alt = vOrder[i];
			std::swap(vA[i], vA[alt]);
			std::swap(vOrder[i], vOrder[alt]);
		}
	}
}

void NUS_Weibull(cv::Mat SaliencyImage, std::vector<myStroke> *StrokeList, ParamBox * Params)
{

	//create sampling probability map: the smaller the SampleProb(i,j), the lower Probability to be sampled
	cv::Mat SampleProb = SaliencyImage.clone();
	for (int i = 0; i < SaliencyImage.cols; i++)
	{
		for (int j = 0; j < SaliencyImage.rows; j++)
		{
			float s = SaliencyImage.at<float>(j, i);
			SampleProb.at<float>(j, i) = (float) 1 - exp(-pow((s / Params->mNon_Uniformity), Params->mDensity));
		}
	}
	//create stroke map on first run, if 
	std::vector<float>SaliencyScores;
	for (int i = 0; i < SampleProb.cols; i++)
	{
		for (int j = 0; j < SampleProb.rows; j++)
		{
			float s = rand() / (float)RAND_MAX;
			if (SampleProb.at<float>(j, i)>s)
			{
				myStroke tmpStroke;
				tmpStroke.StrokeLocation = cv::Point2i(i, j);
				StrokeList->push_back(tmpStroke);
				SaliencyScores.push_back(SampleProb.at<float>(j, i));
			}

		}
	}


	//sort from High saliency to Low saliency: Something Like NMS,
	std::vector<int> SortedScores(SaliencyScores.size());
	std::size_t n(0);
	std::generate(std::begin(SortedScores), std::end(SortedScores), [&]{ return n++; });

	std::sort(std::begin(SortedScores),
		std::end(SortedScores),
		[&](int i1, int i2) { return SaliencyScores[i1] > SaliencyScores[i2]; });

	REORDER(*StrokeList, SortedScores);

	//from END to TOP, delete Strokes if within radius..
	for ( int i = StrokeList->size()-1; i > 0;i--)
	{
		for (int j = 0; j < i;j++)
		{
			if (IfOverlap(StrokeList->at( (i) ).StrokeLocation,StrokeList->at((j)).StrokeLocation ))
			{
				StrokeList->erase(StrokeList->begin() + (i));
				break;
			}
		}
	}


	// If nothing was pruned away, it indicated that the current sampling might not be correct
	if (StrokeList->size() == SortedScores.size())
	{
		AfxMessageBox(_T("Density might be too small to cover the image"), MB_OK | MB_ICONSTOP);
	}



}
