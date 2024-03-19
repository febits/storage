#ifndef HANDLES_H
#define HANDLES_H

#include <stdbool.h>
#include "storage.h"

#define POS(id) (id % STORAGEMAX)

bool price_filter_handler(const struct product *p, struct filter f);
bool type_filter_handler(const struct product *p, struct filter f);
bool freeshipping_filter_handler(const struct product *p, struct filter f);

#endif
