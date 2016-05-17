#pragma once

#include "BufferView.h"

class TextureView : BufferView
{

private:
	GLubyte *m_texBuffer;
	cv::Mat m_texMat;
	GLuint m_textureID;

public:
	TextureView(int width, int height, GLuint textureID);

	virtual bool ShowBufferView(bool show);
	virtual bool UpdateBufferView();

};