#pragma once
#include "shader.h"
#include "TextureManager.h"

class ShaderBucky :
	public Shader
{
public:
	ShaderBucky(void);
	virtual ~ShaderBucky(void);
	virtual void setShaders(char * vertShader, char *fragShader);
};
