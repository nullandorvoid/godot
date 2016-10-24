#include "platform\windows\os_windows.h"
#include "print_string.h"

#include "vector.h"

#include "accessibleProxy.h"
#include "accessibleWindow.h"

bool AccessibleProxy::_alive = true;
#define ALIVE_CHECK if (HRESULT result = checkAlive()) {return result;}
#define GlobalWindow AccessibleWindow::GetGlobalWindow()
#define CHILD_VERIFY(varChild) SELF_OR_CHILD_CHECK(varChild) if(!self && !GlobalWindow.HasChild(childIdx)){return E_INVALIDARG;} AccessibleBase* child = !self ? GlobalWindow.GetChild(childIdx) : NULL;


AccessibleProxy::AccessibleProxy()
{
	refCount = 1;
}

AccessibleProxy::~AccessibleProxy()
{
}

void AccessibleProxy::MarkDead() {
	_alive = false;
}

HRESULT AccessibleProxy::checkAlive()
{
	if (_alive) {
		return S_OK;
	}

	return RPC_E_DISCONNECTED;
}

HRESULT AccessibleProxy::QueryInterface(REFIID riid, void ** ppvObject)
{
	if (!ppvObject)
		return E_INVALIDARG;
	*ppvObject = NULL;

	if (riid == IID_IUnknown || riid == IID_IAccessible)
	{
		// Increment the reference count and return the pointer.
		*ppvObject = (LPVOID)this;
		AddRef();
		return S_OK;
	}
	return E_NOINTERFACE;
}

ULONG AccessibleProxy::AddRef(void)
{
	InterlockedIncrement(&refCount);
	return refCount;
}

ULONG AccessibleProxy::Release(void)
{
	// Decrement the object's internal counter.
	ULONG ulRefCount = InterlockedDecrement(&refCount);
	if (refCount == 0)
	{
		delete this;
	}
	return ulRefCount;
}

HRESULT AccessibleProxy::GetTypeInfoCount(UINT * pctinfo)
{
	*pctinfo = NULL;
	return E_NOTIMPL;
}

HRESULT AccessibleProxy::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo ** ppTInfo)
{
	*ppTInfo = 0;
	return E_NOTIMPL;
}

HRESULT AccessibleProxy::GetIDsOfNames(REFIID riid, LPOLESTR * rgszNames, UINT cNames, LCID lcid, DISPID * rgDispId)
{
	*rgDispId = 0;
	return E_NOTIMPL;
}

HRESULT AccessibleProxy::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS * pDispParams, VARIANT * pVarResult, EXCEPINFO * pExcepInfo, UINT * puArgErr)
{
	*pDispParams = { 0 };
	*pVarResult = { 0 };
	*pExcepInfo = { 0 };
	*puArgErr = 0;
	return E_NOTIMPL;
}

HRESULT AccessibleProxy::get_accParent(IDispatch ** ppdispParent)
{
	ALIVE_CHECK;
	POINTER_CHECK(ppdispParent);

	// Find our parent window
	HWND hWnd = GetParent(GetActiveWindow());
	if (hWnd)
	{
		// if we have a window attempt to get its IAccessible
		// pointer if available.
		AccessibleObjectFromWindow(hWnd, (DWORD)OBJID_CLIENT,
			IID_IAccessible, (void**)ppdispParent);

		return (*ppdispParent) ? S_OK : S_FALSE;
	}
	return S_OK;
}

HRESULT AccessibleProxy::get_accChildCount(long * pcountChildren)
{
	ALIVE_CHECK;
	POINTER_CHECK(pcountChildren);
		
	*pcountChildren = GlobalWindow.GetChildCount();
	return S_OK;
}

HRESULT AccessibleProxy::get_accChild(VARIANT varChild, IDispatch ** ppdispChild)
{
	ALIVE_CHECK;
	POINTER_CHECK(ppdispChild);

	*ppdispChild = NULL;

	if (varChild.vt != VT_I4) {
		return E_INVALIDARG;
	}

	return S_FALSE;
}

