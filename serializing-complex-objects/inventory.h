#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <iostream>
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
    // TODO: RENAME TO ROWS, COLS
    int mainInvRows, mainInvCols;
    vector<vector<ItemStack>> mainInvItems;

    Inventory(int mainInvRows, int mainInvCols);

    // returns the number of ItemStacks in mainInvItems that are empty (have
    // ItemType::NONE). Iterates through mainInvItems, so it's O(m*n).
    // NOTE: we should really keep a "usedSlots" counter, but to keep this demo
    // simple we'll do it the not-so-efficient way
    int getNumUsedSlots();
    // prints size and contents of this inventory in a human-readable way
    void printDebug();

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
