#include "register_types.h"
#include "globals.h"
#include "object_type_db.h"

#ifdef FATP_ACCESSIBLE_WINDOWS
#include "win/accessible.h"
#include "win/accessibleFactory.h"
#else
#include "stub/accessible.h"
#include "stub/accessibleFactory.h"
#endif

void register_accessible_types() {
	Globals::get_singleton()->add_singleton(Globals::Singleton("AccessibleFactory", AccessibleFactory::GetSingleton()));
	 
	ObjectTypeDB::register_type<Accessible>();
}

void unregister_accessible_types() {
	AccessibleFactory::ClearSingleton();
}