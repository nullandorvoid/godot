#ifndef ACCESSIBLE_WINDOW_H
#define ACCESSIBLE_WINDOW_H

#include "OleAcc.h"
#include "vector.h"

#include "accessibleHelpers.h"
#include "accessibleBase.h"

#define FOREACH_CHILD(child, AccessibleWindow) List<int> keys;AccessibleWindow.GetAllKeys(&keys);const List<int>::Element* key;AccessibleBase* child;for (key = keys.front(), child = AccessibleWindow.GetChild(key); key != NULL; key = key->next(), child = AccessibleWindow.GetChild(key))

class AccessibleWindow
{
public:
	AccessibleWindow();
	virtual ~AccessibleWindow();

	void AddChild(AccessibleBase* child);
	void RemoveChild(AccessibleBase* child);

	bool HasChild(int id);
	AccessibleBase* GetChild(int id);
	AccessibleBase* GetChild(const List<int>::Element* key);
	void GetAllKeys(List<int>* keys);
	size_t GetChildCount() {
		return children.size();
	}

	AccessibleBase* FindChild(Variant node);

	static AccessibleWindow& GetGlobalWindow() {
		if (!globalWindow) {
			globalWindow = new AccessibleWindow();
			NotifyWinEvent(EVENT_OBJECT_CREATE, GetActiveWindow(), OBJID_CLIENT, CHILDID_SELF);
		}

		return *globalWindow;
	}
	static void ClearGlobalWindow() {
		if (globalWindow) {
			NotifyWinEvent(EVENT_OBJECT_DESTROY, GetActiveWindow(), OBJID_CLIENT, CHILDID_SELF);
			delete globalWindow;
			globalWindow = NULL;
		}
	}
	private:
		static LRESULT AccessibleWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParams);

		static int lastId;

		Vector<AccessibleBase*> children;

		static AccessibleWindow* globalWindow;
};

#endif


