#pragma once

#include "TextureView.h"

class FrameBufferObjectView : public TextureView
{

private:
	//GLubyte *m_fboBuffer;
	//cv::Mat m_fboMat;
	GLuint m_fboID;

public:
	FrameBufferObjectView(int width, int height, const std::string &windowName, GLuint fboID, GLuint textureUnitID, GLuint textureID);

protected:
	virtual cv::Mat ReadBufferToMatrix();
};