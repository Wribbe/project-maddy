#include "lib/mad_obj.h"
#include "lib/mad_render.h"


void
render(void)
{
  for (size_t i=0; i<NUM_OBJS; i++) {
    printf("Object %zu is%sinitialized\n", i, objects[i].vertices == NULL ? " not " : " ");
  }
}
