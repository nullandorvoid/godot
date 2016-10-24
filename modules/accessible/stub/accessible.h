#ifndef ACCESSIBLE_STUB_H
#define ACCESSIBLE_STUB_H

#include "reference.h"
#include "variant.h"
#include "scene/main/node.h"

class Accessible : public Reference {
	OBJ_TYPE(Accessible, Reference);

protected:
	static void _bind_methods();

public:
	Accessible();
	~Accessible();

	void node_set_stub(Node* n);
	void void_stub();
	void string_set_stub(const String&);
	String string_get_stub();
	void bool_set_stub(bool);
};

#endif

