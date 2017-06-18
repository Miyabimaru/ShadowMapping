#pragma once

#ifndef _DEBUG_TEXTURE_H_
#define _DEBUG_TEXTURE_H_

#include "IDrawable.h"
#include "LightManager.h"

class DebugTexture : public IDrawable
{
private:
	GLuint VAO, VBO_position, VBO_normal, VBO_tex, IBO;
	LightManager * _lightManager;

public:
	DebugTexture(LightManager * lightManager);
	~DebugTexture();

	// Hérité via IDrawable
	virtual void Initialise(IShader * shader) override;
	virtual void Draw(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection) override;
	virtual void DrawDepth(glm::mat4 & model, glm::mat4 & view, glm::mat4 & projection, IShader * depthShader) override;
};

#endif // !_DEBUG_TEXTURE_H_
