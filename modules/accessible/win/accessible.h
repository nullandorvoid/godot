#ifndef ACCESSIBLE_H
#define ACCESSIBLE_H

#include "reference.h"
#include "scene/main/node.h"
#include "accessibleBase.h"
#include "accessibleWindow.h"

class Accessible : public Reference {
	OBJ_TYPE(Accessible, Reference);

protected:
	static void _bind_methods();

public:
	Accessible();
	~Accessible();
	void assign(Node* n);
	void clear();
	void set_name(const String&);
	String get_name();
	void set_value(const String&);
	String get_value();
	void set_shortcut(const String&);
	String get_shortcut();
	void set_using_popup(bool);
	
	void _on_signal(const String& Signals);
private:
	void disconnectSignals();
	void connectSignals();

	AccessibleBase* accessibleObj;
};

#endif // !ACCESSIBLE_H
