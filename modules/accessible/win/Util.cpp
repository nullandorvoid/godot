#include "Util.h"

int32_t index = 0;
String Util::GetUniqueName(String name) {
	return name + String("_") + itos(index++);
}