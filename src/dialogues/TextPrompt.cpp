/*
 * ConfirmPrompt.cpp
 *
 *  Created on: Apr 6, 2012
 *      Author: Simon
 */

#include "TextPrompt.h"
#include "interface/Label.h"
#include "interface/Button.h"
#include "Style.h"

class CloseAction: public ui::ButtonAction
{
public:
	TextPrompt * prompt;
	TextPrompt::DialogueResult result;
	CloseAction(TextPrompt * prompt_, TextPrompt::DialogueResult result_) { prompt = prompt_; result = result_; }
	void ActionCallback(ui::Button * sender)
	{
		ui::Engine::Ref().CloseWindow();
		if(prompt->callback)
			prompt->callback->TextCallback(result, prompt->textField->GetText());
		prompt->SelfDestruct(); //TODO: Fix component disposal
	}
};

TextPrompt::TextPrompt(std::string title, std::string message, bool multiline, TextDialogueCallback * callback_):
	ui::Window(ui::Point(-1, -1), ui::Point(200, 80)),
	callback(callback_)
{
	ui::Label * titleLabel = new ui::Label(ui::Point(4, 5), ui::Point(Size.X-8, 18), title);
	titleLabel->SetTextColour(style::Colour::WarningTitle);
	titleLabel->Appearance.HorizontalAlign = ui::Appearance::AlignLeft;
	titleLabel->Appearance.VerticalAlign = ui::Appearance::AlignMiddle;
	AddComponent(titleLabel);

	ui::Label * messageLabel = new ui::Label(ui::Point(4, 25), ui::Point(Size.X-8, 16), message);
	messageLabel->Appearance.HorizontalAlign = ui::Appearance::AlignLeft;	messageLabel->Appearance.VerticalAlign = ui::Appearance::AlignTop;
	AddComponent(messageLabel);

	textField = new ui::Textbox(ui::Point(4, 45 ), ui::Point(Size.X-8, 16), "", "Reason");
	if(multiline)
	{
		textField->SetMultiline(true);
		textField->Size.Y = 60;
		Size.Y += 45;
		textField->Appearance.VerticalAlign = ui::Appearance::AlignTop;
	}
	else
	{
		textField->Appearance.VerticalAlign = ui::Appearance::AlignMiddle;
	}
	textField->Appearance.HorizontalAlign = ui::Appearance::AlignLeft;
	AddComponent(textField);

	ui::Button * cancelButton = new ui::Button(ui::Point(0, Size.Y-16), ui::Point((Size.X/2)+1, 16), "Cancel");
	cancelButton->Appearance.HorizontalAlign = ui::Appearance::AlignLeft;
	cancelButton->Appearance.VerticalAlign = ui::Appearance::AlignMiddle;
	cancelButton->Appearance.BorderInactive = ui::Colour(200, 200, 200);
	cancelButton->SetActionCallback(new CloseAction(this, ResultCancel));
	AddComponent(cancelButton);
	SetCancelButton(cancelButton);

	ui::Button * okayButton = new ui::Button(ui::Point(Size.X/2, Size.Y-16), ui::Point(Size.X/2, 16), "Okay");
	okayButton->Appearance.HorizontalAlign = ui::Appearance::AlignRight;
	okayButton->Appearance.VerticalAlign = ui::Appearance::AlignMiddle;
	okayButton->Appearance.TextInactive = style::Colour::WarningTitle;
	okayButton->SetActionCallback(new CloseAction(this, ResultOkay));
	AddComponent(okayButton);
	SetOkayButton(okayButton);

	ui::Engine::Ref().ShowWindow(this);
}

void TextPrompt::OnDraw()
{
	Graphics * g = ui::Engine::Ref().g;

	g->clearrect(Position.X-2, Position.Y-2, Size.X+4, Size.Y+4);
	g->drawrect(Position.X, Position.Y, Size.X, Size.Y, 200, 200, 200, 255);
}

TextPrompt::~TextPrompt() {
	if(callback)
		delete callback;
}

