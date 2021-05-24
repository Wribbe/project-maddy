#ifndef MAD_VEC_H
#define MAD_VEC_H

#include <stdlib.h>
#include <stdbool.h>

struct vec3 {
  union {
    struct {
      int x;
      int y;
      int z;
    };
    int v[3];
  };
};


bool vec3_eq(struct vec3 a, struct vec3 b);

#endif
