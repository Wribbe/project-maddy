#include "lib/mad_obj.h"

int xs[NUM_OBJS];
int ys[NUM_OBJS];
int zs[NUM_OBJS];

size_t index_obj_error = 0;
size_t index_obj_first_free = 1;

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
  xs[index] += pos.x;
  ys[index] += pos.y;
  zs[index] += pos.z;
}

struct vec3
mad_obj_pos(size_t index)
{
  return (struct vec3){{{xs[index], ys[index], zs[index]}}};
}
