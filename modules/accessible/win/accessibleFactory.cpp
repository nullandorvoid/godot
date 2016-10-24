#include "accessibleFactory.h"

AccessibleFactory* AccessibleFactory::singleton = NULL;

AccessibleFactory* AccessibleFactory::GetSingleton() {
	if (!singleton) {
		singleton = memnew(AccessibleFactory);
	}
	return singleton;
}

void AccessibleFactory::ClearSingleton() {
	if (singleton) {
		memdelete(singleton);
	}
	singleton = NULL;
}

void AccessibleFactory::_bind_methods() {
	ObjectTypeDB::bind_method("create", &AccessibleFactory::create);
	ObjectTypeDB::bind_method("create_with_name", &AccessibleFactory::create_with_name);
	ObjectTypeDB::bind_method("recreate", &AccessibleFactory::recreate);
	ObjectTypeDB::bind_method("recreate_with_name", &AccessibleFactory::recreate_with_name);
	ObjectTypeDB::bind_method("clear", &AccessibleFactory::clear);
}

Accessible* AccessibleFactory::create(Node* n) {
	Accessible* acc = memnew(Accessible);
	acc->assign(n);
	return acc;
}
Accessible* AccessibleFactory::create_with_name(Node* n, const String& name) {
	Accessible* acc = create(n);
	acc->set_name(name);
	return acc;
}

Accessible * AccessibleFactory::recreate(Object * old, Node * n)
{
	clear(old);
	return create(n);
}

Accessible * AccessibleFactory::recreate_with_name(Object * old, Node * n, const String & name)
{
	clear(old);
	return create_with_name(n, name);
}

Accessible* AccessibleFactory::clear(Object* o) {	
	if (o == NULL)
		return NULL;

	Accessible* acc = dynamic_cast<Accessible*>(o);
	if (acc == NULL)
		return NULL;

	acc->clear();
	memdelete(acc);
	return NULL;
}