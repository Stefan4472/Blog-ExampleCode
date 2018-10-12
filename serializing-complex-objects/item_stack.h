#ifndef ITEM_STACK_H
#define ITEM_STACK_H

#include <stdexcept>
#include "item_type.h"

/*
Super simple ItemStack implementation. Just defined by a ItemType and a
stack size.
*/
class ItemStack
{
  public:
    ItemType itemType;
    int size;

    // create an empty stack
    ItemStack();
    // create an item stack with given ItemType and size
    ItemStack(ItemType itemType, int size);
};

#endif
