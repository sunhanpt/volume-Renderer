#pragma once
#include <GL/glew.h>

class TextureManager
{
private:
	GLuint p;
	int nTexture;
public:
	TextureManager(GLuint p);
	~TextureManager(void);

	// load a 256x256 RGB .RAW file as a texture
	GLuint LoadTexture2DFromRAW( const char * filename, int width, int height, int wrap , const char * varInGLSL);
	GLuint LoadText3DFromFile(char * filename, int width, int height, int depth, const char * varInGLSL);
	GLuint LoadTexture3DFromData(char * texels, int width, int height, int depth, const char * varInGLSL);
};

