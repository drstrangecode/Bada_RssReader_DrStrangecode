/*
 * MainForm.h
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

#ifndef _MAINFORM_H_
#define _MAINFORM_H_

#include <FBase.h>
#include <FGraphics.h>
#include <FUi.h>
#include <FUiAnimFrameAnimator.h>
#include <FMedia.h>
#include <FApp.h>
#include <FIo.h>

#include "XmlParser/FeedParser.h"
#include "Content/FeedItem.h"
#include "Http/FeedRequestThread.h"

class MainForm : public Osp::Ui::Controls::Form,
        public Osp::Ui::IActionEventListener,
        public Osp::Ui::Controls::IListViewItemProvider,
        public Osp::Ui::Controls::IListViewItemEventListener {

        // Construction
    public:

        MainForm(void);
        virtual ~MainForm(void);
        bool Initialize(void);
        virtual result OnDraw(void);

        virtual result OnInitializing(void);
        virtual result OnTerminating(void);
        virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
        virtual void OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList * pArgs);

        void UpdateFeed();

        /* IListViewItemProvider */
        virtual Osp::Ui::Controls::ListItemBase * CreateItem(int index, int itemWidth);
        virtual bool DeleteItem(int index, Osp::Ui::Controls::ListItemBase *pItem, int itemWidth);
        virtual int GetItemCount(void);

        /* IListViewItemEventListener */
        virtual void OnListViewContextItemStateChanged (Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListContextItemStatus status);
        virtual void OnListViewItemStateChanged (Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListItemStatus status);
        virtual void OnListViewItemSwept (Osp::Ui::Controls::ListView &listView, int index, Osp::Ui::Controls::SweepDirection direction);

    private:

        void ParseFeed();

        static const int ACTION_ID_REFRESH = 101;

        Osp::Ui::Controls::ListView * pListView;
        Osp::Base::Collection::ArrayList * pFeedsList;

        FeedRequestThread * pRequestThread;
};

#endif	//_MAINFORM_H_
