#include "item_stack.h"

ItemStack::ItemStack()
{
  itemType = ItemType::NONE;
  size = 0;
}

ItemStack::ItemStack(ItemType itemType, int size)
{
  if (itemType == ItemType::NUM_TYPES)
  {
    throw runtime_error("Invalid ItemType");
  }
  
  this->itemType = itemType;
  this->size = size;
}
