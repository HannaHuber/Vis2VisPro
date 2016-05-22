#include "BufferView.h"

bool BufferView::ShowBufferView(bool show)
{
	if (show)
	{
		if (m_bufferWindowHandle == nullptr)
		{
			cv::Mat texMat = ReadBufferToMatrix();

			cv::namedWindow(m_bufferWindowName.c_str(), CV_WINDOW_AUTOSIZE);
			cv::imshow(m_bufferWindowName.c_str(), texMat);
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

bool BufferView::UpdateBufferView()
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
		cv::Mat texMat = ReadBufferToMatrix();

		// is this the same window ?
		cv::imshow(m_bufferWindowName.c_str(), texMat);

		return true;

	}

	return false;

}