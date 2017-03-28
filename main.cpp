#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <GL/glew.h>
#include <GL/glut.h>

#include "BinaryFileReader.h"
#include "TextureManager.h"
#include "Shader.h"
#include "UserInput.h"
#include "Mat4x4.h"
#include "Vector4.h"
#include "ShaderBucky.h"

Shader *shader;
UserInput *g_input;
Mat4x4 * viewPosMatrix;;

float viewPos[] = {0.f, 0.f, 5.0f};
float viewPosDist = -1.0f;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,0.01,100);
	glMatrixMode(GL_MODELVIEW);

}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	Vector4 viewPosv(viewPos[0], viewPos[1], viewPos[2]);
	Vector4 transformedViewPosv;
	if(viewPosMatrix != NULL && g_input != NULL) {
		g_input ->UpdateGlobalRotation();
		viewPosMatrix ->RotateX( g_input ->GetAngleX() );
		viewPosMatrix ->RotateY( g_input ->GetAngleY() );
		viewPosMatrix ->RotateZ( g_input ->GetAngleZ() );
		transformedViewPosv = (*viewPosMatrix) * viewPosv;
		viewPosMatrix ->SetIdentity();
		transformedViewPosv = transformedViewPosv * (g_input ->GetViewDistance() / viewPosDist);
	}
	// Check angleX,y,z.
	// Also check why transformedViewPosv doesn't change.
	gluLookAt(transformedViewPosv.p[0], transformedViewPosv.p[1], transformedViewPosv.p[2],
		0.0,0.0,0.0,
		0.0f,1.0f,0.0f);
/*	glBegin(GL_QUADS);
//		glColor3f(0.,0.,1.0f);
		glTexCoord2f(0., 0.);
		glVertex3f( -1.0f, -1.0f, 1.0f);
		glTexCoord2f(1., .0);
		glVertex3f( 1.0f,  -1.0f, 1.0f);
		glTexCoord2f(1., 1.);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0., 1.0);
		glVertex3f( -1.0f, 1.0f,  1.0f);
	glEnd();*/
	float ratio = 1.0f;
	glBegin(GL_QUADS);
	// Front Face
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1,.0f * ratio, .0f* ratio,  1.0f* ratio); glVertex3f(-1.0f, -1.0f,  1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio, 0.0f* ratio,  1.0f* ratio); glVertex3f( 1.0f, -1.0f,  1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio,  1.0f* ratio,  1.0f* ratio); glVertex3f( 1.0f,  1.0f,  1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f* ratio,  1.0f* ratio,  1.0f* ratio); glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f* ratio, 0.0f* ratio, 0.0f* ratio); glVertex3f(-1.0f, -1.0f, -1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f* ratio,  1.0f* ratio, 0.0f* ratio); glVertex3f(-1.0f,  1.0f, -1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio,  1.0f* ratio, 0.0f* ratio); glVertex3f( 1.0f,  1.0f, -1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio, 0.0f* ratio, 0.0f* ratio); glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f* ratio,  1.0f* ratio, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f,  1.0f* ratio,  1.0f* ratio); glVertex3f(-1.0f,  1.0f,  1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio,  1.0f* ratio,  1.0f* ratio); glVertex3f( 1.0f,  1.0f,  1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio,  1.0f* ratio, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f, 0.0f, 0.0f);  glVertex3f(-1.0f, -1.0f, -1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio, 0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio, 0.0f,  1.0f* ratio); glVertex3f( 1.0f, -1.0f,  1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f, 0.0f,  1.0f* ratio); glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio, 0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio,  1.0f* ratio, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio,  1.0f* ratio,  1.0f* ratio); glVertex3f( 1.0f,  1.0f,  1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f* ratio, 0.0f,  1.0f* ratio); glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f, 0.0f,  1.0f* ratio); glVertex3f(-1.0f, -1.0f,  1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f,  1.0f* ratio,  1.0f* ratio); glVertex3f(-1.0f,  1.0f,  1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f);  glMultiTexCoord3f(GL_TEXTURE1,0.0f,  1.0f* ratio, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
	glutSwapBuffers();
	glutPostRedisplay();
	shader ->ShaderFileChangeWatcher();
}


void processNormalKeys(unsigned char key, int x, int y) {
	if(g_input) {
		g_input ->Keyboard(key, x, y);
	}
}

void mouseDown(int button, int state, int x, int y) {
	if(g_input) {
		g_input ->Mouse(button, state, x, y);
	}
}

void mouseMotion(int x, int y) {
	if(g_input) {
		g_input ->MouseMotion(x, y);
	}
}

#define printOpenGLError() printOglError(__FILE__, __LINE__)

int printOglError(char *file, int line)
{
    //
    // Returns 1 if an OpenGL error occurred, 0 otherwise.
    //
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}

void InitGL()
{
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Volume Raycasting 3D");

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);
	glutMouseFunc(mouseDown);
	glutMotionFunc(mouseMotion);
	glewInit();

	glDisable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_3D);
	glEnable(GL_TEXTURE_2D);
	glClearColor(0., 0., 0., 1.);

	// Create Matrix for view point manipulation.
	if(viewPosMatrix == NULL) {
		viewPosMatrix = new Mat4x4();
	}
	viewPosDist = viewPos[0] * viewPos[0] + viewPos[1] * viewPos[1] + viewPos[2] * viewPos[2];
	viewPosDist = sqrt(viewPosDist);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	InitGL();
	if (glewIsSupported("GL_VERSION_2_0"))
		printf("Ready for OpenGL 2.0\n");
	else {
		printf("OpenGL 2.0 not supported\n");
		exit(1);
	}

	g_input = new UserInput(viewPos);
	shader = new ShaderBucky();
	shader ->setShaders("textureSimple.vert", "textureSimple.frag");
	glutMainLoop();

	return 0;
}

/*glBegin(GL_QUADS);
	// Front Face
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1,.0f, .0f,  1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f, 0.0f,  1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f,  1.0f,  1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f,  1.0f,  1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f,  1.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f,  1.0f, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f, 0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f,  1.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f,  1.0f,  1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f,  1.0f,  1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f,  1.0f, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f, 0.0f, 0.0f);  glVertex3f(-1.0f, -1.0f, -1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f, 0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f, 0.0f,  1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f, 0.0f,  1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f, 0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f,  1.0f, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f,  1.0f,  1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1, 1.0f, 0.0f,  1.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f, 0.0f,  1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f); glMultiTexCoord3f(GL_TEXTURE1,0.0f,  1.0f,  1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f);  glMultiTexCoord3f(GL_TEXTURE1,0.0f,  1.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();*/

	//glutSolidTeapot(1);