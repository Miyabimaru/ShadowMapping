#pragma once

#ifndef _DEBUG_TEXTURE_H_
#define _DEBUG_TEXTURE_H_

#include "IDrawable.h"

class DebugTexture : public IDrawable
{
public:
	DebugTexture();
	~DebugTexture();

	// Hérité via IDrawable
	virtual void Draw(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection) override;
	virtual void DrawDepth(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection, IShader * depthShader) override;
};

#endif // !_DEBUG_TEXTURE_H_
