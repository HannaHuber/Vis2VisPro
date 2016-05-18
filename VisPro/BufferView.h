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


class BufferView{

protected:
	std::string m_bufferWindowName = "buffer view";
	HWND m_bufferWindowHandle = nullptr;

	int m_width = 1024;
	int m_height = 800;

public:
	BufferView(int width, int height) : m_width(width), m_height(height)
	{

	}

	virtual bool ShowBufferView(bool show);

	virtual bool UpdateBufferView();

protected:
	virtual cv::Mat ReadBufferToMatrix() = 0;

};