#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "lib/mad_obj.h"
#include "lib/mad_vec.h"
#include "lib/macros.h"

size_t FAILED = 0;
size_t TESTS_TOTAL = 0;

#define ASSERT(f, fmt, ...) do {\
  if (!(f)) {\
    printf("ERROR (%s): "fmt"\n", __func__, __VA_ARGS__);\
    CLEANUP();\
    return EXIT_FAILURE; \
  } \
} while(0)

#define TEST_RUN(test_function) do { \
  TESTS_TOTAL++; \
  if (test_function() == EXIT_FAILURE){\
    FAILED++;\
  }\
} while(0)

typedef void(cleanup_function)(void * arg);

#define HANDLERS_NUM_MAX 256
size_t handlers_first_free = 0;

struct cleanup_handler {
  cleanup_function * f;
  void * arg;
};

struct cleanup_handler cleanup_handlers[HANDLERS_NUM_MAX] = {0};

void
CLEANUP_PUSH(cleanup_function f, size_t index)
{
  cleanup_handlers[handlers_first_free].f = f;
  size_t * arg = malloc(sizeof(index));
  *arg = index;
  cleanup_handlers[handlers_first_free].arg = arg;
  handlers_first_free++;
}

void
CLEANUP(void)
{
  for(;handlers_first_free > 0; handlers_first_free--) {
    struct cleanup_handler handler = cleanup_handlers[handlers_first_free-1];
    handler.f(handler.arg);
    free(handler.arg);
  }
}

int
test_obj_init(void)
{
  size_t index = 4;
  mad_obj_init(1, &index);
  ASSERT(
    index == 0,
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
  return EXIT_SUCCESS;
}

int
test_obj_translate(void)
{
  size_t index = 0;
  mad_obj_init(1, &index);
  struct vec3 pos = {{{0, 0, 1}}};
  mad_obj_translate(index, pos);
  ASSERT(
    vec3_eq(mad_obj_pos(index), pos),
    "%s", "Object not at 0,0,1 after translation."
  );
  return EXIT_SUCCESS;
}

int
test_create_triangle(void)
{
  float expected[] = {
    -0.5f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
  };
  size_t obj_index = 0;
  mad_obj_init(1, &obj_index);
  mad_obj_create_triangle(obj_index);
  CLEANUP_PUSH(mad_obj_free, obj_index);
  ASSERT(
    floats_equals(obj_vertices(obj_index), expected, MAD_LEN(expected)),
    "%s", "Did not get a correct triangle from 'mad_obj_create_triangle'"
  );
  CLEANUP();
  return EXIT_SUCCESS;
}

int
main(void)
{
  TEST_RUN(test_obj_init);
  TEST_RUN(test_obj_init_multiple);
  TEST_RUN(test_obj_translate);
  TEST_RUN(test_create_triangle);

  const char * banner = "#################%s#################\n";
  printf(banner, "  TEST RESULTS   ");
  if (FAILED) {
    printf("  %zu test out of %zu failed.\n", FAILED, TESTS_TOTAL);
  } else {
    printf("  All %zu tests passed without errors.\n", TESTS_TOTAL);
  }
  printf(banner, "#################");
}
