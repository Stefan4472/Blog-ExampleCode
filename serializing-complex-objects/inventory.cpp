#include "inventory.h"

Inventory::Inventory(int mainInvRows, int mainInvCols, int hotbarSize)
{
  this->mainInvRows = mainInvRows;
  this->mainInvCols = mainInvCols;
  this->hotbarSize = hotbarSize;
  usedSlots = 0;

  // resize hotbar to correct size
	hotbarItems.resize(hotbarSize);

  // resize mainInventory to correct size (rows * cols)
	mainInvItems.resize(mainInvRows);
	for (int i = 0; i < mainInvRows; i++)
	{
		mainInvItems[i].resize(mainInvCols);
	}
}

void Inventory::addItemStack(ItemStack toAdd, int row, int col, bool inHotbar)
{
  if (inHotbar)
  {
    // bounds check
    if (row != 0 || col < 0 || col >= hotbarSize)
    {
      throw runtime_error("Hotbar index out of bounds (" + to_string(row) + ", " +
        to_string(col) + ")");
    }

    // add one to usedSlots if the current slot had no items in it
    if (hotbarItems[col].itemType == ItemType::NONE)
    {
      usedSlots++;
    }

    // set slot's ItemType and size to that of toAdd
    hotbarItems[col].itemType = toAdd.itemType;
    hotbarItems[col].size = toAdd.size;
  }
  else
  {
    // bounds check
    if (row < 0 || row >= mainInvRows || col < 0 || col >= mainInvCols)
    {
      throw runtime_error("MainInv index out of bounds (" + to_string(row) + ", " +
        to_string(col) + ")");
    }

    // add one to usedSlots if the current slot had no items in it
    if (mainInvItems[row][col].itemType == ItemType::NONE)
    {
      usedSlots++;
    }

    // set slot's ItemType and size to that of toAdd
    mainInvItems[row][col].itemType = toAdd.itemType;
    mainInvItems[row][col].size = toAdd.size;
  }
}

int Inventory::serialize(char bytes[], int maxSize)
{
  // calculate number of bytes required, and make sure it's less than or equal
  // to the provided maxSize
	int reqd_bytes = 4 + 4 * usedSlots;

  if (reqd_bytes > maxSize)
  {
    // NOTE: in practice we'd probably want to define a special exception type.
    // Or, we could have this method return 0 to indicate failure.
    throw runtime_error("Not enough space to serialize inventory");
  }

  // save inventory dimensions
	bytes[0] = (char) mainInvRows;
	bytes[1] = (char) mainInvCols;
  bytes[2] = (char) hotbarSize;
  bytes[3] = (char) reqd_bytes;

  // save hotbar slots first, then mainInventory slots
  int curr_index = 4;
  ItemStack to_save;

  for (int j = 0; j < hotbarSize; j++)
  {
    to_save = hotbarItems[j];
    bytes[curr_index + 0] = 0;
    bytes[curr_index + 1] = j;
    bytes[curr_index + 2] = char(to_save.itemType);
    bytes[curr_index + 3] = char(to_save.size);

    curr_index += 4;
  }

  return reqd_bytes;
}

Inventory* Inventory::restoreFromByteStream(char bytes[], int numBytes)
{
	printf("Restoring Inventory...\n");
	// retrieve data on inventory size, and number of stacks saved
	int main_rows = bytes[0];
	int main_cols = bytes[1];
	int num_stacks = bytes[2];

	// calculate position of hotbarSize and retrieve
	int hotbar_size = bytes[3 + 4 * num_stacks];
	printf("%d rows, %d cols, %d stacks, hotbar %d\n", main_rows, main_cols,
		num_stacks, hotbar_size);
	// TODO: HOW TO RETRIEVE SPRITE OWNER?
	Inventory* inventory = new Inventory(NULL, main_rows, main_cols, hotbar_size);

	// retrieve stored stacks and add
	int start_index;
	for (int i = 0; i < num_stacks; i++)
	{
		start_index = 3 + 4 * i;
		ItemType item_type = ItemType(bytes[start_index]);
		int stack_size = bytes[start_index + 1];
		int stack_row = bytes[start_index + 2];
		int stack_col = bytes[start_index + 3];
		printf("Item %d: %d of %s at %d, %d\n", i, stack_size,
			Item::getName(item_type).c_str(), stack_row, stack_col);
		inventory->addStack(ItemUtil::createStack(item_type, stack_size),
			InvCoordinate(stack_row, stack_col, false));
	}

	// restore hotbar
	start_index = 3 + 4 * num_stacks + 1;
	for (int j = 0; j < hotbar_size; j++)
	{
		ItemType item_type = ItemType(bytes[start_index]);
		int stack_size = bytes[start_index + 1];
		printf("Hotbar %d: %d of %s\n", j, stack_size, Item::getName(item_type).c_str());
		inventory->addStack(ItemUtil::createStack(item_type, stack_size),
			InvCoordinate(0, j, true));
		start_index += 2;
	}
	printf("Finished restoring\n");
	return inventory;
}
