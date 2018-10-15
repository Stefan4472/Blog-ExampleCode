// Demo serialization/deserialization using an example of a simple "Inventory" object
// Compilation: g++ main.cpp item_stack.cpp inventory.cpp -o test_inventory -std=c++11
// Execution: ./test_inventory

#include "inventory.h"
#include "item_stack.h"

using namespace std;

// function declarations (implementations below main)
Inventory* createDemoInventory();
bool testSerialize();
bool testDeserialize();

const int STREAM_BUFFER_SIZE = 400;

int main()
{
  Inventory* test_inv = createDemoInventory();

  // print inventory state
  test_inv->printDebug();

  char serial_buffer[STREAM_BUFFER_SIZE];

  // serialize to the buffer and record the number of bytes it used
  int saved_bytes = test_inv->serialize(serial_buffer, STREAM_BUFFER_SIZE);
  cout << "Used " << saved_bytes << endl;
  
  // delete the original inventory object
  delete test_inv;
  test_inv = NULL;

  // deserialize back into the buffer
  Inventory* deserialized = Inventory::deserialize(serial_buffer, saved_bytes);

  // print debug again and compare to original
  deserialized->printDebug();

  // delete the deserialized inventory object
  delete deserialized;
  deserialized = NULL;
}

// creates a new Inventory with 10 item stacks. Remember to delete it when finished!
Inventory* createDemoInventory()
{
  Inventory* inv = new Inventory(3, 8);

  inv->mainInvItems[0][0] = ItemStack(ItemType::BREAD_LOAF, 15);
  inv->mainInvItems[0][1] = ItemStack(ItemType::BREAD_LOAF, 7);
  inv->mainInvItems[0][2] = ItemStack(ItemType::CHICKEN_LEG, 6);
  inv->mainInvItems[0][6] = ItemStack(ItemType::CHICKEN_LEG, 8);
  inv->mainInvItems[1][3] = ItemStack(ItemType::CAN_OF_BEANS, 12);
  inv->mainInvItems[1][6] = ItemStack(ItemType::CAN_OF_BEANS, 5);
  inv->mainInvItems[1][7] = ItemStack(ItemType::GREEN_POTION, 3);
  inv->mainInvItems[2][1] = ItemStack(ItemType::GREEN_POTION, 2);
  inv->mainInvItems[2][2] = ItemStack(ItemType::BASEBALL_BAT, 1);
  inv->mainInvItems[2][4] = ItemStack(ItemType::SHORT_SWORD, 1);

  return inv;
}
