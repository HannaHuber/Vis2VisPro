#include "ZBufferView.h"

//std::string ZBufferView::zBufferWindowName = "z Buffer image";
//HWND ZBufferView::zBufferWindowHandle = nullptr;


ZBufferView::ZBufferView(int width, int height) : BufferView(width, height)
{
	m_bufferWindowName = "Z buffer view";

	m_depthValues = new float[m_width * m_height];
	for (int i = 0; i < m_width*m_height; i++)
		m_depthValues[i] = 0;

	m_depthMat = cv::Mat(m_height, m_width, CV_32FC1, m_depthValues);
}


bool ZBufferView::ShowBufferView(bool show)
{
	if (show)
	{
		if (m_bufferWindowHandle == nullptr)
		{
			glReadBuffer(GL_FRONT);
			glReadPixels(0, 0, m_width, m_height, GL_DEPTH_COMPONENT, GL_FLOAT, m_depthValues);
			// make an OpenCV image
			cv::Mat depthMat(m_height, m_width, CV_32FC1, m_depthValues);
			//// is this necessary?
			//depthMat.copyTo(m_depthMat);
			cv::flip(depthMat, m_depthMat, 0);

			cv::namedWindow(m_bufferWindowName.c_str(), CV_WINDOW_AUTOSIZE);
			cv::imshow(m_bufferWindowName.c_str(), m_depthMat);
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

bool ZBufferView::UpdateBufferView()
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
		glReadPixels(0, 0, m_width, m_height, GL_DEPTH_COMPONENT, GL_FLOAT, m_depthValues);
		// make an OpenCV image
		cv::Mat depthMat(m_height, m_width, CV_32FC1, m_depthValues);
		//// is this necessary?
		//depthMat.copyTo(m_depthMat);
		cv::flip(depthMat, m_depthMat, 0);
		//cv::cvtColor(m_RGBMat, m_BGRMat, CV_RGB2BGR);


		//// check minimal and maximal value
		//double min, max;
		//cv::minMaxLoc(m_depthMat, &min, &max);

		// is this the same window ?
		cv::imshow(m_bufferWindowName.c_str(), m_depthMat);
		
		return true;

	}

}
