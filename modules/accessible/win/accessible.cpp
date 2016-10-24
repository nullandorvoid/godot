#include "accessible.h"
#include "accessibleButton.h"
#include "accessibleTextureButton.h"
#include "accessibleOptionButton.h"
#include "accessibleRichTextLabel.h"
#include "accessibleLabel.h"
#include "accessiblePopup.h"
#include "accessibleGeneric.h"
#include "accessibleRange.h"
#include "accessibleLineEdit.h"

#include "scene\gui\control.h"
#include "scene\gui\button.h"
#include "scene\gui\texture_button.h"
#include "scene\gui\line_edit.h"
#include "scene\gui\option_button.h"
#include "scene\gui\rich_text_label.h"
#include "scene\gui\label.h"
#include "scene\gui\popup.h"

void Accessible::_bind_methods() {
	ObjectTypeDB::bind_method("assign", &Accessible::assign);
	ObjectTypeDB::bind_method("clear", &Accessible::clear);
	ObjectTypeDB::bind_method("get_name", &Accessible::get_name);
	ObjectTypeDB::bind_method("set_name", &Accessible::set_name);
	ObjectTypeDB::bind_method("get_value", &Accessible::get_value);
	ObjectTypeDB::bind_method("set_value", &Accessible::set_value);
	ObjectTypeDB::bind_method("get_shortcut", &Accessible::get_shortcut);
	ObjectTypeDB::bind_method("set_shortcut", &Accessible::set_shortcut);
	ObjectTypeDB::bind_method("set_using_popup", &Accessible::set_using_popup);
	ObjectTypeDB::bind_method("_on_signal", &Accessible::_on_signal);
}

Accessible::Accessible() {
	accessibleObj = 0;
}

Accessible::~Accessible() {
	clear();
}

void Accessible::connectSignals() {
	if (!accessibleObj)
		return;

	const Vector<String>& signals = accessibleObj->GetNotableSignals();
	for (int i = 0; i < signals.size(); i++) {
		Vector<Variant> binds;
		binds.push_back(String(signals[i]));

		((Object*)accessibleObj->getNode())->connect(signals[i], this, "_on_signal", binds);
	}
}

void Accessible::disconnectSignals() {
	if (!accessibleObj)
		return;

	const Vector<String>& signals = accessibleObj->GetNotableSignals();
	for (int i = 0; i < signals.size(); i++) {
		accessibleObj->getNode().call("disconnect", signals[i], this, "_on_signal");		
	}
}

void Accessible::clear() {
	if (accessibleObj) {
		disconnectSignals();		

		AccessibleWindow::GetGlobalWindow().RemoveChild(accessibleObj);
		delete accessibleObj;
		accessibleObj = 0;
	}
}

#define COMMA ,
#define CREATE_ACC(GodotControl, AccControl, PARAMS) if (GodotControl* control = dynamic_cast<GodotControl*>(node)) {accessibleObj = new AccControl(Variant(control) PARAMS);}
#define ECREATE_ACC(GodotControl, AccControl, PARAMS) else CREATE_ACC(GodotControl, AccControl, PARAMS)
void Accessible::assign(Node* node) {
	if (node) {
		clear();
		
		CREATE_ACC(OptionButton, AccessibleOptionButton)
		ECREATE_ACC(Button, AccessibleButton)
		ECREATE_ACC(TextureButton, AccessibleTextureButton)
		ECREATE_ACC(RichTextLabel, AccessibleRichTextLabel)
		ECREATE_ACC(Label, AccessibleLabel)
		ECREATE_ACC(Popup, AccessiblePopup)
		ECREATE_ACC(Range, AccessibleRange)
		ECREATE_ACC(LineEdit, AccessibleLineEdit)

		ECREATE_ACC(Control, AccessibleGeneric, COMMA 0 COMMA ROLE_SYSTEM_STATICTEXT)

			if (accessibleObj) {
				AccessibleWindow::GetGlobalWindow().AddChild(accessibleObj);
				connectSignals();
		}
	}
}

void Accessible::set_name(const String& val)
{
	if (accessibleObj) {
		accessibleObj->forceName(val);
	}
}

String Accessible::get_name() {
	if (accessibleObj)
		return accessibleObj->getFinalName();
	return "";
}

void Accessible::set_value(const String& val)
{
	if (accessibleObj) {
		accessibleObj->forceValue(val);
	}
}

String Accessible::get_value()
{
	if (accessibleObj) {
		return accessibleObj->getFinalValue();
	}
	return "";
}

void Accessible::set_shortcut(const String& val)
{
	if (accessibleObj) {
		accessibleObj->forceKeyboardShortcut(val);
	}
}

String Accessible::get_shortcut()
{
	if (accessibleObj) {
		return accessibleObj->getFinalShortcut();
	}
	return "";
}

void Accessible::set_using_popup(bool usingPopup)
{
	if (accessibleObj) {
		accessibleObj->setUsingPopup(usingPopup);
	}
}

void Accessible::_on_signal(const String& Signal)
{
	if (accessibleObj) {
		accessibleObj->OnSignal(Signal);		
	}
}