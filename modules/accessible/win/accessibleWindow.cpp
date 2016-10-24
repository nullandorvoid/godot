#include "platform\windows\os_windows.h"
#include "print_string.h"

#include "accessibleWindow.h"
#include "accessibleProxy.h"

int AccessibleWindow::lastId = CHILDID_SELF;
AccessibleWindow* AccessibleWindow::globalWindow = NULL;

AccessibleBase* ChildFromKey(List<int>::Element* key, HashMap<int, AccessibleBase*> children) {
	if (key == NULL) {
		return NULL;
	}
	return children.get(key->get());
}
//#define FOREACH(child, children) List<int> keys; children.get_key_list(&keys); List<int>::Element* key; AccessibleBase* child; for (key = keys.front(), child = ChildFromKey(key, children); key != NULL; key = key->next(), child = ChildFromKey(key, children))
int IDToIndex(int ID) { return ID - 1; }
int IndexToID(int Index) { return Index + 1; }
void ResetIds(const Vector<AccessibleBase*>& Acc) {
	for (int i = 0; i < Acc.size(); i++) {
		Acc[i]->setId(IndexToID(i));
	}
}

AccessibleWindow::AccessibleWindow()
{
	OS_Windows::set_wnd_proc_callback(AccessibleWindowProc);
}

AccessibleWindow::~AccessibleWindow()
{
}

void AccessibleWindow::AddChild(AccessibleBase * child)
{
	if (child != 0) {
		/*do { lastId++; } while (lastId == CHILDID_SELF);

		child->setId(lastId);
		children.set(lastId, child);

		NotifyWinEvent(EVENT_OBJECT_CREATE, GetActiveWindow(), OBJID_CLIENT, child->getId());
		print_line(String("Object added - ID: ") + itos(lastId) + " - Name: " + child->getFinalName());*/

		children.push_back(child);
		ResetIds(children);

		NotifyWinEvent(EVENT_OBJECT_CREATE, GetActiveWindow(), OBJID_CLIENT, child->getId());
		//print_line(String("Object added - ID: ") + itos(child->getId()) + " - Name: " + child->getFinalName());
	}
}

void AccessibleWindow::RemoveChild(AccessibleBase * child)
{
	if (child != 0) {
		children.remove(IDToIndex(child->getId()));
		ResetIds(children);

		NotifyWinEvent(EVENT_OBJECT_DESTROY, GetActiveWindow(), OBJID_CLIENT, child->getId()); 
		//print_line(String("Object removed"));
		/*if (children.erase(child->getId())) {
			NotifyWinEvent(EVENT_OBJECT_DESTROY, GetActiveWindow(), OBJID_CLIENT, child->getId());
			print_line(String("Object removed"));
		}*/
	}
}

bool AccessibleWindow::HasChild(int id) {
	//return children.has(id);
	int index = IDToIndex(id);
	return index >= 0 && index < GetChildCount();
}

AccessibleBase* AccessibleWindow::GetChild(int id) {
	if (!HasChild(id)) {
		return NULL;
	}

	return children.get(IDToIndex(id));
}

AccessibleBase* AccessibleWindow::GetChild(const List<int>::Element* key) {
	if (key == NULL) {
		return NULL;
	}
	return GetChild(key->get());
}

void AccessibleWindow::GetAllKeys(List<int>* keys) {	
	//children.get_key_list(keys);	
	keys->clear();
	for (int i = 0; i < GetChildCount(); i++)
		keys->push_back(IndexToID(i));
}

AccessibleBase * AccessibleWindow::FindChild(Variant node)
{
	FOREACH_CHILD(child, (*this)) {
		if (child->getNode() == node) {
			return child;
		}
	}

	return NULL;
}

LRESULT AccessibleWindow::AccessibleWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_GETOBJECT:
		if ((DWORD)lParam == (DWORD)OBJID_CLIENT) {			
			AccessibleProxy* proxy = new AccessibleProxy();
			if (proxy != NULL) {
				LRESULT result = LresultFromObject(IID_IAccessible, wParam, proxy);
				proxy->Release();
				return result;
			}
			return 0;
		}
		break;
	case WM_DESTROY:
		AccessibleProxy::MarkDead();
		AccessibleWindow::ClearGlobalWindow();
		break;
	}
	return 0;
}