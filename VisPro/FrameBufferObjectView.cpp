#include "FrameBufferObjectView.h"


FrameBufferObjectView::FrameBufferObjectView(int width, int height, GLuint fboID) : BufferView(width, height), m_fboID(fboID)
{
	char _Dest[99];
	_itoa(fboID, _Dest, 10);
	std::string fboIDStr = std::string(_Dest);
	m_bufferWindowName = "frame buffer object view " + fboIDStr;

	m_fboBuffer = new GLubyte[m_width*m_height * 3];
	for (int i = 0; i < m_width*m_height * 3; i++)
		m_fboBuffer[i] = 0;

	m_fboMat = cv::Mat(m_height, m_width, CV_8UC3, m_fboBuffer);
}


bool FrameBufferObjectView::ShowBufferView(bool show)
{
	if (show)
	{
		if (m_bufferWindowHandle == nullptr)
		{
			// TODO: backup current used fbo
			// void glActiveTexture(GLenum texture);

			// setup fbo reading
			glReadBuffer(GL_FRONT); // ???
			// bind fbo
			glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);
			// get frame buffer data
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glReadPixels(0, 0, m_width, m_height, GL_BGR, GL_UNSIGNED_BYTE, m_fboBuffer);

			// TODO: restore fbo
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			// make an OpenCV image
			cv::Mat fboMat(m_height, m_width, CV_8UC3, m_fboBuffer);
			//// is this necessary?
			//fboMat.copyTo(m_fboMat);
			cv::flip(fboMat, m_fboMat, 0);

			cv::namedWindow(m_bufferWindowName.c_str(), CV_WINDOW_AUTOSIZE);
			cv::imshow(m_bufferWindowName.c_str(), m_fboMat);
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

bool FrameBufferObjectView::UpdateBufferView()
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
		// TODO: backup current used fbo
		// void glActiveTexture(GLenum texture);

		// setup fbo reading
		glReadBuffer(GL_FRONT); // ???
		// bind fbo
		glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);
		// get frame buffer data
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glReadPixels(0, 0, m_width, m_height, GL_BGR, GL_UNSIGNED_BYTE, m_fboBuffer);

		// TODO: restore fbo
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// make an OpenCV image
		cv::Mat fboMat(m_height, m_width, CV_8UC3, m_fboBuffer);
		//// is this necessary?
		//fboMat.copyTo(m_fboMat);
		cv::flip(fboMat, m_fboMat, 0);

		cv::imshow(m_bufferWindowName.c_str(), m_fboMat);

		return true;

	}

}
