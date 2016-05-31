#pragma once

/** @file ZBufferView.h
*@brief Z buffer view base class file.
*/

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

/** Z buffer view.
  */
class ZBufferView : public BufferView{

private:
	float *m_depthValues;
	cv::Mat m_depthMat;
	cv::Mat m_grayMat;
	GLuint m_fboHandle;

public:
	/** Constructor.
	* @param width width of buffer
	* @param height height of buffer
	* @param windowName basic name part of OpenCV windows for viewing the buffer
	* @param fboHandle frame buffer object to extract z buffer
	*/
	ZBufferView(int width, int height, const std::string &windowName, GLuint fboHandle);

protected:
	virtual cv::Mat ReadBufferToMatrix();

};