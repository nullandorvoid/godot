#include "accessiblePopup.h"
#include "print_string.h"
#include "accessibleWindow.h"

AccessiblePopup::AccessiblePopup(Variant popup)
	:AccessibleControl(popup, 0)
{
	AddNotableSignal("enter_tree");
	AddNotableSignal("exit_tree");

	if ((bool)getNode().call("is_inside_tree")) {
		initializePopup();
	}
}


AccessiblePopup::~AccessiblePopup()
{
	if ((bool)getNode().call("is_inside_tree")) {
		endPopup();
	}
}

bool AccessiblePopup::hasValue()
{
	return false;
}

String AccessiblePopup::getValue()
{
	return "";
}

LONG AccessiblePopup::getRole()
{
	return ROLE_SYSTEM_DIALOG;
}

bool AccessiblePopup::hasDefaultAction()
{
	return false;
}

String AccessiblePopup::getDefaultAction()
{
	return "";
}

bool AccessiblePopup::doDefaultAction()
{
	return false;
}

bool AccessiblePopup::hasKeyboardShortcut()
{
	return false;
}

String AccessiblePopup::getKeyboardShortcut()
{
	return String();
}

void AccessiblePopup::setValue(const String &)
{
}

void AccessiblePopup::OnSignal(const String& signal)
{
	AccessibleControl::OnSignal(signal);

	if (signal == "enter_tree") {
		initializePopup();
	}
	else if (signal == "exit_tree") {
		endPopup();
	}
}


void AccessiblePopup::initializePopup()
{
	sendWinEvent(EVENT_SYSTEM_DIALOGSTART);

	FOREACH_CHILD(child, AccessibleWindow::GetGlobalWindow()) {
		if (this == child || (bool)getNode().call("is_a_parent_of", child->getNode())) {
			child->setVisibility(getVisibilityReason(), true);
		}
		else {
			child->setVisibility(getVisibilityReason(), false);
		}
	}
}

void AccessiblePopup::endPopup()
{
	sendWinEvent(EVENT_SYSTEM_DIALOGEND);

	FOREACH_CHILD(child, AccessibleWindow::GetGlobalWindow()) {
		child->setVisibility(getVisibilityReason(), true);
	}
}

String AccessiblePopup::getVisibilityReason()
{
	return getName() + "_overlay";
}
