#ifndef MAD_OBJ_H
#define MAD_OBJ_H

#include <stdlib.h>
#include <string.h>
#include "lib/mad_vec.h"

#define NUM_OBJS 256

void
mad_obj_init(size_t num_objects, size_t * ret_index);

void
mad_obj_translate(size_t index, struct vec3 pos);

struct vec3
mad_obj_pos(size_t index);

void
mad_obj_create_triangle(size_t index);

float *
obj_vertices(size_t index);

bool
floats_equals(float * a, float * b, size_t num_to_compare);

void
mad_obj_free(size_t index);

#endif
