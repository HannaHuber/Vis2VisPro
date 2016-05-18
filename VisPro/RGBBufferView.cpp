#include "RGBBufferView.h"


RGBBufferView::RGBBufferView(int width, int height) : BufferView(width, height)
{
	m_bufferWindowName = "RGB buffer view";

	m_RGBValues = new byte[width*height * 3];

	for (int i = 0; i < m_width*m_height; i++)
		m_RGBValues[i] = 0;

	m_RGBMat = cv::Mat(m_height, m_width, CV_8UC3, m_RGBValues);
}

cv::Mat RGBBufferView::ReadBufferToMatrix()
{
	glReadBuffer(GL_FRONT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glReadPixels(0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, m_RGBValues);
	// make an OpenCV image
	cv::Mat rgbMat(m_height, m_width, CV_8UC3, m_RGBValues);
	//// is this necessary?
	//rgbMat.copyTo(m_RGBMat);
	cv::flip(rgbMat, m_RGBMat, 0);
	cv::cvtColor(m_RGBMat, m_BGRMat, CV_RGB2BGR);

	//// check minimal and maximal value
	//double min, max;
	//cv::minMaxLoc(m_RGBMat, &min, &max);

	return m_BGRMat;
}
