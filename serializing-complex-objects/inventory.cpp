#include "inventory.h"

Inventory::Inventory(int mainInvRows, int mainInvCols)
{
  this->mainInvRows = mainInvRows;
  this->mainInvCols = mainInvCols;

  // resize mainInventory to correct size (rows * cols)
	mainInvItems.resize(mainInvRows);
	for (int i = 0; i < mainInvRows; i++)
	{
		mainInvItems[i].resize(mainInvCols);
	}
}

int Inventory::getNumUsedSlots()
{
  int num_used = 0;
  for (int i = 0; i < mainInvRows; i++)
  {
    for (int j = 0; j < mainInvCols; j++)
    {
      if (mainInvItems[i][j].itemType != ItemType::NONE)
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
  cout << "Inventory Size: " << mainInvRows << "x" << mainInvCols << endl;

  ItemStack curr_stack;

  // print slot information
  for (int i = 0; i < mainInvRows; i++)
  {
    for (int j = 0; j < mainInvCols; j++)
    {
      curr_stack = mainInvItems[i][j];
      if (curr_stack.itemType != ItemType::NONE && curr_stack.size)
      {
        cout << "(" << i << ", " << j << "): " << curr_stack.size << " of " <<
          ITEM_NAMES[static_cast<int>(curr_stack.itemType)] << endl;
      }
    }
  }
  cout << "Done" << endl;
}

int Inventory::serialize(char bytes[], int maxSize)
{
  int used_slots = getNumUsedSlots();

  // calculate number of bytes required, and make sure it's less than or equal
  // to the provided maxSize
	int reqd_bytes = 3 + 4 * used_slots;

  if (reqd_bytes > maxSize)
  {
    // NOTE: in practice we'd probably want to define a special exception type.
    // Or, we could have this method return -1 to indicate failure.
    throw runtime_error("Not enough space to serialize inventory");
  }

  // save inventory dimensions
	bytes[0] = (char) mainInvRows;
	bytes[1] = (char) mainInvCols;
  bytes[2] = (char) used_slots;

  int curr_index = 3;
  ItemStack to_save;

  // save mainInventory slots
  for (int i = 0; i < mainInvRows; i++)
  {
    for (int j = 0; j < mainInvCols; j++)
    {
      to_save = mainInvItems[i][j];

      // serialize item slot if it isn't empty
      // NOTE: putting to_save.size in an if-statement is the same as writing
      // to_save.size != 0. Here we're checking that it has a valid ItemType and
      // size is not equal to zero
      if (to_save.itemType != ItemType::NONE && to_save.size)
      {
        bytes[curr_index + 0] = (char) i;
        bytes[curr_index + 1] = (char) j;
        bytes[curr_index + 2] = (char) to_save.itemType;
        bytes[curr_index + 3] = (char) to_save.size;
        cout << int(bytes[curr_index]) << " " << int(bytes[curr_index + 1]) << " " << int(bytes[curr_index + 2]) << " " << int(bytes[curr_index + 3]) << endl;
      }

      curr_index += 4;
    }
  }

  return reqd_bytes;
}

Inventory* Inventory::deserialize(char bytes[], int numBytes)
{
	// retrieve data on inventory size, and number of stacks saved
	int main_rows = (int) bytes[0];
	int main_cols = (int) bytes[1];
	int num_stacks = (int) bytes[2];
  cout << "Deserialize wants " << num_stacks << " stacks and has " << numBytes << endl;
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
    cout << "curr_index is " << curr_index << endl;
    cout << int(bytes[curr_index]) << " " << int(bytes[curr_index + 1]) << " " << int(bytes[curr_index + 2]) << " " << int(bytes[curr_index + 3]) << endl;

    int stack_row = (int) bytes[curr_index + 0];
    int stack_col = (int) bytes[curr_index + 1];
		item_type = ItemType(bytes[curr_index + 2]);
		int stack_size = (int) bytes[curr_index + 3];

    // set inventory slot at given row/col
    inventory->mainInvItems[stack_row][stack_col] = ItemStack(item_type, stack_size);

    // increment curr_index to the next serialized slot
    curr_index += 4;
  }

	return inventory;
}
