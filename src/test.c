#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "lib/mad_obj.h"
#include "lib/mad_vec.h"

size_t ERROR = 0;
#define ASSERT(f, fmt, ...) do {\
    if (!(f)) {\
      ERROR++; \
      printf("ERROR (%s): "fmt"\n", __func__, __VA_ARGS__);\
    } \
  } while(0)


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
test_obj_init(void)
{
  size_t index = 0;
  mad_obj_init(1, &index);
  ASSERT(
    index != 0,
    "%s\n", "Initialization of object did not set returned index correctly."
  );
}

void
test_obj_init_multiple(void)
{
  size_t num_objects = 5;
  size_t indexes[num_objects+1];
  size_t overwrite_control = 1872938;
  indexes[num_objects] = overwrite_control;
  mad_obj_init(num_objects, indexes);
  for (size_t ii=1; ii<num_objects; ii++) {
    size_t distance = indexes[ii] - indexes[ii-1];
    ASSERT(
      distance == 1,
      "Length between index %zu and %zu was not 1: %zu.",
      ii, ii-1, distance
    );
  }
  ASSERT(
    indexes[num_objects] == overwrite_control,
    "%s\n", "Control value overwritten at end of object index list."
  );
}

void
test_obj_translate(void)
{
  size_t index = 0;
  mad_obj_init(1, &index);
  struct vec3 pos = {{{0, 0, 1}}};
  mad_obj_translate(index, pos);
  ASSERT(
    eq_vec3(mad_obj_pos(index), pos),
    "%s", "Object not at 0,0,1 after translation."
  );
}

int
main(void)
{
  test_obj_init();
  test_obj_init_multiple();
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
