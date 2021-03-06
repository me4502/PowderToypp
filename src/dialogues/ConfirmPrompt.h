/*
 * ConfirmPrompt.h
 *
 *  Created on: Apr 6, 2012
 *      Author: Simon
 */

#ifndef CONFIRMPROMPT_H_
#define CONFIRMPROMPT_H_

#include "interface/Window.h"

class ConfirmDialogueCallback;
class ConfirmPrompt: public ui::Window {
public:
	enum DialogueResult { ResultCancel, ResultOkay };
	ConfirmPrompt(std::string title, std::string message, ConfirmDialogueCallback * callback_);
	virtual void OnDraw();
	virtual ~ConfirmPrompt();
	ConfirmDialogueCallback * callback;
};

class ConfirmDialogueCallback
{
	public:
		virtual void ConfirmCallback(ConfirmPrompt::DialogueResult result) {}
		virtual ~ConfirmDialogueCallback() {}
};

#endif /* CONFIRMPROMPT_H_ */
