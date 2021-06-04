#include "lib/mad_obj.h"
#include "lib/macros.h"

size_t index_obj_first_free = 0;

struct mad_obj {
  struct vec3 coords;
  size_t num_vertices;
  float * vertices;
};

struct mad_obj objects[NUM_OBJS] = {0};

void
mad_obj_init(size_t num_objects, size_t * ret_index)
{
  for (size_t ii=0; ii<num_objects && ii<NUM_OBJS; ii++) {
    *ret_index++ = index_obj_first_free++;
  }
}

void
mad_obj_translate(size_t index, struct vec3 pos)
{
  objects[index].coords.x += pos.x;
  objects[index].coords.y += pos.y;
  objects[index].coords.z += pos.z;
}

struct vec3
mad_obj_pos(size_t index)
{
  return objects[index].coords;
}

bool
floats_equals(float * a, float * b, size_t num_to_compare)
{
  for (size_t ii=0; ii<num_to_compare; ii++) {
    if (a[ii] != b[ii]) {
      return false;
    }
  }
  return true;
}

void
mad_obj_create_triangle(size_t index)
{
  size_t size_triangle = 3*3*sizeof(float);
  objects[index].vertices = malloc(size_triangle);
  memset(objects[index].vertices, 0, size_triangle);
  if (objects[index].vertices == NULL) {
    FATAL("%s\n", "Failed to allocate memory for triangle vertices, aborting.");
  }
  float vertices_triangle[] = {
    -0.5f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
  };
  mad_obj_set_vertices(index, vertices_triangle, sizeof(vertices_triangle));
}

float *
obj_vertices(size_t index)
{
  return objects[index].vertices;
}

void
mad_obj_free(void * arg)
{
  size_t index = *((size_t *)arg);
  if (objects[index].vertices) {
    free(objects[index].vertices);
  }
}

void
mad_obj_set_vertices(size_t index, float * vertices, size_t size_vertices)
{
  if (objects[index].vertices != NULL) {
    free(objects[index].vertices);
    objects[index].vertices = NULL;
  }
  objects[index].vertices = malloc(size_vertices);
  if (objects[index].vertices == NULL) {
    FATAL("%s\n", "Could not allocate memory inside mad_obj_set_vertices");
  }
  memcpy(objects[index].vertices, vertices, size_vertices);
}
