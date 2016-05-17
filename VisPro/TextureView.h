#pragma once

#include "BufferView.h"

class TextureView : BufferView
{

private:
	GLubyte *m_texBuffer;
	cv::Mat m_texMat;
	GLuint m_textureID;
	GLuint m_textureUnitID;

public:
	TextureView(int width, int height, GLuint textureID, GLuint textureUnitID);

	virtual bool ShowBufferView(bool show);
	virtual bool UpdateBufferView();

};