#ifndef BOOLBLENDER_ACCESSIBLE_H
#define BOOLBLENDER_ACCESSIBLE_H

#include "hash_map.h"
#include "ustring.h"

class BoolBlender
{
public:
	BoolBlender();
	~BoolBlender();

	bool get();
	bool get(String channel);
	void set(String channel, bool value);
private:
	HashMap<String, bool> values;
};

#endif

