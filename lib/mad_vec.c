#include "lib/mad_vec.h"

bool
vec3_eq(struct vec3 a, struct vec3 b)
{
  for (size_t ii=0; ii<3; ii++) {
    if (a.v[ii] != b.v[ii]) {
      return false;
    }
  }
  return true;
}
