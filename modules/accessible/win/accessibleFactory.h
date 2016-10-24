#ifndef ACCESSIBLE_FACTORY_H
#define ACCESSIBLE_FACTORY_H

#include "reference.h"
#include "accessible.h"

class AccessibleFactory : public Reference {
	OBJ_TYPE(AccessibleFactory, Reference);

protected:
	static void _bind_methods();

public:
	Accessible* create(Node* n);
	Accessible* create_with_name(Node* n, const String& name);

	Accessible* recreate(Object* old, Node* n);
	Accessible* recreate_with_name(Object* old, Node* n, const String& name);

	Accessible* clear(Object* a);

	static AccessibleFactory* GetSingleton();
	static void ClearSingleton();

private:
	static AccessibleFactory* singleton;
};

#endif // !ACCESSIBLE_FACTORY_H
