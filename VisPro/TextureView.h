#pragma once

#include "BufferView.h"

class TextureView : BufferView
{

private:

public:
	TextureView(int width, int height) 
		: BufferView(width, height)
	{

	}

	virtual bool ShowBufferView(bool show);
	virtual bool UpdateBufferView();

};