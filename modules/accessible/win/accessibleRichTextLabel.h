
#ifndef CONTROL_ACCESSIBLE_RICH_TEXT_LABEL_H
#define CONTROL_ACCESSIBLE_RICH_TEXT_LABEL_H

#include "accessibleControl.h"

class AccessibleRichTextLabel : public AccessibleControl
{
public:
	AccessibleRichTextLabel(Variant richTextLabel);
	virtual ~AccessibleRichTextLabel();

	// Inherited via AccessibleControl
	virtual bool hasValue() override;
	virtual String getValue() override;
	virtual LONG getRole() override;
	virtual bool hasDefaultAction() override;
	virtual String getDefaultAction() override;
	virtual bool doDefaultAction() override;
	virtual bool hasKeyboardShortcut() override;
	virtual String getKeyboardShortcut() override;
	virtual void setValue(const String &) override;
};

#endif