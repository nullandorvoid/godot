#include "accessible.h"


Accessible::Accessible()
{
}


Accessible::~Accessible()
{
}

void Accessible::_bind_methods() {
	ObjectTypeDB::bind_method("assign", &Accessible::node_set_stub);
	ObjectTypeDB::bind_method("clear", &Accessible::void_stub);
	ObjectTypeDB::bind_method("get_name", &Accessible::string_get_stub);
	ObjectTypeDB::bind_method("set_name", &Accessible::string_set_stub);
	ObjectTypeDB::bind_method("get_value", &Accessible::string_get_stub);
	ObjectTypeDB::bind_method("set_value", &Accessible::string_set_stub);
	ObjectTypeDB::bind_method("get_shortcut", &Accessible::string_get_stub);
	ObjectTypeDB::bind_method("set_shortcut", &Accessible::string_set_stub);
	ObjectTypeDB::bind_method("set_using_popup", &Accessible::bool_set_stub);
	ObjectTypeDB::bind_method("_on_signal", &Accessible::string_set_stub);
}

void Accessible::node_set_stub(Node * n)
{
}

void Accessible::void_stub()
{
}

void Accessible::string_set_stub(const String &)
{
}

String Accessible::string_get_stub()
{
	return String();
}

void Accessible::bool_set_stub(bool)
{
}
