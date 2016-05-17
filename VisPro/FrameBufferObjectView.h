#pragma once

#include "BufferView.h"

class FrameBufferObjectView : BufferView
{

private:
	GLubyte *m_fboBuffer;
	cv::Mat m_fboMat;
	GLuint m_fboID;

public:
	FrameBufferObjectView(int width, int height, GLuint fboID);

	virtual bool ShowBufferView(bool show);
	virtual bool UpdateBufferView();

};