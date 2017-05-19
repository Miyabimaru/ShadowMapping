#include "IShader.h"

IShader::~IShader()
{
}

ShaderProgram * IShader::getShaderProgram()
{
	return _shaderProgram;
}