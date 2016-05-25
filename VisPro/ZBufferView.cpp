#include "ZBufferView.h"

ZBufferView::ZBufferView(int width, int height, const std::string &windowName, GLuint fboHandle) : BufferView(width, height, windowName), m_fboHandle(fboHandle)
{
	m_bufferWindowName = "Z buffer view: " + windowName;

	m_depthValues = new float[m_width * m_height];
	for (int i = 0; i < m_width*m_height; i++)
		m_depthValues[i] = 0;

	m_depthMat = cv::Mat(m_height, m_width, CV_32FC1, m_depthValues);
}

cv::Mat ZBufferView::ReadBufferToMatrix()
{
	//glReadBuffer(GL_FRONT);
	glReadBuffer(m_fboHandle);
	//glReadBuffer(GL_BACK);
	glReadPixels(0, 0, m_width, m_height, GL_DEPTH_COMPONENT, GL_FLOAT, m_depthValues);
	// make an OpenCV image
	cv::Mat depthMat(m_height, m_width, CV_32FC1, m_depthValues);
	//// is this necessary?
	//depthMat.copyTo(m_depthMat);
	cv::flip(depthMat, m_depthMat, 0);
	//cv::cvtColor(m_RGBMat, m_BGRMat, CV_RGB2BGR);

	// scale values from 0..1 to 0..255
	m_depthMat.convertTo(m_grayMat, CV_8UC1, 255, 0);

	//// check minimal and maximal value
	//double min, max;
	//cv::minMaxLoc(m_depthMat, &min, &max);

	return m_grayMat;
}