#include "boolBlender.h"



BoolBlender::BoolBlender()
{
}


BoolBlender::~BoolBlender()
{
}

bool BoolBlender::get()
{
	List<String> keys;
	values.get_key_list(&keys);

	const List<String>::Element* curKey = keys.front();
	while (curKey != NULL) {
		if (!values.get(curKey->get()))
			return false;

		curKey = curKey->next();
	}

	return true;
}

bool BoolBlender::get(String channel)
{
	if (!values.has(channel))
		return true;

	return values.get(channel);
}

void BoolBlender::set(String channel, bool value)
{
	if (value)
		values.erase(channel);
	else
		values.set(channel, value);
}
