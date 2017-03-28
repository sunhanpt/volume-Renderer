#include "TextureManager.h"
#include "BuckyReader.h"
#include <stdlib.h>
#include <stdio.h>

TextureManager::TextureManager(GLuint p)
{
	this ->p = p;
	nTexture = 0;
}


TextureManager::~TextureManager(void)
{
}


// load a 256x256 RGB .RAW file as a texture
GLuint TextureManager::LoadTexture2DFromRAW( const char * filename, int width, int height, int wrap , const char * varInGLSL)
{
	GLuint texture;
	char * data;
	FILE * file;

	// open texture data
	file = fopen( filename, "rb" );
	if ( file == NULL ) return 0;

	// allocate buffer
	data = (char *) malloc( width * height * 3 );

	// read texture data
	fread( data, width * height * 3, 1, file );
	fclose( file );

	// allocate a texture name
	glGenTextures( 1, &texture );

	// select our current texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture( GL_TEXTURE_2D, texture );

	// select modulate to mix texture with color for shading
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	// when texture area is small, bilinear filter the closest MIP map
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_NEAREST );
	// when texture area is large, bilinear filter the first MIP map
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// if wrap is true, the texture wraps over at the edges (repeat)
	//       ... false, the texture ends at the edges (clamp)
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
		wrap ? GL_REPEAT : GL_CLAMP );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
		wrap ? GL_REPEAT : GL_CLAMP );

	// build our texture MIP maps
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width,
		height, GL_RGB, GL_UNSIGNED_BYTE, data );

	// texture Number update.
	GLint loc;
	loc = glGetUniformLocation(this ->p, varInGLSL);
	glUniform1i(loc, nTexture ++);

	// free buffer
	free( data );

	return texture;
}


GLuint TextureManager::LoadText3DFromFile(char * filename, int width, int height, int depth, const char * varInGLSL)
{
	BuckeyReader *reader = new BuckeyReader(filename);
	char *str = reader ->ReadData();
	return LoadTexture3DFromData(str, width, height, depth, varInGLSL);
}

GLuint TextureManager::LoadTexture3DFromData(char * texels, int width, int height, int depth, const char * varInGLSL)
{
	GLuint texname;
	// request 1 texture name from OpenGL
	glGenTextures(1, &texname);	

	// tell OpenGL we're going to be setting up the texture name it gave us	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_3D, texname);	
	// when this texture needs to be shrunk to fit on small polygons, use linear interpolation of the texels to determine the color
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// when this texture needs to be magnified to fit on a big polygon, use linear interpolation of the texels to determine the color
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// we want the texture to repeat over the S axis, so if we specify coordinates out of range we still get textured.
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// same as above for T axis
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// same as above for R axis
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	// this is a 3d texture, level 0 (max detail), GL should store it in RGB8 format, its WIDTHxHEIGHTxDEPTH in size, 
	// it doesnt have a border, we're giving it to GL in RGB format as a series of unsigned bytes, and texels is where the texel data is.
	glTexImage3D(GL_TEXTURE_3D, 0, /*GL_RGB8*/ 1, width, height, depth, 0, GL_RED, GL_UNSIGNED_BYTE, texels);

	GLint loc ;
	loc = glGetUniformLocation(this ->p, varInGLSL);
	glUniform1i(loc, 1);

	return texname;
}