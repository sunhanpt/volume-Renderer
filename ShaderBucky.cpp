#include "ShaderBucky.h"


ShaderBucky::ShaderBucky(void)
	: Shader()
{
}


ShaderBucky::~ShaderBucky(void)
{
}

void ShaderBucky::setShaders(char * vertShader, char *fragShader)
{
	Shader::setShaders(vertShader, fragShader);
	TextureManager *tex = new TextureManager(this ->GetProgram());
	tex ->LoadTexture2DFromRAW("transfer.raw", 32, 32, true, "volumeLUT");
	tex ->LoadText3DFromFile("bucky.raw", 32, 32, 32, "volumeTexture");
	this ->UpdateUniform3fv("volumeSize", 2.0f, 2.0f, 2.0f);
	this ->UpdateUniform3fv("voxelSize", 32.0f, 32.0f, 32.0f);
	this ->UpdateUniform1f("raystep", 1.0f);
	this ->UpdateUniform1f("opticalScale", 1.0f);
	delete tex;
}