#ifndef DRAWDATA_H_
#define DRAWDATA_H_

#include <GL/gl.h>

class Vertex {

 public:
  Vertex(double* vertex) {
    x_ = vertex[0];
    y_ = vertex[1];
    z_ = vertex[2];
  };

  Vertex() {
    x_ = 0;
    y_ = 0;
    z_ = 0;
  };

  Vertex(double x, double y, double z) {
    x_ = x;
    y_ = y;
    z_ = z;
  };

  Vertex operator+(const Vertex& obj) {
    Vertex tmp(0, 0, 0);
    tmp.x_ = x_ + obj.x_;
    tmp.y_ = y_ + obj.y_;
    tmp.z_ = z_ + obj.z_;
    return tmp;
  };

  Vertex operator-(const Vertex& obj) {
    Vertex tmp(0, 0, 0);
    tmp.x_ = x_ - obj.x_;
    tmp.y_ = y_ - obj.y_;
    tmp.z_ = z_ - obj.z_;
    return tmp;
  };

  double operator*(const Vertex& obj) {
    Vertex tmp(0, 0, 0);
    tmp.x_ = x_ * obj.x_;
    tmp.y_ = y_ * obj.y_;
    tmp.z_ = z_ * obj.z_;
    return (tmp.x_ + tmp.y_ + tmp.z_);
  };

  Vertex operator*(const double& a) {
    Vertex tmp(0, 0, 0);
    tmp.x_ = x_ * a;
    tmp.y_ = y_ * a;
    tmp.z_ = z_ * a;
    return tmp;
  }

  Vertex operator=(const Vertex& obj) {
    x_ = obj.x_;
    y_ = obj.y_;
    z_ = obj.z_;
  }
  

  double x_;
  double y_;
  double z_;
};

class VertexBuffer{

 public:
  
  const Vertex get_vertex(int idx) const;
  void insert_vertex(int idx, Vertex vertex);
  const char* get_vertex_name();
  void set_vertex_name(char *vertex_name);

 private:

  std::vector<Vertex> vertexs_;
  char *vertex_name_;

};

class IndexBuffer {

 public:

  const unsigned get_idx(int idx) const;
  void insert_idx(int idx, unsigned index);
  const char* get_index_name();
  void set_index_name(char *index_name);
  const unsigned get_idxs_size() const {
    return idxs_.size();
  };

 private:

  std::vector<unsigned> idxs_;
  char *index_name_;

}; 

class Batch {

 public:
  
  Batch(
	const VertexBuffer* vetexbuffer,
	const IndexBuffer* indexbuffer,
	const VertexBuffer* normalbuffer,
	const GLenum  mode,
	const char *batch_name);

  const VertexBuffer*  get_vertex_buffer() {
    return vertexbuffer_;
  };

  const IndexBuffer* get_index_buffer() {
    return indexbuffer_;
  };
  
  const VertexBuffer* get_normal_buffer() {
    return normalbuffer_;
  };

  const GLenum get_mode() {
    return mode_;
  };

  const char* get_batch_name() {
    return batch_name_;
  };
  
 private:
  
  const VertexBuffer *vertexbuffer_;
  const IndexBuffer *indexbuffer_;
  const VertexBuffer *normalbuffer_;
  const GLenum  mode_;
  const char *batch_name_;

};


class GraphicDatabase {

 public:
  unsigned get_num_batches();  
  void insert_batch(int idx, Batch *batch);
  Batch *get_batch(char *name);

 private:
  
  std::vector<Batch*> batches_;

};

class Model {

 public:

  Model(Batch *batch);
  void draw();
  
  Batch *batch_;
  double x_;
  double y_;
  double z_;
  
  double theta_;
  double rx_;
  double ry_;
  double rz_;
};



class Animation {

 public:

  Vertex tra_base_;
  Vertex rot_base_;
  Vertex sca_base_;
  double theta_base_;
  Vertex translates_[4];
  Vertex rotation_[4];
  Vertex scale_[4];
  double theta_[4];
  
  void set_animation(Vertex *translate, 
		     Vertex *rotation,
		     Vertex *scale,
		     double *theta);

};

class Node {

 public:

  enum State{
    STAND = 0,
    WALK,
    JUMP,
    NUMOFSTATES
  };

  State state_;
  std::vector<Node*> child_node_;
  int num_child_nodes_;
  Animation *animation_[NUMOFSTATES];
  void draw(int time);
  void set_state(State state);

};

#endif