HRESULT AccessibleProxy::get_accName(VARIANT varChild, BSTR * pszName)
{
	ALIVE_CHECK;
	POINTER_CHECK(pszName);
	CHILD_VERIFY(varChild);

	if (self) {
		return S_FALSE;
	}
	else {		
		*pszName = SysAllocString(child->getFinalName().c_str());
		return S_OK;
	}
}

HRESULT AccessibleProxy::get_accValue(VARIANT varChild, BSTR * pszValue)
{
	ALIVE_CHECK;
	POINTER_CHECK(pszValue);
	CHILD_VERIFY(varChild);

	if (self) {
		return DISP_E_MEMBERNOTFOUND;
	}
	else {
		if (!child->hasFinalValue()) {
			return DISP_E_MEMBERNOTFOUND;
		}

		*pszValue = SysAllocString(child->getFinalValue().c_str());
		return S_OK;
	}
}

HRESULT AccessibleProxy::get_accDescription(VARIANT varChild, BSTR * pszDescription)
{
	ALIVE_CHECK;
	POINTER_CHECK(pszDescription);
	CHILD_VERIFY(varChild);

	if (self) {
		return DISP_E_MEMBERNOTFOUND;
	}
	else {
		*pszDescription = NULL;
		return S_FALSE;
	}
}

HRESULT AccessibleProxy::get_accRole(VARIANT varChild, VARIANT * pvarRole)
{
	ALIVE_CHECK;
	POINTER_CHECK(pvarRole);
	CHILD_VERIFY(varChild);

	if (self) {
		*pvarRole = AccessibleHelpers::CreateI4Variant(ROLE_SYSTEM_CLIENT);
		return S_OK;
	}
	else {		
		*pvarRole = AccessibleHelpers::CreateI4Variant(child->getRole());
		return S_OK;
	}
}

HRESULT AccessibleProxy::get_accState(VARIANT varChild, VARIANT * pvarState)
{
	ALIVE_CHECK;
	POINTER_CHECK(pvarState);
	CHILD_VERIFY(varChild);

	if (self) {
		*pvarState = AccessibleHelpers::CreateI4Variant(0);
		return S_OK;
	}
	else {		
		*pvarState = AccessibleHelpers::CreateI4Variant(child->getState());
		return S_OK;
	}
}

HRESULT AccessibleProxy::get_accHelp(VARIANT varChild, BSTR * pszHelp)
{
	ALIVE_CHECK;
	POINTER_CHECK(pszHelp);
	return DISP_E_MEMBERNOTFOUND;
}

HRESULT AccessibleProxy::get_accHelpTopic(BSTR * pszHelpFile, VARIANT varChild, long * pidTopic)
{
	ALIVE_CHECK;
	POINTER_CHECK(pidTopic);
	return DISP_E_MEMBERNOTFOUND;
}

HRESULT AccessibleProxy::get_accKeyboardShortcut(VARIANT varChild, BSTR * pszKeyboardShortcut)
{
	ALIVE_CHECK;
	POINTER_CHECK(pszKeyboardShortcut);
	CHILD_VERIFY(varChild);

	if (self) {
		return DISP_E_MEMBERNOTFOUND;
	}
	else {
		if (!child->hasFinalShortcut()) {
			return DISP_E_MEMBERNOTFOUND;
		}

		*pszKeyboardShortcut = SysAllocString(child->getFinalShortcut().c_str());
		return S_OK;
	}
}

HRESULT AccessibleProxy::get_accFocus(VARIANT * pvarChild)
{
	ALIVE_CHECK;
	POINTER_CHECK(pvarChild);

	// if we are the focused window then we return this interface.
	HWND hFocused = GetFocus();
	if (GetActiveWindow() == hFocused)
	{
		VARIANT variant = { 0 };
		V_VT(&variant) = VT_EMPTY;

		FOREACH_CHILD(child, GlobalWindow) {
			if (child->canGetKeyFocus() && child->hasKeyFocus()) {
				variant.vt = VT_I4;
				variant.llVal = child->getId();
				break;
			}
		}

		*pvarChild = variant;
	}
	else
	{
		// If we are not the focused window then we need to attempt to get the 
		// IDispatch pointer for the currently focused window from the window itself.
		//
		// Note, we can not always get an interface back. In the cases we can't, we
		// just return S_FALSE;
		pvarChild->vt = VT_DISPATCH;
		return AccessibleObjectFromWindow(hFocused, OBJID_WINDOW,
			IID_IAccessible, (void**)&pvarChild->pdispVal);

	}
	return S_OK;
}

