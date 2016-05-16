#include "RGBBufferView.h"


RGBBufferView::RGBBufferView(int width, int height) : BufferView(width, height)
{
	m_bufferWindowName = "RGB buffer view";

	m_RGBValues = new byte[width*height * 3];

	for (int i = 0; i < m_width*m_height; i++)
		m_RGBValues[i] = 0;

	m_RGBMat = cv::Mat(m_height, m_width, CV_8UC3, m_RGBValues);
}


bool RGBBufferView::ShowBufferView(bool show)
{
	if (show)
	{
		if (m_bufferWindowHandle == nullptr)
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

			cv::namedWindow(m_bufferWindowName.c_str(), CV_WINDOW_AUTOSIZE);
			cv::imshow(m_bufferWindowName.c_str(), m_BGRMat);
			m_bufferWindowHandle = (HWND)cvGetWindowHandle(m_bufferWindowName.c_str());

		}

	}
	else
	{
		if (m_bufferWindowHandle != nullptr)
		{
			cvDestroyWindow(m_bufferWindowName.c_str());
			m_bufferWindowHandle = nullptr;
		}
	}

	return true;
}

bool RGBBufferView::UpdateBufferView()
{
	if (m_bufferWindowHandle != nullptr)
	{
		if (!IsWindowVisible(m_bufferWindowHandle))
		{
			// destroy handle
			cvDestroyWindow(m_bufferWindowName.c_str());
			m_bufferWindowHandle = nullptr;

			return false;
		}

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

		// is this the same window ?
		cv::imshow(m_bufferWindowName.c_str(), m_BGRMat);

		return true;

	}

}
