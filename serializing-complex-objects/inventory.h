#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <stdexcept>
#include "item_stack.h"

using namespace std;

/*
Simple inventory implementation. Has a main inventory with a given number of
rows and columns, which are stored as ItemStacks in a 2d vector. Has a hotbar
with a given number of slots, which are stored as ItemStacks in a 1d vector.

NOTE: THIS IS A SIMPLE DEMO. IT IS NOT MEANT TO BE GENIUS CODE!!!!
*/
class Inventory
{
  public:
    int mainInvRows, mainInvCols, hotbarSlots;
    vector<vector<ItemStack>> mainInvItems;
    vector<ItemStack> hotbarItems;
    int usedSlots;

    Inventory(int mainInvRows, int mainInvCols, int hotbarSize);

    void addItemStack(ItemStack toAdd, int row, int col, bool inHotbar);

    // save state to the given char array. Takes the array to be saved to, as
    // well as the maximum number of bytes it may use. Returns the number of
    // bytes that were actually written to the array.
    int serialize(char bytes[], int maxSize);
    // creates a new Inventory object by deserializing the given char[]. Also
    // given numBytes, which is the number of bytes the Inventory used to
    // serialize itself initially
		static Inventory* deserialize(char bytes[], int numBytes);
};
#endif
