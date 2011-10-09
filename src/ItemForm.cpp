/*
 * ItemForm.cpp
 *
 * Created by: Dr. Strangecode
 * ---------------------------------------------
 * This is free code, it can be used, modified,
 * destroyed, raped and whatever without limits.
 * I own no copyrights over it.
 * This code is provided AS IS without warranty
 * of any kind either expressed or implied,
 * including but not limited to the implied
 * warranties of merchantability and/or fitness
 * for a particular purpose.
 * ---------------------------------------------
 * For more free code visit http://drstrangecode.org
 */

#include "DrStrangecodeRssReader.h"

#include "MainForm.h"
#include "ItemForm.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Base::Utility;
using namespace Osp::Base::Collection;
using namespace Osp::Ui;
using namespace Osp::Ui::Animations;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;
using namespace Osp::Media;
using namespace Osp::Web::Controls;

ItemForm::ItemForm(void) {

}

ItemForm::~ItemForm(void) {

}

void ItemForm::SetFeedItem(FeedItem * feedItem) {
	AppAssertf(feedItem != null, "feedItem is null");
	pFeedItem = feedItem;
	//GetHeader()->SetTitleText(pFeedItem->title);

	String title = pFeedItem->title;
	String authorAndDate;
	authorAndDate.Append(L"Posted on ");
	authorAndDate.Append(pFeedItem->pubDate);
	authorAndDate.Append(L" by ");
	authorAndDate.Append(pFeedItem->creator);

	String snippet = pFeedItem->description;
	snippet.Append(L"... (Touch 'Show Post' to view the entire article)");
	pTitleLabel->SetText(title);
	pDateAuthorLabel->SetText(authorAndDate);
	pSnippetLabel->SetText(snippet);

}

bool ItemForm::Initialize() {
	Construct(L"IDF_ITEMFORM");

	return true;
}

result ItemForm::OnInitializing(void) {
	result r = E_SUCCESS;

	Footer * pFooter = GetFooter();
	pFooter->AddActionEventListener(*this);

	SetFormBackEventListener(this);

	// Create a ContextMenu
	pContextMenu = new ContextMenu();
	pContextMenu->Construct(Point(0, 0), CONTEXT_MENU_STYLE_LIST);

	pContextMenu->AddItem(L"Twitter", CONTEXTMENU_ACTION_TWITTER);
	pContextMenu->AddItem(L"E-mail", CONTEXTMENU_ACTION_EMAIL);
	pContextMenu->AddActionEventListener(*this);

	pTitleLabel = static_cast<Label *>(GetControl(L"IDC_LABEL_TITLE"));
	pDateAuthorLabel = static_cast<Label *>(GetControl(L"IDC_LABEL_AUTHOR_DATE"));
	pSnippetLabel = static_cast<Label *>(GetControl(L"IDC_LABEL_SNIPPET"));

	return r;
}

result ItemForm::OnDraw(void) {
	result r = E_SUCCESS;

	Canvas* pCanvas = GetCanvasN();
	Rectangle rt = pCanvas->GetBounds();

	Application * app = Application::GetInstance();
	AppResource * res = app->GetAppResource();
	Bitmap * pBitmap = res->GetBitmapN(L"form_bg.png", BITMAP_PIXEL_FORMAT_ARGB8888);
	pCanvas->DrawBitmap(rt, *pBitmap);
	delete pBitmap;
	delete pCanvas;

	return r;

}

result ItemForm::OnTerminating(void) {
	result r = E_SUCCESS;
	delete pContextMenu;
	return r;
}

void ItemForm::OnUserEventReceivedN(RequestId requestId,
		Osp::Base::Collection::IList * pArgs) {
	switch (requestId) {
	}

}

void ItemForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId) {
	switch (actionId) {
	case ItemForm::ACTION_ID_SHARE: {
		pContextMenu->SetPosition(50, GetClientAreaBounds().y + GetClientAreaBounds().height);
		pContextMenu->SetShowState(true);
		pContextMenu->Show();

	}
		break;
	case ItemForm::ACTION_ID_OPEN_WEB: {
	}
		break;
	case ItemForm::CONTEXTMENU_ACTION_TWITTER: {
		MessageBox messageBox;
		messageBox.Construct(L"Coming Soon", L"Not yet implemented", MSGBOX_STYLE_OK);
		int modalResult = 0;
		messageBox.ShowAndWait(modalResult);
	}
		break;
	case ItemForm::CONTEXTMENU_ACTION_EMAIL: {
		MessageBox messageBox;
		messageBox.Construct(L"Coming Soon", L"Not yet implemented", MSGBOX_STYLE_OK);
		int modalResult = 0;
		messageBox.ShowAndWait(modalResult);
	}
		break;
	default:
		break;
	}
}

void ItemForm::OnFormBackRequested(Osp::Ui::Controls::Form & source) {
	AppLog("OnFormBackRequested()");
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

	MainForm * pForm = static_cast<MainForm*> (pFrame->GetControl(kMainFormNameString));
	FrameAnimator * pAnimator = pFrame->GetFrameAnimator();
	pAnimator->SetFormTransitionAnimation(FRAME_ANIMATOR_FORM_TRANSITION_ANIMATION_TRANSLATE_RIGHT,
			                              800,
			                              ANIMATION_INTERPOLATOR_EASE_IN_OUT);

	pAnimator->SetCurrentForm(*pForm);
}

