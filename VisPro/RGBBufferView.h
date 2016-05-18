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


class RGBBufferView : public BufferView{

private:

	byte *m_RGBValues;
	cv::Mat m_RGBMat;
	cv::Mat m_BGRMat;

public:
	RGBBufferView(int width, int height);

protected:
	virtual cv::Mat ReadBufferToMatrix();
};