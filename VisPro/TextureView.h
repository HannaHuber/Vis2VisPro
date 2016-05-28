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
	TextureView(int width, int height, const std::string &windowName, Channels channels, GLuint textureUnitID, GLuint textureID);

protected:
	virtual cv::Mat ReadBufferToMatrix();
};