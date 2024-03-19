// bool (*handle)(struct product, void *value);

#include <stdbool.h>
#include "storage.h"

bool price_filter_handler(const struct product *p, struct filter f) {
  return p->price >= f.value.price;
}

bool type_filter_handler(const struct product *p, struct filter f) {
  return p->type == f.value.type;
}

bool freeshipping_filter_handler(const struct product *p, struct filter f) {
  return p->free_shipping == f.value.free_shipping;
}
