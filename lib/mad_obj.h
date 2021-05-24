#ifndef MAD_OBJ_H
#define MAD_OBJ_H

#include <stdlib.h>
#include "lib/mad_vec.h"

#define NUM_OBJS 256

void mad_obj_init(size_t num_objects, size_t * ret_index);

void mad_obj_translate(size_t index, struct vec3 pos);

struct vec3 mad_obj_pos(size_t index);

#endif
