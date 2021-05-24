#ifndef MAD_VEC_H
#define MAD_VEC_H

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

#endif