HRESULT AccessibleProxy::get_accSelection(VARIANT * pvarChildren)
{
	ALIVE_CHECK;
	POINTER_CHECK(pvarChildren);

	*pvarChildren = { 0 };
	return DISP_E_MEMBERNOTFOUND;
}

HRESULT AccessibleProxy::get_accDefaultAction(VARIANT varChild, BSTR * pszDefaultAction)
{
	ALIVE_CHECK;
	POINTER_CHECK(pszDefaultAction);
	CHILD_VERIFY(varChild);

	if (self) {
		return DISP_E_MEMBERNOTFOUND;
	}
	else {
		if (!child->hasDefaultAction()) {
			return DISP_E_MEMBERNOTFOUND;
		}

		*pszDefaultAction = SysAllocString(child->getDefaultAction().c_str());
		return S_OK;
	}
}

HRESULT AccessibleProxy::accSelect(long flagsSelect, VARIANT varChild)
{
	ALIVE_CHECK;
	CHILD_VERIFY(varChild);

	if (self) {
		return DISP_E_MEMBERNOTFOUND;
	}
	else {		
		if (!child->canGetKeyFocus()) {
			return DISP_E_MEMBERNOTFOUND;
		}

		if (flagsSelect & SELFLAG_TAKEFOCUS) {
			child->forceKeyFocus();
			return S_OK;
		}
	}
}

HRESULT AccessibleProxy::accNavigate(long navDir, VARIANT varStart, VARIANT * pvarEndUpAt)
{
	ALIVE_CHECK;
	POINTER_CHECK(pvarEndUpAt);
	CHILD_VERIFY(varStart);

	*pvarEndUpAt = { 0 };
	AccessibleBase* neighborAcc = NULL;
	
	List<int> keys;
	GlobalWindow.GetAllKeys(&keys);

	if (self) {				
		switch (navDir) {
		case NAVDIR_FIRSTCHILD:			
			if (keys.size() > 0)
				neighborAcc = GlobalWindow.GetChild(keys.front());
		case NAVDIR_LASTCHILD:			
			if (keys.size() > 0)
				neighborAcc = GlobalWindow.GetChild(keys.back());
		case NAVDIR_PREVIOUS:
		case NAVDIR_NEXT:
		case NAVDIR_LEFT:
		case NAVDIR_RIGHT:
		case NAVDIR_UP:
		case NAVDIR_DOWN:
			return S_FALSE;
		}
	}
	else {
		Variant neighbor;
		int margin = 2;
		bool findFocusNeighbor = false;		
		switch (navDir) {
			case NAVDIR_FIRSTCHILD:
			case NAVDIR_LASTCHILD:		
				return S_FALSE;
			case NAVDIR_PREVIOUS:				
				if (keys.size() > 0) {
					List<int>::Element* element = keys.find(child->getId());
					if (element != NULL) {
						element = element->prev();

						if (element != NULL) {
							neighborAcc = GlobalWindow.GetChild(element);
						}
					}
				}
				break;
			case NAVDIR_NEXT:						
				if (keys.size() > 0) {
					List<int>::Element* element = keys.find(child->getId());
					if (element != NULL) {
						element = element->next();

						if (element != NULL) {
							neighborAcc = GlobalWindow.GetChild(element);
						}
					}
				}
				break;
			case NAVDIR_LEFT:				
				margin = 0;
				findFocusNeighbor = true;
				break;
			case NAVDIR_RIGHT:				
				margin = 2;
				findFocusNeighbor = true;
				break;
			case NAVDIR_UP:				
				margin = 1;
				findFocusNeighbor = true;
				break;
			case NAVDIR_DOWN:				
				margin = 3;
				findFocusNeighbor = true;
				break;
		}
		
		if (findFocusNeighbor) {
			Variant neighbor;
			try {
				Variant neighborPath = child->getNode().call("get_focus_neighbour", Variant(margin));
				neighbor = child->getNode().call("get_node", neighborPath);
			}
			catch (...) {
				return S_FALSE;
			}
		}

		if (neighborAcc == NULL)
			neighborAcc = GlobalWindow.FindChild(neighbor);
	}

	if (neighborAcc != NULL) {
		VARIANT variant = { 0 };
		V_VT(&variant) = VT_I4;
		variant.llVal = neighborAcc->getId();
		*pvarEndUpAt = variant;		
		return S_OK;
	}
	return S_FALSE;
}

