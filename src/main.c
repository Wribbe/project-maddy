#include <stdlib.h>
#include <stdio.h>
#include "lib/mad_obj.h"
#include "lib/mad_window.h"
#include "lib/mad_render.h"

int
main(void)
{
  size_t obj = 0;
  mad_obj_init(1, &obj);
  mad_obj_create_triangle(obj);

  struct window window = window_create(800, 600, "Window Title");

  for(;;) {
    render();
  }
}
