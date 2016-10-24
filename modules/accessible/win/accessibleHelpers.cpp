#include "accessibleHelpers.h"

HRESULT AccessibleHelpers::isSelf(VARIANT varChild)
{
	if (V_VT(&varChild) != VT_I4) {
		return E_INVALIDARG;
	}
	if (V_I4(&varChild) != CHILDID_SELF) {
		return S_FALSE;
	}
	return S_OK;
}

HRESULT AccessibleHelpers::isSelfAllowChildren(VARIANT varChild, bool& isSelf, int& childIdx)
{
	isSelf = false;
	childIdx = 0;

	if (V_VT(&varChild) != VT_I4) {
		return E_INVALIDARG;
	}

	SHORT id = V_I4(&varChild);
	isSelf = id == CHILDID_SELF;
	childIdx = id;
	return S_OK;
}

VARIANT AccessibleHelpers::CreateI4Variant(LONG value)
{
	VARIANT variant = { 0 };

	V_VT(&variant) = VT_I4;
	V_I4(&variant) = value;

	return variant;
}