HRESULT AccessibleProxy::accLocation(long * pxLeft, long * pyTop, long * pcxWidth, long * pcyHeight, VARIANT varChild)
{
	ALIVE_CHECK;
	POINTER_CHECK(pxLeft);
	POINTER_CHECK(pyTop);
	POINTER_CHECK(pcxWidth);
	POINTER_CHECK(pcyHeight);


	CHILD_VERIFY(varChild);

	if (self) {
		RECT loc;
		GetClientRect(GetActiveWindow(), &loc);

		*pxLeft = loc.left;
		*pyTop = loc.top;
		*pcxWidth = loc.right - loc.left;
		*pcyHeight = loc.bottom - loc.top;

		return S_OK;
	}
	else {
		RECT loc = child->getScreenRectLocation();

		//Return
		*pxLeft = loc.left;
		*pyTop = loc.top;
		*pcxWidth = loc.right - loc.left;
		*pcyHeight = loc.bottom - loc.top;

		return S_OK;
	}
}

HRESULT AccessibleProxy::accHitTest(long xLeft, long yTop, VARIANT * pvarChild)
{
	ALIVE_CHECK;
	POINTER_CHECK(pvarChild);

	HRESULT result = S_FALSE;

	*pvarChild = { 0 };
	V_VT(pvarChild) = VT_EMPTY;

	POINT coord;
	coord.x = xLeft;
	coord.y = yTop;
	ScreenToClient(GetActiveWindow(), &coord);

	Vector<AccessibleBase*> hitChildren;

	//Look for all children hit
	FOREACH_CHILD(child, GlobalWindow) {
		RECT loc = child->getClientRectLocation();

		bool inside = coord.x >= loc.left &&
			coord.x <= loc.right &&
			coord.y >= loc.top &&
			coord.y <= loc.bottom;

		if (inside) {
			hitChildren.push_back(child);
		}
	}

	//Now look for the highest of those children
	AccessibleBase* highestChild = NULL;
	for (size_t i = 0; i < hitChildren.size(); i++) {
		AccessibleBase* child = hitChildren[i];

		if ((bool)child->getNode().call("is_inside_tree") &&
			(highestChild == NULL || (bool)child->getNode().call("is_greater_than", highestChild->getNode()))) {
			highestChild = child;
		}
	}

	if (highestChild) {
		V_VT(pvarChild) = VT_I4;
		pvarChild->lVal = highestChild->getId();
		result = S_OK;
	}

	return result;
}

HRESULT AccessibleProxy::accDoDefaultAction(VARIANT varChild)
{
	ALIVE_CHECK;
	CHILD_VERIFY(varChild);

	if (self) {
		return DISP_E_MEMBERNOTFOUND;
	}
	else {
		if (!child->hasDefaultAction()) {
			return DISP_E_MEMBERNOTFOUND;
		}

		child->doDefaultAction();
		return S_OK;
	}
}

HRESULT AccessibleProxy::put_accName(VARIANT varChild, BSTR szName)
{
	return E_NOTIMPL;
}

HRESULT AccessibleProxy::put_accValue(VARIANT varChild, BSTR szValue)
{
	ALIVE_CHECK;
	CHILD_VERIFY(varChild);

	if (self) {
		return DISP_E_MEMBERNOTFOUND;
	}
	else {
		if (!child->hasFinalValue()) {
			return DISP_E_MEMBERNOTFOUND;
		}

		child->setFinalValue(String(szValue));
		return S_OK;
	}
}
