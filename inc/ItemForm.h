/*
 * ItemForm.h
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

#ifndef _ItemForm_H_
#define _ItemForm_H_

#include <FBase.h>
#include <FGraphics.h>
#include <FUi.h>
#include <FMedia.h>
#include <FApp.h>
#include <FWeb.h>

#include "XmlParser/FeedParser.h"
#include "Content/FeedItem.h"
#include "Http/FeedRequestThread.h"

class ItemForm : public Osp::Ui::Controls::Form,
        public Osp::Ui::IActionEventListener,
        public Osp::Ui::Controls::IFormBackEventListener {

        // Construction
    public:
        ItemForm(void);
        virtual ~ItemForm(void);
        bool Initialize(void);
        virtual result OnDraw(void);

        virtual result OnInitializing(void);
        virtual result OnTerminating(void);
        virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
        virtual void OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList * pArgs);

        /* IFormBackEventListener */
        virtual void OnFormBackRequested(Osp::Ui::Controls::Form & source);

        void SetFeedItem(FeedItem * feedItem);

    private:

        FeedItem *pFeedItem;

        static const int ACTION_ID_OPEN_WEB = 102;

        Osp::Ui::Controls::Label * pTitleLabel;
        Osp::Ui::Controls::Label * pDateAuthorLabel;
        Osp::Ui::Controls::Label * pSnippetLabel;

        void OpenPostInDefaultBrowser();
        void SendPostByEmail();

};

#endif	//_ItemForm_H_
