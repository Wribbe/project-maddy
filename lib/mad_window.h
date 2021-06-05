#ifndef MAD_WINDOW_H
#define MAD_WINDOW_H

struct window {
  int mupp;
};

struct window
window_create(int width, int height, const char * title);

#endif
