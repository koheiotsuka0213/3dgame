#include <fstream>
#include <iostream>
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <vector>
#include "bmp.h"
#include "ObjectDraw.h"

void ObjectDraw::set_texture_id(GLuint t_id) {
  texture_id_ = t_id; 
}

GLuint ObjectDraw::get_texture_id() { 
  return texture_id_;
}

void ObjectDraw::draw_object() {
  // glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
  glBindTexture(GL_TEXTURE_2D, get_texture_id());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 105, 0, 105);
  

  double x;
  double y;
  double size = 0.25;
  switch (get_image_id()) {
  case PLAYER1: { 
    x = 0;
    y = 0.75;
    break;
  }
  case PLAYER2:
    x = 0.25;
    y = 0.75;
    break;
  case BOMB_UP:
    x = 0.50;
    y = 0.75;
    break;
  case FIRE_UP:
    x = 0.75;
    y = 0.75;
    break;
  case HORI_FIRE:
    x = 0;
    y = 0.50;
    break;
  case VER_FIRE:
    x = 0.25;
    y = 0.50;
    break;
  case ENEMY:
    x = 0.50;
    y = 0.50;
    break;
  case WALL:
    x = 0.75;
    y = 0.50;
    break;
  case BRICK:
    x = 0;
    y = 0.25;
    break;
  case FLOOR:
    x = 0.25;
    y = 0.25;
    break;
  case BOMB:
    x = 0.50;
    y = 0.25;
    break;
  case CROSS_FIRE:
    x = 0.75;
    y = 0.25;
    break;
  default:
    fprintf(stderr, "there is no such a object\n");
    break;
  }
  glBegin(GL_QUADS);
  glTexCoord2f(x, y); glVertex2i(get_vertex_x(), get_vertex_y());
  glTexCoord2f(x, y + size); glVertex2i(get_vertex_x(), get_vertex_y() + get_size());
  glTexCoord2f(x + size, y + size); glVertex2i(get_vertex_x() + get_size(), get_vertex_y() + get_size());
  glTexCoord2f(x + size, y); glVertex2i(get_vertex_x() + get_size(), get_vertex_y());
  glEnd();
 
  glDisable(GL_TEXTURE_2D);
  glFlush();
}

void ObjectDraw::set_image_id(ImageID img_id) {
  image_id_ = img_id;
}

ObjectDraw::ImageID ObjectDraw::get_image_id() { 
  return image_id_;
}

void ObjectDraw::set_vertex_x(int x) {
  vertex_x_ = x;
}

void ObjectDraw::set_vertex_y(int y) {
  vertex_y_ = y;
}

int ObjectDraw::get_vertex_x() {
  return vertex_x_;
}

int ObjectDraw::get_vertex_y() {
  return vertex_y_;
}

void ObjectDraw::set_size(int size) {
  size_ = size;
}

int ObjectDraw::get_size() {
  return size_;
}

void ObjectDraw::init_object(GLuint t_id, ImageID img_id, int x, int y, int size) {
  texture_id_ = t_id; 
  image_id_ = img_id;
  vertex_x_ = x;
  vertex_y_ = y;
  size_ = size;
}

void ObjectDraw::set_object(ImageID img_id, int x, int y) {
  image_id_ = img_id;
  vertex_x_ = x;
  vertex_y_ = y;
}
