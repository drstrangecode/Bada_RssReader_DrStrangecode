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

result ItemForm::OnTerminating(void) {
	return E_SUCCESS;
}

void ItemForm::OnUserEventReceivedN(RequestId requestId,
		Osp::Base::Collection::IList * pArgs) {
	switch (requestId) {
	}

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

void ItemForm::SendPostByEmail() {
/*
	String emailSubject;
	String emailBody;

	emailSubject.Append(L"subject:");
	emailSubject.Append(pFeedItem->title);
	emailSubject.Append(L" - Another cool post on Dr. Strangecode blog!");

	emailBody.Append(L"text:");
	emailBody.Append(L"This is a snippet preview.\n");
	emailBody.Append(L"To view the full post click on <a href=\"");
	emailBody.Append(pFeedItem->link);
	emailBody.Append(L"\">this link</a>\n\n--\n");
	emailBody.Append(pFeedItem->description);
	emailBody.Append(L"\n--\n\n");

	 ArrayList* pDataList = null;
	 pDataList = new ArrayList();
	 pDataList->Construct();

	 pDataList->Add(emailSubject);
	 pDataList->Add(emailBody);

	 AppControl* pAc = AppManager::FindAppControlN(APPCONTROL_PROVIDER_EMAIL, APPCONTROL_OPERATION_COMPOSE);
	 pAc->Start(pDataList, null);
	 delete pAc;

	 pDataList->RemoveAll(false);
	 delete pDataList;
*/
	 ArrayList* pDataList = null;
	   pDataList = new ArrayList();
	   pDataList->Construct();

	   String* pData = null;
	   pData = new String(L"subject:Greetings");
	   pDataList->Add(*pData);

	   String* pData2 = null;
	   pData2 = new String(L"text:Hi, how are you?");
	   pDataList->Add(*pData2);

	   String* pData3 = null;
	   pData3 = new String(L"to:name@company.com");
	   pDataList->Add(*pData3);

	   String* pData4 = null;
	   pData4 = new String(L"cc:name2@company.com");
	   pDataList->Add(*pData4);

	   String* pData5 = null;
	   pData5 = new String(L"bcc:");
	   pDataList->Add(*pData5);

	   String* pData6 = null;
	   pData6 = new String(L"attachments:/Res/bada.jpg");
	   pDataList->Add(*pData6);

	   AppControl* pAc = AppManager::FindAppControlN(APPCONTROL_PROVIDER_EMAIL, APPCONTROL_OPERATION_COMPOSE);
	   if(pAc)
	   {
	      pAc->Start(pDataList, null);
	      delete pAc;
	   }
	   pDataList->RemoveAll(true);
	   delete pDataList;

}
