#include "inventory.h"

Inventory::Inventory(int rows, int cols)
{
  this->rows = rows;
  this->cols = cols;

  // resize inventory to correct size (rows * cols)
	items.resize(rows);
	for (int i = 0; i < rows; i++)
	{
		items[i].resize(cols);
	}
}

int Inventory::getNumUsedSlots()
{
  int num_used = 0;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (items[i][j].itemType != ItemType::NONE && items[i][j].size)
      {
        num_used++;
      }
    }
  }
  return num_used;
}

void Inventory::printDebug()
{
  cout << "Printing Debug Information for Inventory " << this << endl;
  cout << "Inventory Size: " << rows << "x" << cols << endl;

  ItemStack curr_stack;

  // print slot information
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      curr_stack = items[i][j];

      // only print item slot if not empty. The ITEM_NAMES array comes from
      // item_type.h
      if (curr_stack.itemType != ItemType::NONE && curr_stack.size > 0)
      {
        cout << "(" << i << ", " << j << "): " << curr_stack.size << " of " <<
          Item::ITEM_NAMES[static_cast<int>(curr_stack.itemType)] << endl;
      }
    }
  }
  cout << "Done" << endl;
}

int Inventory::serialize(char buffer[], int maxSize)
{
  int used_slots = getNumUsedSlots();

  // calculate number of bytes required, and make sure it's less than or equal
  // to the provided maxSize
	int reqd_bytes = 3 + 4 * used_slots;

  if (reqd_bytes > maxSize)
  {
    // NOTE: in practice we'd probably want to define a special exception type.
    // Or, we could have this method return -1 to indicate failure. To keep it
    // simple, we'll just throw a runtime_error
    throw runtime_error("Not enough space to serialize inventory");
  }

  // save inventory dimensions
	bytes[0] = (char) rows;
	bytes[1] = (char) cols;
  bytes[2] = (char) used_slots;

  int curr_index = 3;
  ItemStack to_save;

  // save mainInventory slots
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      to_save = items[i][j];

      // serialize item slot if it isn't empty
      if (to_save.itemType != ItemType::NONE && to_save.size > 0)
      {
        bytes[curr_index + 0] = (char) i;
        bytes[curr_index + 1] = (char) j;
        bytes[curr_index + 2] = (char) to_save.itemType;
        bytes[curr_index + 3] = (char) to_save.size;

        curr_index += 4;
      }
    }
  }

  return reqd_bytes;
}

Inventory* Inventory::deserialize(char buffer[], int numBytes)
{
	// retrieve data on inventory size, and number of stacks saved
	int main_rows = (int) bytes[0];
	int main_cols = (int) bytes[1];
	int num_stacks = (int) bytes[2];

  // calculate the number of bytes an inventory with the given number of rows and
  // columns would need. Make sure we have that much data, and that we got at
  // least 3 bytes from the stream
  int reqd_bytes = 3 + 4 * num_stacks;
  if (numBytes < 3 || reqd_bytes != numBytes)
  {
    throw runtime_error("Invalid or missing serialized data");
  }

  // create Inventory object
  Inventory* inventory = new Inventory(main_rows, main_cols);

	int curr_index = 3;
  ItemType item_type;

  // retrieve stored stacks and add to inventory
	for (int i = 0; i < num_stacks; i++)
	{
    int stack_row = (int) bytes[curr_index + 0];
    int stack_col = (int) bytes[curr_index + 1];
		item_type = ItemType(bytes[curr_index + 2]);
		int stack_size = (int) bytes[curr_index + 3];

    // set inventory slot at given row/col
    inventory->items[stack_row][stack_col] = ItemStack(item_type, stack_size);

    // increment curr_index to the next serialized slot
    curr_index += 4;
  }

	return inventory;
}
