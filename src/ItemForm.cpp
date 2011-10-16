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

#include "Settings.h"

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

void ItemForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId) {
	switch (actionId) {
	case ItemForm::ACTION_ID_OPEN_WEB: {
		OpenPostInDefaultBrowser();
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
/*
    pFrame->SetCurrentForm(*pForm);
    pForm->Draw();
    pForm->Show();
*/

	FrameAnimator * pAnimator = pFrame->GetFrameAnimator();
	pAnimator->SetFormTransitionAnimation(FRAME_ANIMATOR_FORM_TRANSITION_ANIMATION_TRANSLATE_RIGHT,
			                              800,
			                              ANIMATION_INTERPOLATOR_EASE_IN_OUT);

	pAnimator->SetCurrentForm(*pForm);

}

void ItemForm::OpenPostInDefaultBrowser() {

	String url;
	url.Append(L"url:");
	url.Append(pFeedItem->link);

	ArrayList* pDataList = null;
	pDataList = new ArrayList();
	pDataList->Construct();
	pDataList->Add(url);

	AppControl* pAc = AppManager::FindAppControlN(APPCONTROL_PROVIDER_BROWSER, APPCONTROL_OPERATION_VIEW);
	pAc->Start(pDataList, null);
	delete pAc;

	pDataList->RemoveAll(false);
	delete pDataList;

}
