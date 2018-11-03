#ifndef ITEM_TYPE_H
#define ITEM_TYPE_H

using namespace std;

// defines types of items recognized by the engine
enum class ItemType
{
  NONE,
  BREAD_LOAF,
  CHICKEN_LEG,
  CAN_OF_BEANS,
  GREEN_POTION,
  BASEBALL_BAT,
  SHORT_SWORD
};

namespace Item
{
  // item names corresponding to the ItemType enum. Used for debugging.
  const string ITEM_NAMES[7] =
  {
    "The NULL Item",
    "Bread Loaf",
    "Chicken Leg",
    "Can of Beans",
    "Green Potion",
    "Baseball Bat",
    "Short Sword"
  };
}

#endif
