#include "storage.h"
#include "handles.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A Generic function to handle filter types

static const char *products_type_str[] = {"Appliances", "Clotches", "Books",
                                          "Tools"};
static const char *filter_type_str[] = {"Price Filter", "Type Filter",
                                        "Free Shipping Filter"};

#define BOOLEANSTR(b) (b ? "True" : "False")
#define SIZE(array) (sizeof(array) / sizeof(array[0]))
#define PREFIX "\t\t"

#define PRODUCTTYPESTR(pt) (products_type_str[pt])
#define FILTERTYPESTR(ft) (filter_type_str[ft])

bool add_product(struct storage *s, struct product *p) {
  if (s->product_count > STORAGEMAX)
    return false;

  s->products[POS(p->id)] = p;
  s->product_count++;

  return true;
}

void list_product(const struct product *p) {
  printf("\n\t%s:\n", p->name);
  printf(PREFIX "ID: %lX\n", p->id);
  printf(PREFIX "Price: $%.2f\n", p->price);
  printf(PREFIX "Free Shipping: %s\n", BOOLEANSTR(p->free_shipping));
  printf(PREFIX "Type: %s\n", PRODUCTTYPESTR(p->type));
}

void list_products(const struct storage *s) {
  printf(">> Products: %lu\n", s->product_count);
  for (int i = 0; i < STORAGEMAX; i++) {
    if (s->products[i]) {
      list_product(s->products[i]);
    }
  }
}

bool is_product_in_filters(const struct product *p,
                           const struct filter filter_list[],
                           u8 filter_list_len) {
  u8 counter = 0;

  for (int i = 0; i < filter_list_len; i++) {
    if (filter_list[i].handle(p, filter_list[i]))
      counter++;
  }

  return counter == filter_list_len;
}

void list_by_filter(const struct storage *s, const struct filter filter_list[],
                    u8 filter_list_len) {
  printf("\n>> Applying filters - Listing the products by filters bellow:\n");
  for (int i = 0; i < filter_list_len; i++) {
    printf("\t%s: %.2f - %s\n", FILTERTYPESTR(filter_list[i].type),
           filter_list[i].value.price,
           PRODUCTTYPESTR(filter_list[i].value.type));
  }

  for (int i = 0; i < STORAGEMAX; i++) {
    if (s->products[i]) {
      if (is_product_in_filters(s->products[i], filter_list, filter_list_len))
        list_product(s->products[i]);
    }
  }
}

int main(int argc, char **argv) {

  struct storage store = {{NULL}, 0};
  for (int i = 0; i < STORAGEMAX; i++) {
    store.products[i] = NULL;
  }

  struct product samples[] = {
      {0xf7f7f7, 1280.0f, "Fridge", true, APPLIANCES},
      {0xc8f666, 120.0f, "Axe", false, TOOLS},
      {0xd889c1, 50.0f, "Hammer", false, TOOLS},
      {0xe12e11, 500.0f, "Microwave", true, APPLIANCES},
      {0xd98f55, 300.0f, "White Board", false, TOOLS},
      {0xb3105c, 2000.0f, "Air Conditioning", true, APPLIANCES},
      {0xa456c1, 180.0f, "The C Programming Language", false, BOOKS},
      {0xa66fcb, 200.0f, "Linux Device Drivers", false, BOOKS},
      {0xffffff, 3000.0f, "Laptop", true, APPLIANCES},
      {0xcccccc, 50.0f, "Shirt", false, CLOTCHES},
      {0xbbbbbb, 100.0f, "Jeans", false, CLOTCHES},
      {0xaaaaaa, 120.0f, "Sweater", false, CLOTCHES},
      {0xeeeeee, 30.0f, "Shorts", false, CLOTCHES},
      {0xdddddd, 70.0f, "Beanie", false, CLOTCHES},
      {0xedf139, 2500.0f, "iPhone XR", true, APPLIANCES},
      {0xd155ff, 40.0f, "Wrench", false, TOOLS}};

  for (int i = 0; i < SIZE(samples); i++) {
    add_product(&store, &samples[i]);
  }

  list_products(&store);

  struct filter flist1[] = {
      {PRICE_FILTER, .value.price = 120.0f, price_filter_handler},
      {TYPE_FILTER, .value.type = APPLIANCES, type_filter_handler},
      {FREESHIPPING_FILTER, .value.free_shipping = true,
       freeshipping_filter_handler}};

  list_by_filter(&store, flist1, SIZE(flist1));

  struct filter flist2[] = {
      {PRICE_FILTER, .value.price = 1000.0f, price_filter_handler},
      {FREESHIPPING_FILTER, .value.free_shipping = true,
       freeshipping_filter_handler}};

  list_by_filter(&store, flist2, SIZE(flist2));

  struct filter flist3[] = {
      {TYPE_FILTER, .value.type = CLOTCHES, type_filter_handler}};

  list_by_filter(&store, flist3, SIZE(flist3));

  struct filter flist4[] = {
      {TYPE_FILTER, .value.type = TOOLS, type_filter_handler}};

  list_by_filter(&store, flist4, SIZE(flist4));

  struct filter flist5[] = {
    {TYPE_FILTER, .value.type = BOOKS, type_filter_handler},
    {PRICE_FILTER, .value.price = 100.0f, price_filter_handler}
  };

  list_by_filter(&store, flist5, SIZE(flist5));

  return EXIT_SUCCESS;
}
