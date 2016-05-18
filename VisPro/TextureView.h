#pragma once

#include "BufferView.h"

class TextureView : public BufferView
{

protected:
	GLubyte *m_texBuffer;
	cv::Mat m_texMat;
	GLuint m_textureID;
	GLuint m_textureUnitID;

public:
	TextureView(int width, int height, GLuint textureID, GLuint textureUnitID);

protected:
	virtual cv::Mat ReadBufferToMatrix();
};