#ifndef ACCESSIBLE_HELPERS_H
#define ACCESSIBLE_HELPERS_H

#include "OleAcc.h"

#define VARCHILD_CHECK(varChild) if (HRESULT result = AccessibleHelpers::isSelf(varChild)) {return result;}
#define SELF_OR_CHILD_CHECK(varChild) bool self = false; int childIdx = 0; if (HRESULT result = AccessibleHelpers::isSelfAllowChildren(varChild, self, childIdx)) {return result;}
#define POINTER_CHECK(pointer) if (pointer == NULL) {return E_POINTER;}

namespace AccessibleHelpers {
	HRESULT isSelf(VARIANT varChild);
	HRESULT isSelfAllowChildren(VARIANT varChild, bool& isSelf, int& childIdx);
	VARIANT CreateI4Variant(LONG value);
}

#endif