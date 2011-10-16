/*
 * MainForm.cpp
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

#include "MainForm.h"
#include "ItemForm.h"
#include "ListItems/FeedsListItem.h"

#include "DrStrangecodeRssReader.h"
#include "Settings.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Ui;
using namespace Osp::Ui::Animations;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;
using namespace Osp::Media;
using namespace Osp::Io;

MainForm::MainForm(void) {
    pFeedsList = null;
    pRequestThread = null;
}

MainForm::~MainForm(void) {
    if (pFeedsList != null) {
    	pFeedsList->RemoveAll(true);
    	delete pFeedsList;
    }

    delete pRequestThread;
}

bool MainForm::Initialize() {
    Construct(L"IDF_MAINFORM");
    return true;
}

result MainForm::OnInitializing(void) {

    Footer * pFooter = GetFooter();
    pFooter->AddActionEventListener(*this);

    pListView = static_cast<ListView *> (GetControl("IDC_LISTVIEW1"));
    pListView->SetItemProvider(*this);
    pListView->AddListViewItemEventListener(*this);
    pListView->SetTextOfEmptyList(L"Updating...");

    UpdateFeed();

    return E_SUCCESS;
}

result MainForm::OnDraw(void) {
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

result MainForm::OnTerminating(void) {
    result r = E_SUCCESS;

    return r;
}

void MainForm::OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList * pArgs) {

	pRequestThread->Join();
	delete pRequestThread;
	pRequestThread = null;

	String messageBoxTitle;
	String messageBoxText;

    switch (requestId) {
        case FeedRequestThread::USER_EVENT_DATA_AVAILABLE: {
        	messageBoxTitle.Append(L"Completed");
        	messageBoxText.Append(L"RSS feed has been updated.");
        }
        break;
        case FeedRequestThread::USER_EVENT_TRANSACTION_ABORTED: {
        	messageBoxTitle.Append(L"Error");
        	messageBoxText.Append(L"Could not update the RSS feed.\n");
        	messageBoxText.Append(L"Please check your internet connection.");

        	pListView->SetTextOfEmptyList(L"Cannot update feed");
        	pListView->RequestRedraw();
        }
        break;
    }

    MessageBox messageBox;
    messageBox.Construct(messageBoxTitle, messageBoxText, MSGBOX_STYLE_OK);

    int modalResult = 0;
    messageBox.ShowAndWait(modalResult);

    /* Check if the xml feed local file is present */
    if (File::IsFileExist(kMainFeedLocalFilePath)) {
    	/* Parse the feed file */
    	ParseFeed();
    }
}

void MainForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId) {
    switch (actionId) {
        case MainForm::ACTION_ID_REFRESH: {
        	if (pFeedsList != null) {
        		pFeedsList->RemoveAll(true);
        		pListView->UpdateList();
        		pListView->SetTextOfEmptyList(L"Updating...");
        		pListView->RequestRedraw();
        	}

            UpdateFeed();
        }
        break;
        default:
        break;
    }
}

void MainForm::UpdateFeed() {

    /* Start thread */
    String feedUrl = kFeedUrl;
    String fileDownloadPath = kMainFeedLocalFilePath;

    if (pRequestThread != null) {
    	if (pRequestThread->IsRunning()) {
    		MessageBox messageBox;
    		messageBox.Construct(L"Warning", L"Already updating, please wait...", MSGBOX_STYLE_OK);

    		int modalResult = 0;
    		messageBox.ShowAndWait(modalResult);
    		return;
    	}
    }
    pRequestThread = new FeedRequestThread();
    pRequestThread->Construct(this);
    pRequestThread->DownloadFeed(feedUrl, fileDownloadPath);

}

void MainForm::ParseFeed() {

    if (pFeedsList != null) {
    	pFeedsList->RemoveAll(true);
        delete pFeedsList;
        pFeedsList = null;
    }

    String filePath = String(kMainFeedLocalFilePath);
    FeedParser feedParser;
    feedParser.Construct(filePath);
    pFeedsList = feedParser.ParseFeedN();

    pListView->UpdateList();
    pListView->RequestRedraw();
}

Osp::Ui::Controls::ListItemBase * MainForm::CreateItem(int index, int itemWidth) {

    FeedItem *feedItem = static_cast<FeedItem *> (pFeedsList->GetAt(index));

    String title = feedItem->title;
    String categories = L"Categories:";
    String comments;
    String about;

    for (int i = 0; i < feedItem->categories.GetCount(); i++) {
        categories.Append(L" - ");
        categories.Append(*(static_cast<String *> (feedItem->categories.GetAt(i))));
    }

    comments.Format(50, L"- %d comments", feedItem->commentsCount.ToInt());

    about.Append(feedItem->pubDate);
    about.Append(L" by ");
    about.Append(feedItem->creator);
    about.Append(L"\n");
    about.Append(comments);
    about.Append(L"\n");

    FeedsListItem * pItem = new FeedsListItem();
    pItem->Construct(itemWidth, title, categories, about);

    return pItem;

}

bool MainForm::DeleteItem(int index, Osp::Ui::Controls::ListItemBase *pItem, int itemWidth) {
    return false;
}

int MainForm::GetItemCount(void) {
    if (pFeedsList == null)
        return 0;

    return pFeedsList->GetCount();
}

void MainForm::OnListViewContextItemStateChanged (Osp::Ui::Controls::ListView &listView,
                                                  int index, int elementId,
                                                  Osp::Ui::Controls::ListContextItemStatus status) {
    /* Nothing to do */
}

void MainForm::OnListViewItemStateChanged (Osp::Ui::Controls::ListView &listView,
                                           int index, int elementId,
                                           Osp::Ui::Controls::ListItemStatus status) {

	FeedItem * touchedItem = static_cast<FeedItem *>(pFeedsList->GetAt(index));

    Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
    ItemForm * pForm = static_cast<ItemForm*>(pFrame->GetControl(kItemFormNameString));
    pForm->SetFeedItem(touchedItem);
/*
    pFrame->SetCurrentForm(*pForm);
    pForm->Draw();
    pForm->Show();
*/
    FrameAnimator * pAnimator = pFrame->GetFrameAnimator();
    pAnimator->SetFormTransitionAnimation(FRAME_ANIMATOR_FORM_TRANSITION_ANIMATION_TRANSLATE_LEFT, 800, ANIMATION_INTERPOLATOR_EASE_IN_OUT);
    pAnimator->SetCurrentForm(*pForm);


}

void MainForm::OnListViewItemSwept (Osp::Ui::Controls::ListView &listView,
                                    int index,
                                    Osp::Ui::Controls::SweepDirection direction) {
	/* Nothing to do */
}
