#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "lib/mad_obj.h"

size_t ERROR = 0;
#define ASSERT(f, msg)\
  if (!f) {\
    ERROR++; \
    printf("ERROR (%s): ", __func__);\
    printf("%s\n", msg);\
  };

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


bool
eq_vec3(struct vec3 a, struct vec3 b)
{
  for (size_t ii=0; ii<3; ii++) {
    if (a.v[ii] != b.v[ii]) {
      return false;
    }
  }
  return true;
}

void
mad_obj_init(size_t num_objects, size_t * ret_index)
{
}

void
mad_obj_translate(size_t index, struct vec3 pos)
{
}

struct vec3
mad_obj_pos(size_t index)
{
  return (struct vec3){{{-1,-1,-1}}};
}

void
test_obj_translate(void)
{
  size_t index = 0;
  mad_obj_init(1, &index);
  struct vec3 pos = {{{0, 0, 1}}};
  mad_obj_translate(index, pos);
  ASSERT(eq_vec3(mad_obj_pos(index), pos), "Object not at 0,0,1 after translation.");
}

int
main(void)
{
  test_obj_translate();

  const char * banner = "#################%s#################\n";
  printf(banner, "  TEST RESULTS   ");
  if (ERROR) {
    printf("Test-suit failed %zu test.\n", ERROR);
  } else {
    printf("%s\n", "Test-suit succeeded without errors.");
  }
  printf(banner, "#################");
}
