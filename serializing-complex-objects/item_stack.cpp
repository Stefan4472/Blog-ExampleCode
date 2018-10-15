#include "item_stack.h"

ItemStack::ItemStack()
{
  itemType = ItemType::NONE;
  size = 0;
}

ItemStack::ItemStack(ItemType itemType, int size)
{
  this->itemType = itemType;
  this->size = size;
}
