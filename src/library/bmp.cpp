#include <fstream>
#include <iostream>
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

//#include "../../include/bmp.h"


//GLuint texName;

GLuint LoadBMP(const char *fileName)
{
	FILE *file;
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int size;
	unsigned int width, height;
	unsigned char *data;
	

	file = fopen(fileName, "rb");

	if (file == NULL)
	{
	  //		MessageBox(NULL, L"Error: Invaild file path!", L"Error", MB_OK);
		return false;
	}

	if (fread(header, 1, 54, file) != 54)
	{
	  //	MessageBox(NULL, L"Error: Invaild file!", L"Error", MB_OK);
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M')
	{
	  //	MessageBox(NULL, L"Error: Invaild file!", L"Error", MB_OK);
		return false;
	}

	dataPos		= *(int*)&(header[0x0A]);
	size		= *(int*)&(header[0x22]);
	width		= *(int*)&(header[0x12]);
	height		= *(int*)&(header[0x16]);

	if (size == NULL)
		size = width * height * 3;
	if (dataPos == NULL)
		dataPos = 54;

	data = new unsigned char[size];

	fread(data, 1, size, file);

	fclose(file);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	return texture;
}


/*
void disp( void ) {

  glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
  glBindTexture(GL_TEXTURE_2D, texName);

  glBegin(GL_QUADS);
  glTexCoord2f(-1, -1); glVertex2f(0, 0);
  glTexCoord2f(-1, 1); glVertex2f(0, 2);
  glTexCoord2f(1, 1); glVertex2f(2, 2);
  glTexCoord2f(1, -1); glVertex2f(2, 0);
  glEnd();
 
  glDisable(GL_TEXTURE_2D);
  glFlush();
}


int main(int argc , char ** argv){

  glutInit(&argc , argv);
  glutInitWindowSize(400 , 300);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Kitty on your lap");
  
  texName = LoadBMP("../image/folder.bmp");
  glutDisplayFunc(disp);
  glutMainLoop();
  return 0;
  }

*/

