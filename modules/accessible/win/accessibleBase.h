#ifndef BASE_ACCESSIBLE_H
#define BASE_ACCESSIBLE_H

#define ALIVE_CHECK if (HRESULT result = checkAlive()) {return result;}

#include "accessibleHelpers.h"
#include "OleAcc.h"
#include "variant.h"
#include "boolBlender.h"

class AccessibleBase
{
public:
	AccessibleBase(Variant node, LONG defaultState);
	virtual ~AccessibleBase();

	virtual String getName();
	void forceName(const String&);
	void clearForcedName();
	String getFinalName() { return forcingName ? forcedName : getName(); }

	inline LONG getState() { return state; }
	
	virtual RECT getClientRectLocation() = 0;
	RECT getScreenRectLocation();

	virtual bool hasValue() = 0;
	virtual String getValue() = 0;
	void forceValue(const String&);
	void clearForcedValue();
	bool hasFinalValue() { return hasValue() || forcingValue; }
	String getFinalValue() { return forcingValue ? forcedValue : getValue(); }
	void setFinalValue(const String& value) {
		if (forcingValue) {
			forcedValue = value;
		}
		else {
			setValue(value);
		}
	}

	virtual LONG getRole() = 0;

	virtual bool hasDefaultAction() = 0;
	virtual String getDefaultAction() = 0;
	virtual bool doDefaultAction() = 0;

	virtual bool hasKeyboardShortcut() = 0;
	virtual String getKeyboardShortcut() = 0;
	void forceKeyboardShortcut(const String&);
	void clearForcedKeyboardShortcut();
	bool hasFinalShortcut() { return hasKeyboardShortcut() || forcingKeyboardShortcut; }
	String getFinalShortcut() { return forcingKeyboardShortcut ? forcedKeyboardShortcut : getKeyboardShortcut(); }

	virtual bool canGetKeyFocus() = 0;
	virtual bool hasKeyFocus() = 0;
	virtual bool forceKeyFocus() = 0;

	void setUsingPopup(bool);

	void setId(int id) { ID = id; }
	int getId() { return ID; }

	Variant getNode() { return node; }

	const Vector<String>& GetNotableSignals() {
		return notableSignals;
	}
	virtual void OnSignal(const String& signal){}

	void setVisibility(String reason, bool visible);
protected:	
	virtual void setValue(const String&) = 0;
	void setState(LONG state);
	void addState(LONG state);
	void removeState(LONG state);
	
	void AddNotableSignal(const String& Signal);
	void sendWinEvent(DWORD msg);	
private:

	int ID;	

	Variant node;
	String name;
	LONG state;

	bool forcingName;
	String forcedName;

	bool forcingValue;
	String forcedValue;

	bool forcingKeyboardShortcut;
	String forcedKeyboardShortcut;

	Vector<String> notableSignals;

	BoolBlender visibilityController;
};

#endif


