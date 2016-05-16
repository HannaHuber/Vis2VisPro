#pragma once

// Standard
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

#include "StringHelpers.hpp"
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\features2d\features2d.hpp>
#include <opencv2\nonfree\features2d.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\nonfree\nonfree.hpp>

#include <Windows.h> 
#include <opencv2\highgui\highgui_c.h>

#include <glew.h>

#include "BufferView.h"


class ZBufferView : public BufferView{

private:
	float *m_depthValues;
	cv::Mat m_depthMat;
	cv::Mat m_grayMat;

public:
	ZBufferView(int width, int height);

	virtual bool ShowBufferView(bool show);

	virtual bool UpdateBufferView();

};