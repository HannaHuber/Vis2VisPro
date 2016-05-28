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


enum Channels {RGB, RG_B, R_G_B, R, G, B};

class BufferView{

protected:
	std::string m_bufferWindowName = "buffer view";
	//HWND m_bufferWindowHandle = nullptr;
	std::vector<std::tuple<HWND, std::string>> m_bufferWindowHandles;

	int m_width = 1024;
	int m_height = 800;

	Channels m_channels;

public:
	BufferView(int width, int height, const std::string &windowName, Channels channels = Channels::RGB) : m_width(width), m_height(height), m_bufferWindowName(windowName), m_channels(channels)
	{
		m_bufferWindowName = "buffer view: " + windowName;
	}

	virtual bool ShowBufferView(bool show);

	virtual bool UpdateBufferView();

protected:
	virtual cv::Mat ReadBufferToMatrix() = 0;

	virtual std::vector<std::tuple<cv::Mat, std::string>> SplitMatrixToChannels(const cv::Mat &rgbMat);
	virtual std::string GetBufferWindowChannelName(const std::string &channelName);

};