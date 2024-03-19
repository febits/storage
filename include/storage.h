#ifndef STORAGE_H
#define STORAGE_H

#include <stdbool.h>
#include "types.h"

#define STORAGEMAX 100000

enum product_type {
  APPLIANCES,
  CLOTCHES,
  BOOKS,
  TOOLS
};

enum filter_type {
  PRICE_FILTER,
  TYPE_FILTER,
  FREESHIPPING_FILTER
};

struct product {
  u64 id;
  f64 price;
  char *name;
  bool free_shipping; 

  enum product_type type;
};

struct filter {
  enum filter_type type;

  union {
    f64 price;
    bool free_shipping;
    enum product_type type;
  } value;

  bool (*handle)(const struct product *p, struct filter);
};


struct storage {
  struct product *products[STORAGEMAX];
  u64 product_count;
};

#endif
