#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "lib/mad_obj.h"
#include "lib/mad_vec.h"

size_t FAILED = 0;
size_t TESTS_TOTAL = 0;

#define MAD_ASSERT(f, fmt, ...) do {\
  if (!(f)) {\
    printf("ERROR (%s): "fmt"\n", __func__, __VA_ARGS__);\
    return EXIT_FAILURE; \
  } \
} while(0)

#define MAD_TEST_RUN(test_function) do { \
  TESTS_TOTAL++; \
  if (test_function() == EXIT_FAILURE){\
    FAILED++;\
  }\
} while(0)

int
test_obj_init(void)
{
  size_t index = 0;
  mad_obj_init(1, &index);
  MAD_ASSERT(
    index != 0,
    "%s\n", "Initialization of object did not set returned index correctly."
  );
  return EXIT_SUCCESS;
}

int
test_obj_init_multiple(void)
{
  size_t num_objects = 5;
  size_t indexes[num_objects+1];
  size_t overwrite_control = 1872938;
  indexes[num_objects] = overwrite_control;
  mad_obj_init(num_objects, indexes);
  for (size_t ii=1; ii<num_objects; ii++) {
    size_t distance = indexes[ii] - indexes[ii-1];
    MAD_ASSERT(
      distance == 1,
      "Length between index %zu and %zu was not 1: %zu.",
      ii, ii-1, distance
    );
  }
  MAD_ASSERT(
    indexes[num_objects] == overwrite_control,
    "%s\n", "Control value overwritten at end of object index list."
  );
  return EXIT_SUCCESS;
}

int
test_obj_translate(void)
{
  size_t index = 0;
  mad_obj_init(1, &index);
  struct vec3 pos = {{{0, 0, 1}}};
  mad_obj_translate(index, pos);
  MAD_ASSERT(
    vec3_eq(mad_obj_pos(index), pos),
    "%s", "Object not at 0,0,1 after translation."
  );
  return EXIT_SUCCESS;
}

int
main(void)
{

  MAD_TEST_RUN(test_obj_init);
  MAD_TEST_RUN(test_obj_init_multiple);
  MAD_TEST_RUN(test_obj_translate);

  const char * banner = "#################%s#################\n";
  printf(banner, "  TEST RESULTS   ");
  if (FAILED) {
    printf("  %zu/%zu of the tests fialed.\n", FAILED, TESTS_TOTAL);
  } else {
    printf("  All %zu tests passed without errors.\n", TESTS_TOTAL);
  }
  printf(banner, "#################");
}
